#include <stdio.h>
#include <stdlib.h>
#include "xor_list.h"


/*
 * Crea un nodo de lista
 */
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

/*
 * Crea un apuntador de lista
 */
lista_t *nueva_lista(void) {
	lista_t *newp = (lista_t *)malloc(sizeof(lista_t));
	if (!newp) {
		fprintf(stderr, "Error reservando memoria\n");
		return NULL;
	}
	newp->ini = newp->fin = NULL;
	return newp;
}

/*
 * Inicializa (vacia) una lista
 */
void inicializar_lista(lista_t *listp){
  nodo_t *nodop = listp->ini;
  nodo_t *prev = NULL, *temp;
  while (nodop != NULL){
    temp = nodop;
    nodop = NEXT(nodop, prev);
    prev = temp;
    free(temp);
  }
  listp->ini = NULL;
  listp->fin = NULL;
}

/*
 * Verifica si la lista esta vacia
 */
int es_vacia(lista_t *listp) {
	return !listp || !listp->ini;
}

/* 
 * Inserta un nodo con valor elem al inicio
 */
int insertar_principio(lista_t *listp, int elem) {
  nodo_t *nuevo = nuevo_nodo(elem);
  if (nuevo == NULL)
    return 0;
  // Insertar el nuevo nodo al principio de la lista
	if (listp->ini == NULL) {
		// La lista está vacía, el nuevo nodo es el único en la lista
		listp->ini = nuevo_nodo;
		listp->fin = nuevo_nodo;
		nuevo_nodo->seq_ptr = NULL;
	} else {
		// La lista no está vacía, el nuevo nodo es el primero en la lista
		nuevo_nodo->seq_ptr = listp->ini;
		listp->ini->seq_ptr = NODE_XOR(nuevo_nodo, listp->ini->seq_ptr);
		listp->ini = nuevo_nodo;
	}

	return 1; // Inserción exitosa
}

/*
 * Inserta un nodo con valor elem al final
 */
int insertar_final(lista_t *listp, int elem) {
    nodo_t *nuevo = nuevo_nodo(elem);
    if (nuevo == NULL)
    	return 0;
    // Insertar el nuevo nodo al final de la lista
	if (listp->fin == NULL) {
		// La lista está vacía, el nuevo nodo es el único en la lista
		listp->ini = nuevo_nodo;
		listp->fin = nuevo_nodo;
		nuevo_nodo->seq_ptr = NULL;
	} else {
		// La lista no está vacía, el nuevo nodo es el último en la lista
		nuevo_nodo->seq_ptr = listp->fin;
		listp->fin->seq_ptr = NODE_XOR(listp->fin, nuevo_nodo);
		listp->fin = nuevo_nodo;
	}

	return 1; // Inserción exitosa
}

/*
 * Inserta ordenado un nodo con valor elem
 */
int insertar_orden(lista_t *listp, int elem) {
    nodo_t *nuevo = nuevo_nodo(elem);
    if (nuevo == NULL)
    	return 0;
    nodo_t *actual = listp->ini;
    nodo_t *anterior = NULL;
    while (actual != NULL && actual->valor < elem) {
        anterior = actual;
        actual = actual->seq_ptr;
    }
    if (anterior == NULL) {
        // insertar al inicio
        nuevo->seq_ptr = listp->ini;
        listp->ini = nuevo;
        if (listp->fin == NULL) {
            listp->fin = nuevo;
        }
    } else if (actual == NULL) {
        // insertar al final
        anterior->seq_ptr = nuevo;
        nuevo->seq_ptr = NULL;
        listp->fin = nuevo;
    } else {
        // insertar en medio
        nuevo->seq_ptr = actual;
        anterior->seq_ptr = nuevo;
    }
    return 1; // inserción exitosa
}

/*
 * Elimina el primer elemento de la lista y almacena su valor en elem
 */
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

/*
 * Elimina el ultimo elemento de la lista y almacena su valor en elem
 */
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

/*
 * Elimina la primera ocurrencia de un valor
 */
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

/*
 * Determina si el elemento esta en la lista
 */
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

/*
 * Imprime la lista de inicio a final
 */
void listar_inicio_final(lista_t *listp) {
	nodo_t *nodop = listp->ini, *prev = NULL, *aux;
	printf("--> ");
	while (nodop) {
		printf("%i --> ", nodop->valor);
		aux = nodop;
		nodop = NEXT(nodop, prev);
		prev = aux;
	}
	printf("NULL\n");
}

/*
 * Imprime la lista de final a inicio
 */
void listar_final_inicio(lista_t *listp) {
	nodo_t *nodop = listp->fin, *nxt = NULL, *aux;
	printf("NULL");
	while (nodop) {
		printf(" <-- %i", nodop->valor);
		aux = nodop;
		nodop = PREV(nodop, nxt);
		nxt = aux;
	}
	printf("\n");
}

/*
 * Devuelve longitud de la lista
 */
int cantidad_elementos(lista_t *listp) {
  int contador = 0;

  // Verificamos si la lista está vacía
  if (listp->ini == NULL) {
    return 0;
  }

  // Recorremos la lista y aumentamos el contador por cada nodo
  nodo_t *nodop = listp->ini;
  while (nodop != NULL) {
    contador++;
    nodop = nodop->seq_ptr;
  }

  return contador;
}
