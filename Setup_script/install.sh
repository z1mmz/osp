#!/bin/sh
module="driver"
device="chard"
mode="777"
# invoke insmod with all arguments we got
# and use a pathname, as newer modutils don't look in . by default
/sbin/insmod ./$module.ko $* || exit 1
# remove stale nodes
rm -f /dev/${device}
major=$(awk "\$2==\"$device\" {print \$1}" /proc/devices)

echo $major
mknod /dev/${device} c $major 0

chmod $mode  /dev/${device}
