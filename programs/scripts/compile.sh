mkdir -p ./bin
gcc -I ./hardcoded -I ../emulator write_program.c bytefiles.c -o ./bin/write_program
gcc -I ./ -I ../emulator ../emulator/vm.c bytefiles.c run_program.c -o ./bin/run_program