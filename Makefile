CC = g++
CFLAGS = -Wall -g
LDFLAGS =
OBJFILES = cipsp.o patcher.o util.o
TARGET = cipsp
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) output *~
test:
	./cipsp fe4.smc naga7.ips
	shasum fe4.smc; shasum output