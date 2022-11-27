# Archivo de objeto para la implementacion de las listas
xor_list.o: xor_list.h xor_list.c
	gcc -Wall -c xor_list.c -o xor_list.o

# Archivo de objeto para el programa principal
proy2.o: proy2.c xor_list.h
	gcc -Wall -c proy2.c -o proy2.o

# Ejecutable
proy2: proy2.o xor_list.o
	gcc -Wall proy2.o xor_list.o -o proy2