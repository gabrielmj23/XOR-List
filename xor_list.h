/*
 * Tipos de datos
 */
typedef struct node {
	int valor;
	struct node *seq_ptr;
}
node_t;

typedef struct {
	Node *ini, *fin;	
}
lista_t;

/*
 * Macros para navegar la lista
 */
#define NEXT(cur,prev) (cur->seq_ptr ^ prev)
#define PREV(cur,next) (cur->seq_ptr ^ next)

/*
 * Funciones de utilidad
 */
node_t *nuevo_nodo(double elem);
lista_t *nueva_lista(void);
void elimina_lista(lista_t *listp);

/*
 * Funciones del TAD
 */
// Insertar al inicio, final y ordenado
void inserta_ilista(lista_t *listp, int elem);
void inserta_flista(lista_t *listp, int elem);
void inserta_lista(lista_t *listp, int elem);
// Sacar el primero, ultimo y primera ocurrencia
void sacarp_lista(lista_t *listp, int *elem);
void sacarf_lista(lista_t *listp, int *elem);
int sacar_lista(lista_t *listp, int elem);
// Funciones variadas
int buscar_lista(lista_t *listp, int elem);
void imprime_lista(lista_t *listp);
void concatenar(lista_t *l1, lista_t *l2, lista_t *l3);
void invertir(lista_t *listp, lista_t *revp);
int lista_vacia(lista_t *listp);