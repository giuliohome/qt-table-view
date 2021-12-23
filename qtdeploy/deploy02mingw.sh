#!/bin/bash

ldd FirstApp.exe | grep mingw | while read -r line ; do
    IN=$line
    arrIN=(${IN// => / })
    depLIB=${arrIN[1]}
    echo $depLIB
    cp $depLIB . 
    # mingw dependency dll copied
done

