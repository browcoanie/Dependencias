#include <iostream>
using namespace std; // Necesario para 'cout'

struct Node
{
    int value;
    Node *next;
};

// Verifica si la pila está vacía (si el puntero principal es nulo)
bool isVoid(Node *p){
    if(!p) return true;
    return false;
}

// Añade un elemento al tope de la pila
void push(Node **p, int value){
    Node *newElement = new Node;
    newElement -> value = value;
    newElement->next = *p; 
    *p = newElement;
}

// Saca (elimina) el elemento del tope de la pila y lo devuelve.
int pop(Node **p){
    // CORRECCIÓN: Se comprueba '*p' (el contenido) en lugar de 'p' (el puntero al puntero)
    if(isVoid(*p)) return -1; 
    Node *aux = *p;
    int value = aux -> value;
    *p = (*p) -> next;
    delete aux;
    return value;
}

// Devuelve el valor del elemento del tope de la pila sin eliminarlo.
int top(Node *p){
    // CORRECCIÓN: Se comprueba 'p' (el puntero al tope)
    if(isVoid(p)) return -1; 
    return p -> value;
}

// Elimina recursivamente TODAS las ocurrencias de 'value' en la pila.
void deleteValue(Node **p, int value){
    if(isVoid(*p)) return;
    int currentValue = pop(p);
    deleteValue(p, value);
    if(currentValue != value) push(p, currentValue);
}

// Elimina elementos duplicados, conservando solo la ÚLTIMA aparición (la más profunda).
void deleteRepeated(Node **p){
    if(isVoid(*p)) return;
    int value = pop(p);
    deleteValue(p,value); // Elimina todas las otras ocurrencias
    deleteRepeated(p);    // Llama recursivamente para el resto
    push(p, value);       // Vuelve a poner este valor (que ahora es único)
}

// Saca (elimina) el elemento del FONDO de la pila y lo devuelve.
// -- VERSIÓN CORREGIDA --
int popBottom(Node **p){
    if (isVoid(*p)) return -1;
    
    int value = pop(p); // Saca el tope
    
    if(isVoid(*p)){
        // 1. Caso Base: La pila quedó vacía.
        // 'value' es el elemento del fondo.
        return value; 
    }
    
    // 2. Sigue bajando recursivamente
    int result = popBottom(p);
    
    // 3. Al volver, reconstruye la pila
    push(p, value); 
    
    // 4. Devuelve el resultado (el valor del fondo)
    return result; 
}


// Añade un elemento en el FONDO de la pila.
void pushButtom(Node **p, int value){
    if(isVoid(*p)) {
        push(p, value);
        return;
    }
    int currentValue = pop(p);
    pushButtom(p,value);
    push(p, currentValue);
}

// Compara dos pilas: tope(A) con fondo(B).
// -- VERSIÓN CORREGIDA --
bool compare(Node **a, Node **b){
    // Caso base 1: Ambas vacías, son iguales
    if(isVoid(*a) && isVoid(*b)) return true;
    // Caso base 2: Una vacía y la otra no, son diferentes
    if(isVoid(*a) || isVoid(*b)) return false;

    int valueA = pop(a);       // Saca tope de A
    int valueB = popBottom(b); // Saca fondo de B (usa la versión corregida)
    
    bool result = false; // Asume que son diferentes

    if(valueA == valueB) {
        // Si ESTE PAR es igual, verifica si el RESTO también lo es
        result = compare(a, b);
    }
    
    // Reconstruye las pilas para la llamada anterior
    push(a, valueA);
    pushButtom(b, valueB);
    
    // Devuelve el resultado de la comparación
    return result;
}

// Reorganiza la pila: deja todos los impares arriba y todos los pares abajo.
void organizarImparPar(Node**p){
    if(isVoid(*p)) return;

    int value = pop(p);
    organizarImparPar(p);
    if (value % 2 == 0)
    {
        // Es par, va al fondo
        pushButtom(p,value);
    }
    else{
         // Es impar, va al tope
        push(p,value);
    }
}

// Ordena de MAYOR a MENOR el bloque contiguo de NÚMEROS IMPARES
// que se encuentra en el tope de la pila.
void ordenarImparesMayorMenor(Node **p){
    if(isVoid(*p) || (*p) -> value % 2 == 0) return;

    int value = pop(p);                  
    ordenarImparesMayorMenor(p);         

    if(isVoid(*p) || value >= top(*p) || (*p) -> value % 2 == 0) {
        push(p, value);
    } else {
        int aux = pop(p);
        push(p, value);
        push(p, aux);
    }
}


// --- INICIO CORRECCIÓN 'ordenarParesMayorMenor' ---

// FUNCIÓN AUXILIAR NUEVA
// Inserta un valor par en la sección de pares (fondo),
// manteniendo el orden de mayor a menor.
void insertarParOrdenado(Node **p, int valorPar) {
    
    // Caso base 1: Pila vacía, o...
    // Caso base 2: Llegamos al final de la sección de pares
    // (el tope actual es un número impar).
    if (isVoid(*p) || (top(*p) % 2 == 1)) {
        push(p, valorPar); // Insertamos el valor par aquí
        return;
    }

    // Comparamos 'valorPar' contra el tope PAR actual
    if (valorPar >= top(*p)) {
        // 'valorPar' es mayor, va encima del tope actual
        push(p, valorPar);
    } 
    else {
        // 'valorPar' es menor, debe ir más abajo
        int tempPar = pop(p);
        insertarParOrdenado(p, valorPar); // Sigue bajando
        push(p, tempPar); // Vuelve a poner el par más grande
    }
}

// Ordena solo la sección de pares (en el fondo) de mayor a menor.
// -- VERSIÓN CORREGIDA --
void ordenarParesMayorMenor(Node **p) {
    if (isVoid(*p)) return;
    
    int valor = pop(p);
    ordenarParesMayorMenor(p); // Llama recursiva
    
    if (valor % 2 == 1) {
        // Si es impar, simplemente lo pone de vuelta encima.
        push(p, valor);
    } 
    else {
        // Si es par, llama a la función auxiliar para que
        // lo inserte en el lugar correcto en la sección de pares.
        insertarParOrdenado(p, valor);
    }
}
// --- FIN CORRECCIÓN 'ordenarParesMayorMenor' ---


// Verifica si 'value' existe en una pila 'q' que tiene el formato [valor, contador, ...]
bool existInQ(Node **p, int value){
    if(isVoid(*p)) return false;
    
    if(top(*p) == value) return true; 
    
    int currentValue = pop(p); // Este es el 'valor'
    int counter = pop(p);      // Este es el 'contador'
    
    bool result = existInQ(p, value);
    
    push(p,counter);
    push(p,currentValue);
    return result;
}

// Cuenta cuántas veces aparece 'value' en la pila 'p', sin destruirla.
int count(Node **p, int value){
    if(isVoid(*p)) return 0;
    
    int currentValue = pop(p);
    int counter = count(p, value); // Llama recursiva
    
    if(currentValue == value) counter++; // Suma si lo encuentra
    
    push(p, currentValue); // Vuelve a poner el valor
    
    return counter; // Devuelve el conteo
}

// Crea una pila 'q' a partir de 'p' con formato [val1, cont1, val2, cont2...].
// Preserva la pila 'p' original.
void makeStack(Node **p, Node **q){
    if(isVoid(*p)) return;
    
    int value = pop(p); 
    
    if(!existInQ(q, value)){
        int counter = count(p, value) + 1; 
        pushButtom(q, value);
        pushButtom(q, counter);
    }
    
    makeStack(p,q); 
    
    push(p, value); 
}

// Invierte el orden de la pila (el tope pasa al fondo y viceversa).
void invertStack(Node  **p){
    if(isVoid(*p)) return;
    int value = pop(p); 
    invertStack(p); 
    pushButtom(p, value); 
}

// Inserta 'value' en una pila ordenada de MENOR a MAYOR (ascendente).
// (Tu lógica original ordenaba menor (tope) a mayor (fondo)).
void insertInSortedOrder(Node **p, int value){
    if(isVoid(*p) || value < top(*p)) { 
        push(p, value); 
    } else{
        int cima = pop(p);
        insertInSortedOrder(p,value); 
        push(p, cima);
    }
}

// Ordena la pila de MENOR (tope) a MAYOR (fondo).
void sortStack(Node **p){
    if (isVoid(*p)) return;
    int value = pop(p);
    sortStack(p);
    insertInSortedOrder(p,value);
}

// Apila los dígitos de un número. (Ej: 512 -> pila [5, 1, 2] con 2 en el tope).
void pilaDigitos(Node **p, int numero){
    if(numero < 10){
        push(p, numero);
        return;
    }
    pilaDigitos(p, numero /10);
    int digito = numero % 10;
    push(p,digito);
}

// Suma dos números representados en pilas (A y B) y guarda el resultado en 'aux'.
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

// Añade un elemento en el FONDO de la pila. (Función idéntica a 'pushButtom').
void apilarFondo(Node **p, int value){
    if (isVoid(*p))
    {
        push(p,value);
        return;
    }
    int currentValue = pop(p);
    apilarFondo(p,value);
    push(p,currentValue);
}

// Inserta en orden descendente (mayor a menor) y evita duplicados
// -- VERSIÓN CORREGIDA --
void insertarOdernado(Node **p, int value){
    // Caso base 1: Pila vacía
    if (isVoid(*p)) {
        push(p, value);
        return; 
    }
    
    // Caso base 2: Duplicado
    if (value == top(*p)) {
        cout << "El " << value << " esta repetido\n";
        return; 
    }
    
    // Caso base 3: Encontró su lugar (value >= tope actual)
    if (value >= top(*p)) {
        push(p, value); // Error de sintaxis corregido
        return; 
    }
    
    // Caso recursivo: 'value' es < que el tope, debe ir más abajo
    int currenTop = pop(p);
    insertarOdernado(p, value);
    push(p, currenTop);
}


// Inserta 'valueX' justo DESPUÉS de la primera aparición de 'valueZ' (buscando desde el tope).
bool insertarDespuesZ(Node **p, int valueX, int valueZ){
    if(isVoid(*p)) return false;
    if(valueX == top(*p)){
        cout << "El "<< valueX << " esta repetido\n";
        return false;
    }

    int currentValue = top(*p);
    pop(p);
    if(currentValue == valueZ){
        push(p,currentValue); // Vuelve a poner Z
        push(p,valueX);     // Pone X encima de Z
        return true;
    }
    bool zEncontrado = insertarDespuesZ(p,valueX,valueZ);
    push(p,currentValue); // Reconstruye la pila
    return zEncontrado;
}

// Elimina la PRIMERA aparición de 'value' (buscando desde el tope).
void eliminarPrimero(Node **p,int value){
    if(isVoid(*p)) return;

    if(value == top(*p)) {
        pop(p); // Lo encuentra y lo elimina
        return; // Termina
    }

    int currentValue = top(*p);
    pop(p);
    eliminarPrimero(p,value); // Sigue buscando
    push(p,currentValue); // Reconstruye
}

// Elimina TODAS las apariciones de 'value'. (Función idéntica a 'deleteValue').
void eliminarTodas(Node**p,int value){
    if(isVoid(*p)) return ;
    int currentValue = top(*p);
    pop(p);
    eliminarTodas(p, value);
    if (currentValue != value){
        push(p,currentValue); // Solo vuelve a apilar si NO es el valor
    }
}

// Elimina la ÚLTIMA aparición de 'value' (la más profunda en la pila).
bool eliminarUltima(Node **p, int value ){
    if(isVoid(*p))return false;

    int currentValue = top(*p);
    pop(p);
    bool encontradoUltimo = eliminarUltima(p,value);

    if (encontradoUltimo){
        push(p,currentValue);
        return true;
    }
    else{
        if(currentValue == value){
            return true; // Se encontró, no lo apila
        }else{
            push(p,currentValue);
            return false;
        }
    }
}

// Verifica si 'value' existe en la pila. (Función de búsqueda simple).
bool trueOrFalse(Node **p, int value){
    if (isVoid(*p)) return false;
    
    int currentValue = top(*p);
    pop(p);

    bool encontrado = trueOrFalse(p,value); // Busca en el resto

    push(p, currentValue); // Reconstruye

    return (currentValue == value) || (encontrado);
}

// Función auxiliar (iterativa) para verificar si un número es primo.
bool esPrimo(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false; 
    
    for (int i = 3; (i * i) <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true; 
}

// Elimina todos los NÚMEROS PRIMOS de la pila.
void eliminarPrimos(Node **p) {
    if (isVoid(*p)) return;

    int value = top(*p);
    pop(p);

    eliminarPrimos(p); // Llamada recursiva

    if (esPrimo(value)) {
        return; // Si es primo, NO apilar
    }
    
    push(p, value); // Si NO es primo, apilar
}

// Elimina todos los números IMPARES de la pila (conserva solo los pares).
void eliminarPar(Node **p){
    if(isVoid(*p)) return;

    int value = top(*p);
    pop(p);

    eliminarPar(p);
    if (value % 2 == 1) return; // Si es impar, NO apilar
    push(p, value); // Si es par, apilar
}

// Función auxiliar (iterativa) que verifica si TODOS los dígitos de 'value' son impares.
bool soloImpares( int value){
    if(value == 0) return false; // 0 se considera par

    while(value > 0){
        int digito = value % 10;
        if(digito % 2 == 0){ // Si encuentra un dígito par
            return false;
        }
        value = value / 10;
    }
    return true; // No encontró dígitos pares
}

// Elimina de la pila todos los números compuestos ÚNICAMENTE por dígitos impares.
void eliminarDigitoImpar(Node **p){
    if(isVoid(*p)) return;
    int value = top(*p);
    pop(p);
    eliminarDigitoImpar(p);
    if(soloImpares(value)){
        return; // Si solo tiene impares, NO apilar
    }
    push(p,value); // Si tiene al menos un par, apilar
}

// Función auxiliar (iterativa) que verifica si 'value' tiene AL MENOS DOS dígitos pares.
bool alMenosDosPares(int value){
    int contadorPares = 0;
    if(value == 0) { // Trata el 0 como un solo dígito par
        contadorPares = 1;
    }

    value = abs(value); // Maneja números negativos

    while(value > 0){
        int digito = value % 10;
        if(digito % 2 == 0) contadorPares ++;
        if(contadorPares == 2) return true;
        value = value / 10;
    }
    return false;
}

// Elimina de la pila todos los números que tengan al menos DOS dígitos pares.
// -- VERSIÓN CORREGIDA --
void eliminarDosDigitoPar(Node **p){
    if(isVoid(*p)) return;
    int value = top(*p);
    pop(p);
    
    // CORRECCIÓN: La llamada recursiva debe ser a sí misma
    eliminarDosDigitoPar(p); 
    
    if(alMenosDosPares(value)){
        return; // Si tiene al menos dos pares, no apilar
    }
    push(p,value); // Si no, apilar
}


// Elimina elementos duplicados, conservando solo la ÚLTIMA aparición (la más profunda).
void eliminarRepetidosPrimera(Node **p){
    if(isVoid(*p)) return;
    int currentValue = top(*p);
    pop(p);
    eliminarTodas(p,currentValue); // Elimina todas las otras ocurrencias
    eliminarRepetidosPrimera(p); // Recursividad
    push(p,currentValue); // Vuelve a poner esta (la última)
}

// Elimina elementos duplicados, conservando solo la PRIMERA aparición (la del tope).
void eliminarRepetidosUltima(Node **p){
    if(isVoid(*p)) return;
    int currentValue = top(*p);
    pop(p);
    eliminarRepetidosUltima(p); // Llamada recursiva
    
    bool yaEsta = trueOrFalse(p,currentValue); 
    
    if(!yaEsta){
        push(p,currentValue);
    }
    // Si 'yaEsta' es true, no se apila (se elimina).
}
