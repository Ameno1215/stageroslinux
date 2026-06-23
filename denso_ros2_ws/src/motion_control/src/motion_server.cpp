#include "motion_control/motion_server.hpp"

#include <cmath>


namespace motion_control
{

    MotionServer::MotionServer(const rclcpp::NodeOptions& options)
    : rclcpp::Node("motion_server", options)
    {
        // Declare parameters for convenient launch-time configuration
        this->declare_parameter<std::string>("model", "vs060");
        this->declare_parameter<std::string>("planning_group", "arm");
        this->declare_parameter<double>("velocity_scale", 1.0);
        this->declare_parameter<double>("accel_scale", 1.0);
        this->declare_parameter<std::string>("ik_solver", "pick_ik");
        this->declare_parameter<std::string>("ik_solver_plugin", "pick_ik/PickIkPlugin");
        this->declare_parameter<std::string>("solver", "pick_ik");
        this->declare_parameter<std::string>("solver_plugin", "pick_ik/PickIkPlugin");
        this->declare_parameter<std::string>("kinematics_solver", "pick_ik/PickIkPlugin");
        this->declare_parameter<bool>("use_health_monitor", true);
        this->declare_parameter<bool>("require_drives_powered", false);
        this->declare_parameter<std::string>("robot_status_topic", "/robot_status");
        // Keep explicit declarations for nested keys queried by external clients.
        this->declare_parameter<std::string>(
            "robot_description_kinematics.arm.kinematics_solver",
            "pick_ik/PickIkPlugin");
        this->declare_parameter<std::string>(
            "robot_description_kinematics.manipulator.kinematics_solver",
            "kdl_kinematics_plugin/KDLKinematicsPlugin");
        // this->set_parameter(rclcpp::Parameter("use_sim_time", true));

        // Initialisation du système d'écoute TF
        tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
        rclcpp::QoS qos(10);
        qos.transient_local();
        visual_marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("motion_server_markers", qos);

        // Separate node + action client for the Pilz MoveGroupSequence action.
        seq_node_ = std::make_shared<rclcpp::Node>("motion_server_seq_client");
        seq_client_ = rclcpp_action::create_client<moveit_msgs::action::MoveGroupSequence>(
            seq_node_, "/sequence_move_group");

        srv_init_ = this->create_service<srv::InitRobot>(
            "init_robot",
            std::bind(&MotionServer::onInitRobot, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_joints_ = this->create_service<srv::MoveJoints>(
            "move_joints",
            std::bind(&MotionServer::onMoveJoints, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_pose_ = this->create_service<srv::MoveToPose>(
            "move_to_pose",
            std::bind(&MotionServer::onMoveToPose, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_pose_via_joint_ = this->create_service<srv::MoveToPose>(
            "move_to_pose_via_joint",
            std::bind(&MotionServer::onMoveToPoseViaJoint, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_waypoints_ = this->create_service<srv::MoveWaypoints>(
            "move_waypoints",
            std::bind(&MotionServer::onMoveWaypoints, this, std::placeholders::_1, std::placeholders::_2));

        srv_scaling_ = this->create_service<srv::SetScaling>(
            "set_scaling",
            std::bind(&MotionServer::onSetScaling, this, std::placeholders::_1, std::placeholders::_2));

        srv_get_scaling_ = this->create_service<srv::GetScaling>(
            "get_scaling",
            std::bind(&MotionServer::onGetScaling, this, std::placeholders::_1, std::placeholders::_2));

        srv_get_joints_ = this->create_service<srv::GetJointState>(
            "get_joint_state",
            std::bind(&MotionServer::onGetJointState, this, std::placeholders::_1, std::placeholders::_2));

        srv_get_pose_ = this->create_service<srv::GetCurrentPose>(
            "get_current_pose",
            std::bind(&MotionServer::onGetCurrentPose, this, std::placeholders::_1, std::placeholders::_2));

        srv_virtual_cage_ = this->create_service<srv::SetVirtualCage>(
            "set_virtual_cage",
            std::bind(&MotionServer::onSetVirtualCage, this, std::placeholders::_1, std::placeholders::_2));

        srv_manage_box_ = this->create_service<srv::ManageBox>(
            "manage_box",
            std::bind(&MotionServer::onManageBox, this, std::placeholders::_1, std::placeholders::_2));

        srv_manage_mesh_ = this->create_service<srv::ManageMesh>(
            "manage_mesh",
            std::bind(&MotionServer::onManageMesh, this, std::placeholders::_1, std::placeholders::_2));

        srv_clear_env_ = this->create_service<std_srvs::srv::Trigger>(
            "clear_environment",
            std::bind(&MotionServer::onClearEnvironment, this, std::placeholders::_1, std::placeholders::_2));

        // --- Continuous TCP path tracing ---
        // Dedicated callback group: on the MultiThreadedExecutor this lets the sampling
        // timer (and the trace services) run while a blocking motion callback is busy in
        // the default group, so the trace keeps growing DURING a movement.
        trace_cb_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

        srv_set_trace_ = this->create_service<std_srvs::srv::SetBool>(
            "set_tcp_trace",
            std::bind(&MotionServer::onSetTcpTrace, this, std::placeholders::_1, std::placeholders::_2),
            rmw_qos_profile_services_default, trace_cb_group_);

        srv_clear_trace_ = this->create_service<std_srvs::srv::Trigger>(
            "clear_tcp_trace",
            std::bind(&MotionServer::onClearTcpTrace, this, std::placeholders::_1, std::placeholders::_2),
            rmw_qos_profile_services_default, trace_cb_group_);

        // Runs on the non-blocking trace group so the bridge can flag motor-off intent even
        // if a motion is holding mtx_; the handler only does an atomic store on the monitor.
        srv_set_drives_expected_ = this->create_service<std_srvs::srv::SetBool>(
            "set_drives_expected",
            std::bind(&MotionServer::onSetDrivesExpected, this, std::placeholders::_1, std::placeholders::_2),
            rmw_qos_profile_services_default, trace_cb_group_);

        // 30 Hz sampler; it early-returns when tracing is disabled, so it is cheap when idle.
        trace_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(33),
            std::bind(&MotionServer::sampleTcpTrace, this),
            trace_cb_group_);

        RCLCPP_INFO(this->get_logger(), "MotionServer ready. Call /init_robot first");
    }

    bool MotionServer::ensureMoveGroupInitialized(std::string& why) const {
        if (!initialized_ || !move_group_) {
            why = "Robot not initialized. Call /init_robot first";
            return false;
        }
        return true;
    }

    bool MotionServer::getRobotFaultMessage(std::string& why) const {
        if (health_monitor_ && health_monitor_->hasError()) {
            why = "[ROBOT FAULT] " + health_monitor_->getErrorMessage()
                + " | Clear the robot fault, then call /init_robot again";
            return true;
        }
        return false;
    }
    
    bool MotionServer::ensureInitialized(std::string& why) const {
        if (!initialized_ || !move_group_) {
            why = "Robot not initialized. Call /init_robot first";
            return false;
        }
        if (getRobotFaultMessage(why)) {
            return false;
        }
        return true;
    }

    void MotionServer::onInitRobot(
        const std::shared_ptr<srv::InitRobot::Request> req,
        std::shared_ptr<srv::InitRobot::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        // get param from launch file
        auto model = this->get_parameter("model").as_string();
        auto group = this->get_parameter("planning_group").as_string();
        auto ik_solver = this->get_parameter("ik_solver").as_string();
        auto ik_solver_plugin = this->get_parameter("ik_solver_plugin").as_string();
        // Compatibility with clients that still use legacy "solver*" parameter names.
        if (ik_solver.empty()) {
            ik_solver = this->get_parameter("solver").as_string();
        }
        if (ik_solver_plugin.empty()) {
            ik_solver_plugin = this->get_parameter("solver_plugin").as_string();
        }

        double v = req->velocity_scale > 0.0 ? req->velocity_scale : this->get_parameter("velocity_scale").as_double();
        double a = req->accel_scale > 0.0 ? req->accel_scale : this->get_parameter("accel_scale").as_double();

        model_ = model;
        planning_group_ = group;
        vel_scale_ = std::min(std::max(v, 0.0), 1.0);
        accel_scale_ = std::min(std::max(a, 0.0), 1.0);

        try {
            // Create MoveIt interfaces
            move_group_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(
                shared_from_this(), planning_group_);
            planning_scene_ = std::make_shared<moveit::planning_interface::PlanningSceneInterface>();

            planning_frame_ = move_group_->getPlanningFrame();
            RCLCPP_INFO(this->get_logger(), "Using planning frame: %s", planning_frame_.c_str());

            // Cache the end-effector link for the TCP-trace timer (avoids touching the
            // non thread-safe MoveGroupInterface from the timer's callback group).
            {
                std::lock_guard<std::mutex> tlk(trace_mtx_);
                ee_link_ = move_group_->getEndEffectorLink();
            }

            // Resting pipeline = OMPL for all joint-space planning. Cartesian moves
            // temporarily switch to Pilz LIN (planCartesianLin) and restore OMPL.
            move_group_->setPlanningPipelineId("ompl");

            const bool use_health_monitor = this->get_parameter("use_health_monitor").as_bool();
            const bool require_drives_powered = this->get_parameter("require_drives_powered").as_bool();
            const auto robot_status_topic = this->get_parameter("robot_status_topic").as_string();

            if (use_health_monitor && !health_monitor_) {
                health_monitor_ = std::make_unique<RobotHealthMonitor>(
                    this, model_, "/joint_states", require_drives_powered, robot_status_topic);

                health_monitor_->onError([this](const std::string& reason) {
                    RCLCPP_ERROR(this->get_logger(),
                        "[MotionServer] Halting MoveIt — hardware fault: %s", reason.c_str());
                    if (move_group_) move_group_->stop();
                });

                health_monitor_->onCleared([this]() {
                    RCLCPP_INFO(this->get_logger(),
                        "[MotionServer] Hardware fault cleared — call /init_robot to resume");
                });

                RCLCPP_INFO(this->get_logger(),
                    "Health monitor enabled for model '%s'", model_.c_str());
            } else if (!use_health_monitor) {
                RCLCPP_INFO(this->get_logger(),
                    "Health monitor disabled (use_health_monitor=false)");
            }

            // Activate only if it exists
            if (health_monitor_) {
                // Start with motors EXPECTED OFF. At init the drives are not powered yet
                // (the program energizes them later via set_servo_on), so "drives OFF" is the
                // normal idle state, not a fault. Setting this BEFORE activation closes the
                // startup race where a robot_status with drives OFF arrived before the bridge
                // could sync its intent — which produced a spurious "drives are OFF" fault.
                // A real drive drop during a commanded motion still latches (motors_on=true by then).
                health_monitor_->setDrivesExpectedOn(false);
                health_monitor_->setActive(true);
                health_monitor_->clearError();
            }

            // This gives us access to the full PlanningScene (collision world,
            // allowed collision matrix, robot state) needed by diagnostic helpers.
            psm_ = std::make_shared<planning_scene_monitor::PlanningSceneMonitor>(
            shared_from_this(), "robot_description");

            // Start listening to the planning scene topic published by move_group
            psm_->startSceneMonitor("/monitored_planning_scene");
            // Start listening to the robot's joint state for state updates
            psm_->startStateMonitor("/joint_states");
            // Wait briefly for the first scene to arrive
            if (!psm_->waitForCurrentRobotState(this->now(), 2.0)) {
                RCLCPP_WARN(this->get_logger(),
                    "PlanningSceneMonitor: timed out waiting for robot state. "
                    "Diagnostics may be incomplete on first call.");
            }

            move_group_->setMaxVelocityScalingFactor(vel_scale_);
            move_group_->setMaxAccelerationScalingFactor(accel_scale_);

            // Find best parameters for fast and reliable planning. These can be tuned based on the robot's performance and environment complexity.
            double p_time = req->planning_time > 0.0 ? req->planning_time : 5.0;
            int p_attempts = req->planning_attempts > 0 ? req->planning_attempts : 10;
            bool a_replan = req->allow_replanning;
            std::string planner_id = req->planner_id.empty() ? "PRMstar" : req->planner_id;

            move_group_->setPlanningTime(p_time); // Maximum time (in seconds) allowed for planning.
            move_group_->setNumPlanningAttempts(p_attempts);  //Number of attempts simultaneously launched by MoveIt to find a valid plan (with different random seeds).
            move_group_->allowReplanning(a_replan); // If true, MoveIt will automatically try to replan if the current plan fails during execution (e.g., due to a new obstacle).
            move_group_->setPlannerId(planner_id);

            // Log available joints and links
            auto names = move_group_->getRobotModel()->getLinkModelNames();
            RCLCPP_INFO(this->get_logger(), "--- Links available for this robot ---");
            for (const auto& name : names) {
                RCLCPP_INFO(this->get_logger(), "Link: %s", name.c_str());
            }

            std::ostringstream oss;
            oss << "Initialized with model=" << model_
                << ", group=" << planning_group_
                << ", ik_solver=" << ik_solver
                << ", ik_solver_plugin=" << ik_solver_plugin
                << ", vel_scale=" << vel_scale_
                << ", accel_scale=" << accel_scale_
                << ", plan_time=" << p_time
                << ", plan_attempts=" << p_attempts
                << ", replan=" << (a_replan ? "true" : "false")
                << ",planner_id=" << planner_id
                << ", planning_frame=" << move_group_->getPlanningFrame()
                << ", ee_link=" << move_group_->getEndEffectorLink();

            initialized_ = true;
            res->success = true;
            res->message = oss.str();
            RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());

            std::vector<double> jmin, jmax;
            std::vector<std::string> jnames;
            std::string msg;
            if (getJointLimits(jmin, jmax, &jnames, msg)) {
                RCLCPP_INFO(this->get_logger(), "%s", msg.c_str());
                // jmin.size() == jmax.size() == nb_joints (6 for VS060)
            } else {
                RCLCPP_ERROR(this->get_logger(), "Could not get joint limits: %s", msg.c_str());
            }
        } catch (const std::exception& e) {
            initialized_ = false;
            move_group_.reset();
            planning_scene_.reset();
            res->success = false;
            res->message = std::string("Init failed: ") + e.what();
            RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
        }
    }

    planning_scene::PlanningSceneConstPtr MotionServer::getLockedPlanningScene() const
    {
        if (!psm_) return nullptr;

        planning_scene_monitor::LockedPlanningSceneRO locked_scene(psm_);
        return planning_scene::PlanningScene::clone(
            locked_scene.operator->()->shared_from_this());
    }

    bool MotionServer::solveBestIK(
        const geometry_msgs::msg::Pose& target_pose,
        const moveit::core::RobotState& seed_state,
        std::vector<double>& best_joints,
        std::string& out_msg,
        std::vector<std::vector<double>>* all_branches)
    {
        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        if (!jmg) {
            out_msg = "Unknown planning group: " + planning_group_;
            return false;
        }

        // from the seed, NOT getCurrentState()
        std::vector<double> reference_joints;
        seed_state.copyJointGroupPositions(jmg, reference_joints);

        // Pre-fetch the data needed by each filter
        const auto& joint_models = jmg->getActiveJointModels();
        const auto& joint_var_names = jmg->getVariableNames();

        // User-defined joint constraints set via applyJointConstraints()
        auto path_constraints = move_group_->getPathConstraints();
        std::unordered_map<std::string, std::pair<double, double>> user_constraint_map;
        for (const auto& jc : path_constraints.joint_constraints) {
            const double cmin = jc.position - jc.tolerance_below;
            const double cmax = jc.position + jc.tolerance_above;
            user_constraint_map[jc.joint_name] = {cmin, cmax};
        }

        // Planning scene snapshot for collision checking (self + environment)
        auto scene = getLockedPlanningScene();
        if (!scene) {
            out_msg = "[IK] PlanningSceneMonitor unavailable — collision filtering disabled";
            RCLCPP_ERROR(this->get_logger(), "%s", out_msg.c_str());
            return false;
        }

        // Multi-seed IK search
        constexpr int    NUM_ATTEMPTS = 64;
        constexpr double IK_TIMEOUT   = 0.1;
        const std::vector<double> weights = {1.0, 2.0, 2.0, 4.0, 5.0, 4.0};

        std::vector<std::pair<double, std::vector<double>>> valid_solutions;
        valid_solutions.reserve(NUM_ATTEMPTS);

        int ik_failures = 0;
        int rejected_limits = 0;
        int rejected_constraints = 0;
        int rejected_collision = 0;

        auto candidate = std::make_shared<moveit::core::RobotState>(seed_state);

        for (int i = 0; i < NUM_ATTEMPTS; ++i)
        {
            if (i == 0) {
                *candidate = seed_state;
            } else {
                candidate->setToRandomPositions(jmg);
            }

            if (!candidate->setFromIK(jmg, target_pose, IK_TIMEOUT)) {
                ik_failures++;
                continue;
            }
            candidate->update();

            std::vector<double> candidate_joints;
            candidate->copyJointGroupPositions(jmg, candidate_joints);

            // Filter 1: URDF joint limits
            bool out_of_limits = false;
            for (size_t j = 0; j < joint_models.size(); ++j) {
                const auto& b = joint_models[j]->getVariableBounds()[0];
                if (b.position_bounded_ &&
                    (candidate_joints[j] < b.min_position_ ||
                    candidate_joints[j] > b.max_position_))
                {
                    out_of_limits = true;
                    break;
                }
            }
            if (out_of_limits) { rejected_limits++; continue; }

            // Filter 2: user-defined joint constraints
            bool violates_user_constraints = false;
            if (!user_constraint_map.empty()) {
                for (size_t j = 0; j < joint_var_names.size(); ++j) {
                    auto it = user_constraint_map.find(joint_var_names[j]);
                    if (it != user_constraint_map.end() &&
                        (candidate_joints[j] < it->second.first ||
                        candidate_joints[j] > it->second.second))
                    {
                        violates_user_constraints = true;
                        break;
                    }
                }
            }
            if (violates_user_constraints) { rejected_constraints++; continue; }

            // Filter 3: collision (self + environment)
            {
                std::vector<std::string> pairs, self_pairs, env_pairs;
                if (checkStateCollision(scene, *candidate, planning_group_,
                                        pairs, self_pairs, env_pairs))
                {
                    rejected_collision++;
                    continue;
                }
            }

            // Cost relative to the seed
            double cost = 0.0;
            for (std::size_t j = 0; j < candidate_joints.size(); ++j) {
                const double w = (j < weights.size()) ? weights[j] : 1.0;
                const double diff = candidate_joints[j] - reference_joints[j];
                cost += w * w * diff * diff;
            }

            valid_solutions.emplace_back(cost, std::move(candidate_joints));
        }

        if (valid_solutions.empty()) {
            const std::string breakdown =
                "IK fails=" + std::to_string(ik_failures)
                + ", limits=" + std::to_string(rejected_limits)
                + ", constraints=" + std::to_string(rejected_constraints)
                + ", collision=" + std::to_string(rejected_collision);
            RCLCPP_WARN(this->get_logger(),
                "[IK] FAILED — 0/%d seeds valid, 0 branches | rejected: %s",
                NUM_ATTEMPTS, breakdown.c_str());

            out_msg = "IK failed: no valid solution found after "
                    + std::to_string(NUM_ATTEMPTS) + " attempts (" + breakdown + ")";
            return false;
        }

        // Deduplicate into distinct branches
        constexpr double BRANCH_TOLERANCE = 0.01;
        auto same_branch = [&](const std::vector<double>& a, const std::vector<double>& b) {
            for (size_t j = 0; j < a.size(); ++j) {
                if (std::abs(a[j] - b[j]) > BRANCH_TOLERANCE) return false;
            }
            return true;
        };

        std::vector<std::pair<double, std::vector<double>>> distinct_branches;
        for (const auto& sol : valid_solutions) {
            bool is_duplicate = false;
            for (const auto& kept : distinct_branches) {
                if (same_branch(sol.second, kept.second)) {
                    is_duplicate = true;
                    break;
                }
            }
            if (!is_duplicate) {
                distinct_branches.push_back(sol);
            }
        }

        // Sort by ascending cost (cheapest = "closest to seed" first)
        std::sort(distinct_branches.begin(), distinct_branches.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

        RCLCPP_INFO(this->get_logger(),
            "[IK] %d/%d seeds valid — %zu distinct branches found | "
            "rejected: IK fails=%d, limits=%d, constraints=%d, collision=%d",
            static_cast<int>(valid_solutions.size()), NUM_ATTEMPTS,
            distinct_branches.size(),
            ik_failures, rejected_limits, rejected_constraints, rejected_collision);

        // Expose all branches if the caller wants them (e.g. demo mode)
        if (all_branches) {
            all_branches->clear();
            all_branches->reserve(distinct_branches.size());
            for (const auto& br : distinct_branches) {
                all_branches->push_back(br.second);
            }
        }

        // Return the best (lowest cost) branch
        const double best_cost = distinct_branches.front().first;
        best_joints = distinct_branches.front().second;

        RCLCPP_INFO(this->get_logger(),
            "[IK] Best branch selected (cost=%.4f)", best_cost);

        out_msg = "IK OK (cost=" + std::to_string(best_cost)
                + ", " + std::to_string(valid_solutions.size()) + "/"
                + std::to_string(NUM_ATTEMPTS) + " valid, "
                + std::to_string(distinct_branches.size()) + " branches)";
        return true;
    }

    bool MotionServer::solveIKAndPlanJoints(
        const geometry_msgs::msg::Pose& target_pose,
        bool execute,
        std::string& out_msg)
    {
        move_group_->setStartStateToCurrentState();
        moveit::core::RobotStatePtr current_state = move_group_->getCurrentState(2.0);
        if (!current_state) {
            out_msg = "Failed to obtain current robot state";
            return false;
        }

        std::vector<double> best_joints;
        std::vector<std::vector<double>> all_branches; // for debug mode
        std::string ik_msg;

        // Seed = current state of the robot (move_to_pose: we start from where the robot is)
        auto ik_t0 = std::chrono::high_resolution_clock::now();
        bool ik_ok = solveBestIK(target_pose, *current_state, best_joints, ik_msg, &all_branches);
        double ik_dt = std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - ik_t0).count();
        if (!ik_ok) {
            out_msg = ik_msg + " (solve took " + std::to_string(ik_dt) + "s)";

            // Rich diagnosis on the target pose (collision / reachability / singularity /
            // joint limits), same analyzer as the Pilz LIN path, so an IK-only failure is
            auto scene = getLockedPlanningScene();
            if (scene) {
                moveit::core::MoveItErrorCode ik_code;
                ik_code.val = moveit::core::MoveItErrorCode::NO_IK_SOLUTION;
                auto report = diagnosePlanningFailure(
                    ik_code, *move_group_, scene, planning_group_,
                    &target_pose, nullptr, ik_dt, this->get_logger());
                if (!report.summary.empty()) {
                    out_msg += " | " + report.summary;
                }
            }
            return false;
        }
        RCLCPP_INFO(this->get_logger(), "[IK] %s (solve took %.3fs)", ik_msg.c_str(), ik_dt);

        return planAndExecuteJoints(best_joints, false, execute, out_msg, ik_dt);

    #if 0  // DEMO MODE: visit each distinct branch sequentially
        // Set to `#if 1` to re-enable

        // Reference de retour = état courant au moment de l'appel
        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        std::vector<double> initial_joints;
        current_state->copyJointGroupPositions(jmg, initial_joints);

        std::ostringstream summary;
        summary << "IK demo executed " << all_branches.size() << " branch(es): ";

        int success_count = 0;
        int failure_count = 0;

        for (size_t b = 0; b < all_branches.size(); ++b) {
            const auto& joints = all_branches[b];

            // Log the branch values
            std::ostringstream js;
            js << std::fixed << std::setprecision(4) << "[";
            for (size_t j = 0; j < joints.size(); ++j) {
                if (j > 0) js << ", ";
                js << joints[j];
            }
            js << "]";

            RCLCPP_INFO(this->get_logger(),
                "[IK-DEMO] Branch %zu/%zu: %s",
                b + 1, all_branches.size(), js.str().c_str());

            if (!execute) {
                // Plan-only mode: just report each branch, don't move
                success_count++;
                summary << "[" << b + 1 << "]plan_ok ";
                continue;
            }

            // Step 1: go to the branch
            std::string branch_msg;
            bool ok = planAndExecuteJoints(joints, false, true, branch_msg);
            if (!ok) {
                RCLCPP_WARN(this->get_logger(),
                    "[IK-DEMO] Branch %zu execution failed: %s",
                    b + 1, branch_msg.c_str());
                failure_count++;
                summary << "[" << b + 1 << "]FAIL ";
                continue;
            }

            success_count++;
            summary << "[" << b + 1 << "]ok ";

            std::this_thread::sleep_for(std::chrono::milliseconds(1500));

            if (b + 1 < all_branches.size()) {
                std::string return_msg;
                bool back_ok = planAndExecuteJoints(initial_joints, false, true, return_msg);
                if (!back_ok) {
                    RCLCPP_ERROR(this->get_logger(),
                        "[IK-DEMO] Failed to return to initial state: %s — aborting demo",
                        return_msg.c_str());
                    summary << "(return failed, demo aborted)";
                    out_msg = summary.str();
                    return false;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
            }
        }

        out_msg = summary.str() + " | "
                + std::to_string(success_count) + " ok, "
                + std::to_string(failure_count) + " failed";

        RCLCPP_INFO(this->get_logger(), "[IK-DEMO] %s", out_msg.c_str());
        return success_count > 0;

    #endif
    }

    bool MotionServer::planAndMaybeExecutePose(
        const geometry_msgs::msg::PoseStamped& target,
        bool execute,
        std::string& out_msg)
    {
        move_group_->clearPoseTargets();

        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        auto start_time = std::chrono::high_resolution_clock::now();

        std::string ik_joint_msg;
        bool ok = solveIKAndPlanJoints(target.pose, execute, ik_joint_msg);

        auto end_time = std::chrono::high_resolution_clock::now();
        double total_duration = std::chrono::duration<double>(end_time - start_time).count();

        if (!ok) {
            out_msg = "IK+Joint planning failed: " + ik_joint_msg
                    + " (took " + std::to_string(total_duration) + "s)";
            return false;
        }

        if (execute) {
            out_msg = "IK+Joint planned and executed pose successfully: " + ik_joint_msg
                    + " (total=" + std::to_string(total_duration) + "s)";
        } else {
            out_msg = "IK+Joint planned pose successfully: " + ik_joint_msg
                    + " (execute=false, total=" + std::to_string(total_duration) + "s)";
        }

        return true;
    }

    void MotionServer::onSetScaling(
        const std::shared_ptr<srv::SetScaling::Request> req,
        std::shared_ptr<srv::SetScaling::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        // Clamp to [0, 1]
        const double v = std::min(std::max(req->velocity_scale, 0.0), 1.0);
        const double a = std::min(std::max(req->accel_scale, 0.0), 1.0);

        vel_scale_ = v;
        accel_scale_ = a;

        // If MoveGroupInterface is already initialized, apply immediately
        if (move_group_) {
            move_group_->setMaxVelocityScalingFactor(vel_scale_);
            move_group_->setMaxAccelerationScalingFactor(accel_scale_);
        }

        std::ostringstream oss;
        oss << "Scaling updated: velocity_scale=" << vel_scale_
            << ", accel_scale=" << accel_scale_
            << ". This will be used for all subsequent motions";

        res->success = true;
        res->message = oss.str();

        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }

    void MotionServer::onGetScaling(
        const std::shared_ptr<srv::GetScaling::Request> /*req*/,
        std::shared_ptr<srv::GetScaling::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        res->velocity_scale = vel_scale_;
        res->accel_scale = accel_scale_;

        std::ostringstream oss;
        oss << "Received request to set scaling: velocity_scale=" << vel_scale_
            << ", accel_scale=" << accel_scale_;

        res->success = true;
        res->message = oss.str();

        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }

    std::optional<geometry_msgs::msg::PoseStamped> MotionServer::computeAbsoluteTarget(
        double x, double y, double z,
        double r1, double r2, double r3, double r4,
        const std::string& rot_format,
        const std::string& ref_frame,
        bool is_relative,
        std::string& out_error_msg)
    {
        geometry_msgs::msg::PoseStamped final_pose;
        final_pose.header.frame_id = planning_frame_;
        final_pose.header.stamp = this->now();

        // Prepare the target transformation (Delta or Absolute)
        tf2::Vector3 target_translation(x, y, z);
        tf2::Quaternion target_rotation;

        if (rot_format == "RPY") {
            target_rotation.setRPY(r1, r2, r3); // r1=Roll, r2=Pitch, r3=Yaw
        } else {
            target_rotation = tf2::Quaternion(r1, r2, r3, r4); // X, Y, Z, W
            target_rotation.normalize();
        }

        tf2::Transform target_transform(target_rotation, target_translation);

        // If it's absolute in the WORLD framework, we're done!
        if (!is_relative && ref_frame == "WORLD") {
            tf2::toMsg(target_transform, final_pose.pose);
            return final_pose;
        }

        const std::string ee_link = move_group_->getEndEffectorLink();
        geometry_msgs::msg::Pose current_pose;

        try {
            geometry_msgs::msg::PoseStamped cp = move_group_->getCurrentPose(ee_link);

            const auto& q = cp.pose.orientation;
            const double norm = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
            if (!std::isfinite(norm) || norm < 0.99 || norm > 1.01) {
                out_error_msg = "getCurrentPose() returned invalid quaternion (norm="
                              + std::to_string(norm) + ")";
                return std::nullopt;
            }

            current_pose = cp.pose;

            RCLCPP_INFO(this->get_logger(),
                "Current pose (MoveIt): pos(%.4f, %.4f, %.4f) quat(%.4f, %.4f, %.4f, %.4f)",
                current_pose.position.x, current_pose.position.y, current_pose.position.z,
                current_pose.orientation.x, current_pose.orientation.y,
                current_pose.orientation.z, current_pose.orientation.w);
        } catch (const std::exception& e) {
            out_error_msg = std::string("Failed to get current pose from MoveIt: ") + e.what();
            return std::nullopt;
        }

        tf2::Transform current_transform;
        tf2::fromMsg(current_pose, current_transform);

        tf2::Transform result_transform;

        if (is_relative && ref_frame == "TOOL") {
            result_transform = current_transform * target_transform;
        }
        else if (is_relative && ref_frame == "WORLD") {
            result_transform.setOrigin(current_transform.getOrigin() + target_translation);
            result_transform.setRotation(target_rotation * current_transform.getRotation());
        }
        else {
            out_error_msg = "Absolute combination + TOOL marker not supported. Please use WORLD reference for absolute poses";
            return std::nullopt;
        }

        tf2::toMsg(result_transform, final_pose.pose);
        return final_pose;
    }

    bool MotionServer::planCartesianLin(
        const geometry_msgs::msg::PoseStamped& target,
        double vel_scaling,
        moveit_msgs::msg::RobotTrajectory& trajectory,
        std::string& out_msg)
    {
        const double vscale = std::min(std::max(vel_scaling, 0.0), 1.0);

        move_group_->clearPoseTargets();
        move_group_->setPlanningPipelineId("pilz_industrial_motion_planner");
        move_group_->setPlannerId("LIN");
        move_group_->setMaxVelocityScalingFactor(vscale);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);
        move_group_->setStartStateToCurrentState();
        move_group_->setPoseTarget(target);

        moveit::planning_interface::MoveGroupInterface::Plan plan;
        auto plan_t0 = std::chrono::high_resolution_clock::now();
        auto code = move_group_->plan(plan);
        double plan_dt = std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - plan_t0).count();

        // ALWAYS restore the default OMPL pipeline so a following joint-space move
        // is not silently planned with Pilz (MoveGroupInterface is stateful).
        move_group_->setPlanningPipelineId("ompl");
        move_group_->setPlannerId("");

        if (code != moveit::core::MoveItErrorCode::SUCCESS) {
            out_msg = "Pilz LIN planning failed: " + moveitErrorCodeToString(code)
                    + " (took " + std::to_string(plan_dt) + "s)";

            // Full diagnosis on the LIN goal pose (collision / IK reachability / singularity
            // / joint limits / timeout) — same analyzer used for joint-space planning.
            auto scene = getLockedPlanningScene();
            if (scene) {
                auto report = diagnosePlanningFailure(
                    code, *move_group_, scene, planning_group_,
                    &target.pose, nullptr, plan_dt, this->get_logger());
                if (!report.summary.empty()) {
                    out_msg += " | " + report.summary;
                }
            }
            return false;
        }

        // Pilz emits one joint waypoint every sampling_time (0.1s, hardcoded in MoveIt).
        // Between them the controller interpolates in JOINT space, which cuts the corner of
        // the true Cartesian line — the faster the move, the larger that chordal deviation.
        // We densify the path along the (already validated) line: re-sample it finely, solve
        // seeded IK on each sub-point, and inherit Pilz's timing so the requested Cartesian
        // speed is preserved.
        //
        // Densification is MANDATORY (no fallback): the raw Pilz trajectory is not precise
        // enough, and its joint-interpolated path between the sparse nodes is not finely
        // collision-checked. If densification or the fine collision recheck fails, we refuse
        // the move rather than execute a coarse/unverified path.
        const size_t pilz_pts = plan.trajectory_.joint_trajectory.points.size();
        moveit_msgs::msg::RobotTrajectory dense = plan.trajectory_;
        std::string dmsg;
        if (!densifyCartesianTrajectory(dense, kDensifyMaxCartStep, kDensifyMaxAngStep, dmsg)) {
            out_msg = "Pilz LIN densification failed: " + dmsg
                    + " (likely a near-singular line where seeded IK can't follow) — move refused";
            RCLCPP_ERROR(this->get_logger(), "[LIN] %s", out_msg.c_str());
            return false;
        }

        std::string cmsg;
        if (!validateTrajectoryCollisionFree(dense, cmsg)) {
            out_msg = "Pilz LIN densified trajectory collides between waypoints: " + cmsg
                    + " — move refused";
            RCLCPP_ERROR(this->get_logger(), "[LIN] %s", out_msg.c_str());
            return false;
        }

        trajectory = dense;
        RCLCPP_INFO(this->get_logger(),
            "[LIN] densified %zu -> %zu points (%s)",
            pilz_pts, dense.joint_trajectory.points.size(), dmsg.c_str());
        out_msg = "Pilz LIN OK + densified (vel_scale=" + std::to_string(vscale)
                + ", " + std::to_string(dense.joint_trajectory.points.size()) + " pts)";
        return true;
    }

    bool MotionServer::densifyCartesianTrajectory(
        moveit_msgs::msg::RobotTrajectory& trajectory,
        double max_cart_step,
        double max_ang_step,
        std::string& out_msg)
    {
        const auto& jt = trajectory.joint_trajectory;
        const auto& pts = jt.points;
        if (pts.size() < 2) { out_msg = "fewer than 2 points to densify"; return false; }

        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        if (!jmg) { out_msg = "unknown planning group"; return false; }
        const std::string ee = move_group_->getEndEffectorLink();
        const auto& names = jt.joint_names;
        const size_t ndof = names.size();
        if (ndof == 0 || pts.front().positions.size() != ndof) {
            out_msg = "joint name / position size mismatch"; return false;
        }

        moveit::core::RobotState state(move_group_->getRobotModel());
        state.setToDefaultValues();

        auto set_state = [&](const std::vector<double>& j) {
            for (size_t k = 0; k < ndof; ++k) state.setVariablePosition(names[k], j[k]);
            state.update();
        };
        auto fk = [&](const std::vector<double>& j) -> Eigen::Isometry3d {
            set_state(j);
            return state.getGlobalLinkTransform(ee);
        };
        auto t_of = [](const trajectory_msgs::msg::JointTrajectoryPoint& p) {
            return p.time_from_start.sec + p.time_from_start.nanosec * 1e-9;
        };

        std::vector<std::vector<double>> dpos;
        std::vector<double> dtime;
        dpos.reserve(pts.size() * 16);
        dtime.reserve(pts.size() * 16);

        dpos.push_back(pts.front().positions);
        dtime.push_back(t_of(pts.front()));
        std::vector<double> seed = pts.front().positions;

        for (size_t i = 1; i < pts.size(); ++i) {
            const auto& ja = pts[i - 1].positions;
            const auto& jb = pts[i].positions;
            const Eigen::Isometry3d Ta = fk(ja);
            const Eigen::Isometry3d Tb = fk(jb);
            const Eigen::Vector3d pa = Ta.translation();
            const Eigen::Vector3d pb = Tb.translation();
            const Eigen::Quaterniond qa(Ta.rotation());
            const Eigen::Quaterniond qb(Tb.rotation());
            const double dpos_m = (pb - pa).norm();
            const double dang = std::abs(qa.angularDistance(qb));
            const double ta = t_of(pts[i - 1]);
            const double tb = t_of(pts[i]);

            size_t K = static_cast<size_t>(std::ceil(std::max(
                dpos_m / std::max(max_cart_step, 1e-6),
                dang   / std::max(max_ang_step, 1e-6))));
            K = std::min<size_t>(std::max<size_t>(K, 1), kDensifyMaxSubSteps);

            for (size_t k = 1; k < K; ++k) {
                const double a = static_cast<double>(k) / static_cast<double>(K);
                Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
                T.translation() = pa + a * (pb - pa);
                T.linear() = qa.slerp(a, qb).toRotationMatrix();

                set_state(seed);  // seed IK from the previous solution -> stays on the branch
                if (!state.setFromIK(jmg, T, kDensifyIkTimeout)) {
                    out_msg = "IK failed at segment " + std::to_string(i)
                            + " substep " + std::to_string(k);
                    return false;
                }
                std::vector<double> jk;
                state.copyJointGroupPositions(jmg, jk);

                double md = 0.0;
                for (size_t d = 0; d < ndof; ++d) md = std::max(md, std::abs(jk[d] - seed[d]));
                if (md > kDensifyMaxJointJump) {
                    out_msg = "IK branch jump (" + std::to_string(md)
                            + " rad) at segment " + std::to_string(i);
                    return false;
                }

                dpos.push_back(jk);
                dtime.push_back(ta + a * (tb - ta));
                seed = jk;
            }
            // Pin the node exactly to Pilz's own on-line solution (exact endpoint + anchor).
            dpos.push_back(jb);
            dtime.push_back(tb);
            seed = jb;
        }

        // Keep timestamps strictly increasing (defensive against equal Pilz samples).
        for (size_t m = 1; m < dtime.size(); ++m)
            if (dtime[m] <= dtime[m - 1]) dtime[m] = dtime[m - 1] + 1e-4;

        // Rebuild the message with finite-difference velocities; endpoints stay at rest
        // (Pilz LIN starts and ends with zero Cartesian velocity).
        trajectory_msgs::msg::JointTrajectory out;
        out.joint_names = names;
        out.points.resize(dpos.size());
        for (size_t m = 0; m < dpos.size(); ++m) {
            auto& p = out.points[m];
            p.positions = dpos[m];
            p.velocities.assign(ndof, 0.0);
            p.time_from_start.sec = static_cast<int32_t>(dtime[m]);
            p.time_from_start.nanosec = static_cast<uint32_t>(
                (dtime[m] - static_cast<int64_t>(dtime[m])) * 1e9);
        }
        for (size_t m = 1; m + 1 < dpos.size(); ++m) {
            const double dt = dtime[m + 1] - dtime[m - 1];
            if (dt <= 0.0) continue;
            for (size_t d = 0; d < ndof; ++d)
                out.points[m].velocities[d] = (dpos[m + 1][d] - dpos[m - 1][d]) / dt;
        }

        trajectory.joint_trajectory = out;
        out_msg = "densified " + std::to_string(pts.size())
                + " -> " + std::to_string(dpos.size()) + " points";
        return true;
    }

    bool MotionServer::planAndExecuteSequence(
        const std::vector<geometry_msgs::msg::Pose>& waypoints,
        double vel_scaling,
        double blend_radius,
        bool execute,
        std::string& out_msg)
    {
        using MGS = moveit_msgs::action::MoveGroupSequence;

        if (!seq_client_->wait_for_action_server(std::chrono::seconds(5))) {
            out_msg = "Pilz sequence action '/sequence_move_group' unavailable "
                      "(MoveGroupSequenceAction capability not loaded in move_group)";
            return false;
        }

        const std::string eef = move_group_->getEndEffectorLink();
        const double vscale = std::min(std::max(vel_scaling, 0.0), 1.0);
        const double ascale = std::min(std::max(accel_scale_, 0.0), 1.0);
        const double blend = std::max(0.0, blend_radius);

        moveit_msgs::msg::MotionSequenceRequest seq_req;
        for (size_t i = 0; i < waypoints.size(); ++i) {
            moveit_msgs::msg::MotionSequenceItem item;

            item.req.group_name = planning_group_;
            item.req.pipeline_id = "pilz_industrial_motion_planner";
            item.req.planner_id = "LIN";
            item.req.max_velocity_scaling_factor = vscale;
            item.req.max_acceleration_scaling_factor = ascale;
            item.req.allowed_planning_time = 5.0;
            item.req.num_planning_attempts = 1;

            geometry_msgs::msg::PoseStamped ps;
            ps.header.frame_id = planning_frame_;
            ps.pose = waypoints[i];
            item.req.goal_constraints.push_back(
                kinematic_constraints::constructGoalConstraints(eef, ps, 1e-3, 1e-2));

            // blend_radius applies at the END of a segment; the LAST item must be 0 (Pilz rule).
            item.blend_radius = (i + 1 < waypoints.size()) ? blend : 0.0;

            seq_req.items.push_back(item);
        }

        MGS::Goal goal;
        goal.request = seq_req;
        goal.planning_options.plan_only = !execute;

        auto goal_future = seq_client_->async_send_goal(goal);
        if (rclcpp::spin_until_future_complete(seq_node_, goal_future, std::chrono::seconds(30))
                != rclcpp::FutureReturnCode::SUCCESS) {
            out_msg = "Failed to send Pilz sequence goal (timeout)";
            return false;
        }
        auto goal_handle = goal_future.get();
        if (!goal_handle) {
            out_msg = "Pilz sequence goal rejected by server";
            return false;
        }

        auto result_future = seq_client_->async_get_result(goal_handle);
        if (rclcpp::spin_until_future_complete(seq_node_, result_future, std::chrono::seconds(300))
                != rclcpp::FutureReturnCode::SUCCESS) {
            out_msg = "Pilz sequence result timeout";
            return false;
        }

        auto wrapped = result_future.get();

        // The sequence server fills response.error_code with the real MoveIt reason even
        // when it ABORTS the goal — read it regardless of the action result code so the
        // failure message is actionable (not just "result code 6 = ABORTED").
        const bool action_ok = (wrapped.code == rclcpp_action::ResultCode::SUCCEEDED);
        int err_val = moveit_msgs::msg::MoveItErrorCodes::SUCCESS;
        if (wrapped.result) {
            err_val = wrapped.result->response.error_code.val;
        }

        if (!action_ok || err_val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
            moveit_msgs::msg::MoveItErrorCodes ec;
            ec.val = err_val;
            moveit::core::MoveItErrorCode seq_code(ec);

            const char* action_state =
                (wrapped.code == rclcpp_action::ResultCode::ABORTED)  ? "ABORTED"  :
                (wrapped.code == rclcpp_action::ResultCode::CANCELED) ? "CANCELED" :
                (wrapped.code == rclcpp_action::ResultCode::SUCCEEDED)? "SUCCEEDED": "UNKNOWN";

            out_msg = std::string("Pilz sequence failed (action ") + action_state
                    + ", MoveIt code: " + moveitErrorCodeToString(seq_code) + ")"
                    + " — a LIN segment is likely infeasible (singularity, joint/Cartesian limit, "
                      "collision) or blend_radius too large / segment too short.";
            return false;
        }

        out_msg = "Pilz Sequence OK (" + std::to_string(waypoints.size())
                + " LIN segments, blend=" + std::to_string(blend)
                + "m, vel_scale=" + std::to_string(vscale) + ")";
        return true;
    }

    void MotionServer::applyVelocityScaling(
        moveit_msgs::msg::RobotTrajectory& trajectory,
        double path_tolerance)
    {
        // Re-time the (concatenated joint-space waypoint) trajectory with TOTG so it honors
        // vel_scale_/accel_scale_ and has continuous velocities at segment junctions.
        // (Cartesian moves no longer pass here: Pilz LIN/Sequence time their own trajectories.)
        robot_trajectory::RobotTrajectory rt(
            move_group_->getRobotModel(), planning_group_);

        rt.setRobotTrajectoryMsg(*move_group_->getCurrentState(), trajectory);

        // <= 0 means "use default"; otherwise clamp to a sane range so a bad request can't
        // ask for a wildly large corner-cut (the final trajectory is collision-checked anyway).
        double tol = (path_tolerance > 0.0)
            ? std::min(std::max(path_tolerance, 0.001), 0.5)
            : kDefaultTotgPathTolerance;
        RCLCPP_INFO(this->get_logger(),
            "[TRAJ] TOTG re-timing with path_tolerance=%.4f rad%s",
            tol, (path_tolerance > 0.0) ? " (requested)" : " (default)");

        trajectory_processing::TimeOptimalTrajectoryGeneration totg(
            tol,    // path_tolerance (rad) — how much TOTG can deviate from path to smooth corners
            0.01,   // resample_dt (s) — finer interpolation
            0.001   // min_angle_change
        );

        // Check return value — if retiming fails, the robot would
        // execute with the raw (unscaled) timestamps, potentially at full speed.
        // This is a SAFETY-CRITICAL check.
        bool ok = totg.computeTimeStamps(rt, vel_scale_, accel_scale_);
        if (!ok) {
            RCLCPP_ERROR(this->get_logger(),
                "SAFETY: TOTG retiming FAILED (vel=%.2f, accel=%.2f). "
                "Trajectory will NOT be executed to prevent uncontrolled speed. "
                "Clearing trajectory points as a safety measure.",
                vel_scale_, accel_scale_);
            // Clear the trajectory to prevent execution with raw timestamps
            trajectory.joint_trajectory.points.clear();
            return;
        }

        // Convert back to message with correct timestamps
        rt.getRobotTrajectoryMsg(trajectory);
    }

    void MotionServer::logCartesianFkTrace(
        const std::string& label,
        const moveit_msgs::msg::RobotTrajectory& trajectory) const
    {
        const auto& joint_traj = trajectory.joint_trajectory;
        const auto& points = joint_traj.points;

        if (!move_group_) {
            RCLCPP_WARN(this->get_logger(), "[FK_TRACE:%s] MoveGroup is not initialized", label.c_str());
            return;
        }

        if (points.empty()) {
            RCLCPP_WARN(this->get_logger(), "[FK_TRACE:%s] Trajectory has 0 points", label.c_str());
            return;
        }

        if (joint_traj.joint_names.empty()) {
            RCLCPP_WARN(this->get_logger(), "[FK_TRACE:%s] Trajectory has no joint names", label.c_str());
            return;
        }

        const std::string ee_link = move_group_->getEndEffectorLink();
        if (ee_link.empty()) {
            RCLCPP_WARN(this->get_logger(), "[FK_TRACE:%s] End-effector link is empty", label.c_str());
            return;
        }

        auto state = move_group_->getCurrentState(1.0);
        if (!state) {
            RCLCPP_WARN(this->get_logger(), "[FK_TRACE:%s] Cannot get current robot state", label.c_str());
            return;
        }

        std::vector<Eigen::Vector3d> positions;
        positions.reserve(points.size());

        auto append_fk_sample = [&](const std::vector<double>& joint_positions, size_t source_index, double t) {
            for (size_t j = 0; j < joint_traj.joint_names.size(); ++j) {
                state->setVariablePosition(joint_traj.joint_names[j], joint_positions[j]);
            }
            state->update();

            const Eigen::Isometry3d& tf = state->getGlobalLinkTransform(ee_link);
            const Eigen::Vector3d p = tf.translation();
            positions.push_back(p);

            RCLCPP_DEBUG(
                this->get_logger(),
                "[FK_TRACE:%s] sample=%zu source_point=%zu t=%.6f xyz=(%.6f, %.6f, %.6f)",
                label.c_str(), positions.size() - 1, source_index, t, p.x(), p.y(), p.z());
        };

        for (size_t i = 0; i < points.size(); ++i) {
            const auto& pt = points[i];
            if (pt.positions.size() != joint_traj.joint_names.size()) {
                RCLCPP_WARN(
                    this->get_logger(),
                    "[FK_TRACE:%s] Point %zu has %zu positions for %zu joint names",
                    label.c_str(), i, pt.positions.size(), joint_traj.joint_names.size());
                return;
            }

            const double t = pt.time_from_start.sec + pt.time_from_start.nanosec * 1e-9;
            if (i == 0) {
                append_fk_sample(pt.positions, i, t);
                continue;
            }

            const auto& prev_pt = points[i - 1];
            double max_joint_delta = 0.0;
            for (size_t j = 0; j < pt.positions.size(); ++j) {
                max_joint_delta = std::max(max_joint_delta, std::abs(pt.positions[j] - prev_pt.positions[j]));
            }

            const size_t samples = std::max<size_t>(
                1,
                std::min<size_t>(100, static_cast<size_t>(std::ceil(max_joint_delta / 0.01))));
            const double t_prev = prev_pt.time_from_start.sec + prev_pt.time_from_start.nanosec * 1e-9;

            for (size_t s = 1; s <= samples; ++s) {
                const double alpha = static_cast<double>(s) / static_cast<double>(samples);
                std::vector<double> interp(pt.positions.size(), 0.0);
                for (size_t j = 0; j < pt.positions.size(); ++j) {
                    interp[j] = prev_pt.positions[j] + alpha * (pt.positions[j] - prev_pt.positions[j]);
                }
                append_fk_sample(interp, i, t_prev + alpha * (t - t_prev));
            }
        }

        if (positions.size() == 1) {
            RCLCPP_INFO(
                this->get_logger(),
                "[FK_TRACE:%s] points=1 xyz=(%.6f, %.6f, %.6f)",
                label.c_str(),
                positions.front().x(), positions.front().y(), positions.front().z());
            return;
        }

        const Eigen::Vector3d start = positions.front();
        const Eigen::Vector3d end = positions.back();
        const Eigen::Vector3d line = end - start;
        const double straight_len = line.norm();

        double path_len = 0.0;
        double max_step = 0.0;
        double max_dev = 0.0;
        size_t max_dev_index = 0;

        for (size_t i = 1; i < positions.size(); ++i) {
            const double step = (positions[i] - positions[i - 1]).norm();
            path_len += step;
            max_step = std::max(max_step, step);
        }

        if (straight_len > 1e-12) {
            for (size_t i = 0; i < positions.size(); ++i) {
                const Eigen::Vector3d rel = positions[i] - start;
                const Eigen::Vector3d projected =
                    start + line * (rel.dot(line) / (straight_len * straight_len));
                const double dev = (positions[i] - projected).norm();
                if (dev > max_dev) {
                    max_dev = dev;
                    max_dev_index = i;
                }
            }
        }

        const double path_ratio = straight_len > 1e-12 ? path_len / straight_len : 0.0;
        const double total_time = points.back().time_from_start.sec
                                + points.back().time_from_start.nanosec * 1e-9;

        RCLCPP_INFO(
            this->get_logger(),
            "[FK_TRACE:%s] trajectory_points=%zu fk_samples=%zu time=%.6fs start=(%.6f, %.6f, %.6f) end=(%.6f, %.6f, %.6f) "
            "straight=%.6fm path=%.6fm ratio=%.6f max_dev=%.6fm@%zu max_step=%.6fm",
            label.c_str(),
            points.size(), positions.size(), total_time,
            start.x(), start.y(), start.z(),
            end.x(), end.y(), end.z(),
            straight_len, path_len, path_ratio,
            max_dev, max_dev_index, max_step);

        if (path_ratio > 1.02 || max_dev > 0.002) {
            RCLCPP_WARN(
                this->get_logger(),
                "[FK_TRACE:%s] Non-straight Cartesian trace suspected: ratio=%.6f, max_dev=%.6fm",
                label.c_str(), path_ratio, max_dev);
        }
    }

    // Trajectory sanity check before sending to the controller
    bool MotionServer::validateTrajectory(
        const moveit_msgs::msg::RobotTrajectory& trajectory,
        std::string& out_msg) const
    {
        const auto& points = trajectory.joint_trajectory.points;

        if (points.empty()) {
            out_msg = "SAFETY: Trajectory has 0 points — refusing execution";
            RCLCPP_ERROR(this->get_logger(), "%s", out_msg.c_str());
            return false;
        }

        double total_time = points.back().time_from_start.sec
                          + points.back().time_from_start.nanosec * 1e-9;

        RCLCPP_INFO(this->get_logger(),
            "[TRAJ] %zu points, total duration: %.4fs, joints: %zu",
            points.size(), total_time,
            trajectory.joint_trajectory.joint_names.size());

        // Check for suspiciously short segments that could cause controller jerk
        int short_segment_count = 0;
        for (size_t i = 1; i < points.size(); ++i) {
            double t_prev = points[i-1].time_from_start.sec + points[i-1].time_from_start.nanosec * 1e-9;
            double t_curr = points[i].time_from_start.sec + points[i].time_from_start.nanosec * 1e-9;
            double dt = t_curr - t_prev;
            if (dt < 1e-6) {
                short_segment_count++;
            }
        }
        if (short_segment_count > 0) {
            RCLCPP_WARN(this->get_logger(),
                "[TRAJ] WARNING: %d segment(s) with near-zero time delta detected — "
                "controller may experience jerk", short_segment_count);
        }

        return true;
    }

    // Re-check the (post-TOTG) trajectory against the planning scene. Needed because TOTG's
    // path_tolerance rounds segment-junction corners, deviating from the per-segment paths
    // that OMPL validated — a deviation nothing else re-checks. We interpolate between
    // consecutive points so a thin obstacle can't be tunneled through.
    bool MotionServer::validateTrajectoryCollisionFree(
        const moveit_msgs::msg::RobotTrajectory& trajectory,
        std::string& out_msg) const
    {
        const auto& joint_traj = trajectory.joint_trajectory;
        const auto& points = joint_traj.points;

        if (points.empty()) {
            // validateTrajectory already rejects this; treat as nothing-to-check here.
            return true;
        }

        auto scene = getLockedPlanningScene();
        if (!scene) {
            out_msg = "SAFETY: PlanningSceneMonitor unavailable — cannot collision-check "
                      "the final trajectory; refusing execution";
            RCLCPP_ERROR(this->get_logger(), "%s", out_msg.c_str());
            return false;
        }

        moveit::core::RobotState state(move_group_->getRobotModel());
        state.setToDefaultValues();

        // Max joint step (rad) between collision samples; finer than this we interpolate.
        constexpr double MAX_STEP_RAD = 0.02;

        auto check_state = [&](const std::vector<double>& positions,
                               size_t point_index, std::string& fail) -> bool {
            for (size_t j = 0; j < joint_traj.joint_names.size() && j < positions.size(); ++j) {
                state.setVariablePosition(joint_traj.joint_names[j], positions[j]);
            }
            state.update();

            std::vector<std::string> pairs, self_pairs, env_pairs;
            if (checkStateCollision(scene, state, planning_group_, pairs, self_pairs, env_pairs)) {
                std::ostringstream oss;
                oss << "SAFETY: post-TOTG trajectory is in collision at point " << point_index
                    << " (corner-rounding deviated into an obstacle): ";
                for (size_t i = 0; i < pairs.size() && i < 5; ++i) {
                    if (i > 0) oss << ", ";
                    oss << pairs[i];
                }
                fail = oss.str();
                return false;
            }
            return true;
        };

        // Check the very first point.
        if (!check_state(points.front().positions, 0, out_msg)) {
            RCLCPP_ERROR(this->get_logger(), "%s", out_msg.c_str());
            return false;
        }

        // Check every subsequent point, interpolating sub-steps when the joint delta is large.
        for (size_t i = 1; i < points.size(); ++i) {
            const auto& prev = points[i - 1].positions;
            const auto& curr = points[i].positions;
            if (prev.size() != curr.size()) continue;

            double max_delta = 0.0;
            for (size_t j = 0; j < curr.size(); ++j) {
                max_delta = std::max(max_delta, std::abs(curr[j] - prev[j]));
            }

            const size_t sub = std::max<size_t>(
                1, static_cast<size_t>(std::ceil(max_delta / MAX_STEP_RAD)));

            for (size_t s = 1; s <= sub; ++s) {
                const double alpha = static_cast<double>(s) / static_cast<double>(sub);
                std::vector<double> interp(curr.size());
                for (size_t j = 0; j < curr.size(); ++j) {
                    interp[j] = prev[j] + alpha * (curr[j] - prev[j]);
                }
                if (!check_state(interp, i, out_msg)) {
                    RCLCPP_ERROR(this->get_logger(), "%s", out_msg.c_str());
                    return false;
                }
            }
        }

        RCLCPP_INFO(this->get_logger(),
            "[TRAJ] Post-TOTG collision check passed (%zu points)", points.size());
        return true;
    }

    // Post-execution diagnostics
    std::string MotionServer::diagnoseExecutionFailure(
        const moveit::core::MoveItErrorCode& exec_code)
    {
        // Delegates to the free diagnostic (in motion_diagnostics), passing the live
        // node state it needs (MoveGroup, locked planning scene, planning group).
        return motion_control::diagnoseExecutionFailure(
            exec_code, *move_group_, getLockedPlanningScene(),
            planning_group_, this->get_logger());
    }

    void MotionServer::onSetTcpTrace(
        const std::shared_ptr<std_srvs::srv::SetBool::Request> req,
        std::shared_ptr<std_srvs::srv::SetBool::Response> res)
    {
        std::lock_guard<std::mutex> lk(trace_mtx_);
        trace_enabled_ = req->data;
        res->success = true;
        res->message = trace_enabled_
            ? "TCP trace ENABLED (sampling the live tool-tip path)"
            : "TCP trace DISABLED (existing trace kept; call clear_tcp_trace to erase it)";
        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }

    void MotionServer::onClearTcpTrace(
        const std::shared_ptr<std_srvs::srv::Trigger::Request> /*req*/,
        std::shared_ptr<std_srvs::srv::Trigger::Response> res)
    {
        std::lock_guard<std::mutex> lk(trace_mtx_);
        trace_points_.clear();
        publishTraceMarker(/*clear=*/true);
        res->success = true;
        res->message = "TCP trace cleared";
        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }

    void MotionServer::onSetDrivesExpected(
        const std::shared_ptr<std_srvs::srv::SetBool::Request> req,
        std::shared_ptr<std_srvs::srv::SetBool::Response> res)
    {
        // No mtx_ lock on purpose: the underlying setter is atomic, and we must stay
        // responsive even if a motion is in flight. health_monitor_ is created once in
        // onInitRobot and never reset, so reading the pointer here is safe.
        if (!health_monitor_) {
            res->success = false;
            res->message = "Health monitor not active (use_health_monitor=false or robot "
                           "not initialized yet) — nothing to update";
            RCLCPP_WARN(this->get_logger(), "%s", res->message.c_str());
            return;
        }

        health_monitor_->setDrivesExpectedOn(req->data);
        res->success = true;
        res->message = std::string("Drives expected ") + (req->data ? "ON" : "OFF")
                     + " — drives-powered/motion_possible fault "
                     + (req->data ? "ENFORCED" : "SUPPRESSED (intentional power-off)");
        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }

    void MotionServer::sampleTcpTrace()
    {
        // Snapshot the frames under the lock, then do the (thread-safe) TF lookup unlocked.
        std::string frame, ee;
        {
            std::lock_guard<std::mutex> lk(trace_mtx_);
            if (!trace_enabled_) return;
            frame = planning_frame_;
            ee = ee_link_;
        }
        if (frame.empty() || ee.empty()) return;

        geometry_msgs::msg::Point p;
        try {
            auto tf = tf_buffer_->lookupTransform(frame, ee, tf2::TimePointZero);
            p.x = tf.transform.translation.x;
            p.y = tf.transform.translation.y;
            p.z = tf.transform.translation.z;
        } catch (const std::exception&) {
            return;  // TF not available yet — skip this tick silently
        }

        std::lock_guard<std::mutex> lk(trace_mtx_);
        if (!trace_enabled_) return;  // could have been disabled between the two locks

        if (!trace_points_.empty()) {
            const auto& last = trace_points_.back();
            const double dx = p.x - last.x;
            const double dy = p.y - last.y;
            const double dz = p.z - last.z;
            const double dist = std::sqrt(dx * dx + dy * dy + dz * dz);
            if (dist < kTraceMinDist) return;        // not enough movement to record
            if (dist > kTraceMaxJump) {              // discontinuity -> start a fresh line
                trace_points_.clear();
            }
        }

        trace_points_.push_back(p);
        if (trace_points_.size() > kTraceMaxPoints) {
            trace_points_.erase(trace_points_.begin());  // moving window
        }
        publishTraceMarker(/*clear=*/false);
    }

    void MotionServer::publishTraceMarker(bool clear)
    {
        // Precondition: caller holds trace_mtx_.
        visualization_msgs::msg::Marker m;
        m.header.frame_id = planning_frame_;
        m.header.stamp = this->now();
        m.ns = "tcp_trace";
        m.id = 0;
        m.type = visualization_msgs::msg::Marker::SPHERE_LIST;

        if (clear || trace_points_.empty()) {
            m.action = visualization_msgs::msg::Marker::DELETE;
            visual_marker_pub_->publish(m);
            return;
        }

        m.action = visualization_msgs::msg::Marker::ADD;
        m.pose.orientation.w = 1.0;
        m.scale.x = 0.004;  // sphere diameter (x/y/z) = 4 mm
        m.scale.y = 0.004;
        m.scale.z = 0.004;
        m.color.r = 0.0f;
        m.color.g = 1.0f;
        m.color.b = 0.2f;
        m.color.a = 1.0f;
        m.points = trace_points_;
        visual_marker_pub_->publish(m);
    }

    void MotionServer::onMoveToPose(
        const std::shared_ptr<motion_control::srv::MoveToPose::Request> req,
        std::shared_ptr<motion_control::srv::MoveToPose::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string error_msg;
        if (!ensureInitialized(error_msg)) { res->success = false; res->message = error_msg; return; }

        auto maybe_target = computeAbsoluteTarget(
            req->x, req->y, req->z, req->r1, req->r2, req->r3, req->r4,
            req->rotation_format, req->reference_frame, req->is_relative, error_msg
        );

        if (!maybe_target.has_value()) { res->success = false; res->message = error_msg; return; }
        auto target_pose = maybe_target.value();

        // Validate quaternion to catch NaN/Inf before sending to MoveIt
        {
            const auto& q = target_pose.pose.orientation;
            double norm = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
            if (!std::isfinite(norm) || norm < 0.99 || norm > 1.01) {
                res->success = false;
                res->message = "Invalid quaternion after transformation (norm=" + std::to_string(norm) + "). Check rotation inputs.";
                return;
            }
        }

        // Log the resolved target on the path for post-incident reconstruction
        RCLCPP_INFO(this->get_logger(),
            "[MoveToPose] Resolved target: pos=[%.4f, %.4f, %.4f] quat=[%.4f, %.4f, %.4f, %.4f] "
            "frame=%s ref=%s relative=%s cartesian=%s execute=%s",
            target_pose.pose.position.x, target_pose.pose.position.y, target_pose.pose.position.z,
            target_pose.pose.orientation.x, target_pose.pose.orientation.y,
            target_pose.pose.orientation.z, target_pose.pose.orientation.w,
            target_pose.header.frame_id.c_str(),
            req->reference_frame.c_str(),
            req->is_relative ? "true" : "false",
            req->cartesian_path ? "true" : "false",
            req->execute ? "true" : "false");

        if (!req->constrained_joints.empty()) {
            std::ostringstream oss_c;
            oss_c << "[MoveToPose] Joint constraints: ";
            for (size_t i = 0; i < req->constrained_joints.size(); ++i) {
                if (i > 0) oss_c << ", ";
                oss_c << req->constrained_joints[i] << "=["
                    << req->joint_min[i] << ", " << req->joint_max[i] << "]";
            }
            RCLCPP_INFO(this->get_logger(), "%s", oss_c.str().c_str());
        }

        // Speed application
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        if (req->cartesian_path)
        {
            // Cartesian => straight TCP line via Pilz LIN
            moveit_msgs::msg::RobotTrajectory trajectory;
            std::string lin_msg;

            // Linear speed is the global scaling (vel_scale_), set centrally via set_scaling —
            // same knob as joint moves. Cartesian moves take no per-move speed argument.
            const double vscale = vel_scale_;

            auto start_time = std::chrono::high_resolution_clock::now();
            bool planned = planCartesianLin(target_pose, vscale, trajectory, lin_msg);
            auto end_time = std::chrono::high_resolution_clock::now();
            double planning_duration = std::chrono::duration<double>(end_time - start_time).count();

            RCLCPP_INFO(this->get_logger(), "Cartesian (Pilz LIN) result: %s (%.2fs)",
                        lin_msg.c_str(), planning_duration);

            if (!planned) {
                res->success = false;
                res->message = lin_msg + " (took " + std::to_string(planning_duration) + "s)";
                return;
            }

            logCartesianFkTrace("MOVE_TO_POSE_LIN", trajectory);

            // Validate trajectory before sending to controller
            std::string traj_err;
            if (!validateTrajectory(trajectory, traj_err)) {
                res->success = false;
                res->message = traj_err;
                return;
            }

            if (req->execute) {
                const auto& pts = trajectory.joint_trajectory.points;
                double traj_duration = pts.back().time_from_start.sec
                                    + pts.back().time_from_start.nanosec * 1e-9;

                auto exec_t0 = std::chrono::high_resolution_clock::now();
                auto exec_code = move_group_->execute(trajectory);
                double exec_dt = std::chrono::duration<double>(
                    std::chrono::high_resolution_clock::now() - exec_t0).count();

                std::string robot_fault;
                if (getRobotFaultMessage(robot_fault)) {
                    res->success = false;
                    res->message = robot_fault;
                } else if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
                    res->success = false;
                    res->message = diagnoseExecutionFailure(exec_code);
                } else {
                    res->success = true;
                    res->message = "Cartesian (LIN) executed. " + lin_msg
                                + " (plan=" + std::to_string(planning_duration)
                                + "s, trajectory=" + std::to_string(traj_duration)
                                + "s, real=" + std::to_string(exec_dt) + "s)";
                }
            } else {
                res->success = true;
                res->message = "Cartesian (LIN) planned (execute=false). " + lin_msg;
            }
        }
        else
        {
            // Apply optional joint constraints (joint-space only)
            {
                std::string constraint_err;
                if (!applyJointConstraints(req->constrained_joints, req->joint_min, req->joint_max, constraint_err)) {
                    res->success = false;
                    res->message = constraint_err;
                    return;
                }
            }
            auto clear_fn = [this]() { move_group_->clearPathConstraints(); };
            struct CGuard { std::function<void()> fn; ~CGuard() { fn(); } } cg_{clear_fn};

            // Standard joint space planning
            std::string msg;
            res->success = planAndMaybeExecutePose(target_pose, req->execute, msg);
            res->message = msg;
        }
    }

    void MotionServer::onMoveWaypoints(
        const std::shared_ptr<motion_control::srv::MoveWaypoints::Request> req,
        std::shared_ptr<motion_control::srv::MoveWaypoints::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureInitialized(why)) { res->success = false; res->message = why; return; }

        if (req->waypoints.empty()) {
            res->success = false;
            res->message = "The list of waypoints is empty";
            return;
        }

        // --- VERIFY PARALLEL ARRAYS ---
        if (req->is_relative_list.size() != req->waypoints.size() ||
            req->reference_frame_list.size() != req->waypoints.size())
        {
            res->success = false;
            res->message = "Configuration arrays (is_relative_list, reference_frame_list) must match the waypoints array size.";
            return;
        }

        // Initial base point: The current position of the robot
        tf2::Transform current_base_tf;
        {
            const std::string ee_link = move_group_->getEndEffectorLink();
            try {
                geometry_msgs::msg::PoseStamped cp = move_group_->getCurrentPose(ee_link);

                const auto& q = cp.pose.orientation;
                const double norm = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
                if (!std::isfinite(norm) || norm < 0.99 || norm > 1.01) {
                    res->success = false;
                    res->message = "getCurrentPose() returned invalid quaternion (norm="
                                 + std::to_string(norm) + ")";
                    return;
                }

                tf2::fromMsg(cp.pose, current_base_tf);

                RCLCPP_INFO(this->get_logger(),
                    "[MoveWaypoints] Base pose (MoveIt): pos(%.4f, %.4f, %.4f)",
                    cp.pose.position.x, cp.pose.position.y, cp.pose.position.z);
            } catch (const std::exception& e) {
                res->success = false;
                res->message = std::string("Failed to get current pose from MoveIt: ") + e.what();
                return;
            }
        }

        std::vector<geometry_msgs::msg::Pose> absolute_waypoints;

        // Conversion loop
        for (size_t i = 0; i < req->waypoints.size(); ++i) {
            tf2::Transform wp_tf;
            tf2::fromMsg(req->waypoints[i], wp_tf);
            tf2::Transform target_tf;

            // Retrieve the specific configuration for THIS waypoint
            bool is_rel = req->is_relative_list[i];
            std::string ref_frame = req->reference_frame_list[i];

            if (is_rel) {
                if (ref_frame == "TOOL") {
                    // Post-multiplication: delta applied along the tool's axes
                    target_tf = current_base_tf * wp_tf;
                } else { // WORLD
                    // Pre-multiplication: delta applied along the fixed world axes
                    target_tf.setOrigin(current_base_tf.getOrigin() + wp_tf.getOrigin());
                    target_tf.setRotation(wp_tf.getRotation() * current_base_tf.getRotation());
                    target_tf.getRotation().normalize();
                }
            } else {
                // Absolute point
                target_tf = wp_tf;
            }

            // The point we just calculated becomes the new reference base for the next point!
            current_base_tf = target_tf;

            tf2::Quaternion q_check = target_tf.getRotation();
            double norm = q_check.length();
            if (!std::isfinite(norm) || norm < 0.99 || norm > 1.01) {
                res->success = false;
                res->message = "Invalid quaternion at waypoint " + std::to_string(i)
                            + " (norm=" + std::to_string(norm) + ")";
                return;
            }

            geometry_msgs::msg::Pose abs_pose;
            tf2::toMsg(target_tf, abs_pose);
            absolute_waypoints.push_back(abs_pose);

            // Log each resolved waypoint for post-incident reconstruction
            RCLCPP_INFO(this->get_logger(),
                "[MoveWaypoints] WP#%zu resolved: pos=[%.4f, %.4f, %.4f] "
                "quat=[%.4f, %.4f, %.4f, %.4f] (rel=%s frame=%s)",
                i, abs_pose.position.x, abs_pose.position.y, abs_pose.position.z,
                abs_pose.orientation.x, abs_pose.orientation.y,
                abs_pose.orientation.z, abs_pose.orientation.w,
                is_rel ? "true" : "false", ref_frame.c_str());
        }

        RCLCPP_INFO(this->get_logger(),
            "[MoveWaypoints] %zu waypoints resolved, cartesian=%s, execute=%s",
            absolute_waypoints.size(),
            req->cartesian_path ? "true" : "false",
            req->execute ? "true" : "false");

        // Apply velocity and acceleration scaling factors
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        if (req->cartesian_path)
        {

            // Cartesian waypoints => single blended Pilz LIN sequence (/sequence_move_group).
            // blend_radius rounds the corners (0 = stop at each corner). The action plans and,
            // when execute=true, executes the whole blended trajectory natively.
            // Linear speed = global scaling (vel_scale_), set centrally via set_scaling.
            const double vscale = vel_scale_;

            auto seq_t0 = std::chrono::high_resolution_clock::now();
            std::string seq_msg;
            bool ok = planAndExecuteSequence(absolute_waypoints, vscale,
                                             req->blend_radius, req->execute, seq_msg);
            double seq_dt = std::chrono::duration<double>(
                std::chrono::high_resolution_clock::now() - seq_t0).count();

            RCLCPP_INFO(this->get_logger(), "[MoveWaypoints] Pilz Sequence: %s (%.2fs)",
                        seq_msg.c_str(), seq_dt);

            std::string robot_fault;
            if (ok && req->execute && getRobotFaultMessage(robot_fault)) {
                res->success = false;
                res->message = robot_fault;
            } else {
                res->success = ok;
                res->message = seq_msg + " (" + std::to_string(seq_dt) + "s)";
            }
        }
        else {
            moveit_msgs::msg::RobotTrajectory combined_trajectory;
            combined_trajectory.joint_trajectory.joint_names = move_group_->getJointNames();

            const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
            if (!jmg) {
                res->success = false;
                res->message = "Unknown planning group: " + planning_group_;
                return;
            }
            const auto& names = jmg->getVariableNames();

            moveit::core::RobotStatePtr current_start_state = move_group_->getCurrentState();

            int32_t acc_sec = 0;
            uint32_t acc_nanosec = 0;
            auto start_time = std::chrono::high_resolution_clock::now();

            for (size_t i = 0; i < absolute_waypoints.size(); ++i) {
                std::vector<double> best_joints;
                std::string ik_msg;
                if (!solveBestIK(absolute_waypoints[i], *current_start_state, best_joints, ik_msg)) {
                    res->success = false;
                    res->message = "IK failed at waypoint " + std::to_string(i + 1) + ": " + ik_msg;
                    move_group_->setStartStateToCurrentState();
                    return;
                }
                RCLCPP_INFO(this->get_logger(),
                    "[MoveWaypoints] Segment %zu/%zu — %s",
                    i + 1, absolute_waypoints.size(), ik_msg.c_str());

                // Map best_joints to the {name:value} format expected by setJointValueTarget
                std::map<std::string, double> joint_map;
                for (size_t j = 0; j < names.size(); ++j) {
                    joint_map[names[j]] = best_joints[j];
                }

                // Planning joint-space
                move_group_->setStartState(*current_start_state);
                move_group_->setJointValueTarget(joint_map);

                moveit::planning_interface::MoveGroupInterface::Plan segment_plan;
                auto seg_t0 = std::chrono::high_resolution_clock::now();
                auto code = move_group_->plan(segment_plan);
                double seg_dt = std::chrono::duration<double>(
                    std::chrono::high_resolution_clock::now() - seg_t0).count();

                RCLCPP_INFO(this->get_logger(),
                    "[MoveWaypoints] Segment %zu/%zu planning: %s (%.3fs, %zu points)",
                    i + 1, absolute_waypoints.size(),
                    (code == moveit::core::MoveItErrorCode::SUCCESS) ? "OK" : "FAILED",
                    seg_dt,
                    segment_plan.trajectory_.joint_trajectory.points.size());

                if (code != moveit::core::MoveItErrorCode::SUCCESS) {
                    // Diagnostics: We have a valid IK solution, but the planner hasn't
                    // found a path to reach it (constraints, obstacles along the way, etc.)
                    std::string diag_msg;
                    auto scene = getLockedPlanningScene();
                    if (scene) {
                        std::vector<double> goal_vec(best_joints);
                        auto report = diagnosePlanningFailure(
                            code, *move_group_, scene, planning_group_,
                            nullptr, &goal_vec,
                            seg_dt, this->get_logger());
                        diag_msg = report.summary;
                    }

                    res->success = false;
                    res->message = "Planning failed at waypoint " + std::to_string(i + 1)
                                + ": " + moveitErrorCodeToString(code);
                    if (!diag_msg.empty()) res->message += " | " + diag_msg;
                    move_group_->setStartStateToCurrentState();
                    return;
                }

                // Assemble the trajectory and adjust timing
                int32_t segment_duration_sec = 0;
                uint32_t segment_duration_nanosec = 0;

                // Warn about velocity discontinuity at segment junctions.
                // MoveIt plans each segment with zero-velocity endpoints. Skipping
                // points[0] avoids duplicate positions but does NOT guarantee
                // velocity continuity. The controller may experience a velocity jump.
                size_t start_index = (i == 0) ? 0 : 1;

                if (i > 0 && !combined_trajectory.joint_trajectory.points.empty()
                    && segment_plan.trajectory_.joint_trajectory.points.size() > 1) {
                    // Log the velocity at the junction for INFOging
                    const auto& last_pt = combined_trajectory.joint_trajectory.points.back();
                    const auto& next_pt = segment_plan.trajectory_.joint_trajectory.points[1]; // first used point
                    if (!last_pt.velocities.empty() && !next_pt.velocities.empty()) {
                        double max_vel_jump = 0.0;
                        for (size_t j = 0; j < last_pt.velocities.size() && j < next_pt.velocities.size(); ++j) {
                            max_vel_jump = std::max(max_vel_jump,
                                std::abs(last_pt.velocities[j] - next_pt.velocities[j]));
                        }
                        if (max_vel_jump > 0.1) {  // rad/s threshold
                            RCLCPP_WARN(this->get_logger(),
                                "[MoveWaypoints] Velocity discontinuity at segment %zu junction: "
                                "max delta=%.4f rad/s — controller may jerk", i, max_vel_jump);
                        }
                    }
                }

                for (size_t j = start_index; j < segment_plan.trajectory_.joint_trajectory.points.size(); ++j) {
                    auto pt = segment_plan.trajectory_.joint_trajectory.points[j];

                    segment_duration_sec = pt.time_from_start.sec;
                    segment_duration_nanosec = pt.time_from_start.nanosec;

                    uint32_t total_nanosec = pt.time_from_start.nanosec + acc_nanosec;
                    int32_t total_sec = pt.time_from_start.sec + acc_sec + (total_nanosec / 1000000000);
                    total_nanosec = total_nanosec % 1000000000;

                    pt.time_from_start.sec = total_sec;
                    pt.time_from_start.nanosec = total_nanosec;

                    combined_trajectory.joint_trajectory.points.push_back(pt);
                }

                // Accumulate time for the next segment
                acc_sec += segment_duration_sec;
                acc_nanosec += segment_duration_nanosec;
                if (acc_nanosec >= 1000000000) {
                    acc_sec += (acc_nanosec / 1000000000);
                    acc_nanosec = acc_nanosec % 1000000000;
                }

                // Update the start state for the next segment calculation
                if (segment_plan.trajectory_.joint_trajectory.points.empty()) {
                    res->success = false;
                    res->message = "Planner returned an empty trajectory at waypoint " + std::to_string(i+1);
                    move_group_->setStartStateToCurrentState();
                    return;
                }
                std::vector<double> last_positions = segment_plan.trajectory_.joint_trajectory.points.back().positions;
                current_start_state->setJointGroupPositions(planning_group_, last_positions);
            }

            // Restore normal state
            move_group_->clearPoseTargets();
            move_group_->setStartStateToCurrentState();

            auto end_time = std::chrono::high_resolution_clock::now();
            double planning_duration = std::chrono::duration<double>(end_time - start_time).count();

            // Retime the combined trajectory to eliminate velocity discontinuities
            // at segment junctions (joint-space waypoints; Cartesian waypoints use Pilz Sequence).
            // path_tolerance (rad) is the joint-space analogue of the Cartesian blend_radius.
            applyVelocityScaling(combined_trajectory, req->path_tolerance);

            // Summary of the assembled multi-segment trajectory
            RCLCPP_INFO(this->get_logger(),
                "[MoveWaypoints] Combined trajectory: %zu points, total planning duration: %.3fs",
                combined_trajectory.joint_trajectory.points.size(),
                planning_duration);

            // Validate combined trajectory before sending to controller
            std::string traj_err;
            if (!validateTrajectory(combined_trajectory, traj_err)) {
                res->success = false;
                res->message = traj_err;
                return;
            }

            // Re-check collisions on the FINAL (post-TOTG) trajectory: TOTG corner-rounding
            // can deviate from the per-segment paths OMPL validated. Refuse on collision.
            std::string collision_err;
            if (!validateTrajectoryCollisionFree(combined_trajectory, collision_err)) {
                res->success = false;
                res->message = collision_err;
                return;
            }

            // Execute
            if (req->execute) {
                const auto& pts = combined_trajectory.joint_trajectory.points;
                double traj_duration = pts.back().time_from_start.sec
                                    + pts.back().time_from_start.nanosec * 1e-9;

                auto exec_t0 = std::chrono::high_resolution_clock::now();
                auto exec_code = move_group_->execute(combined_trajectory);
                double exec_dt = std::chrono::duration<double>(
                    std::chrono::high_resolution_clock::now() - exec_t0).count();

                std::string robot_fault;
                if (getRobotFaultMessage(robot_fault)) {
                    res->success = false;
                    res->message = robot_fault;
                } else if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
                    res->success = false;
                    res->message = diagnoseExecutionFailure(exec_code);
                } else {
                    res->success = true;
                    res->message = "Waypoint sequence executed successfully (plan="
                                + std::to_string(planning_duration)
                                + "s, trajectory=" + std::to_string(traj_duration)
                                + "s, real=" + std::to_string(exec_dt) + "s)";
                }
            }
        }
    }

    bool MotionServer::planAndExecuteJoints(
        const std::vector<double>& joints, bool is_relative, bool execute, std::string& out_msg, double ik_seconds)
    {
        // Optional "IK=...s, " prefix shown inside the result message when an IK step preceded this call.
        const std::string ik_prefix = (ik_seconds >= 0.0)
            ? "IK=" + std::to_string(ik_seconds) + "s, "
            : "";
        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        const auto& names = jmg->getVariableNames();

        if (joints.size() != names.size()) {
            out_msg = "Incorrect joint size. Expected: " + std::to_string(names.size());
            return false;
        }

        std::map<std::string, double> target;
        std::vector<double> current = move_group_->getCurrentJointValues();

        for (size_t i = 0; i < names.size(); ++i) {
            target[names[i]] = is_relative ? current[i] + joints[i] : joints[i];
        }

        // Log target and current joints on the happy path
        {
            std::ostringstream oss_cur, oss_tgt;
            oss_cur << std::fixed << std::setprecision(4) << "[";
            oss_tgt << std::fixed << std::setprecision(4) << "[";
            for (size_t i = 0; i < names.size(); ++i) {
                if (i > 0) { oss_cur << ", "; oss_tgt << ", "; }
                oss_cur << current[i];
                oss_tgt << target[names[i]];
            }
            oss_cur << "]"; oss_tgt << "]";
            RCLCPP_INFO(this->get_logger(),
                "[PlanJoints] current=%s target=%s relative=%s execute=%s",
                oss_cur.str().c_str(), oss_tgt.str().c_str(),
                is_relative ? "true" : "false",
                execute ? "true" : "false");
        }

        move_group_->setStartStateToCurrentState();
        move_group_->setJointValueTarget(target);
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // --- Pre-planning validation (fast-fail before expensive planning) ---
        auto scene = getLockedPlanningScene();
        if (scene) {
            moveit::core::RobotState goal_state(move_group_->getRobotModel());
            std::vector<double> goal_vec;
            for (const auto& name : names) {
                goal_vec.push_back(target[name]);
            }
            goal_state.setJointGroupPositions(jmg, goal_vec);
            goal_state.update();

            // Check joint limits
            auto violations = checkJointLimits(goal_state, planning_group_);
            if (!violations.empty()) {
                out_msg = "Goal violates joint limits: ";
                for (size_t i = 0; i < violations.size(); ++i) {
                    if (i > 0) out_msg += ", ";
                    out_msg += violations[i];
                }
                return false;
            }

            // Check goal collision
            std::vector<std::string> pairs, self_pairs, env_pairs;
            if (checkStateCollision(scene, goal_state, planning_group_, pairs, self_pairs, env_pairs)) {
                out_msg = "Goal state is in collision: ";
                for (size_t i = 0; i < pairs.size() && i < 5; ++i) {
                    if (i > 0) out_msg += ", ";
                    out_msg += pairs[i];
                }
                return false;
            }
        }

        moveit::planning_interface::MoveGroupInterface::Plan plan;
        auto t0 = std::chrono::high_resolution_clock::now();
        auto code = move_group_->plan(plan);
        double dt = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();

        if (code != moveit::core::MoveItErrorCode::SUCCESS) {
            std::string diag_msg;
            if (scene) {
                // Convert target map to vector for diagnostics
                std::vector<double> goal_joints_vec;
                for (const auto& name : names) {
                    goal_joints_vec.push_back(target[name]);
                }
                auto report = diagnosePlanningFailure(
                    code, *move_group_, scene, planning_group_,
                    nullptr, &goal_joints_vec,
                    dt, this->get_logger());
                diag_msg = report.summary;
            }

            out_msg = "Planning failed: " + moveitErrorCodeToString(code)
                    + " (took " + std::to_string(dt) + "s)";
            if (!diag_msg.empty()) {
                out_msg += " | " + diag_msg;
            }
            return false;
        }

        // Log trajectory characteristics on the happy path
        RCLCPP_INFO(this->get_logger(),
            "[PlanJoints] Plan OK: %zu points, planning took %.3fs",
            plan.trajectory_.joint_trajectory.points.size(), dt);

        if (execute) {
            std::string traj_err;
            if (!validateTrajectory(plan.trajectory_, traj_err)) {
                out_msg = traj_err;
                return false;
            }

            // Theoretical trajectory duration
            const auto& pts = plan.trajectory_.joint_trajectory.points;
            double traj_duration = pts.back().time_from_start.sec
                                + pts.back().time_from_start.nanosec * 1e-9;

            auto exec_t0 = std::chrono::high_resolution_clock::now();
            auto exec = move_group_->execute(plan);
            double exec_dt = std::chrono::duration<double>(
                std::chrono::high_resolution_clock::now() - exec_t0).count();

            std::string robot_fault;
            if (getRobotFaultMessage(robot_fault)) {
                out_msg = robot_fault;
                return false;
            }
            if (exec != moveit::core::MoveItErrorCode::SUCCESS) {
                out_msg = diagnoseExecutionFailure(exec);
                return false;
            }
            out_msg = "Joint trajectory executed (" + ik_prefix + "plan=" + std::to_string(dt)
                    + "s, trajectory=" + std::to_string(traj_duration)
                    + "s, real=" + std::to_string(exec_dt) + "s)";
        } else {
            out_msg = "Joint trajectory planned (execute=false) (" + ik_prefix + "took " + std::to_string(dt) + "s)";
        }
        return true;
    }

    void MotionServer::onMoveJoints(
        const std::shared_ptr<motion_control::srv::MoveJoints::Request> req,
        std::shared_ptr<motion_control::srv::MoveJoints::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureInitialized(why)) { res->success = false; res->message = why; return; }

        RCLCPP_INFO(this->get_logger(),
        "[MoveJoints] Request: %zu joints, relative=%s, execute=%s",
        req->joints.size(),
        req->is_relative ? "true" : "false",
        req->execute ? "true" : "false");

        if (!req->constrained_joints.empty()) {
            std::ostringstream oss_c;
            oss_c << "[MoveJoints] Joint constraints: ";
            for (size_t i = 0; i < req->constrained_joints.size(); ++i) {
                if (i > 0) oss_c << ", ";
                oss_c << req->constrained_joints[i] << "=["
                    << req->joint_min[i] << ", " << req->joint_max[i] << "]";
            }
            RCLCPP_INFO(this->get_logger(), "%s", oss_c.str().c_str());
        }

        // --- Apply optional joint constraints ---
        {
            std::string constraint_err;
            if (!applyJointConstraints(req->constrained_joints, req->joint_min, req->joint_max, constraint_err)) {
                res->success = false;
                res->message = constraint_err;
                return;
            }
        }
        auto clear_fn = [this]() { move_group_->clearPathConstraints(); };
        struct CGuard { std::function<void()> fn; ~CGuard() { fn(); } } cg_{clear_fn};

        std::string msg;
        res->success = planAndExecuteJoints(req->joints, req->is_relative, req->execute, msg);
        res->message = msg;
    }

    void MotionServer::onMoveToPoseViaJoint(
        const std::shared_ptr<motion_control::srv::MoveToPose::Request> req,
        std::shared_ptr<motion_control::srv::MoveToPose::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string error_msg;
        if (!ensureInitialized(error_msg)) { res->success = false; res->message = error_msg; return; }

        auto maybe_target = computeAbsoluteTarget(
            req->x, req->y, req->z,
            req->r1, req->r2, req->r3, req->r4,
            req->rotation_format, req->reference_frame,
            req->is_relative, error_msg);

        if (!maybe_target.has_value()) { res->success = false; res->message = error_msg; return; }
        auto target_pose = maybe_target.value();

        // Validate quaternion
        const auto& q = target_pose.pose.orientation;
        double norm = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
        if (!std::isfinite(norm) || norm < 0.99 || norm > 1.01) {
            res->success = false;
            res->message = "Invalid quaternion after transformation (norm=" + std::to_string(norm) + "). Check rotation inputs.";
            return;
        }

        // Log the resolved target
        RCLCPP_INFO(this->get_logger(),
            "[MoveToPoseViaJoint] Target: pos=[%.4f, %.4f, %.4f] quat=[%.4f, %.4f, %.4f, %.4f]",
            target_pose.pose.position.x, target_pose.pose.position.y, target_pose.pose.position.z,
            target_pose.pose.orientation.x, target_pose.pose.orientation.y,
            target_pose.pose.orientation.z, target_pose.pose.orientation.w);

        if (!req->constrained_joints.empty()) {
            std::ostringstream oss_c;
            oss_c << "[MoveToPoseViaJoint] Joint constraints: ";
            for (size_t i = 0; i < req->constrained_joints.size(); ++i) {
                if (i > 0) oss_c << ", ";
                oss_c << req->constrained_joints[i] << "=["
                    << req->joint_min[i] << ", " << req->joint_max[i] << "]";
            }
            RCLCPP_INFO(this->get_logger(), "%s", oss_c.str().c_str());
        }

        std::string msg;

        // --- Apply optional joint constraints ---
        {
            std::string constraint_err;
            if (!applyJointConstraints(req->constrained_joints, req->joint_min, req->joint_max, constraint_err)) {
                res->success = false;
                res->message = constraint_err;
                return;
            }
        }
        auto clear_fn = [this]() { move_group_->clearPathConstraints(); };
        struct CGuard { std::function<void()> fn; ~CGuard() { fn(); } } cg_{clear_fn};

        res->success = solveIKAndPlanJoints(target_pose.pose, req->execute, msg);
        res->message = "[IK OK] " + msg;
    }

    void MotionServer::onGetJointState(
        const std::shared_ptr<srv::GetJointState::Request> /*req*/,
        std::shared_ptr<srv::GetJointState::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        // Check if MoveGroupInterface is initialized
        std::string why;
        if (!ensureMoveGroupInitialized(why)) {
            res->success = false;
            res->message = why;
            return;
        }

        // Get current joint values from MoveIt
        auto joints = move_group_->getCurrentJointValues();
        res->joints = joints;
        res->success = true;
        res->message = "OK";
        }

    void MotionServer::onGetCurrentPose(
        const std::shared_ptr<motion_control::srv::GetCurrentPose::Request> req,
        std::shared_ptr<motion_control::srv::GetCurrentPose::Response> res)
    {
        // Thread-safety: Protect MoveIt access
        std::lock_guard<std::mutex> lock(mtx_);

        // Handle default frames
        // If child_frame is empty, use the robot's End-Effector
        std::string target_frame = req->child_frame_id;
        if (target_frame.empty()) {
            if (move_group_) {
                target_frame = move_group_->getEndEffectorLink();
            } else {
                res->success = false;
                res->message = "MoveGroup not ready. Cannot determine End-Effector link";
                return;
            }
        }

        // If frame_id is empty, default to "world"
        std::string reference_frame = req->frame_id.empty() ? planning_frame_ : req->frame_id;

        try {
            // Lookup Transform via TF2
            geometry_msgs::msg::TransformStamped t;
            t = tf_buffer_->lookupTransform(
                reference_frame,
                target_frame,
                tf2::TimePointZero, // Get the latest available transform
                tf2::durationFromSec(0.5) // Timeout: fail fast if TF tree is broken
            );

            // Fill Standard Pose (Position + Quaternion)
            res->pose.header = t.header;
            res->pose.pose.position.x = t.transform.translation.x;
            res->pose.pose.position.y = t.transform.translation.y;
            res->pose.pose.position.z = t.transform.translation.z;
            res->pose.pose.orientation = t.transform.rotation;

            // Calculate Euler Angles (Always included)
            // Convert GeometryMsg Quaternion to TF2 Quaternion
            tf2::Quaternion q(
                t.transform.rotation.x,
                t.transform.rotation.y,
                t.transform.rotation.z,
                t.transform.rotation.w
            );

            // Convert to RPY (Roll-Pitch-Yaw / Extrinsic XYZ)
            tf2::Matrix3x3 m(q);
            double roll, pitch, yaw;
            m.getRPY(roll, pitch, yaw);

            // Fill the float array
            res->euler_rpy = {roll, pitch, yaw};

            res->success = true;
            res->message = "Pose retrieved via TF2 for link: " + target_frame;
        }
        catch (const tf2::TransformException & ex) {
            // Handle TF2 errors (e.g., frame does not exist)
            res->success = false;
            res->message = std::string("TF2 Error: ") + ex.what();
            RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
        }
    }

    void MotionServer::onSetVirtualCage(
        const std::shared_ptr<srv::SetVirtualCage::Request> req,
        std::shared_ptr<srv::SetVirtualCage::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureMoveGroupInitialized(why)) { res->success = false; res->message = why; return; }

        std::vector<moveit_msgs::msg::CollisionObject> collision_objects;
        std::vector<std::string> wall_names = {"cage_front", "cage_back", "cage_left", "cage_right", "cage_top", "cage_bottom"};

        if (!req->enable) {
            // // Destroy the cage (MoveIt to REMOVE these objects)
            for (const auto& name : wall_names) {
                moveit_msgs::msg::CollisionObject obj;
                obj.id = name;
                obj.operation = obj.REMOVE;
                collision_objects.push_back(obj);
            }
            planning_scene_->applyCollisionObjects(collision_objects);
            res->success = true; res->message = "Virtual cage removed";
            return;
        }

        // Cage construction
        const double thickness = 0.01; // Walls tickness of 1cm

        // Utility function to generate a wall as a CollisionObject
        auto make_wall = [&](const std::string& id, double cx, double cy, double cz, double sx, double sy, double sz) {
            moveit_msgs::msg::CollisionObject obj;
            obj.header.frame_id = planning_frame_;
            obj.id = id;
            obj.operation = obj.ADD;

            shape_msgs::msg::SolidPrimitive primitive;
            primitive.type = primitive.BOX;
            primitive.dimensions = {sx, sy, sz};

            geometry_msgs::msg::Pose pose;
            pose.position.x = cx; pose.position.y = cy; pose.position.z = cz;
            pose.orientation.w = 1.0;

            obj.primitives.push_back(primitive);
            obj.primitive_poses.push_back(pose);
            return obj;
        };

        // Calculation of the cage's internal dimensions
        double dim_x = req->front + req->back;
        double dim_y = req->left + req->right;
        double dim_z = req->top + req->bottom;

        // Calculation of the overall center of the cage
        double cx = (req->front - req->back) / 2.0;
        double cy = (req->left - req->right) / 2.0;
        double cz = (req->top - req->bottom) / 2.0;

        // Front Wall (+X)
        collision_objects.push_back(make_wall("cage_front", req->front + thickness/2, cy, cz, thickness, dim_y, dim_z));
        // Back Wall (-X)
        collision_objects.push_back(make_wall("cage_back", -req->back - thickness/2, cy, cz, thickness, dim_y, dim_z));
        // Left Wall (+Y)
        collision_objects.push_back(make_wall("cage_left", cx, req->left + thickness/2, cz, dim_x + thickness*2, thickness, dim_z));
        // Right Wall (-Y)
        collision_objects.push_back(make_wall("cage_right", cx, -req->right - thickness/2, cz, dim_x + thickness*2, thickness, dim_z));
        // Ceiling (+Z)
        collision_objects.push_back(make_wall("cage_top", cx, cy, req->top + thickness/2, dim_x + thickness*2, dim_y + thickness*2, thickness));
        //  Floor (-Z)
        collision_objects.push_back(make_wall("cage_bottom", cx, cy, -req->bottom - thickness/2, dim_x + thickness*2, dim_y + thickness*2, thickness));


        moveit_msgs::msg::PlanningScene planning_scene_msg;
        planning_scene_msg.is_diff = true;

        std_msgs::msg::ColorRGBA cage_color;
        cage_color.r = req->r;
        cage_color.g = req->g;
        cage_color.b = req->b;
        cage_color.a = req->a;

        for (const auto& obj : collision_objects) {
            moveit_msgs::msg::ObjectColor oc;
            oc.id = obj.id;
            oc.color = cage_color;
            planning_scene_msg.object_colors.push_back(oc);
        }

        // Apply the cage to the planning scene
        planning_scene_msg.world.collision_objects = collision_objects;
        planning_scene_->applyPlanningScene(planning_scene_msg);

        res->success = true;
        res->message = "Virtual cage successfully activated";
    }

    void MotionServer::onManageBox(
        const std::shared_ptr<srv::ManageBox::Request> req,
        std::shared_ptr<srv::ManageBox::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureMoveGroupInitialized(why)) { res->success = false; res->message = why; return; }

        // --- 1. Math and Pose Calculations ---
        tf2::Quaternion q;
        if (req->rotation_format == "RPY") {
            q.setRPY(req->r1, req->r2, req->r3);
        } else {
            q = tf2::Quaternion(req->r1, req->r2, req->r3, req->r4);
            q.normalize();
        }

        tf2::Matrix3x3 m(q);
        tf2::Vector3 z_vec = m.getColumn(2);

        double offset = req->size_z / 2.0;
        double cx = req->x + (offset * z_vec.x());
        double cy = req->y + (offset * z_vec.y());
        double cz = req->z + (offset * z_vec.z());

        geometry_msgs::msg::Pose pose;
        pose.position.x = cx;
        pose.position.y = cy;
        pose.position.z = cz;
        pose.orientation.x = q.x();
        pose.orientation.y = q.y();
        pose.orientation.z = q.z();
        pose.orientation.w = q.w();

        // --- 2. Setup MoveIt Object and RViz Marker ---
        moveit_msgs::msg::CollisionObject obj;
        obj.header.frame_id = planning_frame_;
        obj.id = req->box_id;

        visualization_msgs::msg::Marker marker;
        marker.header.frame_id = planning_frame_;
        marker.header.stamp = this->now();
        marker.ns = "boxes";
        marker.id = getMarkerId(req->box_id);

        moveit_msgs::msg::PlanningScene planning_scene_msg;
        planning_scene_msg.is_diff = true;

        // --- 3. Collision vs Visual Logic ---
        if (req->action == "REMOVE") {
            obj.operation = moveit_msgs::msg::CollisionObject::REMOVE;
            marker.action = visualization_msgs::msg::Marker::DELETE;
            visual_only_boxes_.erase(req->box_id);
        } else {
            if (req->enable_collision) {
                // COLLISION ON: MoveIt handles it
                obj.operation = moveit_msgs::msg::CollisionObject::ADD;

                shape_msgs::msg::SolidPrimitive primitive;
                primitive.type = primitive.BOX;
                primitive.dimensions = {req->size_x, req->size_y, req->size_z};

                obj.primitives.push_back(primitive);
                obj.primitive_poses.push_back(pose);

                moveit_msgs::msg::ObjectColor oc;
                oc.id = obj.id;
                oc.color.r = req->r;
                oc.color.g = req->g;
                oc.color.b = req->b;
                oc.color.a = req->a;
                planning_scene_msg.object_colors.push_back(oc);

                // Hide RViz marker
                marker.action = visualization_msgs::msg::Marker::DELETE;
                visual_only_boxes_.erase(req->box_id);
            } else {
                // COLLISION OFF: Purely visual in RViz
                obj.operation = moveit_msgs::msg::CollisionObject::REMOVE;

                marker.action = visualization_msgs::msg::Marker::ADD;
                marker.type = visualization_msgs::msg::Marker::CUBE;
                marker.pose = pose;
                marker.scale.x = req->size_x;
                marker.scale.y = req->size_y;
                marker.scale.z = req->size_z;
                marker.color.r = req->r;
                marker.color.g = req->g;
                marker.color.b = req->b;
                marker.color.a = req->a;
                visual_only_boxes_.erase(req->box_id);
            }
        }

        // --- 4. Apply changes ---
        planning_scene_msg.world.collision_objects.push_back(obj);
        planning_scene_->applyPlanningScene(planning_scene_msg);
        visual_marker_pub_->publish(marker);

        res->success = true;
        res->message = "Box '" + req->box_id + "' action '" + req->action + "' applied. Collision: " + (req->enable_collision ? "ON" : "OFF");
    }


    void MotionServer::onManageMesh(
        const std::shared_ptr<srv::ManageMesh::Request> req,
        std::shared_ptr<srv::ManageMesh::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureMoveGroupInitialized(why)) { res->success = false; res->message = why; return; }

        moveit_msgs::msg::CollisionObject obj;
        obj.header.frame_id = planning_frame_; // Placed relative to the planning frame
        obj.id = req->mesh_id;

        if (req->action == "REMOVE") {
            obj.operation = obj.REMOVE;
        } else {
            obj.operation = obj.ADD;

            // Create the scale vector
            Eigen::Vector3d scale(req->scale_x, req->scale_y, req->scale_z);

            // Load the mesh from the specified path (must start with file:// or package://)
            shapes::Mesh* m = shapes::createMeshFromResource(req->mesh_path, scale);

            if (!m) {
                res->success = false;
                res->message = "Failed to load mesh from: " + req->mesh_path;
                RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
                return;
            }

            // Convert to ROS message
            shape_msgs::msg::Mesh mesh_msg;
            shapes::ShapeMsg shape_msg;
            shapes::constructMsgFromShape(m, shape_msg);
            mesh_msg = boost::get<shape_msgs::msg::Mesh>(shape_msg);
            delete m; // Free the memory

            // Calculate the pose (Translation + Rotation)
            tf2::Quaternion q;
            if (req->rotation_format == "RPY") {
                q.setRPY(req->r1, req->r2, req->r3);
            } else {
                q = tf2::Quaternion(req->r1, req->r2, req->r3, req->r4);
                q.normalize();
            }

            geometry_msgs::msg::Pose pose;
            pose.position.x = req->x;
            pose.position.y = req->y;
            pose.position.z = req->z;
            pose.orientation.x = q.x();
            pose.orientation.y = q.y();
            pose.orientation.z = q.z();
            pose.orientation.w = q.w();

            // Add to the CollisionObject
            obj.meshes.push_back(mesh_msg);
            obj.mesh_poses.push_back(pose);
        }

        // Apply to the planning scene
        moveit_msgs::msg::PlanningScene planning_scene_msg;
        planning_scene_msg.is_diff = true;

        planning_scene_msg.world.collision_objects.push_back(obj);

        if (req->action != "REMOVE") {
            moveit_msgs::msg::ObjectColor oc;
            oc.id = obj.id;
            oc.color.r = req->r;
            oc.color.g = req->g;
            oc.color.b = req->b;
            oc.color.a = req->a;
            planning_scene_msg.object_colors.push_back(oc);
        }

        planning_scene_->applyPlanningScene(planning_scene_msg);

        res->success = true;
        res->message = "Mesh '" + req->mesh_id + "' action '" + req->action + "' applied with color.";
        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }

    void MotionServer::onClearEnvironment(
        const std::shared_ptr<std_srvs::srv::Trigger::Request> /*req*/,
        std::shared_ptr<std_srvs::srv::Trigger::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureMoveGroupInitialized(why)) {
            res->success = false;
            res->message = why;
            return;
        }

        auto object_ids = planning_scene_->getKnownObjectNames();

        auto attached = planning_scene_->getAttachedObjects();
        std::set<std::string> attached_ids;
        for (const auto& [id, _] : attached) {
            attached_ids.insert(id);
        }

        std::vector<std::string> to_remove;
        for (const auto& id : object_ids) {
            if (attached_ids.count(id) == 0) {
                to_remove.push_back(id);
            }
        }

        visualization_msgs::msg::Marker deleteall;
        deleteall.header.frame_id = planning_frame_;
        deleteall.header.stamp = this->now();
        deleteall.ns = "boxes";
        deleteall.action = visualization_msgs::msg::Marker::DELETEALL;
        visual_marker_pub_->publish(deleteall);

        // Build REMOVE operations for collision objects
        std::vector<moveit_msgs::msg::CollisionObject> removals;
        for (const auto& id : to_remove) {
            moveit_msgs::msg::CollisionObject obj;
            obj.id = id;
            obj.operation = moveit_msgs::msg::CollisionObject::REMOVE;
            removals.push_back(obj);

            visualization_msgs::msg::Marker marker;
            marker.header.frame_id = planning_frame_;
            marker.header.stamp = this->now();
            marker.ns = "boxes";
            marker.id = getMarkerId(id);
            marker.action = visualization_msgs::msg::Marker::DELETE;
            visual_marker_pub_->publish(marker);
        }

        if (!removals.empty()) {
            planning_scene_->applyCollisionObjects(removals);
        }

        // Also clean up visual-only boxes (not in planning scene, only RViz markers)
        for (const auto& id : visual_only_boxes_) {
            to_remove.push_back(id);

            visualization_msgs::msg::Marker marker;
            marker.header.frame_id = planning_frame_;
            marker.header.stamp = this->now();
            marker.ns = "boxes";
            marker.id = getMarkerId(id);
            marker.action = visualization_msgs::msg::Marker::DELETE;
            visual_marker_pub_->publish(marker);
        }
        visual_only_boxes_.clear();

        if (to_remove.empty()) {
            res->success = true;
            res->message = "Environment already clean (0 objects)";
            return;
        }

        std::ostringstream oss;
        oss << "Removed " << to_remove.size() << " object(s): ";
        for (size_t i = 0; i < to_remove.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << to_remove[i];
        }

        res->success = true;
        res->message = oss.str();
        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }

    bool MotionServer::applyJointConstraints(
        const std::vector<std::string>& joint_names,
        const std::vector<double>& joint_min,
        const std::vector<double>& joint_max,
        std::string& out_msg)
    {
        // No constraints requested — nothing to do
        if (joint_names.empty()) return true;

        // Validate parallel arrays
        if (joint_names.size() != joint_min.size() ||
            joint_names.size() != joint_max.size())
        {
            out_msg = "Joint constraint arrays must have equal length. "
                    "Got names=" + std::to_string(joint_names.size())
                    + " min=" + std::to_string(joint_min.size())
                    + " max=" + std::to_string(joint_max.size());
            return false;
        }

        // Validate that each named joint exists in the planning group
        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        if (!jmg) {
            out_msg = "Unknown planning group: " + planning_group_;
            return false;
        }
        const auto& group_joints = jmg->getVariableNames();
        std::set<std::string> valid_names(group_joints.begin(), group_joints.end());

        moveit_msgs::msg::Constraints constraints;

        for (size_t i = 0; i < joint_names.size(); ++i) {
            if (valid_names.find(joint_names[i]) == valid_names.end()) {
                out_msg = "Joint '" + joint_names[i]
                        + "' is not part of planning group '" + planning_group_ + "'. "
                        + "Available joints: ";
                for (const auto& n : group_joints) out_msg += n + " ";
                return false;
            }

            if (joint_min[i] >= joint_max[i]) {
                out_msg = "Invalid constraint for '" + joint_names[i]
                        + "': min (" + std::to_string(joint_min[i])
                        + ") >= max (" + std::to_string(joint_max[i]) + ")";
                return false;
            }

            moveit_msgs::msg::JointConstraint jc;
            jc.joint_name = joint_names[i];
            jc.position = (joint_min[i] + joint_max[i]) / 2.0;
            jc.tolerance_above = (joint_max[i] - joint_min[i]) / 2.0;
            jc.tolerance_below = (joint_max[i] - joint_min[i]) / 2.0;
            jc.weight = 1.0;
            constraints.joint_constraints.push_back(jc);
        }

        move_group_->setPathConstraints(constraints);

        RCLCPP_INFO(this->get_logger(),
            "[Constraints] Applied %zu joint constraint(s)", joint_names.size());
        for (size_t i = 0; i < joint_names.size(); ++i) {
            RCLCPP_INFO(this->get_logger(),
                "  %s: [%.4f, %.4f]", joint_names[i].c_str(), joint_min[i], joint_max[i]);
        }

        return true;
    }


    bool MotionServer::getJointLimits(
        std::vector<double>& joint_min,
        std::vector<double>& joint_max,
        std::vector<std::string>* joint_names,
        std::string& out_msg) const
    {
        if (!initialized_ || !move_group_) {
            out_msg = "Robot not initialized. Call /init_robot first";
            return false;
        }

        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        if (!jmg) {
            out_msg = "Unknown planning group: " + planning_group_;
            return false;
        }

        joint_min.clear();
        joint_max.clear();
        if (joint_names) joint_names->clear();

        const auto& active_joints = jmg->getActiveJointModels();
        joint_min.reserve(active_joints.size());
        joint_max.reserve(active_joints.size());
        if (joint_names) joint_names->reserve(active_joints.size());

        for (const auto* jm : active_joints) {
            const auto& bounds = jm->getVariableBounds();
            if (bounds.empty()) {
                out_msg = "Joint '" + jm->getName() + "' has no variable bounds";
                return false;
            }

            const auto& b = bounds[0];

            if (b.position_bounded_) {
                joint_min.push_back(b.min_position_);
                joint_max.push_back(b.max_position_);
            } else {
                // Continuous joint — no hard limit in URDF. Fall back to ±π.
                RCLCPP_WARN(this->get_logger(),
                    "[GetJointLimits] Joint '%s' is unbounded (continuous). "
                    "Using [-pi, pi] as a fallback.", jm->getName().c_str());
                joint_min.push_back(-M_PI);
                joint_max.push_back( M_PI);
            }

            if (joint_names) joint_names->push_back(jm->getName());
        }

        std::ostringstream oss;
        oss << "Retrieved limits for " << joint_min.size() << " joint(s): ";
        for (size_t i = 0; i < joint_min.size(); ++i) {
            if (i > 0) oss << ", ";
            if (joint_names) oss << (*joint_names)[i] << "=";
            oss << "[" << std::fixed << std::setprecision(4)
                << joint_min[i] << ", " << joint_max[i] << "]";
        }
        out_msg = oss.str();
        return true;
    }



}  // namespace motion_control
