# project name (generate executable with this name)
TARGET	= RayCast_Test

CC		= gcc

# compiling flags here
CFLAGS	= -std=c99 -Wall -lm -I.

LINKER	= gcc -o

# linking flags here
LFLAGS	= -Wall -lm -I.

# change these to set the proper directories where each files shoould be
ROOTDIR = ../..
SRCDIR	= $(ROOTDIR)/src
INCLDIR	= $(ROOTDIR)/include
TESTDIR = $(ROOTDIR)/test
BINDIR  = bin
OBJDIR	= obj

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS) $(LIBDIR)/$(LIB) $(LFLAGS)
	@echo $(TARGET)": Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I$(HDRDIR) -c $< -o $@
	@echo $(TARGET)": Compiled "$<" successfully!"

.PHONY: clean

clean:
	@$(rm) $(OBJDIR)/$(OBJECTS)
	@$(rm) $(BINDIR)/$(TARGET)
	@echo $(TARGET)": Cleanup complete!"

.PHONY: run

run:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)
	@mkdir -p $(LIBDIR)
	@make clean
	@make
	@$(BINDIR)/$(TARGET)