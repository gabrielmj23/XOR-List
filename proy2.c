#include <stdio.h>
#include <stdlib.h>
#include "xor_list.h"
#define CANT_OPC 12

int pedir_valor(char *mensaje) {
	printf("%s", mensaje);
	int v;
	scanf("%i", &v);
	fflush(stdin);
	return v;
}

void insertar(int (*func)(lista_t *, int), lista_t *listp, int dato) {
	if ((*func)(listp, dato))
		printf("Se inserto %i con exito\n", dato);
	else
		printf("Ocurrio un error\n");
	getchar();
	getchar();
}

void sacar(int (*func)(lista_t *, int *), lista_t *listp) {
	int devuelto;
	if ((*func)(listp, &devuelto))
		printf("Se saco el elemento con valor %i\n", devuelto);
	else
		printf("Error: La lista esta vacia\n");
	getchar();
	getchar();
}


int main() {
	const char *opciones[] = {
		"1. Inicializar lista",
		"2. Verificar si esta vacia",
		"3. Insertar al inicio",
		"4. Insertar al final",
		"5. Insertar ordenado",
		"6. Buscar un elemento",
		"7. Sacar primer elemento",
		"8. Sacar ultimo elemento",
		"9. Sacar primera ocurrencia",
		"10. Imprimir de inicio a final",
		"11. Imprimir de final a inicio",
		"12. Mostrar cantidad de elementos",
		"Otro: Salir"
	};
	lista_t *lista = nueva_lista();
	int opc, i, dato;

	do {
		system("clear");
		printf("*** Listas enlazadas XOR ***\nIngrese una opcion:\n");
		for (i = 0; i < CANT_OPC; i++)
			printf("%s\n", opciones[i]);
		scanf("%i", &opc);
		fflush(stdin);

		switch (opc) {
		case 1:
			inicializar_lista(lista);
			printf("Inicializada\n");
			getchar();
			getchar();
			break;

		case 2:
			if (es_vacia(lista))
				printf("La lista esta vacia\n");
			else
				printf("La lista no esta vacia\n");
			getchar();
			getchar();
			break;

		case 3:
			dato = pedir_valor("Ingrese el elemento a insertar: ");
			insertar(insertar_principio, lista, dato);
			break;

		case 4:
			dato = pedir_valor("Ingrese el elemento a insertar: ");
			insertar(insertar_final, lista, dato);
			break;

		case 5:
			dato = pedir_valor("Ingrese el elemento a insertar: ");
			insertar(insertar_orden, lista, dato);
			break;

		case 6:
			dato = pedir_valor("Ingrese el elemento a buscar: ");
			if (buscar_elemento(lista, dato))
				printf("%i esta en la lista\n", dato);
			else
				printf("%i no esta en la lista\n", dato);
			getchar();
			getchar();
			break;

		case 7:
			sacar(sacar_principio, lista);
			break;

		case 8:
			sacar(sacar_final, lista);
			break;

		case 9:
			dato = pedir_valor("Ingrese el elemento a eliminar: ");
			if (sacar_primera_ocurrencia(lista, dato))
				printf("Se elimino la primera ocurrencia de %i con exito\n", dato);
			else
				printf("No se encontro %i\n", dato);
			getchar();
			getchar();
			break;

		case 10:
			listar_inicio_final(lista);
			getchar();
			getchar();
			break;

		case 11:
			listar_final_inicio(lista);
			getchar();
			getchar();
			break;

		case 12:
			printf("La lista tiene %i elementos\n", cantidad_elementos(lista));
			getchar();
			getchar();
			break;
		}
	} while (opc >= 1 && opc <= 12);

	return 0;
}