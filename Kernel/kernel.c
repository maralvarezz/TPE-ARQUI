#include"./include/kernel.h"

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
		char c;
		int hours=sys_hours();
		char *s3= numToStr(hours-3,2);
		driver_print(s3,2);
		driver_print(":",1);
		int minutes=sys_minutes();
		char *s= numToStr(minutes,2);
		driver_print(s,2);
		driver_print(":",1);
		int seconds=sys_seconds();
		char *s2= numToStr(seconds,2);
		driver_print(s2,2);
		driver_print("\n",1);
		sys_cursor();
		*/
		while(1){
			_hlt();
			//c = getChar();
		}
		

	/*driver_print("hola iNGRESE UN MENSAJE\n",24);
	for(int i=0;i<7;i++){
		driver_read(buffer);
		driver_print("\n",1);
	}
	//driver_read(buffer);
	//sys_wait(50);
	driver_read(buffer,20);
		for(int j=0;j<1;j++){
		for(int i=0;i<49;i++){
			driver_print("holaholaholaholaholaholaholaholaholaholaholahola",50-i);
			driver_print("\n",1);
		}
	}*/
	//driver_print("holaholaholaholaholaholaholaholaholaholaholahola",50);
	//driver_clear();
	//driver_print("holaholaholaholaholaholaholaholaholaholaholahola",50);
	

	//driver_print(buffer,20);

	//B6E8E4 celeste mas oscuro
	//CDF4F1 celeste mas clarito
	return 0;
}
