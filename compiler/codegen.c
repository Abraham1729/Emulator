#include "codegen.h"
#include "opcodes.h"
#include <stdlib.h>

// TODO: clean up this hardcoded value too //
OpCode TokenTypeTable[TTT_SIZE];  /* maps ASCII characters to token types */
void init_ttt(void) // Does the mapping //
{
    for (int i = 0; i < TTT_SIZE; i++) TokenTypeTable[i] = OP_HALT;  /* default to 0/Halt */
    TokenTypeTable[TOK_ADD] = OP_ADD;
    TokenTypeTable[TOK_SUB] = OP_SUB;
    TokenTypeTable[TOK_MUL] = OP_MUL;
    TokenTypeTable[TOK_DIV] = OP_DIV;
    TokenTypeTable[TOK_PRINT] = OP_PRINT;
    TokenTypeTable[TOK_NUMBER] = OP_PUSH; // TODO: re-eval whether this is the right way to handle numbers... you'll still need to add an extra instuction with the numerical value, do you really want these two pieces disjoint?
    // digits & whitepsace are handled specially in the lexer, so we don't need to map them here
}

uint8_t* translate_statements(ASTNode **statements, int num_statements, int* instruction_count) {
    // TODO: figure out dynamic sizing of instructions
    // We can't cue off of num_statemnets, since the total number of instructions 
    // is going to be dependent on the number of children that they have...
    // An option would be to loop through all the statements and get a count of children
    // You could then determine the size of memory to allocate by doing 2x child count
    // This is because numbers are a PUSH + NUM (2 instr) and ops are just 1.
    // This also means at a minimum ADD 3 4 has 6 instr spaces, 5 for the math and 1 for the HALT
    // TODO: decide if I should just build this child count in the parser
    // instead of doing an extra traversal of the tree after the fact. 
    uint8_t* instructions = malloc(sizeof(uint8_t*) * MAX_INSTRUCTIONS);
    if (instructions == NULL) {
        fprintf(stderr, "unable to allocate memory for instructions array.\n");
        exit(1);
    }

    init_ttt();

    for (int i = 0; i < num_statements; i++) {
        translate_node(statements[i], instructions, instruction_count);
    }

    // TODO: Add step to free the ASTNode statement array //

    // Tack HALT to end //
    instructions[(*instruction_count)++] = OP_HALT;
    return instructions;
    // Return

}

void translate_node(ASTNode *node, uint8_t *instructions, int *instruction_count) {
    // Base case: No children //
    if (node->num_children == 0) {
        // guard on legitimate childless nodes //
        if (
            node->NodeType == TOK_PRINT || 
            node->NodeType == TOK_NUMBER
        ) {
            translate_tokentype_to_opcode(node, instructions, instruction_count);
            return;
        } else {
            fprintf(stderr, "translate_node: illigitmate childless node type %d.\n", node->NodeType);
            exit(1);
        }
    } else {
        if (node->num_children > 0) {
            // Recursive case: Evaluate children sequentially //
            for (int i = 0; i < node->num_children; i++) {
                translate_node(node->children[i], instructions, instruction_count);
            }

            // Now that children have been evaluated, add the operation to the instruction stack //
            translate_tokentype_to_opcode(node, instructions, instruction_count);            
        } else {
            fprintf(stderr,"translate_node: node of type %d has negative child count.\n", node->NodeType);
            exit(1);
        }
    }
}


// Let's make another helper to do the mapping between TokenType and OpCode in a given node... //
void translate_tokentype_to_opcode(ASTNode *node, uint8_t *instructions, int *instruction_count) {
    switch (node->NodeType) {
        case TOK_NUMBER:
            // Maps to PUSH, add numerical value on top of that
            instructions[(*instruction_count)++] = TokenTypeTable[node->NodeType];
            instructions[(*instruction_count)++] = node->value;
            break;
        default:
            instructions[(*instruction_count)++] = TokenTypeTable[node->NodeType];
            break;        
    }
}

// Given array of uint8_t opcodes, write to file in bin?
// void write_to_file(uint8_t* instructions);