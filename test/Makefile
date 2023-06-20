LIBO2S_PATH = ..

CPPFLAGS += -I $(LIBO2S_PATH)/include
CPPFLAGS += $(shell pkg-config --cflags-only-I *.pc)
CFLAGS   += $(shell pkg-config --cflags-only-other *.pc)
LDFLAGS  += $(shell pkg-config --libs-only-L *.pc)
LDLIBS   += $(shell pkg-config --libs-only-l *.pc)
