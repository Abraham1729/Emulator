# Compile program loader & executor #
cd ./programs
./scripts/run.sh
cd ..

# Compile compiler & use compiled compiler to compile compiled src code as .bin #
cd ./compiler
./scripts/run.sh
cd ..

# Run compiled emulator and pass in compiled .bin which was compiled with the compiled compiler #
./programs/bin/run_program "./compiler/apps/output.bin"

# cleanup pass #
cd ./programs
./scripts/cleanup.sh
cd ..

cd ./compiler
./scripts/cleanup.sh
cd ..