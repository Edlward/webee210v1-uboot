###ABOUT

 This u-boot is get form the web,and rewrites for webee210 by [izobs](https://http://izobs.github.io/),here is the menu of the uboot

                #####    Boot for Webee210 Main Menu    #####                                                                             
                #####    Webee210 USB download mode     #####                                                                             
                [1] Download U-boot to Nand Flash                                                                                         
                [2] Download Linux Kernel (uImage.bin) to Nand Flash                                                                      
                [3] Download YAFFS image (root.bin) to Nand Flash                                                                         
                [4] Download Program to SDRAM and Run it                                                                                  
                [5] Boot the system from Nand Flash                                                                                       
                [6] Boot the system from SD Card                                                                                          
                [7] Format the Nand Flash -(°□°!)                                                                                         
                [q] Return to uboot command mode                                                                                          
#################################################  

###USAGE
         @ make distclean
         @ make webee210_config
         @ make

###DOWNLAOD

__cat your sd card device__:                    

        sudo fdisk -l
__you may see this in ubuntu__:                  

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


__downlaod uboot to your sd card__:                    
donwlaod the `webee210-uboot.bin` to the first block of your sd.     
        # cd ~/webee210v2
        # sudo dd iflag=dsync oflag=dsync if=webee210-uboot.bin of=/dev/mmcblk0 seek=1 
        # sync


