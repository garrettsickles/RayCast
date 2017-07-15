# project name (generate executable with this name)
TARGET	= RayCast

# compiler
CC		= gcc

# compiling flags here
CFLAGS	= -std=c99 -O3 -Wall -lm -mavx2 -mfma

# archiving command
AR = ar rcs

# change these to set the proper directories where each files shoould be
ROOTDIR = ../..
SRCDIR	= $(ROOTDIR)/src
INCLDIR	= $(ROOTDIR)/include
TESTDIR = $(ROOTDIR)/test
BINDIR  = bin
OBJDIR	= obj

LIBEXT = a

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

rm       = rm -f

.PHONY: static

static: $(OBJECTS)
	@$(AR) $(BINDIR)/$(TARGET).$(LIBEXT) $(OBJECTS)
	@echo $(TARGET)": Library archived!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCLDIR) -c $< -o $@
	@echo $(TARGET)": Compiled "$<" successfully!"


.PHONY: clean

clean:
	@$(rm) $(OBJECTS)
	@$(rm) $(BINDIR)/$(TARGET).$(LIBEXT)

	@echo $(TARGET)": Cleanup complete!"

.PHONY: all

all:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@make clean
	@make static
	@make -f test.make run LIB=$(BINDIR)/$(TARGET).$(LIBEXT)
	