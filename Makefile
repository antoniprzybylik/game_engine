.PHONY: all clean build debug tests run-tests
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

all: build | tests

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	rm -f $(TARGET)
	ar r $(TARGET) $(OBJS)
	ranlib $(TARGET)

debug: CXXFLAGS += -DGLIBCXX_DEBUG -g
debug: clean | compile
	rm -f $(TARGET)
	ar r $(TARGET) $(OBJS)
	ranlib $(TARGET)

tests:
	make -C tests/

run-tests:
	make run -C tests/

clean:
	rm -f $(OBJS) $(DEPS)

%.o : %.cpp
	$(CXX) $< -o $@ -c $(CXXFLAGS)

%.o : %.ttf
	$(LINK) -r -b binary $< -o $@

-include $(DEPS)
