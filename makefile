ppm: src/main.o src/password.o
	gcc $^ -o $@ -lcrypto

src/%.o: src/%.c
	gcc $^ -o $@ -lcrypto -c

.PHONY: clean

clean:
	rm src/*.o
	rm ppm
