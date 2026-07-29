import logging
import os
import textwrap
from datetime import datetime
from logging.handlers import RotatingFileHandler
from pathlib import Path
from typing import Optional

# ROS 2 log level mapping to Python logging levels
_ROS_TO_PY_LEVEL = {
    10: logging.DEBUG,
    20: logging.DEBUG,
    30: logging.WARNING,
    40: logging.ERROR,
    50: logging.CRITICAL,
}

LOGGER_NAME = "MotionBridge"
DEFAULT_LOG_DIR = Path(__file__).resolve().parent / "log"


class WrappingFormatter(logging.Formatter):
    """Wraps long log lines, indenting continuation lines to align with the message start."""

    def __init__(self, fmt, datefmt=None, width=200):
        super().__init__(fmt, datefmt)
        self.width = width

    def format(self, record):
        full = super().format(record)

        if len(full) <= self.width:
            return full

        msg_start = full.find(record.message)
        if msg_start == -1:
            return full

        prefix = full[:msg_start]
        indent = " " * len(prefix)
        max_msg_width = self.width - len(prefix)

        result_lines = []
        for i, line in enumerate(record.message.split("\n")):
            wrapped = textwrap.fill(
                line,
                width=max_msg_width,
                initial_indent="" if i == 0 else indent,
                subsequent_indent=indent,
            )
            result_lines.append(wrapped)

        return prefix + "\n".join(result_lines)


def get_logger() -> logging.Logger:
    """Returns the singleton logger. Safe to call before setup_logger()."""
    return logging.getLogger(LOGGER_NAME)


def _resolve_path(log_path: Optional[str]) -> Path:
    if log_path:
        directory = Path(log_path).expanduser()
    else:
        directory = DEFAULT_LOG_DIR
    directory.mkdir(parents=True, exist_ok=True)
    return directory

def _resolve_name(log_name: Optional[str], add_date: bool = False,
                  date_fmt: str = "%Y-%m-%d") -> str:
    stamp = datetime.now().strftime(date_fmt)

    if log_name:
        base, ext = os.path.splitext(log_name)
        name = f"{base}_{stamp}{ext}" if add_date else log_name
    else:
        name = f"log_robot_{stamp}"

    if not os.path.splitext(name)[1]:
        name += ".log"
    return name

def setup_logger(
    log_path: Optional[str] = None,
    log_name: Optional[str] = None,
    level=logging.DEBUG,
    console: bool = True,
    add_date: bool = False,
    date_fmt: str = "%Y-%m-%d",
    max_bytes: int = 5 * 1024 * 1024,
    backup_count: int = 3,
    width: int = 200,
) -> logging.Logger:
    """
    (Re)configures the MotionBridge logger.

    log_path : directory for the log file. Defaults to this module's directory.
    add_date : si True, insère un horodatage dans le nom fourni via log_name.
               Sans effet sur le nom par défaut, qui contient toujours la date.
    date_fmt : format de l'horodatage (ex: "%Y-%m-%d_%H-%M-%S" pour un fichier
               par lancement du serveur).
    log_name : file name. Defaults to log_robot_YYYY-MM-DD.log
    level    : logging level, as an int or a string ("DEBUG", "INFO", ...).
    """
    if isinstance(level, str):
        level = getattr(logging, level.upper(), logging.DEBUG)

    directory = _resolve_path(log_path)
    filename = _resolve_name(log_name, add_date=add_date, date_fmt=date_fmt)
    full_path = directory / filename

    logger = get_logger()
    logger.setLevel(level)

    # Idempotent: drop previous handlers so a second call doesn't duplicate output
    for handler in list(logger.handlers):
        logger.removeHandler(handler)
        handler.close()

    formatter = WrappingFormatter(
        "%(asctime)s - %(levelname)s - %(message)s", width=width
    )

    if console:
        console_handler = logging.StreamHandler()
        console_handler.setFormatter(formatter)
        logger.addHandler(console_handler)

    file_handler = RotatingFileHandler(
        full_path, maxBytes=max_bytes, backupCount=backup_count
    )
    file_handler.setFormatter(formatter)
    logger.addHandler(file_handler)

    logger.info(f"Logger initialized -> {full_path} (level={logging.getLevelName(level)})")
    return logger