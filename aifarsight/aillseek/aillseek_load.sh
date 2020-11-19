#!/bin/bash

module="aillseek"
device="aillseek"
mode="664"
group="linux"
user="linux"

sudo /sbin/insmod ./${module}.ko || exit 1

major=$(awk "\$2==\"${module}\" {print \$1}" /proc/devices)
echo "major: ${major}"
if [ -c /dev/${device} ];then
	sudo rm -f /dev/${device}
fi

sudo /bin/mknod /dev/${device} c ${major} 0
sudo /bin/chown ${user} /dev/${device}
sudo /bin/chgrp ${group} /dev/${device}
sudo /bin/chmod ${mode} /dev/${device}
/bin/ls -l /dev/${device}
