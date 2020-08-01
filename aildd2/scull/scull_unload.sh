#!/bin/bash

module="scull"
device="scull"

sudo /sbin/rmmod ./${module}.ko $* || exit 1
sudo rm -f /dev/${device}[0-3]
