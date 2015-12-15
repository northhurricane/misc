#!/bin/bash

FILES="`git status | grep 'modified:' | grep -v '../'`"
echo $FILES
#PURE_FILES=`echo $FILES | awk -F' ' '{print $NF}'`
PURE_FILES=`echo $FILES | sed "s/# modified:/ /g" `
#echo $PURE_FILES
git add $PURE_FILES
