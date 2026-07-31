#!/usr/bin/env python3

###
# Downloads various tools from GitHub releases.
#
# Usage:
#   python3 tools/download_tool.py wibo build/tools/wibo --tag 1.0.0
#
# If changes are made, please submit a PR to
# https://github.com/encounter/dtk-template
###

import argparse
import hashlib
import io
import os
import platform
import shutil
import stat
import urllib.request
import zipfile
from typing import Callable, Dict
from pathlib import Path


def binutils_url(tag):
    uname = platform.uname()
    system = uname.system.lower()
    arch = uname.machine.lower()
    if system == "darwin":
        system = "macos"
        arch = "universal"
    elif arch == "amd64":
        arch = "x86_64"

    repo = "https://github.com/encounter/gc-wii-binutils"
    return f"{repo}/releases/download/{tag}/{system}-{arch}.zip"


def compilers_url(tag: str) -> str:
    return f"https://files.decomp.dev/compilers_{tag}.zip"


def dtk_url(tag: str) -> str:
    uname = platform.uname()
    suffix = ""
    system = uname.system.lower()
    if system == "darwin":
        system = "macos"
    elif system == "windows":
        suffix = ".exe"
    arch = uname.machine.lower()
    if arch == "amd64":
        arch = "x86_64"

    repo = "https://github.com/ChimpsAtSea/jeff" 
    return f"{repo}/releases/download/{tag}/dtk-{system}-{arch}{suffix}"


def objdiff_cli_url(tag: str) -> str:
    uname = platform.uname()
    suffix = ""
    system = uname.system.lower()
    if system == "darwin":
        system = "macos"
    elif system == "windows":
        suffix = ".exe"
    arch = uname.machine.lower()
    if arch == "amd64":
        arch = "x86_64"

    repo = "https://github.com/encounter/objdiff"
    return f"{repo}/releases/download/{tag}/objdiff-cli-{system}-{arch}{suffix}"


def sjiswrap_url(tag: str) -> str:
    repo = "https://github.com/encounter/sjiswrap"
    return f"{repo}/releases/download/{tag}/sjiswrap-windows-x86.exe"


def wibo_url(tag: str) -> str:
    repo = "https://github.com/decompals/wibo"
    return f"{repo}/releases/download/{tag}/wibo"


TOOLS: Dict[str, Callable[[str], str]] = {
    "binutils": binutils_url,
    "compilers": compilers_url,
    "dtk": dtk_url,
    "objdiff-cli": objdiff_cli_url,
    "sjiswrap": sjiswrap_url,
    "wibo": wibo_url,
}

def discard(path: Path) -> None:
    try:
        path.unlink()
    except OSError:
        pass  # still in use, a later download will clean it up


def same_contents(a: Path, b: Path) -> bool:
    try:
        if a.stat().st_size != b.stat().st_size:
            return False
        with open(a, "rb") as f:
            digest_a = hashlib.sha256(f.read()).digest()
        with open(b, "rb") as f:
            digest_b = hashlib.sha256(f.read()).digest()
    except OSError:
        return False
    return digest_a == digest_b


def replace_locked(src: Path, dst: Path) -> None:
    try:
        os.replace(src, dst)
        return
    except PermissionError:
        pass

    # The destination is in use -- a running dtk.exe, an antivirus scan, an
    # editor holding it open. If it already holds exactly what we downloaded,
    # keep it and just freshen its timestamp so the build system stops
    # considering it out of date.
    if same_contents(src, dst):
        discard(src)
        try:
            dst.touch()
        except OSError:
            pass
        print(f"{dst} is in use but already up to date, keeping it")
        return

    # On Windows a running executable cannot be overwritten, but it can usually
    # be renamed out of the way. Move the old file aside, put the new one in
    # place, then delete the old one once nothing holds it open any more.
    for index in range(16):
        stale = dst.with_name(f"{dst.name}.old{index if index else ''}")
        try:
            if stale.exists():
                stale.unlink()
            os.replace(dst, stale)
        except OSError:
            continue
        try:
            os.replace(src, dst)
        except OSError:
            os.replace(stale, dst)  # put the original back
            break
        discard(stale)
        return

    discard(src)
    raise PermissionError(f"{dst} is in use and could not be replaced")


def download(url, response, output) -> None:
    output.parent.mkdir(parents=True, exist_ok=True)
    if url.endswith(".zip"):
        data = io.BytesIO(response.read())
        with zipfile.ZipFile(data) as f:
            f.extractall(output)
        # Make all files executable
        for root, _, files in os.walk(output):
            for name in files:
                os.chmod(os.path.join(root, name), 0o755)
        output.touch(mode=0o755)  # Update dir modtime
    else:
        # The pid keeps concurrent builds from fighting over one scratch file.
        temporary = output.with_name(f"{output.name}.{os.getpid()}.download")
        with open(temporary, "wb") as f:
            shutil.copyfileobj(response, f)
        st = os.stat(temporary)
        os.chmod(temporary, st.st_mode | stat.S_IEXEC)
        try:
            replace_locked(temporary, output)
        except OSError as e:
            discard(temporary)
            if not output.exists():
                raise
            try:
                output.touch()
            except OSError:
                pass
            print(f"WARNING: {e}, keeping the existing {output}")

def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("tool", help="Tool name")
    parser.add_argument("output", type=Path, help="output file path")
    parser.add_argument("--tag", help="GitHub tag", required=True)
    args = parser.parse_args()

    url = TOOLS[args.tool](args.tag)
    output = Path(args.output)

    print(f"Downloading {url} to {output}")
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    try:
        with urllib.request.urlopen(req) as response:
            download(url, response, output)
    except urllib.error.URLError as e:
        if str(e).find("CERTIFICATE_VERIFY_FAILED") == -1:
            raise e
        try:
            import certifi
            import ssl
        except:
            print("\"certifi\" module not found. Please install it using \"python -m pip install certifi\".")
            return
            
        with urllib.request.urlopen(req, context=ssl.create_default_context(cafile=certifi.where())) as response:
            download(url, response, output)

if __name__ == "__main__":
    main()
