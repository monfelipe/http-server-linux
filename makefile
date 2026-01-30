CC      := clang
CFLAGS  := -Wall -Wextra -O2

CLIENT_DIR := client
SERVER_DIR := server

CLIENT_BIN := $(CLIENT_DIR)/main
SERVER_BIN := $(SERVER_DIR)/main

CLIENT_SRC := $(CLIENT_DIR)/main.c
SERVER_SRC := $(SERVER_DIR)/main.c

.PHONY: all client server clean

all: client server

client: $(CLIENT_BIN)

server: $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $< -o $@

$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(CLIENT_BIN) $(SERVER_BIN)
