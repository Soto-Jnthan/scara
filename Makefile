# Makefile for 8051 SDCC project

# Compiler and flags
CC = /usr/bin/sdcc
CFLAGS = -c -mmcs51 --std-sdcc2y --peep-asm -I/usr/include/mcs51 -Iinc
LFLAGS = -Wl"-u" --out-fmt-ihx -mmcs51

# Files
SRCDIR := src
BUILDDIR := build
SRC := $(wildcard $(SRCDIR)/*.c)

# Extract main.c separately
MAIN_SRC := $(SRCDIR)/main.c
MAIN_OBJ := $(BUILDDIR)/main.rel

# All other sources
OTHER_SRC := $(filter-out $(MAIN_SRC), $(SRC))
OTHER_OBJ := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.rel, $(OTHER_SRC))

# Final target
TARGET := $(BUILDDIR)/release.hex

.PHONY: all clean

all: $(TARGET)

# Ensure build dir exists
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Build rule for all .rel files
$(BUILDDIR)/%.rel: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Link everything, with main.rel first
$(TARGET): $(MAIN_OBJ) $(OTHER_OBJ)
	$(CC) $(LFLAGS) -o $@ $^

# Clean all generated files
clean:
	rm -rf $(BUILDDIR)
