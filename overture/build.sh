#!/bin/bash
# Build script for the engine
set echo on

mkdir -p ../bin

# Get a list of all the .cpp files.
cFilenames=$(find . -type f -name "*.cpp")

assembly="overture"
compilerFlags="-g -shared -fdeclspec -fPIC -std=c++17" 
includeFlags="-Isrc -Ideps/include"
linkerFlags="-lstdc++ -lglfw -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp -lvulkan -lbgfx"
defines="-D_DEBUG -DEXPORT -DBX_CONFIG_DEBUG"
#defines="-DEXPORT"

echo "Building $assembly..."
clang $cFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags
