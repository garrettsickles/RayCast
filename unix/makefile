# Name
TARGET = raycast
TEST   = $(TARGET)_test

# Compiling flags here
CFLAGS = -std=c99 -O3 -Wall -mavx2 -mfma
LFLAGS = -lm

# Commands
MD = mkdir -p
RM = rm -f
AR = ar rcs

# File extensions
SRCEXT = c
INCEXT = h
OBJEXT = o 
LIBEXT = a
SOEXT  = so

# Directories
ROTDIR = ..
SRCDIR = $(ROTDIR)/src
INCDIR = $(ROTDIR)
TSTDIR = $(ROTDIR)/test
CCDIR  = $(CC)
LIBDIR = $(CC)/lib
OBJDIR = $(CC)/obj
BINDIR = $(CC)/bin

TESTS    := $(wildcard $(TSTDIR)/*.$(SRCEXT))
SOURCES  := $(wildcard $(SRCDIR)/*.$(SRCEXT))
INCLUDES := $(wildcard $(INCDIR)/*.$(INCLEXT))
TSTOBJS  := $(TESTS:$(TSTDIR)/%.$(SRCEXT)=$(OBJDIR)/%.$(OBJEXT))
SRCOBJS  := $(SOURCES:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.$(OBJEXT))

# Names
SONAME  = lib$(TARGET).$(SOEXT)
LIBNAME = lib$(TARGET).$(LIBEXT)

lib: $(SRCOBJS)
	@$(CC) -shared -Wl,-soname,$(SONAME) -o $(LIBDIR)/$(SONAME) $^ -lc $(LFLAGS)
	@$(AR) $(LIBDIR)/$(LIBNAME) $(SRCOBJS)
	@echo $(LIBNAME)": Static Library Archived!"
	@echo $(SONAME)": Shared Object Archived!"

$(SRCOBJS): $(OBJDIR)/%.$(OBJEXT) : $(SRCDIR)/%.$(SRCEXT)
	@$(CC) $(CFLAGS) -fPIC -I$(INCDIR) -c $< -o $@
	@echo $(TARGET)": Compiled "$<" successfully!"

clean:
	@$(RM) $(OBJDIR)/*
	@$(RM) $(LIBDIR)/*
	@$(RM) $(BINDIR)/*
	@echo "Cleanup complete!"

setup:
	@$(MD) $(CCDIR)
	@$(MD) $(BINDIR)
	@$(MD) $(OBJDIR)
	@$(MD) $(LIBDIR)

rebuild:
	@make setup CC=$(CC)
	@make clean CC=$(CC)
	@make lib CC=$(CC)
	
test: $(TSTOBJS)
	@make rebuild CC=$(CC)
	@$(CC) -L$(LIBDIR) -Wl,-rpath=$(LIBDIR) $(CFLAGS) -o $(BINDIR)/$(TEST) $(TSTDIR)/$(TEST).$(SRCEXT) -l$(TARGET) $(LFLAGS) -I$(INCDIR)
	./$(BINDIR)/$(TEST)

$(TSTOBJS): $(OBJDIR)/%.$(OBJEXT) : $(TSTDIR)/%.$(SRCEXT)
	@$(CC) $(CFLAGS) -fPIC -I$(INCDIR) -c $< -o $@
	@echo $(TARGET)": Compiled "$<" successfully!"