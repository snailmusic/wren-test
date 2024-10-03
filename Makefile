CC=zig cc

all: wrentest

wrentest: wrentest.c
	$(CC) wrentest.c -Iinclude -Llib -lwren -o wrentest

run: all
	./wrentest

clean:
	rm -f wrentest

world: clean all