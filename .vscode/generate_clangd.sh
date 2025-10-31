#!/usr/bin/env bash
set -e

# Verify required environment variables
if [[ -z "$DEVKITARM" || -z "$DEVKITPRO" ]]; then
  echo "Error: DEVKITARM or DEVKITPRO not set. Please export them before running this task."
  exit 1
fi

# Generate .clangd config
cat > "${PWD}/.clangd" <<EOF
CompileFlags:
  Add:
    - --sysroot=${DEVKITARM}/arm-none-eabi
  Remove:
    - -mthumb-interwork
EOF

echo ".clangd generated successfully at ${PWD}/.clangd"