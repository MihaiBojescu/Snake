SRCDIR=./src
BUILDDIR=./build

CC=g++
LD=g++
GLLIBS=-lGL -lglut

TARGET=Snake

.PHONY: all
all: $(TARGET)

$(TARGET):
	$(CC) $(SRCDIR)/* $(GLLIBS) -o $(BUILDDIR)/$@

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/$(TARGET) $(OBJECTS)
