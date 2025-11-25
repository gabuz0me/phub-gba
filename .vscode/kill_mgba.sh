#!/bin/bash
if [ -f .mgba_pid ]; then
  kill $(cat .mgba_pid)
  rm .mgba_pid
fi