SHELL := /bin/bash

all: build
debug: build.debug

install: check_sudo gen.dynamic
	cp target/lib/libmem_mam.so /usr/local/lib
	chmod 0755 /usr/local/lib/libmem_mam.so
	ldconfig
	cp src/mem_mam.h /usr/local/include

gen.dynamic: build.dynamic
	gcc -shared -o target/lib/libmem_mam.so target/lib/mem_mam.o

test: debug
	gcc -g -fsanitize=address test/main.c target/debug/mem_mam.o -o target/test/test.out -lpthread
test.run: test
	./target/test/test.out

test.dynamic:
	gcc test/main.c -lmem_mam -o target/test/dynamic.out -lpthread
test.dynamic.run: test.dynamic
	./target/test/dynamic.out

test.multithread: debug
	gcc -g -fsanitize=address test/multithread.c target/debug/mem_mam.o -o target/test/multithread.out -lpthread
test.multithread.run: test.multithread
	./target/test/multithread.out


build: gen_folders
	gcc -c src/mem_mam.c -o target/lib/mem_mam.o

build.dynamic: gen_folders
	gcc -c -fPIC src/mem_mam.c -o target/lib/mem_mam.o

build.debug: gen_folders.debug
	gcc -c -g -fsanitize=address src/mem_mam.c -o target/debug/mem_mam.o

check_sudo:
	if [[ "$EUID" -ne 0 ]];\
		then echo "Instalation needs root permissions to continue";\
		echo "Aborting...";\
		exit 1;\
	fi

.SILENT:
.IGNORE:gen_folders gen_folders.debug clean
gen_folders:
	mkdir target 2> /dev/null
	mkdir target/lib 2> /dev/null

gen_folders.debug:
	mkdir target 2> /dev/null
	mkdir target/debug 2> /dev/null
	mkdir target/test 2> /dev/null

clean:
	rm -rf target 2> /dev/null
