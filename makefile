SRCDIR=src/*.cpp
INCLUDEDIR=includes/*.h
BUILDDIR=./build

CC=g++
GLLIBS=-lGL -lGLU -lGLEW -lglfw

TARGET=Snake

.PHONY: all
all: $(TARGET)

$(TARGET):
	$(CC) -I$(INCLUDEDIR) $(SRCDIR) $(GLLIBS) -o $(BUILDDIR)/$@
    
.PHONY: clean
clean:
	rm -f $(BUILDDIR)/$(TARGET) $(OBJECTS)
