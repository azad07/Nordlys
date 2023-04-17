#!/bin/bash
# Build script for engine
set echo on
# TODO: fix this.
cd /Users/ashishazad/Desktop/Nordlys/Nordlys

echo "$(tput setaf 1)Building everything.....$(tput setaf 7)"

pushd engine
./build.sh
popd

pushd testbed
./build.sh
popd

echo "All assemblies built successfully."