#!/bin/bash
# Build script for the engine
set echo on

mkdir -p ../bin

# Get a list of all the .cpp files.
cFilenames=$(find . -type f -name "*.cpp")

assembly="spectre"
compilerFlags="-g -shared -fdeclspec -fPIC" 
includeFlags="-Isrc"
linkerFlags="-lstdc++"
defines="-D_DEBUG -DEXPORT"

echo "Building $assembly..."
clang $cFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags