PROJ_ROOT:=$(shell pwd)
PROJ_NAME:=appexe

LIBS:=-lraylib -lm
INCS:=-I$(PROJ_ROOT)/source -I$(PROJ_ROOT)/source/engine
BUILDIR:=$(PROJ_ROOT)/build
OBJDIR:=$(BUILDIR)/obj

CC:=cc
CFLAGS:=-Wall -Wextra -Wno-unused-parameter -fPIC
DEFINES:=-DPLATFORM_LINUX
BUILD_CONFIG:=dev

TARGET:=$(PROJ_ROOT)/$(PROJ_NAME)
SRCDIR:=$(PROJ_ROOT)/source
SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

GAMEDLTARGET:=$(BUILDIR)/libgame.so
GAMESRCDIR:=$(SRCDIR)/gamedl
GAMESRC:=$(shell find $(GAMESRCDIR) -iname '*.c')
GAMEOBJS:=$(patsubst $(wildcard */%.c), $(OBJDIR)/%.o, $(GAMESRC))
GAMEINL:=$(wildcard $(GAMESRCDIR)/*.inl)

ENGINETARGET:=$(BUILDIR)/libengine.so
ENGINESRCDIR:=$(SRCDIR)/engine
ENGINESRC:=$(shell find $(ENGINESRCDIR) -iname '*.c')
ENGINEOBJS:=$(patsubst $(wildcard */%.c), $(OBJDIR)/%.o, $(ENGINESRC))


# build configuration detection ###################################################
# default build config is development unless specified at make runtime
# e.g., make TARGET_CONFIG=release clean all
ifeq ($(TARGET_CONFIG), debug)
BUILD_CONFIG=debug
else ifeq ($(TARGET_CONFIG), release)
BUILD_CONFIG=release
endif

ifeq ($(BUILD_CONFIG), dev)
CFLAGS += -g -ggdb
DEFINES += -DHOTRELOAD
else ifeq ($(BUILD_CONFIG), debug)
CFLAGS += -g -O2
else ifeq ($(BUILD_CONFIG), release)
CFLAGS += -O3
endif


.PHONY: all
all: clean $(ENGINETARGET) $(TARGET) $(GAMEDLTARGET)

.PHONY: game
game: $(GAMEDLTARGET)

$(GAMEDLTARGET): $(GAMEOBJS) $(ENGINETARGET) $(GAMEINL)
	@echo "making $@"
	@$(CC) $(CFLAGS) $(INCS) -shared -o $@ $< $(DEFINES) $(LIBS) -ldl

$(OBJDIR)/%.o: $(GAMESRCDIR)/%.c | build-dirs
	@echo "making $@"
	@$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(DEFINES) $(LIBS)

$(ENGINETARGET): $(ENGINEOBJS)
	@echo "making $@"
	@$(CC) $(CFLAGS) $(INCS) -shared -o $@ $^ $(DEFINES) $(LIBS)

$(OBJDIR)/%.o: $(ENGINESRCDIR)/%.c | build-dirs
	@echo "making $@"
	@$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(DEFINES) $(LIBS)

$(TARGET): $(OBJS) $(ENGINETARGET)
	@echo "making $@"
	@$(CC) $(CFLAGS) $(INCS) -o $@ $^ $(DEFINES) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | build-dirs
	@echo "making $@"
	@$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(DEFINES) $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(GAMEDLTARGET) $(ENGINETARGET)

.PHONY: build-dirs
build-dirs:
	@mkdir -p $(OBJDIR)
