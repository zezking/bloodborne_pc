#!/usr/bin/env bash
# Open the bbport settings launcher (GTK4 GUI): game folder, fullscreen, FPS, online, mods...
# Start there applies the same saved settings as ./bb.sh does directly.
set -euo pipefail
cd -- "$(dirname -- "$0")"

# Build-time deps in the user prefix (the launcher starts run.sh -> build.sh, which needs cmake).
export PATH="$HOME/.local/bin:$PATH"
export PKG_CONFIG_PATH="$HOME/.local/opt/bbdeps/share/pkgconfig${PKG_CONFIG_PATH:+:$PKG_CONFIG_PATH}"
export VULKAN_SDK="$HOME/.local/opt/bbdeps"
export CMAKE_PREFIX_PATH="$HOME/.local/opt/bbdeps${CMAKE_PREFIX_PATH:+:$CMAKE_PREFIX_PATH}"

exec bash launcher/bb-launcher.sh "$@"
