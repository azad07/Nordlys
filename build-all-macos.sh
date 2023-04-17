#!/bin/bash
# Build script for rebuilding everything
set echo on

# TODO: fix this.
cd /Users/ashishazad/Desktop/Nordlys/Nordlys

echo "Building everything..."

# set vulkan sdk path.
source /Users/ashishazad/VulkanSDK/1.3.236.0/setup-env.sh


make -f Makefile.engine.macos.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.testbed.macos.mak all
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "All assemblies built successfully."