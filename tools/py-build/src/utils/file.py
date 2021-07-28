import errno
import os
import shutil
import sys

from typing import List
from pathlib import Path

from utils.logger import log

def get_file_list(path: Path, pattern: str) -> List[Path]:
    return sorted(path.glob(pattern))

# Deletes `path` and all subdirectories (if there are any)
def delete_dir(root: Path):
    if root.exists():
        # Remove root file.
        try:
            if root.is_symlink() or root.is_file():
                log.warning('Deleting file: ', path=root)
                root.unlink()
            elif root.is_dir():
                for path in os.listdir(root):
                    file = root / path

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
        except FileNotFoundError as err:
            log.error('Failed to remove file: ', path=root)
            log.error(f'{err}')
        except BlockingIOError:
            log.error('File busy or being handled by another process: ', path=root)
            sys.exit(os.strerror(errno.EBUSY))
