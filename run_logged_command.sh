#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 4 ]; then
  echo "Usage: $0 <log_stamp> <title> <keep_open:0|1> <base64_command>" >&2
  exit 2
fi

LOG_STAMP="$1"
TITLE="$2"
KEEP_OPEN="$3"
CMD_B64="$4"

SAFE_TITLE="$(printf '%s' "$TITLE" | tr '[:upper:]' '[:lower:]' | sed 's/[^a-z0-9]/_/g')"
SAFE_TITLE="$(printf '%s' "$SAFE_TITLE" | sed 's/_\+/_/g; s/^_//; s/_$//')"

LOG_DIR="$HOME/workspace/launch_logs"
LOG_FILE="$LOG_DIR/${LOG_STAMP}_${SAFE_TITLE}.log"

mkdir -p "$LOG_DIR"
CMD="$(printf '%s' "$CMD_B64" | base64 -d)"

set +e
bash -lc "$CMD" 2>&1 | tee "$LOG_FILE"
EXIT_CODE=${PIPESTATUS[0]}
set -e

echo
echo "Process exited with code ${EXIT_CODE}. Log: ${LOG_FILE}"

if [ "$KEEP_OPEN" = "1" ]; then
  exec bash
fi

exit "$EXIT_CODE"
