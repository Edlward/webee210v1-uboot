列出你SD卡的信息:
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

将`/dev/mmcblk0p2 `和`/dev/mmcblk0p3 `等卸载
# umount /dev/mmcblk0p2
# umount /dev/mmcblk0p3
开始使用fdisk 操作SD卡
# fdisk /dev/mmcblk0

Command (m for help): 

输入p,打印sd信息:

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
输入d删除/dev/mmcblk0p2,/dev/mmcblk0p3,他们对应part2,part3

Command (m for help): d
Partition number (1-4): 2

Command (m for help): d
Selected partition 3

用n新建分区
Command (m for help): n
Partition type:
   p   primary (0 primary, 0 extended, 4 free)
   e   extended
Select (default p): 
这里选p,然后进入分区.SD卡可以分为4个part,我们先分part 1:

Partition number (1-4, default 1): 1
默认是从2048开始的,为了给uboot留意下空间大于20M,这里没关系.我们从4380开始.大小为50M,存放linux kernel.
First sector (2048-15564799, default 2048): 4380
Last sector, +sectors or +size{K,M,G} (4380-15564799, default 15564799): +50M
输入p查看:
Command (m for help): p

Disk /dev/mmcblk0: 7969 MB, 7969177600 bytes
4 heads, 16 sectors/track, 243200 cylinders, total 15564800 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

        Device Boot      Start         End      Blocks   Id  System
/dev/mmcblk0p1            4380      106779       51200   83  Linux

接下来分part2,存放yaffs2文件系统,可以大一些:

Command (m for help): n
Partition type:
   p   primary (1 primary, 0 extended, 3 free)
   e   extended
Select (default p): p
Partition number (1-4, default 2): 2
First sector (2048-15564799, default 2048): 106780

这的起始地址选part1的结束的地址+1就可以了,即:106779+1.我的SD卡是8G的,所以我给他分配了2G
这个可以自己分配
然后输入p:
Disk /dev/mmcblk0: 7969 MB, 7969177600 bytes
4 heads, 16 sectors/track, 243200 cylinders, total 15564800 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

        Device Boot      Start         End      Blocks   Id  System
/dev/mmcblk0p1            4380      106779       51200   83  Linux
/dev/mmcblk0p2          106780     4301083     2097152   83  Linux
最后输入w,完成分配
Command (m for help): w
分区完的SD是没有格式的,我们需要将他格式化为FAT32,因为我们的uboot支持这个格式

# mkfs.vfat /dev/mmcblk0p1
    mkfs.vfat 3.0.14 (23 Jan 2023)
# mkfs.vfat /dev/mmcblk0p2
    mkfs.vfat 3.0.14 (23 Jan 2023)

加入你的系统支持自动挂载,此时sd的分区就会被挂.接下来烧入uboot,
sudo dd iflag=dsync oflag=dsync if=webee210-uboot.bin of=/dev/mmcblk0 seek=1
将你的uImage拷贝到分区1/dev/mmcblk0p1,yaffs2 到分区2//dev/mmcblk0p2 
这样前期准备工作完成,接下来只需要通过uboot的SD下载模式烧到nand flash即可!

