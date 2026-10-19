#!/usr/bin/env bash
# Launch Bloodborne through bbport with the settings saved by the GUI launcher
# (launcher/bbport_launcher.py --play: loads ~/.config/bbport-launcher/settings.json,
# checks the game folder and execs run.sh — Steam Deck game mode uses the same path).
#
# Usage: ./bb.sh [options passed to run.sh]   (e.g. --software for Lavapipe)
# Env:   BB_* variables set here win over the launcher's saved settings.
set -euo pipefail
cd -- "$(dirname -- "$0")"

# Always save this run's log and per-frame stats to logs/ (GUI-proof: env wins when the
# launcher's Save log switch is off).
export BB_SAVE_LOG=${BB_SAVE_LOG:-1}

# Build-time deps in the user prefix (cmake in ~/.local/bin; libs in ~/.local/opt/bbdeps).
# run.sh re-invokes build.sh incrementally, so these must be set.
export PATH="$HOME/.local/bin:$PATH"
export PKG_CONFIG_PATH="$HOME/.local/opt/bbdeps/share/pkgconfig${PKG_CONFIG_PATH:+:$PKG_CONFIG_PATH}"
export VULKAN_SDK="$HOME/.local/opt/bbdeps"
export CMAKE_PREFIX_PATH="$HOME/.local/opt/bbdeps${CMAKE_PREFIX_PATH:+:$CMAKE_PREFIX_PATH}"

# --play: the game directly, no settings window. Says where to pick the game folder if unset.
exec bash launcher/bb-launcher.sh --play "$@"
