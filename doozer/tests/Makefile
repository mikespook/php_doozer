CC = cc
CFLAGS = -g
OUTPUT = client_test
LIB = -lprotobuf-c
SOURCES = client_test.c ../msg.pb-c.c ../client.c
HOST = 127.0.0.1
PORT = 8046

all: 
	$(CC) -o $(OUTPUT) $(SOURCES) $(LIB)

test: all
	./$(OUTPUT) $(HOST) $(PORT)

clean:
	rm $(OUTPUT)
