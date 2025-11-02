PROJECT_NAME := Application
CC		:= gcc
SRCDIR	:= src
BUILDDIR  := build
TARGET	:= $(PROJECT_NAME)
SOURCES   := $(shell find $(SRCDIR) -type f -name *.c)
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
DEPS	  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .d,$(basename $(SOURCES))))
CFLAGS	:= -std=c2x -Wall -D_GNU_SOURCE -g
LIB	   := -lSDL3 -lSDL3_image -lSDL3_ttf
INC	   :=

GREEN=`tput setaf 2`
RESET=`tput sgr0`

define print_green
	@echo "$(GREEN)$(1)$(RESET)"
endef

all: $(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

$(TARGET): $(BUILDDIR) $(OBJECTS)
	$(call print_green,"Linking object files...")
	@$(CC) $(OBJECTS) -o $(TARGET) $(LIB)
	$(call print_green,"$(TARGET) has been created!")

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

-include $(DEPS)

.PHONY: clean all