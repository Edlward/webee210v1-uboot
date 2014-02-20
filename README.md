###ABOUT

 This u-boot is get form the web,and rewrites for webee210 by [izobs](https://izobs.github.io),here is the main menu of the uboot


        #####    Boot for Webee210 Main Menu    #####             
        [1] Webee210 USE_USB_DOWN Download mode                
        [2] Webee210 USE_SD_DOWN Download mode                 
        [q] quit to Command line                               
        #################################################                              

###USAGE
         @ make distclean
         @ make webee210_config
         @ make

###DOWNLOAD

__1.cat your sd card device__:                    

        sudo fdisk -l
__2.you may see this in ubuntu__:                  

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


__3.downlaod uboot to your sd card__:                    
donwlaod the `webee210-uboot.bin` to the first block of your sd.

        # cd ~/webee210v2
        # sudo dd iflag=dsync oflag=dsync if=webee210-uboot.bin of=/dev/mmcblk0 seek=1 
        # sync


###UBOOT MENU

As the meun showed,there are two download mode of the menu

        #####    Boot for Webee210 Main Menu    #####             
        [1] Webee210 USE_USB_DOWN Download mode                
        [2] Webee210 USE_SD_DOWN Download mode                 
        [q] quit to Command line                               
        #################################################                                                            

1.__the USB download mode__

        #####    Webee210 USB download mode     #####         
        [1] Download U-boot to Nand Flash                
        [2] Download Linux Kernel (uImage.bin) to Nand Flash              
        [3] Download YAFFS image (root.bin) to Nand Flash                
        [4] Download Program to SDRAM and Run it               
        [5] Boot the system from Nand Flash                       
        [6] Boot the system from SD Card(support ext2 filesystem only)                 
        [7] Format the Nand Flash -(°□°!)                          
        [q] Return to Menu  
        ################################################# 
        Enter your selection (╭￣3￣)╭ : 

In linux,your can get the dnw tool from there [webee-dnw](https://github.com/iZobs/webee-dnw)

2.__the SD download mode__

        #####    Boot for Webee210 Main Menu    #####
        #####    Webee210 SD download mode     #####
        [1] Download Linux Kernel (filename:uImage) to Nand Flash from SD
        [2] Download YAFFS image (filename:webee_yaffs2_img) to Nand Flash from SD
        [3] Boot the system from Nand Flash 
        [4] Format the Nand Flash -(°□°!) 
        [q] Return to Menu 
        ################################################# 
        Enter your selection (╭￣3￣)╭ : 

In this mode,you can download the linux kernel and the yaffs2 file-system to the nand flash by SD card.
But you should do something to your SD card first:

__(1).Cat Your SD__

here is my SD card on ubuntu: 

        # sudo du
        # fdisk -l
           Disk /dev/mmcblk0: 7969 MB, 7969177600 bytes
            4 heads, 16 sectors/track, 243200 cylinders, total 15564800 sectors
            Units = sectors of 1 * 512 = 512 bytes
            Sector size (logical/physical): 512 bytes / 512 bytes
            I/O size (minimum/optimal): 512 bytes / 512 bytes
            Disk identifier: 0x00000000

                Device Boot      Start         End      Blocks   Id  System
        /dev/mmcblk0p2           43008      247807      102400   83  Linux
        /dev/mmcblk0p3          247808    15564799     7658496   83  Linux


__(2).Parted your SD card__:

we should ummout the dev that we going to delete: 

        # umount /dev/mmcblk0p2
        # umount /dev/mmcblk0p3

here we start:

        # fdisk /dev/mmcblk0

        Command (m for help): 

type `p` to get info

        Command (m for help): p
        Disk /dev/mmcblk0: 7969 MB, 7969177600 bytes
        4 heads, 16 sectors/track, 243200 cylinders, total 15564800 sectors
        Units = sectors of 1 * 512 = 512 bytes
        Sector size (logical/physical): 512 bytes / 512 bytes
        I/O size (minimum/optimal): 512 bytes / 512 bytes
        Disk identifier: 0x00000000
            
        Device Boot      Start         End      Blocks   Id  System
        /dev/mmcblk0p2           43008      247807      102400   83  Linux
        /dev/mmcblk0p3          247808    15564799     7658496   83  Linux

type `d` to delete `/dev/mmcblk0p2`,`/dev/mmcblk0p3`:

        Command (m for help): d
        Partition number (1-4): 2
          
        Command (m for help): d
        Selected partition 3

type `n` to get the new part we want:

        Command (m for help): n
        Partition type:
           p   primary (0 primary, 0 extended, 4 free)
           e   extended
        Select (default p): 

we should choose `p` ,and then `1` to get part 1:

        Partition number (1-4, default 1): 1

the default block is start from 2048,in order to make room for uboot,wo start from 4380.and the size is 50MB.We are going to put the linux kernel here:

        First sector (2048-15564799, default 2048): 4380
        Last sector, +sectors or +size{K,M,G} (4380-15564799, default 15564799): +50M
                
        Command (m for help): p
        
        Disk /dev/mmcblk0: 7969 MB, 7969177600 bytes
        4 heads, 16 sectors/track, 243200 cylinders, total 15564800 sectors
        Units = sectors of 1 * 512 = 512 bytes
        Sector size (logical/physical): 512 bytes / 512 bytes
        I/O size (minimum/optimal): 512 bytes / 512 bytes
        Disk identifier: 0x00000000
           
                Device Boot      Start         End      Blocks   Id  System
        /dev/mmcblk0p1            4380      106779       51200   83  Linux

using the same way,wo just get the part 2,which we going to put the yaffs2 file.the start block of part 2 should be the end of part1 plus 1,and that is:106779+1.the size is depend on your yaffs2 file.

        Command (m for help): n
        Partition type:
           p   primary (1 primary, 0 extended, 3 free)
           e   extended
        Select (default p): p
        Partition number (1-4, default 2): 2
        First sector (2048-15564799, default 2048): 106780

        Disk /dev/mmcblk0: 7969 MB, 7969177600 bytes
        4 heads, 16 sectors/track, 243200 cylinders, total 15564800 sectors
        Units = sectors of 1 * 512 = 512 bytes
        Sector size (logical/physical): 512 bytes / 512 bytes
        I/O size (minimum/optimal): 512 bytes / 512 bytes
        Disk identifier: 0x00000000

                Device Boot      Start         End      Blocks   Id  System
        /dev/mmcblk0p1            4380      106779       51200   83  Linux
        /dev/mmcblk0p2          106780     4301083     2097152   83  Linux

the make it work,we should type `w`,and we will get the Partition we want

        Command (m for help): w

__(3).Format Your Partition__:

format the Partition of SD into `FAT32`:

        # mkfs.vfat /dev/mmcblk0p1
            mkfs.vfat 3.0.14 (23 Jan 2023)
        # mkfs.vfat /dev/mmcblk0p2
            mkfs.vfat 3.0.14 (23 Jan 2023)

__(4)Put the file into SD__

just copy the uImage file to `/dev/mmcblk0p1`,and the yaffs2 file to `/dev/mmcblk0p2`.                            
__warning: make sure the filename of your  uImage file is `uImage`,and yaffs2 file is `webee_yaffs2_img`__


