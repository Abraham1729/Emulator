CC = gcc
CFLAGS = -Wall -Wextra -std=c99
CPPFLAGS = -I. -Iemulator
VM_SRC = emulator/vm.c
VM_OBJ = emulator/vm.o
BINDIR = bin
PROGRAMS := $(patsubst programs/%.c,%,$(wildcard programs/*.c))
TARGETS := $(addprefix $(BINDIR)/,$(PROGRAMS))

.PHONY: all clean

all: $(TARGETS)

$(BINDIR):
	mkdir -p $@

$(BINDIR)/%: programs/%.c $(VM_OBJ) | $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(VM_OBJ) -o $@

$(VM_OBJ): $(VM_SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(VM_SRC) -o $@

clean:
	rm -rf $(BINDIR) $(VM_OBJ)
