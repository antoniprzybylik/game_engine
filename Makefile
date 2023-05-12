.PHONY: all clean build debug
.SUFFIXES: .o .cpp

TARGET = libengine.a

CXX = g++
LINK = ld

CXXFLAGS = -MMD -MP -std=c++20 -Wall -pedantic

OBJS = \
engine.o \
sprite_skin.o \
sprite.o \
game_window.o \
algebra.o \
font_arial.o \

DEPS = $(OBJS:%.o=%.d)

all: build

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	ar r $(TARGET) $(OBJS)
	ranlib $(TARGET)

debug: CXXFLAGS += -DGLIBCXX_DEBUG -g
debug: clean | compile
	ar r $(TARGET) $(OBJS)
	ranlib $(TARGET)

clean:
	rm -f $(OBJS) $(DEPS)

%.o : %.cpp
	$(CXX) $< -o $@ -c $(CXXFLAGS)

%.o : %.ttf
	$(LINK) -r -b binary $< -o $@

-include $(DEPS)
