#!/bin/bash

if [ ! -d tracks.anger ]; then
    git clone https://github.com/kidanger/GP_tracks.git tracks.anger
else
    cd tracks.anger
    git pull
    cd ..
fi

make -C tracks.anger
