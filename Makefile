all: build
debug: build.debug

test: debug
	gcc -g -fsanitize=address test/main.c target/debug/mem_mam.o -o target/test/test.out

test.run: test
	./target/test/test.out

build: gen_folders
	gcc -c src/mem_mam.c -o target/lib/mem_mam.o

build.debug: gen_folders.debug
	gcc -c -g -fsanitize=address src/mem_mam.c -o target/debug/mem_mam.o

.SILENT:
.IGNORE:
gen_folders:
	mkdir target
	mkdir target/lib

gen_folders.debug:
	mkdir target
	mkdir target/debug
	mkdir target/test

clean:
	rm -rf target
