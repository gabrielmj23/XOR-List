#include <stdio.h>
#include <stdlib.h>
#include "xor_list.h"


// Crea un nodo de lista
nodo_t *nuevo_nodo(int elem) {
	nodo_t *newp = (nodo_t *)malloc(sizeof(nodo_t));
	if (!newp) {
		fprintf(stderr, "Error reservando memoria\n");
		return NULL;
	}
	newp->seq_ptr = NULL;
	newp->valor = elem;
	return newp;
}

// Crea un apuntador de lista
lista_t *nueva_lista(void) {
	lista_t *newp = (lista_t *)malloc(sizeof(lista_t));
	if (!newp) {
		fprintf(stderr, "Error reservando memoria\n");
		return NULL;
	}
	newp->ini = newp->fin = NULL;
	return newp;
}

// Verifica si la lista esta vacia
int es_vacia(lista_t *listp) {
	return !listp || !listp->ini;
}

// Elimina el primer elemento de la lista y almacena su valor en elem
int sacar_principio(lista_t *listp, int *elem) {
	if (es_vacia(listp))
		return 0;

	// Modificar puntero de secuencia del siguiente nodo si existe
	nodo_t *np = listp->ini, *sig = NEXT(np, NULL);
	if (sig)
		sig->seq_ptr = NODE_XOR(sig->seq_ptr, listp->ini);
	// Guardar valor del nodo
	*elem = np->valor;
	// Ajustar apuntadores de la lista
	listp->ini = sig;
	if (listp->fin == np)
		listp->fin = NULL;
	// Liberar memoria
	free(np);
	return 1;
}

// Elimina el ultimo elemento de la lista y almacena su valor en elem
int sacar_final(lista_t *listp, int *elem) {
	if (es_vacia(listp))
		return 0;

	// Modificar puntero de secuencia del penultimo nodo si existe
	nodo_t *np = listp->fin, *ant = PREV(np, NULL);
	if (ant)
		ant->seq_ptr = NODE_XOR(ant->seq_ptr, listp->fin);
	// Guardar valor
	*elem = np->valor;
	// Ajustar apuntadores de la lista
	listp->fin = ant;
	if (listp->ini == np)
		listp->ini = NULL;
	// Liberar memoria
	free(np);
	return 1;
}

// Elimina la primera ocurrencia de un valor
int sacar_primera_ocurrencia(lista_t *listp, int elem) {
	if (es_vacia(listp))
		return 0;

	nodo_t *np = listp->ini, *prev = NULL, *aux;
	while (np) {
		if (np->valor == elem) {
			// Se encontro el nodo
			nodo_t *sig = NEXT(np, prev);
			// Modificar apuntador del siguiente si existe. Si no, modificar fin de lista
			if (sig)
				sig->seq_ptr = NODE_XOR(prev, NEXT(sig, np));
			else
				listp->fin = prev;
			// Modificar apuntador del anterior si existe. Si no, modificar inicio de lista
			if (prev)
				prev->seq_ptr = NODE_XOR(PREV(prev, np), sig);
			else
				listp->ini = sig;
			// Liberar
			free(np);
			return 1;
		}
		// Avanzar
		aux = np;
		np = NEXT(np, prev);
		prev = aux;
	}
	return 0;
}

// Determina si el elemento esta en la lista
int buscar_elemento(lista_t *listp, int elem) {
	if (es_vacia(listp))
		return 0;

	nodo_t *np = listp->ini, *prev = NULL, *aux;
	while (np) {
		// Si hay coincidencia se devuelve la posicion
		if (np->valor == elem)
			return 1;
		// Si no, se avanza
		aux = np;
		np = NEXT(np, prev);
		prev = aux;
	}
	return 0;
}