#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <string.h>
#include "videoDriver.h"
#include "lib.h"
#include "moduleLoader.h"
#include "naiveConsole.h"
#include "idtLoader.h"
#include "keyboard.h"
#include "libraryC.h"

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

#endif

