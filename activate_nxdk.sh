#!/usr/bin/env bash

export NXDK_DIR="$(dirname $(realpath "${BASH_SOURCE[0]:-$0}"))/nxdk"
export PATH="$NXDK_DIR/bin:$PATH"