struct Node
{
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
    if(!p) return -1;
    Node *aux = *p;
    int value = aux -> value;
    *p = (*p) -> next;
    delete aux;
    return value;
}

int top(Node *p){
    if(!p) return -1;
    return p -> value;
}

void deleteValue(Node **p, int value){
    if(isVoid(*p)) return;
    int currentValue = pop(p);
    deleteValue(p, value);
    if(currentValue != value) push(p, currentValue);
}
void deleteRepeated(Node **p){
    if(isVoid(*p)) return;
    int value = pop(p);
    deleteValue(p,value);
    deleteRepeated(p);
    push(p, value);
}


int popBottom(Node **p){
    if (isVoid(*p)) return -1;
    
    int value = pop(p);
    if(isVoid(*p)){// verifica si quedo vacia despues del pop
        return value; // Este era el último elemento (el fondo)
    }
    int result = popBottom(p);
    if(result == -1) return value;
    push(p, value);
    return result;
    
}

void pushButtom(Node **p, int value){
    if(isVoid(*p)) {
        push(p, value);
        return; // Añadido un return para que no siga ejecutando
    }
    int currentValue = pop(p);
    pushButtom(p,value);
    push(p, currentValue);
}

bool compare(Node **a, Node **b){
    if(isVoid(*a) && isVoid(*b)) return true;
    if(isVoid(*a) || isVoid(*b)) return false;

    int valueA = pop(a), valueB = popBottom(b);
    bool result = false;

    if(valueA == valueB) result = compare(a,b);
    push(a, valueA);
    pushButtom(b, valueB);
    return result;

}

void organizarImparPar(Node**p){
    if(isVoid(*p)) return;

    int value = pop(p);
    organizarImparPar(p);
    if (value % 2 == 0)
    {
        // Es par
        pushButtom(p,value);
    }
    else{
         // Es impar
        push(p,value);
    }
    
}

void ordenarImparesMayorMenor(Node **p){
    // Paso 1: Si está vacía o llegamos a un par, stop
    if(isVoid(*p) || (*p) -> value % 2 == 0) return;


    int value = pop(p);                      // Paso 2: Sacar tope impar
    ordenarImparesMayorMenor(p);             // Paso 3: Ordenar resto


     // Paso 4: Insertar en posición ordenada
    if(isVoid(*p) || value >= top(*p) || (*p) -> value % 2 == 0) {
        push(p, value);

    }else{
        int aux = pop(p);
        push(p, value);
        push(p, aux);
    }

}

void ordenarParesMayorMenor(Node **p) {
    if (isVoid(*p)) return;
    
    int valor = pop(p);
    ordenarParesMayorMenor(p);
    
    // Si es impar, simplemente push (está en la sección de impares)
    if (valor % 2 == 1) {
        push(p, valor);
    } 
    // Si es par, ordenar en el fondo
    else {
        if (isVoid(*p) || top(*p) % 2 == 1 || valor >= top(*p)) {
            push(p, valor);
        } else {
            int temp = pop(p);
            push(p, valor);
            push(p, temp);
        }
    }
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

// Invierte la pila
void invertStack(Node  **p){
    if(isVoid(*p)) return;
    int value = pop(p); // Desapilar el tope;
    invertStack(p); // recursividad
    pushButtom(p, value);
}

// Inserta el valor en el lugar indicado
void insertInSortedOrder(Node **p, int value){
    if(isVoid(*p) || value < top(*p)) {// no esta vacia ya que es 5 el valor // como valor es 5 se pregunta 5 < 3? no, entonces sigue
        push(p, value); 
    } else{
        int cima = pop(p);// en la pila esta [3 | 8] ahora saca el 3 y la pila queda [8]
        insertInSortedOrder(p,value); // repeti el proceso
        push(p, cima);// mete el 5 despues del 8 [5 | 8]
    }

}

//Ordena la pila de mayor a menor

void sortStack(Node **p){
    if (isVoid(*p)) return;
    int value = pop(p);
    sortStack(p);
    insertInSortedOrder(p,value);

}

void pilaDigitos(Node **p, int numero){
    // Caso base
    // Si el número es de un solo dígito (0-9),
    if(numero < 10){
        push(p, numero);
        return;
    }
    // 1. Llama a la función con el número "reducido"
    // (ej. 512 -> 51)
    pilaDigitos(p, numero /10);

    // 2. Obtiene el último dígito del número ACTUAL
    // (ej. 512 % 10 -> 2)
    int digito = numero % 10;

    push(p,digito);

}

void sumaPilas(Node **A, Node **B,Node **aux, int count){
    if(isVoid(*A) && isVoid(*B) && count == 0) return;
    
    int digitoA = 0,digitoB = 0 ;
    if(!isVoid(*A)) digitoA = pop(A);
    if(!isVoid(*B)) digitoB = pop(B);

    int sumaColumna = digitoA + digitoB + count;
    int nuevoCount = sumaColumna / 10;
    int digitoResultado = sumaColumna % 10;
    push(aux, digitoResultado);

    sumaPilas(A,B, aux, nuevoCount);



}
