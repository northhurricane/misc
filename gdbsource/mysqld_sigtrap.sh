#!/bin/bash

echo "signal mysqld trap"

PROCESS_ID=`ps -ef | grep mysqld | grep -v 'bash' | grep -v 'grep' | awk '{print $8 " " $2}' | grep mysqld | awk '{print $2}'`


PROCESS_EXIST=`echo $PROCESS_ID | wc -l`
if [ $PROCESS_EXIST -eq 1 ]
then
  echo "mysqld process id is "$PROCESS_ID
else
  echo "process not exist"
  exit 1
fi

echo "sending signal trap"
sudo kill -s SIGTRAP $PROCESS_ID


