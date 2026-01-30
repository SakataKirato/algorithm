CC = gcc
CFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lgmp

TARGET = a.out
SRC = 2a-3.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean