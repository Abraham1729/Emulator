// Need to write raw bytes to file in same directory so I can demonstrate that run_program works as intended //
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bytefiles.h"
#include "arithmetic.h"
#include "jump_demo.h"
#include "stack_ops.h"
#include "loop_countdown.h"

int main(void) {
    // Jump Demo //
    size_t bytesize = sizeof(jump_demo_program[0]);
    size_t length = sizeof(jump_demo_program) / bytesize;
    write_bytes_to_file("output/jump_demo", jump_demo_program, length);

    // Arithmetic //
    length = sizeof(arithmetic_program) / bytesize;
    write_bytes_to_file("output/program", arithmetic_program, length);

    // Stack Ops //
    length = sizeof(stack_ops_program) / bytesize;
    write_bytes_to_file("output/stack_ops", stack_ops_program, length);
 
    // Loop Countdown //
    length = sizeof(loop_countdown_program) / bytesize;
    write_bytes_to_file("output/loop_countdown", loop_countdown_program, length);

    return 0;
}