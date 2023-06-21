LIBO2S_PATH := ..
LIBO2S      := $(LIBO2S_PATH)/libo2s.a

NAME        := test_libo2s.exe

SOURCES     != find . -type f -name '*.cpp'
OBJECTS     := $(SOURCES:.cpp=.o)

CPPFLAGS += -I $(LIBO2S_PATH)/include
LDFLAGS  += -L $(LIBO2S_PATH)
LDLIBS   += -lo2s
LDLIBS   += $(LIBS)

build: $(NAME)

clean:
	$(RM) $(OBJECTS)

$(NAME): $(OBJECTS) | $(LIBO2S)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(LIBO2S):
	$(MAKE) -C $(@D) $(@F)
