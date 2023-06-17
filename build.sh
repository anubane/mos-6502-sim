#!/bin/bash

clear
echo "Begin project build..."

echo "Checking if build directory exists..."

if [ -d "build" ]; then
    echo "'build' directory found"
else
    mkdir -p build
fi

cd build

echo "preparing the makefiles via cmake..."
cmake -DCMAKE_BUILD_TYPE=Debug ..

echo "building the project..."
make
