#!/bin/bash
# Build script for the engine
set echo on

mkdir -p ../bin

# Get a list of all the .cpp files.
cFilenames=$(find . -type f -name "*.c*")

assembly="overture"
compilerFlags="-g -shared -fdeclspec -fPIC" 
includeFlags="-Isrc -Ideps/include -Ideps/glad/include"
linkerFlags="-lstdc++ -lglfw -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp -lGL"
defines="-D_DEBUG"

echo "Building $assembly..."
echo "clang $cFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags"
clang $cFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags
