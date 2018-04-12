CC=gcc -O2

ppm: src/main.o src/password.o
	$(CC) $^ -o $@ -lcrypto

debug: CC=gcc -g
debug: ppm

src/%.o: src/%.c
	$(CC) $^ -o $@ -c

.PHONY: clean debug

clean:
	rm src/*.o
	rm ppm
