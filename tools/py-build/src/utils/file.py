from pathlib import Path
from typing import List
import errno
import os
import shutil
import sys

from utils.logger import log

# Returns a list of globbed files.
def get_file_list(path: Path, pattern: str) -> List[Path]:
    return sorted(path.glob(pattern))


# Deletes `path` and all subdirectories (if there are any)
def delete_dir(file: Path):
    if file.exists():
        try:
            if file.is_symlink() or file.is_file():
                log.warning('Deleting file: ', path=file)
                file.unlink()
            elif file.is_dir():
                log.warning('Deleting directory: ', path=file)
                shutil.rmtree(file)
        except FileNotFoundError as err:
            log.error('Failed to remove file: ', path=file)
            log.error(f'{err}')
        except BlockingIOError:
            log.error('File busy or being handled by another process: ', path=file)
            sys.exit(os.strerror(errno.EBUSY))
