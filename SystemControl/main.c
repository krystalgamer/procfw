#include <pspsdk.h>
#include <pspsysmem_kernel.h>
#include <pspkernel.h>
#include <psputilsforkernel.h>
#include <pspsysevent.h>
#include <pspiofilemgr.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "utils.h"
#include "systemctrl.h"
#include "printk.h"

PSP_MODULE_INFO("SystemControl", 0x3007, 1, 0);

u32 psp_model = 0;
u32 psp_fw_version = 0;

void fill_vram(u32 color)
{
	u32 *p = (u32*)0x44000000;

	while (p < (u32*)0x44200000) 
		*p++ = color;
}

int module_start(SceSize args, void* argp)
{
	fill_vram(0x000000ff);
	psp_model = sceKernelGetModel();
	psp_fw_version = sceKernelDevkitVersion();
	
	printk_init(NULL);
	printk("SystemControl: model 0%dg FW 0x%08X\n", psp_model+1, psp_fw_version);

	syspatch_init();

	return 0;
}
