#!/bin/bash
mGBA --gdb "$1"
echo $! > .mgba_pid