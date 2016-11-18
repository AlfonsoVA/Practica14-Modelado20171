#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Aquí va la definición de tu estructura 'elemento'
  esta debe de tener al menos dos campos:
  struct elemento *siguiente: es el apuntador al siguiente elemento de la lista
  void *valor: es el apuntador al valor guardado
*/
//definimos la estructura
struct elemento{
	struct Elemento *siguiente;
	void *valor;
};	
	
// defino alias para los datos (struct elemento) y (Elemento**)
typedef struct elemento Elemento; /*No cambies esta línea*/
typedef Elemento** Lista; /*No cambies esta línea*/

/*Compara 2 'Elemento' que contienen como valor un 'int'*/
int cmp_int(const void* a, const void* b);

/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*));

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista lista);

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista lista, size_t posicion);

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_int(Lista lista);

/*Crea una lista vacía*/
Lista crea_lista();

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
int inserta_elemento(Lista lista, void *valor);

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista);
	