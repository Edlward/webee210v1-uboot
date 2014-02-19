/*
 *  MEUN create by izobs 
 * 	E-mail:ivincentlin@gmail.com
 */



#include <common.h>
#include <command.h>
#include <nand.h>

#ifdef CONFIG_CMD_MENU

extern char console_buffer[];
extern int readline (const char *const prompt);


#define USE_USB_DOWN		1


/*keyboard scan*/
char awaitkey(void)     
{
                                                              
    int i;
                                                     
    char c;
                                  
    while (1) 
	{
                                            
		if (tstc()) /* we got a key press	*/
              
		return getc();
                                 
    }
                                                                                       
    return 0;                                               
}

void main_menu_usage(char menu_type)
{

	printf("\r\n#####	 Boot for Webee210 Main Menu	#####\r\n");

	if( menu_type == USE_USB_DOWN)
	{
		printf("#####    Webee210 USB download mode     #####\r\n\n");
	}
	printf("[1] Download program to Nand Flash\r\n");
	printf("[2] Download Linux Kernel (uImage.bin) to Nand Flash\r\n");
	printf("[3] Download YAFFS image (root.bin) to Nand Flash\r\n");
	printf("[4] Download Program to SDRAM and Run it\r\n");
	printf("[5] Boot the system from  nand flash \r\n");
	printf("[6] Boot the system from  SD card \r\n");
	printf("[7] Format the Nand Flash -(°□°!) \r\n");
	printf("[q] Return to uboot command mode -（╯－＿－）╯╧╧  \r\n");
	printf("################################################# \r\n\n");
	printf("Enter your selection (╭￣3￣)╭ : ");
}


void menu_shell(void)
{
	char keyselect;
	char cmd_buf[200];

	while (1)
	{
		main_menu_usage(USE_USB_DOWN);
		keyselect = awaitkey();
		printf("%c\n", keyselect);
		switch (keyselect)
		{
			case '1':
			{
				/*  Usbd-otg-hs.c (arch\arm\cpu\armv7):			setenv("filesize",buf); */
				/*  $(filesize) is the size of  dnw download file */
				printf("[1] Download program to Nand Flash\r\n");
				strcpy(cmd_buf, "dnw 0x20000000; nand erase 0x0 0x80000; nand write 0x20000000 0x0 $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}

			case '2':
			{

				printf("[2] Download Linux Kernel (uImage.bin) to Nand Flash\r\n");
				strcpy(cmd_buf, "dnw 0x20000000; nand erase 0x100000 0x300000; nand write 0x20000000 0x100000 $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}


			case '3':
			{
				printf("[3] Download YAFFS image (root.bin) to Nand Flash\r\n");
				strcpy(cmd_buf, "dnw 0x20000000; nand erase  0x600000 0x12c00000; nand write.yaffs 0x20000000 0x600000 $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}

			case '4':
			{
				char addr_buff[12];
				printf("Enter download address:(eg: 0x20000000)\n");
				readline(NULL);
				strcpy(addr_buff,console_buffer);
				sprintf(cmd_buf, "dnw %s;go %s", addr_buff, addr_buff);
				run_command(cmd_buf, 0);
				break;
			}

			case '5':
			{

				printf("Start Linux ...\n");
				printf("\n");
				printf("Boot the linux (YAFFS2)\n");
				strcpy(cmd_buf, "setenv bootargs noinitrd root=/dev/mtdblock2 init=/linuxrc console=ttySAC0,115200 rootfstype=yaffs2 mem=512M");
				run_command(cmd_buf, 0);
				strcpy(cmd_buf, "setenv bootcmd 'nand read 0x20007fc0 0x100000 0x500000;bootm 0x20007fc0'; save");
				run_command(cmd_buf, 0);
				strcpy(cmd_buf, "nand read 0x20007fc0 0x100000 0x500000");
				run_command(cmd_buf, 0);
				strcpy(cmd_buf, "bootm 0x20007fc0");
				run_command(cmd_buf, 0);
				break;
			}

			case '6':
			{
				printf("Start Linux from SD card .....\n");
				break;
			}

			case '7':
			{
				strcpy(cmd_buf, "nand erase.chip ");
				run_command(cmd_buf, 0);
				break;
			}

			case 'Q':
			case 'q':
			{
				return;	
				break;
			}
		}
				
	}
}

int do_menu (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	menu_shell();
	return 0;
}

U_BOOT_CMD(
	menu,	CONFIG_SYS_MAXARGS,	0,	do_menu,
	"display a menu, to select the items to do something",
	"\n"
	"\tdisplay a menu, to select the items to do something"
);

#endif

