##cat your sd card device:
        sudo fdisk -l
 you may see this:
        Partition table entries are not in disk order

        Disk /dev/mmcblk0: 7969 MB, 7969177600 bytes
        221 heads, 20 sectors/track, 3521 cylinders, total 15564800 sectors
        Units = sectors of 1 * 512 = 512 bytes
        Sector size (logical/physical): 512 bytes / 512 bytes
        I/O size (minimum/optimal): 512 bytes / 512 bytes
        Disk identifier: 0x00000000

                Device Boot      Start         End      Blocks   Id  System
        /dev/mmcblk0p1            8192    15564799     7778304    b  W95 FAT32

`/dev/mmcblk0` is your sd device. make sure your sd format is `FAT32`


###downlaod uboot to your sd card:
donwlaod the `webee210-uboot.bin` to the first block of your sd.
        # cd ~/webee210v2
        # sudo dd iflag=dsync oflag=dsync if=webee210-uboot.bin of=/dev/mmcblk0 seek=1 
        # sync


