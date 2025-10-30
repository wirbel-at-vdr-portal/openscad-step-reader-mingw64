# Makefile for mingw64.
# Install first opencascade: pacman -S mingw-w64-x86_64-opencascade


CPPFLAGS=-I./include -I/mingw64/include/opencascade -D_USE_MATH_DEFINES=1 -Wfatal-errors
CXXFLAGS=-std=c++11 -g -O0

# all dlls installed by pacman for package 'mingw-w64-x86_64-opencascade',
# see pacman -Ql mingw-w64-x86_64-opencascade
# unfortunally, opencascade doesnt have pkgconfig support.
TKDLLS_W_EXT = $(sort $(wildcard /mingw64/bin/libTK*.dll))
TKDLLS_WO_EXT=$(TKDLLS_W_EXT:.dll=)
OPENCASCADE_DLLS=$(subst /mingw64/bin/lib,-l,$(TKDLLS_WO_EXT))


LDFLAGS=-lm -lfreetype -pthread -lstdc++ $(OPENCASCADE_DLLS)
SOURCES := $(sort $(wildcard *.cpp))
OBJS     = $(SOURCES:.cpp=.o)

all: openscad-step-reader

openscad-step-reader: $(OBJS)
	g++ $(OBJS) -o openscad-step-reader $(LDFLAGS)


# some manual dependency tracking for each object file:
openscad-step-reader.o: openscad-step-reader.cpp triangle.h tessellation.h openscad-triangle-writer.h explore-shape.h

tessellation.o: tessellation.cpp tessellation.h triangle.h

openscad-triangle-writer.o: openscad-triangle-writer.cpp openscad-triangle-writer.h triangle.h

explore-shape.o: explore-shape.cpp explore-shape.h


.PHONY: clean
clean:
	rm -f $(OBJS) openscad-step-reader openscad-step-reader.exe


testdll:
	@echo $(DLLS)
