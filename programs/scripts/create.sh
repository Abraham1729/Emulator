mkdir -p apps
./bin/write_program
echo "Running programs in ./apps:"
echo "----------------------------"
echo "Arithmetic Program:"
./bin/run_program ./apps/arithmetic
echo "Jump Program:"
./bin/run_program ./apps/jump_demo
echo "Loop Program:"
./bin/run_program ./apps/loop_countdown
echo "Stack Program:"
./bin/run_program ./apps/stack_ops