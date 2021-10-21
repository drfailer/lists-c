CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=-fPIC -shared -lc

testprog: main_test.c liblist.c
	$(CC) $(CFLAGS) -o $@ $^

liblist.so: liblists.c lists.h
	$(CC) $(LDFLAGS) -o $@ liblists.c

clean:
	rm *.o liblist.so
