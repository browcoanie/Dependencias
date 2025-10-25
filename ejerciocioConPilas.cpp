#include <iostream>
using namespace std;

// --- Tu código de Pilas (struct y funciones básicas) ---

struct Node{
    int value;      
    Node *next;     
};

bool isVoid(Node *p){
    if(!p) return true;
    return false;
}

void push(Node **p, int value){
    Node *newElement = new Node;
    newElement -> value = value;
    newElement->next = *p; 
    *p = newElement;
}

int pop(Node **p){
    if(isVoid(*p)) return -1; // Usar isVoid para consistencia
    Node *aux = *p;
    int value = aux -> value;
    *p = (*p) -> next;
    delete aux;
    return value;
}

int top(Node *p){
    if(isVoid(p)) return -1; // Usar isVoid para consistencia
    return p -> value;
}

// --- Tus Funciones de Lógica Avanzada ---

void pushButtom(Node **p, int value){
    if(isVoid(*p)) {
        push(p, value);
        return; // Añadido un return para que no siga ejecutando
    }
    int currentValue = pop(p);
    pushButtom(p,value);
    push(p, currentValue);
}


bool existInQ(Node **p, int value){
    if(isVoid(*p)) return false;
    
    // La pila q guarda [valor, contador, valor, contador...]
    // Así que top() debería ser un valor, no un contador
    if(top(*p) == value) return true; 
    
    int currentValue = pop(p); // Este es el 'valor'
    int counter = pop(p);      // Este es el 'contador'
    
    bool result = existInQ(p, value);
    
    push(p,counter);
    push(p,currentValue);
    return result;
}

// ⭐️ --- ¡CORRECCIÓN IMPORTANTE AQUÍ! --- ⭐️
// Tu función calculaba el contador pero nunca lo devolvía.
int count(Node **p, int value){
    if(isVoid(*p)) return 0;
    
    int currentValue = pop(p);
    int counter = count(p, value); // Llama recursiva
    
    if(currentValue == value) counter++; // Suma si lo encuentra
    
    push(p, currentValue); // Vuelve a poner el valor
    
    return counter; // <-- ESTA LÍNEA FALTABA
}

void makeStack(Node **p, Node **q){
    if(isVoid(*p)) return;
    
    int value = pop(p); // Saca un valor de p
    
    if(!existInQ(q, value)){
        // Si no está en q, cuéntalo y añádelo al fondo
        int counter = count(p, value) + 1; // +1 por el que sacamos
        pushButtom(q, value);
        pushButtom(q, counter);
    }
    
    makeStack(p,q); // Llama recursiva con el resto de p
    
    push(p, value); // Vuelve a poner el valor en p para no destruirla
}

// --- Función Auxiliar para Imprimir una Pila ---
// (Para poder ver los resultados)

void printStack(Node *p) {
    cout << "Pila (cima -> fondo): [ ";
    Node *temp = p;
    while (temp != NULL) {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << "]" << endl;
}


// --- ¡AQUÍ ESTÁ TU MAIN! ---

int main(){

    // 1. "Creamos" las dos pilas (empiezan vacías)
    Node *pila_P = NULL;
    Node *pila_Q = NULL;

    // 2. Llenamos la pila P con datos de ejemplo
    // La pila quedará: [5, 8, 3, 5, 8, 5] (el último 5 es la cima)
    push(&pila_P, 5);
    push(&pila_P, 8);
    push(&pila_P, 5);
    push(&pila_P, 3);
    push(&pila_P, 8);
    push(&pila_P, 5);

    cout << "--- Estado Inicial ---" << endl;
    printStack(pila_P);
    printStack(pila_Q);

    // 3. Llamamos a tu función principal
    cout << "\n--- Ejecutando makeStack(&p, &q)... ---" << endl;
    makeStack(&pila_P, &pila_Q);

    // 4. Mostramos los resultados
    cout << "\n--- Estado Final ---" << endl;
    cout << "Pila P (deberia estar intacta):" << endl;
    printStack(pila_P);

    cout << "\nPila Q (resumen de frecuencias):" << endl;
    cout << "Formato (Valor, Contador):" << endl;
    
    // Vaciamos la pila Q para leerla
    // La pila Q se llenó con pushButtom, así que el primer
    // elemento que contamos está en el fondo.
    // Al hacer pop, saldrán en el orden en que se encontraron.
    cout << "[";
    while(!isVoid(pila_Q)){
        int valor = pop(&pila_Q);
        int contador = pop(&pila_Q);
        cout << valor << "," << contador;
    }
    cout << "]";

    // 5. Limpiamos la memoria (opcional pero buena práctica)
    while(!isVoid(pila_P)) {
        pop(&pila_P);
    }
    
    return 0;
}
