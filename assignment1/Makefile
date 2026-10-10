CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGETS = client server

.PHONY: all clean

all: $(TARGETS)

client: client.c
	$(CC) $(CFLAGS) -o $@ $^

server: server.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)
