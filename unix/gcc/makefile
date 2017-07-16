# Name
TARGET    = raycast
TEST      = $(TARGET)_test
NIXTARGET = lib$(TARGET)

# Compiler
CC = gcc

# Compiling flags here
CFLAGS = -std=c99 -O3 -Wall -I. -mavx2 -mfma

# Archiving command
AR = ar rcs

# File extensions
SRCEXT  = c
INCLEXT = h
OBJEXT  = o 

# Directories
ROOTDIR = ../..
SRCDIR  = $(ROOTDIR)/src
INCLDIR = $(ROOTDIR)/include
TSTDIR  = $(ROOTDIR)/test
LIBDIR  = bin
OBJDIR  = obj
BINDIR  = bin

SOEXT   = so
LIBEXT  = a

SOURCES  := $(filter-out ./$(TEST).$(SRCEXT), $(wildcard $(SRCDIR)/*.$(SRCEXT)))
INCLUDES := $(wildcard $(INCLDIR)/*.$(INCLEXT))
OBJECTS  := $(SOURCES:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.$(OBJEXT))
rm       = rm -f

# Linking flags here
LFLAGS =  -lm

$(LIBDIR)/$(NIXTARGET).$(SOEXT): $(OBJECTS)
	@$(CC) -shared -Wl,-soname,$(LIBDIR)/$(NIXTARGET).$(SOEXT) -o $@ $^ -lc -L. $(LFLAGS)
	@echo $(LIBDIR)/$(NIXTARGET).$(SOEXT)": Shared Object Archived!"

$(OBJECTS): $(OBJDIR)/%.$(OBJEXT) : $(SRCDIR)/%.$(SRCEXT)
	@$(CC) $(CFLAGS) -c $< -fPIC -o $@ -I$(INCLDIR)/
	@echo $(NIXTARGET)": Compiled "$<" successfully!"

.PHONY: static

static: $(OBJECTS)
	@$(AR) $(LIBDIR)/$(NIXTARGET).$(LIBEXT) $(OBJECTS)
	@echo $(LIBDIR)/$(NIXTARGET).$(LIBEXT)": Static Library archived!"

.PHONY: test

test:
	@$(CC) $(CFLAGS) -o $(BINDIR)/$(TEST) $(TSTDIR)/$(TEST).$(SRCEXT) -L. $(LIBDIR)/$(NIXTARGET).$(SOEXT) $(LFLAGS) -I $(INCLDIR)/
	./$(BINDIR)/$(TEST)

.PHONY: clean

clean:
	@$(rm) $(OBJDIR)/*
	@$(rm) $(LIBDIR)/*
	@$(rm) $(BINDIR)/*

	@echo "Cleanup complete!"


.PHONY: all

all:
	@make clean
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(LIBDIR)
	@make
	@make static
	@make test