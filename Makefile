CFLAGS=-std=c99 -pedantic -Wall
LDFLAGS=-lpthread

sleepsort: sleepsort.o
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) *.o sleepsort
