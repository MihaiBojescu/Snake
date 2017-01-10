SRCDIR=src/*.cpp
INCLUDES=-Iincludes/*.h -I/usr/include/freetype2
BUILDDIR=./build

CC=g++
GLLIBS=-lGL -lGLU -lGLEW -lglfw
LIBS=-lfreetype
LINKS=-L/usr/lib

TARGET=Snake

.PHONY: all
all: $(TARGET)

$(TARGET):
	$(CC) $(INCLUDES) $(SRCDIR) $(GLLIBS) $(LIBS) -o $(BUILDDIR)/$@

debug:
	$(CC) $(INCLUDES) $(SRCDIR) $(GLLIBS) $(LIBS) -o $(BUILDDIR)/SnakeDebug -D DEBUG -g

debugShaders:
	$(CC) $(INCLUDES) $(SRCDIR) $(GLLIBS) $(LIBS) -o $(BUILDDIR)/SnakeDebug -D DEBUG_SHADERS -g
    
.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*
