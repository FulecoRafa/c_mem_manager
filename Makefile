all: build
debug: build.debug

build: gen_folders
	gcc -c src/mem_mam.c -o target/lib/mem_mam.o

.SILENT:
.IGNORE:
gen_folders:
	mkdir target
	mkdir target/lib
