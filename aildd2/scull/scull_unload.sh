#!/bin/bash

module="scull"
device="scull"

sudo /sbin/rmmod ${module} $* || exit 1
sudo rm -f /dev/${device}[0-3]
sudo rm -f /dev/${device}pipe[0-3]
