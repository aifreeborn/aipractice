#!/bin/bash

module="scull"
device="scull"
mode="664"
group="linux"
user="linux"

sudo /sbin/insmod ./${module}.ko $* || exit 1

major=$(awk "\$2==\"${module}\" {print \$1}" /proc/devices)
echo "major: ${major}"
sudo rm -f /dev/${device}[0-3]
for i in {0..3}
do
	sudo /bin/mknod /dev/${device}${i} c ${major} ${i}
done
sudo /bin/chown ${user} /dev/${device}[0-3]
sudo /bin/chgrp ${group} /dev/${device}[0-3]
sudo /bin/chmod ${mode} /dev/${device}[0-3]
/bin/ls -l /dev/${device}[0-3]
