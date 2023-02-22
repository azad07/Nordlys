#!/bin/bash
# Build script for engine
set echo on

echo "Building everything..."

pushd engine
./build.sh
popd


pushd testbed
./build.sh
popd

echo "All assemblies built successfully."