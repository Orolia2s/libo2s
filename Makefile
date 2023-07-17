##
 # Simple Makefile
 #
 # Performs the minimal amount of steps required to generate a given file
 #
 # Features:
 #  - Auto rebuild when headers are modified
 #  - Store intermediate objects in a separate folder
 #  - Self-documented
##

Name    := libo2s
Static  := $(Name).a
Shared  := $(Name).so
Version ?= $(shell git tag --sort '-version:refname' --merged | head -1)

ImplementationFolder := src
InterfaceFolder      := include
TestFolder           := test
BuildFolder          := cache
Subfolders           != find $(ImplementationFolder) -type d

CFLAGS   += -Wall -Wextra
CPPFLAGS += -DLIBO2S_VERSION=$(Version)
CPPFLAGS += -I $(InterfaceFolder)
CPPFLAGS += -MMD

Sources != find $(ImplementationFolder) -type f -name '*.c'
Objects := $(Sources:$(ImplementationFolder)/%.c=$(BuildFolder)/%.o)

Tester  := $(TestFolder)/test_libo2s.exe

# When rendering the help, pretty print certain words
Cyan       := \033[36m
Yellow     := \033[33m
Bold       := \033[1m
EOC        := \033[0m
PP_command := $(Cyan)
PP_section := $(Bold)

##@ General

default: help ## When no target is specified, display the usage

help: ## Display this help.
	@awk 'BEGIN {FS = ":.*##"; printf "\nThis Makefile allows one to setup their machine, build, run and test this ublox parser.\n\nUsage:\n  make $(PP_command)<target>$(EOC)\n"} /^[a-zA-Z_0-9-]+:.*?##/ { printf "  $(PP_command)%-15s$(EOC) %s\n", $$1, $$2 } /^##@/ { printf "\n$(PP_section)%s$(EOC):\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

raw_help: ## Display the help without color
	@$(MAKE) help --no-print-directory PP_COMMAND= PP_SECTION= EOC=

version: ## Display the project's version
	@echo $(Version)

info: ## Print the project's name, version, copyright notice and author
	@echo $(Name) version $(Version)
	@echo
	@echo "Copyright (C) 2023 Orolia Systemes et Solutions"
	@echo
	@echo Written by A. Gagniere, H. Folcher

.PHONY: default help raw_help version info

##@ Building

static: $(Static) ## Compile the static library

shared: $(Shared) ## Compile the shared library. Appropriate compilation flags like -fPIC needs to have been set

.PHONY: static shared

##@ Developping

test: $(Tester)
	./$<

format: $(Sources)
	echo $^ | xargs -L1 clang-format -i
	find $(ImplementationFolder) $(InterfaceFolder) -type f -name '*.h' | xargs -L1 clang-format -i

.PHONY: test

##@ Cleaning

clean: ## Remove intermediate objects
	$(RM) -r $(BuildFolder)

fclean: clean ## Remove all generated files
	$(RM) $(Static) $(Shared)

.PHONY: clean fclean

# Non phony rules

include $(wildcard $(Objects:.o=.d)) # To know on which header each .o depends

$(Subfolders:$(ImplementationFolder)%=$(BuildFolder)%): # Create the build folder and its subfolders
	mkdir -p $@

$(Objects): $(BuildFolder)/%.o: $(ImplementationFolder)/%.c # declare the dependency between objects sources

$(Static): $(Objects) # Group all the compiled objects into an indexed archive
	$(AR) rcs $@ $^

$(Shared): $(Objects) # Create a shared object
	$(CC) $(CFLAGS) -shared $^ $(LDFLAGS) $(LDLIBS) -o $@

$(Tester): $(Static)
	$(MAKE) -C $(@D) conan_build

.PHONY: $(Tester)

# When a rule is expanded, both the target and the prerequisites
# are immediately evaluated. Enabling a second expansion allows
# a prerequisite to use automatic variables like $@, $*, etc
.SECONDEXPANSION:

$(Objects): | $$(@D) # Compile a single object
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
