#include "libraryUser.h"
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

void check(int i);

char * getCommand(int i);

void putLine();

void printUserDef();