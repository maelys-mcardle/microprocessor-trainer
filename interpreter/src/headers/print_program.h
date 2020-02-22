#ifndef SNOWFLAKE_PRINT_PROGRAM_H
#define SNOWFLAKE_PRINT_PROGRAM_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

void print_program(Program *program);
void print_instruction(Program *program, Instruction *instruction);
bool print_parameter(Program *program, short current_instruction, ParameterType type, ParameterValue value);
void print_identifier(Program *program, short current_instruction, short naming_instruction, int target_identifier, char *format);
bool print_device(int device);
char *get_name(Program *program, short naming_instruction, int target_identifier);

#endif