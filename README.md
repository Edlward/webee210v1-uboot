###参与webee210-uboot的开发

如果你想参与本__webee210-uboot__的开发,请用力hit下面的链接:

[webee210-uboot开发指南](https://github.com/iZobs/webee210-uboot/blob/master/Develop-doc.md)

###关于
这是网蜂webee210的uboot程序,下面是其主菜单:

        #####    Boot for Webee210 Main Menu    #####             
        [1] Webee210 USE_USB_DOWN Download mode                
        [2] Webee210 USE_SD_DOWN Download mode                 
        [q] quit to Command line                               
        #################################################                              

###编译

         @ make distclean
         @ make webee210_config
         @ make

###烧uboot到你的sd卡

__1.查看你的SD__:

在ubuntu下,通过下面的命令查看你的sd卡:                               

        sudo fdisk -l
下面是在ubuntu下打印的信息:                

        Partition table entries are not in disk order
        Disk /dev/mmcblk0: 7969 MB, 7969177600 bytes
        221 heads, 20 sectors/track, 3521 cylinders, total 15564800 sectors
        Units = sectors of 1 * 512 = 512 bytes
        Sector size (logical/physical): 512 bytes / 512 bytes
        I/O size (minimum/optimal): 512 bytes / 512 bytes
        Disk identifier: 0x00000000

                Device Boot      Start         End      Blocks   Id  System
        /dev/mmcblk0p1            8192    15564799     7778304    b  W95 FAT32

`/dev/mmcblk0` 是你的SD设备,确保他是`FAT32`格式的.


__2.下载uboot到你的SD卡__:                    

        # cd ~/webee210-uboot
        # sudo dd iflag=dsync oflag=dsync if=webee210-uboot.bin of=/dev/mmcblk0 seek=1 
        # sync

_注意:项目目录下有一个`sd-burn.sh`的脚本,请在执行前打开来看看里面的文件名和sd卡的路径是否和你的电脑相同._

###UBOOT 菜单

uboot有两级菜单,这是第一级.可以选择usb烧录或是SD卡烧录,或是退出到命令行模式.

        #####    Boot for Webee210 Main Menu    #####             
        [1] Webee210 USE_USB_DOWN Download mode                
        [2] Webee210 USE_SD_DOWN Download mode                 
        [q] quit to Command line                               
        #################################################                                                            

1.__USB下载模式__

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

在ubuntu,你可以从这里获得dnw烧录软件[webee-dnw](https://github.com/iZobs/webee-dnw)

2.__SD烧录模式__

        #####    Boot for Webee210 Main Menu    #####
        #####    Webee210 SD download mode     #####
        [1] Download Linux Kernel (filename:uImage) to Nand Flash from SD
        [2] Download YAFFS image (filename:webee_yaffs2_img) to Nand Flash from SD
        [3] Boot the system from Nand Flash 
        [4] Format the Nand Flash -(°□°!) 
        [q] Return to Menu 
        ################################################# 
        Enter your selection (╭￣3￣)╭ : 

在这个模式下,你可以烧录linux内核和文件系统到你的nand flash.                
不过你需要先对你的SD做一些准备工作:

__(1).查看你的SD卡__

在ubuntu下: 

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


__(2).对你的SD卡进行分区__:

先对已经存在的的分区进行卸载: 

        # umount /dev/mmcblk0p2
        # umount /dev/mmcblk0p3

用fdisk进行分区:

        # fdisk /dev/mmcblk0

        Command (m for help): 

输入 `p` 打印SD信息:

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

输入 `d` 删除分区 `/dev/mmcblk0p2`,`/dev/mmcblk0p3`:

        Command (m for help): d
        Partition number (1-4): 2
          
        Command (m for help): d
        Selected partition 3

输入 `n` 切割新分区 :           

        Command (m for help): n
        Partition type:
           p   primary (0 primary, 0 extended, 4 free)
           e   extended
        Select (default p): 

选`1`,意味着分区1:          

        Partition number (1-4, default 1): 1

为了给uboot留空间,我们从4380开始,大小为50M,存放linux内核,即uImage:              

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

同样的方式,我们来切割分区2.分区2的开始为分区1的结束blocks+1,即:106779+1.大小取决于你的yaffs2 file.             

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

输入`w`,让上面的配置生效:          

        Command (m for help): w

__(3).格式化你的分区__:

将分区格式化为 `FAT32`:

        # mkfs.vfat /dev/mmcblk0p1
            mkfs.vfat 3.0.14 (23 Jan 2023)
        # mkfs.vfat /dev/mmcblk0p2
            mkfs.vfat 3.0.14 (23 Jan 2023)

__(4)将文件直接复制到你的SD卡__

 cp linux 内核到 `/dev/mmcblk0p1`,文件系统到 `/dev/mmcblk0p2`.                  

__注意 : 确保你的 uImage 文件名为 `uImage`,yaffsz文件系统名为 `webee_yaffs2_img`__


