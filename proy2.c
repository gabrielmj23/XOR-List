#include <stdio.h>
#include "xor_list.h"

int main() {
	lista_t *lista = nueva_lista();
	int nums[] = { 1, 2, 3, 4, 6 };
	for (int i = 0; i < 5; i++)
		insertar_final(lista, nums[i]);
	listar_inicio_final(lista);
	listar_final_inicio(lista);
	insertar_orden(lista, 5);
	listar_inicio_final(lista);
	insertar_final(lista, 10);
	int e;
	sacar_principio(lista, &e);
	printf("Primer elemento eliminado: %i\n", e);
	listar_inicio_final(lista);
	printf("Longitud: %i\n", cantidad_elementos(lista));
	return 0;
}