CC = cc
CFLAGS = -Wall -Wextra

# Targets
CLIENT = chat_client
SERVER = chat_server

# Source files
CLIENT_SRC = client.c utils.c
SERVER_SRC = server.c utils.c

# Object files
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

# Default build: both client and server
all: $(CLIENT) $(SERVER)

# Build client
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Build server
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(CLIENT) $(SERVER)

# Rebuild
re: clean all
