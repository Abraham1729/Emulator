CC = gcc
CFLAGS = -Wall -Wextra -std=c99
CPPFLAGS = -I. -Iemulator
VM_SRC = emulator/vm.c
VM_OBJ = emulator/vm.o
BINDIR = bin
PROGRAMS = $(BINDIR)/arithmetic $(BINDIR)/stack_ops $(BINDIR)/loop_countdown

.PHONY: all clean

all: $(PROGRAMS)

$(BINDIR):
	mkdir -p $@

$(BINDIR)/arithmetic: programs/arithmetic.c $(VM_OBJ) | $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) programs/arithmetic.c $(VM_OBJ) -o $@

$(BINDIR)/stack_ops: programs/stack_ops.c $(VM_OBJ) | $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) programs/stack_ops.c $(VM_OBJ) -o $@

$(BINDIR)/loop_countdown: programs/loop_countdown.c $(VM_OBJ) | $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) programs/loop_countdown.c $(VM_OBJ) -o $@

$(VM_OBJ): $(VM_SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(VM_SRC) -o $@

clean:
	rm -rf $(BINDIR) $(VM_OBJ)
