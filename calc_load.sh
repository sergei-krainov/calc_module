#!/bin/sh

MODULE=calc
DEVICE=calc-dev
MODE=644

if [ "$1" = ""  -o \( "$2" != "" \) ]
then
    echo "Usage: $0 start|stop"
    exit 1
fi

case $1 in
start)
    echo "Starting module $MODULE.ko"
    /sbin/insmod $MODULE.ko || exit 1
    
    rm -f /dev/$DEVICE
    MAJOR=$(awk -v mod=$DEVICE '$2 == mod {print $1}' /proc/devices)
    
    mknod /dev/$DEVICE c $MAJOR 0
    
    GROUP="staff"
    grep -q '^staff:' /etc/group || GROUP="wheel"
    
    chgrp $GROUP /dev/$DEVICE
    chmod $MODE /dev/$DEVICE
    ;;
stop)
    echo "Stopping module $MODULE.ko"
    /sbin/rmmod $MODULE.ko
    rm -f /dev/$DEVICE
    ;;
*)
    echo "*Usage: $0 start|stop"
;;
esac
