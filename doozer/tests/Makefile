CC = cc
CFLAGS = -g
OUTPUT = client_test
LIB = -lprotobuf-c
SOURCES = client_test.c ../msg.pb-c.c

all: 
	$(CC) -o $(OUTPUT) $(SOURCES) $(LIB)

test: all
	./$(OUTPUT) 127.0.0.1 8046

clean:
	rm $(OUTPUT)
