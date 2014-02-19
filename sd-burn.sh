#!/bin/bash
echo "burning to SD card.............."
sudo dd iflag=dsync oflag=dsync if=webee210-uboot.bin of=/dev/mmcblk0 seek=1
echo "sync........."
sync
echo  "DONE-( ͡° ͜ʖ ͡° )✧-YAP!"
