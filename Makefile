CC = g++
CFLAGS = -Wall -g
LDFLAGS =
OBJFILES = build/cipsp.o build/patcher.o build/util.o
VPATH = src
OBJDIR = build
TARGET = cipsp
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(TARGET) output *~