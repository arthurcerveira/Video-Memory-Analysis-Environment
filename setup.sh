#!/bin/bash

# Initialize HEVC Test Model
cd hm-videomem/build/linux
make
cd ../../..

# Initialize VVC Test Model
cd vtm-mem/

DIR="./build/"
if [ -d "$DIR" ]; then
    cd build
    make
else
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make
fi
