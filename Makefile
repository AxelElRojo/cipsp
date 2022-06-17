CC = g++
CFLAGS = -Wall -g
LDFLAGS =
VPATH = src
OBJDIR = build
TARGET = cipsp

SOURCES = $(shell find $(VPATH) -type f -name *.cpp)
OBJECTS = $(patsubst $(VPATH)/%,$(OBJDIR)/%,$(SOURCES:.cpp=.o))

all: $(TARGET)

$(TARGET): $(OBJDIR)/$(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

$(OBJDIR)/$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)
	mv *.o $(OBJDIR)

clean:
	rm -f $(OBJECTS) $(TARGET) output *~