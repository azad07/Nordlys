#!/bin/bash
# Build script for engine
set echo on

#mkdir -pv ../bin

# set vulkan sdk path.
source /Users/ashishazad/VulkanSDK/1.3.236.0/setup-env.sh

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.c")

# echo "Files:" $cFilenames

assembly="engine"
compilerFlags="-g -shared -fdeclspec -fPIC"
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I$VULKAN_SDK/include"
linkerFlags="-lvulkan  -L$VULKAN_SDK/lib"
defines="-D_DEBUG -DNEXPORT"

echo "$(tput setaf 1)Building $assembly...$(tput setaf 7)"
clang $cFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags