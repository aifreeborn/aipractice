#!/bin/bash

module="aillseek"
device="aillseek"
mode="664"
group="linux"
user="linux"

sudo /sbin/rmmod ./${module}.ko
sudo rm -f /dev/${device}
/bin/ls -l /dev/${device}
