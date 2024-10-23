#include <string.h>
#include "videoDriver.h"
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include "idtLoader.h"


extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

extern void _hlt();

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main()
{	

	load_idt();

	((EntryPoint)sampleCodeModuleAddress)();
	/*
	while (1) {
		for (int r = 0; r < 1000; r += 25) {
			for (int k = 0; k < 1000; k += 25) {
				int color = ((r / 25) + (k / 25)) % 2 == 0 ? 0x00B6E8E4 : 0x00CDF4F1;
				for (int i = 0; i < 25; i++) {
					for (int j = 0; j < 25; j++) {
						putPixel(color, i + k, j + r);
					}
				}
			}
		}
	}
	*/

	while(1){
		_hlt();
	}

	//B6E8E4 celeste mas oscuro
	//CDF4F1 celeste mas clarito
	return 0;
}
