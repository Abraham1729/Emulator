#ifndef CODEGEN_H
#define CODEGEN_H
#include "parser.h"
#include <stdint.h>
#include "opcodes.h"

#define MAX_INSTRUCTIONS 1024
#define TTT_SIZE 32

// 1 to translate the statements into machine code
uint8_t* translate_statements(ASTNode **statements, int num_statements, int *instruction_count);

void translate_node(ASTNode *node, uint8_t *instructions, int *instruction_count);

// 1 to write the translated results to file
void write_to_file(uint8_t* instructions);

// We need to make a similar lookup table for tokentype -> opcode since we don't have dicts //
// TODO: review MAX_ENUM_VALUE enum as an option for removing this hardcoded dep //
extern OpCode TokenTypeTable[TTT_SIZE];  /* maps TokenType enum to OpCodes */
void init_ttt(void); // Does the mapping //

// Helper which leverages TTT to retrieve OpCode //
void translate_tokentype_to_opcode(ASTNode *node, uint8_t *instructions, int *instruction_count);

#endif // CODEGEN_H