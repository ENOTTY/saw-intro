#!/bin/bash

export PATH=$PATH:/opt/z3/bin:/opt/saw/bin:/opt/yices/bin

# Needed for Saw interactive to work
export LC_ALL=C.UTF-8

exec "$@"
