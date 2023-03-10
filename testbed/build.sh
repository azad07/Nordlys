#!/bin/bash
# Build script for engine
set echo on

mkdir -pv ../bin

# set vulkan sdk path.
source /Users/ashishazad/VulkanSDK/1.3.236.0/setup-env.sh

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.c")

# echo "Files:" $cFilenames

assembly="testbed"
compilerFlags="-g "
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I$VULKAN_SDK/include -I../engine/src"
linkerFlags="-L./../bin/ -lengine"
defines="-D_DEBUG -DIEXPORT"

echo "Building $assembly..."
clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags