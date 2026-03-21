all:
	gcc -I../core -I../phase -I. ../core/main.c ../core/init.c ../core/print.c ../phase/movement.c ../phase/placement.c file_io.c -o game
run: all
	./game
clean:
	rm -f game