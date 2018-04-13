CC=gcc -O2

ppm: src/main.o src/password.o
	$(CC) $^ -o $@ -lcrypto

debug: CC=gcc -g
debug: clean ppm

src/%.o: src/%.c
	$(CC) $^ -o $@ -c

.PHONY: clean debug test

test: ppm
	test/test.sh ppm

clean:
	rm src/*.o
	rm ppm
