#!/bin/bash
# Build script for testbed
set echo on

mkdir -p ../bin

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.cpp")

# echo "Files:" $cFilenames

assembly="testbed"
compilerFlags="-g -fdeclspec -fPIC -std=c++17" 
includeFlags="-Isrc -I../overture/src/ -I../overture/deps/include/"
linkerFlags="-L../bin/ -loverture -Wl,-rpath,. -lstdc++ -lm -lbgfx"
defines="-D_DEBUG -DIMPORT -DBX_CONFIG_DEBUG"
#defines="-DIMPORT"

echo "Building $assembly..."
echo clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
