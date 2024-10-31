#include "libraryUser.h"
#include "snakes.h"
#include <stdint.h>

extern void invalidopcode();

extern void divzero();

void command_help();

void command_time();

void command_clear();

void command_modifyuser();

void command_registers();

void command_divzero();

void command_invalidopcode();

void command_snakes();

void command_username();

void command_exit();

void entry();

void printUserDef();

void terminal();

void noCommand();

void readLine();

void checkCommand(char*  c);

void check();

char * getCommand();

void putLine();

void printUserDef();

void command_reducesize();

void command_increasesize();