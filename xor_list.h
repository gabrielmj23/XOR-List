#include <stdint.h>

/*
 * Tipos de datos
 */
typedef struct nodo {
	int valor;
	struct nodo *seq_ptr;
}
nodo_t;

typedef struct {
	nodo_t *ini, *fin;	
}
lista_t;

/*
 * Macros para navegar la lista
 */
#define NODE_XOR(ptr1, ptr2) (nodo_t *)((uintptr_t)ptr1 ^ (uintptr_t)ptr2)
#define NEXT(cur,prev) NODE_XOR(cur->seq_ptr, prev)
#define PREV(cur,next) NODE_XOR(cur->seq_ptr, next)


/*
 * Funciones de utilidad
 */
nodo_t *nuevo_nodo(int elem);
lista_t *nueva_lista(void);
void inicializar_lista(lista_t *listp);
void elimina_lista(lista_t *listp);
int es_vacia(lista_t *listp);

/*
 * Funciones del TAD
 */
// Insertar al inicio, final y ordenado
int insertar_principio(lista_t *listp, int elem);
int insertar_final(lista_t *listp, int elem);
int insertar_orden(lista_t *listp, int elem);
// Sacar el primero, ultimo y primera ocurrencia
int sacar_principio(lista_t *listp, int *elem);
int sacar_final(lista_t *listp, int *elem);
int sacar_primera_ocurrencia(lista_t *listp, int elem);
// Funciones variadas
int buscar_elemento(lista_t *listp, int elem);
void listar_inicio_final(lista_t *listp);
void listar_final_inicio(lista_t *listp);
int cantidad_elementos(lista_t *listp);