all: file_info.c
	gcc -o run file_info.c

run: all
	./run

clean: 
	rm run
