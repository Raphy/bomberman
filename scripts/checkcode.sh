#!/bin/sh

command -v cppcheck 2>&1 > /dev/null
if [ $? -eq 0 ] ; then

    cppcheck src/

else
    echo "Sorry, you don't have cppcheck on your system."
    echo "Install it with apt-get or another manager."  
fi