.PHONY: all clean build debug
.SUFFIXES: .o .cpp

PROJECT = test

CXX = g++
LINK = g++
STRIP = strip

CXXFLAGS = -MMD -MP -Wall -O3
LDFLAGS = -fPIC -lsfml-graphics -lsfml-window -lsfml-system

OBJS = \
main.o \
engine.o \
sprite_skin.o \
sprite.o \
game_window.o \
algebra.o \

DEPS = $(OBJS:%.o=%.d)

all: build

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	$(LINK) $(OBJS) -o $(PROJECT) $(LDFLAGS)
	$(STRIP) $(PROJECT)

debug: CXXFLAGS += -DGLIBCXX_DEBUG -g
debug: LDFLAGS += -fsanitize=undefined,address
debug: clean | compile
	$(LINK) $(OBJS) -o $(PROJECT) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(DEPS)

.cpp.o:
	$(CXX) $< -o $@ -c $(CXXFLAGS)

-include $(DEPS)
