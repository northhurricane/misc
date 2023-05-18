#!/bin/bash

#测试
#1、空参数；2、带参数；3、是否等于
#判断参数是否为空。针对测试1，2
echo "First arg is ${1}"
echo "Test 1"
if [ "X${1}" != "X" ]
then
  echo "1"
else
  echo "2"
fi

#判断参数内容
echo "Test 2"
if [ "${1}" == "a" ];
then
  echo "1"
else
  echo "2"
fi
