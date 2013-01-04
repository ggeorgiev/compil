#!/bin/bash
if [ "$1" = "clean" ]
then
    git clean -f -d -x
fi