make: 
	gcc -c main.c -Wall
 
	gcc -c fonction.c -Wall
	
	gcc -c menu.c -Wall
	gcc -o snake main.o fonction.o menu.o 
clean:

	rm snake

	rm *.o
