#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{	
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado;
    borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}

int cmp_int(const void* a, const void* b){
	//guardamos los valores en los tmp_a y tmp_b... reciclando de la P.13 :b	
	int tmp_a=*(int *)a;
	int tmp_b=*(int *)b;		
	if(tmp_a<tmp_b){			
		return -1;
	}
	if(tmp_a>tmp_b){
		return 1;		
	}	
	return 0;	
}

Lista crea_lista(){//Crea lista con malloc, eso con el size of lista por 1
	Lista la_lista = calloc(1,sizeof(Lista));
	return la_lista;
}

size_t longitud(Lista lista){	
	size_t len= 0;
	Elemento *tmp = *lista;
	while(tmp != NULL){
		len+=1;
		tmp= tmp->siguiente;
	}	
	return len;
}

int inserta_elemento(Lista lista, void *valor){		
	Elemento *elem= calloc(1,sizeof(Elemento));			
	elem->siguiente= *lista;
	elem->valor=valor;
	*lista= elem;
	size_t len= longitud(lista);
	return len;	
}

void imprime_lista_int(Lista lista){
	size_t len = longitud(lista);
	Elemento *tmp= *lista;
	int i, val;
	for(i=0; i<len; i++){
		val= *(int*)tmp->valor;
		printf("%d\t", val);
		tmp= tmp->siguiente;	
	}
}

Elemento *quita_elemento(Lista lista, size_t posicion){
	size_t len =longitud(lista);

	//Si la posicion no existe
	if(len<=posicion || posicion<0 ){
		return NULL;					
	}

	//Si esta al inicio
	if(posicion==0){
		Elemento *a_borrar= *lista;		
		Elemento *cabeza= (*lista)->siguiente;//Usamos (*lista) para usar el siguiente y valor del apuntador... (geez!)
		(*lista)->siguiente= NULL;
		(*lista)->valor= NULL;
		*lista = cabeza;		
		return a_borrar;
	}

	//Si esta al final
	if(posicion==len-1){
		Elemento *a_borrar= *lista;
		Elemento *penultimo;
		int i;
		for(i=0; i<len; i++){//Iteramos com tmp para llegar al penultimo elemento	
			penultimo= a_borrar;		
			a_borrar= a_borrar->siguiente;
		}		
		penultimo->siguiente= NULL;
		a_borrar->valor= NULL;
		a_borrar->siguiente= NULL;
		return a_borrar;
	}

	//En otro caso (entre otros elementos)
	Elemento *anterior_a_borrar= *lista;
	int i=0;
	while(i<posicion-1){//Iteramos hasta el anterior a borrar
		anterior_a_borrar= anterior_a_borrar->siguiente;
		i++;
	}
	//Usamos el apuntador al elemento que va despues del elemento a borrar
		//para que el elemento anterior a borrar lo tenga como el siguiente
	Elemento *a_borrar= anterior_a_borrar->siguiente;
	Elemento *despues_del_borrar= a_borrar->siguiente;	

	anterior_a_borrar->siguiente= despues_del_borrar;

	a_borrar->valor= NULL;
	a_borrar->siguiente= NULL;
	return a_borrar;
}

void borra_lista(Lista lista){		
	Elemento *tmp;
	size_t len= longitud(lista);
	int i;	
	//Iteramos con la longitud de la lista entonces vamos borrando 
		//y liberando memoria con el primer elemento de la lista restante 
	for(i=0; i<len; i++){ 
		tmp= quita_elemento(lista, 0);
		free(tmp->valor);
		free(tmp);
	}	
	//liberamos memoria de la lista
	free(lista);
}

void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){	
	size_t len= longitud(lista);	
	int arr[len];
	int i=0;
	Elemento *tmp= *lista;
	Elemento *tmp_ord= *lista;

	//Iterando sobre la longitud d ela lista vamos agregando elementos a arreglo		
	for(i=0; i<len; i++){
		arr[i]= (int*)tmp->valor;
		tmp= tmp->siguiente;
	}	
	//Usamos la funcion qsort, tomando el arreglo creado, la longitud,
		//el tamanio de cada elemento y la funcion comparadora
	qsort(arr,len,sizeof(int),(*cmp));

	//Con el arreglo ya ordenado cambiamos vamos cambiando los valores de la lista
	for(i=0; i<len; i++){
		*(int*)tmp_ord->valor= arr[i];
		tmp_ord= tmp_ord->siguiente;
	}	
    
}
