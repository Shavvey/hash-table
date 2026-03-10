CC=gcc
FLAGS=-W -Wall -g
# Exec name
EXEC=htab
# Object files that will be linked together
OBJS=src/main.o src/hash.o

all: $(EXEC)

# Create the final exec
$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(CFLAGS) $(LDFLAGS)
 
# Compile each object file from their source file
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)
