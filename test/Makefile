# Input files
SOURCE_PATH := .
SOURCES     != find $(SOURCE_PATH) -type f -name '*.cpp'

# Generated files
NAME        := test_libo2s.exe
BUILD_PATH  := cache
OBJECTS     := $(SOURCES:$(SOURCE_PATH)/%.cpp=$(BUILD_PATH)/%.o)

# Dependency
LIBO2S_PATH := ..
LIBO2S      := $(LIBO2S_PATH)/libo2s.a

# Compilation
CXXFLAGS    += -g -Wall -Wextra
CPPFLAGS    += -I $(LIBO2S_PATH)/include
LDFLAGS     += -L $(LIBO2S_PATH)
LIBS        ?= -lCatch2Main -lCatch2 # Conan sets it, nix doesn't
LDLIBS      += -lo2s
LDLIBS      += $(LIBS)

CONAN_ENV := conanbuild.sh

##@ Compilation

conan_build: $(CONAN_ENV)
	bash -c "( . $< && $(MAKE) --no-print-directory build )"

build: $(NAME)

##@ Cleaning

clean:
	$(RM) -r $(BUILD_PATH)

fclean: clean
	$(RM) $(NAME)

# Non phony rules

$(BUILD_PATH):
	mkdir -p $@

$(NAME): $(OBJECTS) $(LIBO2S)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

$(LIBO2S):
	$(MAKE) -C $(@D) $(@F)

$(CONAN_ENV):
	conan install .

.SECONDEXPANSION:

$(OBJECTS): $(BUILD_PATH)/%.o: %.cpp | $$(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
