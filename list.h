

// Definición de un nodo para la lista enlazada
struct Node{
    int value;      // Valor almacenado en el nodo
    Node *next;     // Puntero al siguiente nodo de la lista
};

// Inserta un elemento al inicio de la lista
void insert_head(Node **p,int element){
    Node *newElement = new Node;      // Crea un nuevo nodo en memoria
    newElement -> value = element;    // Asigna el valor al nuevo nodo
    newElement -> next = *p;          // El siguiente del nuevo nodo apunta al actual primer nodo
    *p = newElement;                  // Actualiza el puntero de la lista para que apunte al nuevo nodo
};

// Inserta un elemento al final de la lista
void insert_back(Node **p,int element){
    Node *newElement = new Node;      // Crea un nuevo nodo en memoria
    newElement -> value = element;    // Asigna el valor al nuevo nodo
    newElement ->next = NULL;         // El siguiente del nuevo nodo es NULL (será el último)
    if(*p == NULL){                   // Si la lista está vacía
        *p = newElement;              // El nuevo nodo es el primero de la lista
    } else{
        Node *aux = *p;               // Crea un puntero auxiliar para recorrer la lista
        while(aux && aux-> next != NULL){ // Avanza hasta el último nodo
            aux = aux -> next;
        }
        aux -> next = newElement;     // El último nodo apunta al nuevo nodo
    }
}

// Elimina todos los nodos de la lista y libera la memoria
void delete_list(Node *p){
    Node *aux;                        // Puntero auxiliar para guardar el nodo actual
    while(p != NULL){                 // Mientras haya nodos en la lista
        aux = p;                      // Guarda el nodo actual
        p = aux -> next;              // Avanza al siguiente nodo
        delete aux;                   // Libera la memoria del nodo actual
    }
}

// CORREGIDA: Ahora retorna un booleano indicando si eliminó o no
bool delete_node(Node **p, int element) {
    if (*p == NULL) return false; // Si la lista está vacía, no hay nada que eliminar

    Node *current = *p;
    Node *previous = nullptr;

    // Buscar el nodo con el valor especificado
    while (current != NULL && current->value != element) {
        previous = current;
        current = current->next;
    }

    // Si no se encontró el elemento, salir
    if (current == NULL) return false;

    // Si el nodo a eliminar es el primero
    if (previous == nullptr) {
        *p = current->next; // Actualizar la cabeza de la lista
    } else {
        previous->next = current->next; // Saltar el nodo a eliminar
    }

    delete current; // Liberar la memoria del nodo eliminado
    return true;    // Indica que sí se eliminó
}

// CORREGIDA: Ahora retorna el contador
int count(Node *p) {
    int contador = 0; // Inicializa el contador en 0
    Node *aux = p;   // Puntero auxiliar para recorrer la lista

    while (aux != NULL) { // Recorre la lista hasta el final
        contador++;       // Incrementa el contador por cada nodo
        aux = aux->next;  // Avanza al siguiente nodo
    }
    return contador; // RETORNA el valor del contador
}


// Busca un elemento en una lista enlazada simple
bool search(Node *p, int element){
    Node *aux = p;              // Crea un puntero auxiliar que apunta al inicio de la lista
    while(aux != NULL){         // Mientras no se llegue al final de la lista (aux no es NULL)
        if(aux->value == element){ // Si el valor del nodo actual es igual al elemento buscado
            return true;        // Retorna true (elemento encontrado)
        }
        aux = aux->next;        // Avanza al siguiente nodo de la lista
    }
    return false;               // Si termina el ciclo, el elemento no está en la lista; retorna false
}


void get_at_position(Node *p, int position){
    // Creamos un puntero auxiliar para recorrer la lista
    Node *aux = p;
    // Inicializamos la posición actual en 0
    int current_position = 0;

    // Recorremos la lista mientras no lleguemos al final
    while (aux != nullptr) {
        // Si la posición actual es igual a la buscada
        if (current_position == position) {
            // Mostramos el valor del nodo en la posición deseada
            cout << "Elemento en la posición " << position << ": " << aux->value << endl;
            // Terminamos la función porque ya encontramos el nodo
            return;
        }
        // Avanzamos al siguiente nodo
        aux = aux->next;
        // Incrementamos la posición actual
        current_position++;
    }

    // Si salimos del ciclo, la posición es inválida (mayor que el tamaño de la lista)
    throw out_of_range("Posición inválida");
}

// Suma todos los valores de los nodos en una lista enlazada simple
void sumar_lista(Node *p){
    Node *aux = p;      // Crea un puntero auxiliar para recorrer la lista, empezando en el primer nodo
    int suma = 0;       // Variable para acumular la suma de los valores

    // Recorre la lista mientras el nodo actual no sea nulo
    while (aux != nullptr) {
        suma += aux->value;   // Suma el valor del nodo actual a la variable suma
        aux = aux->next;      // Avanza al siguiente nodo de la lista
    }

    // Muestra el resultado de la suma en la consola
    cout << "Suma de los elementos de la lista: " << suma << endl;
}


// Invierte una lista enlazada simple.
// p: puntero al puntero del primer nodo (cabeza) de la lista.
void invert_list(Node **p) {
    Node *prev = nullptr;      // Inicializa el puntero al nodo anterior como nulo (la nueva cola de la lista).
    Node *current = *p;        // Apunta al nodo actual, comenzando desde la cabeza de la lista.
    Node *next = nullptr;      // Se usará para guardar el siguiente nodo temporalmente.

    // Recorre la lista hasta que current sea nulo (fin de la lista).
    while (current != nullptr) {
        next = current->next;      // Guarda el siguiente nodo antes de modificar el enlace.
        current->next = prev;      // Invierte el enlace: ahora el nodo actual apunta al anterior.
        prev = current;            // Avanza prev al nodo actual (será el anterior en la próxima iteración).
        current = next;            // Avanza current al siguiente nodo guardado.
    }
    *p = prev; // Al final, prev apunta a la nueva cabeza de la lista. Actualiza el puntero original.
}



void bubble_sort(Node **p) {
    // Si la lista está vacía, no hay nada que ordenar
    if (*p == nullptr) return;

    bool swapped; // Indica si se realizó algún intercambio en la pasada actual
    do {
        swapped = false; // Al inicio de cada pasada, asumimos que no hay intercambios
        Node *current = *p; // Comenzamos desde la cabeza de la lista
        Node *prev = nullptr; // Puntero al nodo anterior, inicialmente nulo

        // Recorremos la lista hasta el penúltimo nodo
        while (current->next != nullptr) {
            // Si el valor actual es mayor que el siguiente, hay que intercambiar
            if (current->value > current->next->value) {
                Node *temp = current->next; // temp apunta al nodo siguiente

                // Realiza el intercambio de nodos
                current->next = temp->next; // El nodo actual apunta al siguiente del siguiente
                temp->next = current;       // El nodo siguiente apunta al nodo actual

                // Si estamos al inicio de la lista, actualizamos la cabeza
                if (prev == nullptr) {
                    *p = temp;
                } else {
                    // Si no, enlazamos el nodo anterior con el nuevo nodo en la posición
                    prev->next = temp;
                }

                // prev ahora apunta al nodo que quedó antes de current tras el intercambio
                prev = temp;
                swapped = true; // Marcamos que hubo intercambio
            } else {
                // Si no hay que intercambiar, avanzamos ambos punteros
                prev = current;
                current = current->next;
            }
        }
        // Si swapped es true, se repite el proceso para asegurar el orden
    } while (swapped);
}
