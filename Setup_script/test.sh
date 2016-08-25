#!/bin/sh
module="chard"
device="chard"
mode="777"

major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

echo $major
