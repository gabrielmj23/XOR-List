/*
 * Tipos de datos:
 */
typedef struct node {
	double valor;
	struct node *seq_ptr;
}
Node;

typedef struct lista {
	Node *head, *last;	
}
Lista;

/*
 * Macros para navegar la lista
 */
#define NEXT(cur,prev) cur->seq_ptr ^ prev->seq_ptr
#define PREV(cur,next) cur->seq_ptr ^ next->seq_ptr

/*
 * Funciones de utilidad
 */
Node *nuevo_nodo(double elem);
Lista *nueva_lista();

/*
 * Funciones del TAD
 */
void insertar_inicio(Lista *listp, double elem);
void insertar_final(Lista *listp, double elem);
void insertar_ordenado(Lista *listp, double elem);
void concatenar(Lista *l1, Lista *l2, Lista *l3);
void invertir(Lista *listp, Lista *revp);
int vacia(Lista *listp);
void borrar_primero(Lista *listp);
void borrar_ultimo(Lista *listp);
void borrar_primera_ocurrencia(Lista *listp, double elem);