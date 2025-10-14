#include <iostream>
#include "principiosDeInversiondeDepenendencias.h"
using namespace std;

void mostrar(Node *p){
    if(p == NULL){
        cout << "La lista está vacía";
        return;
    }
    Node *aux = p;
    cout << "Elementos de la lista: ";
    while(aux != NULL){
        cout << aux->value << " ";
        if (aux == aux->next) {
            cout << "\nError: ciclo detectado en la lista.";
            break;
        }
        aux = aux->next;
    }
    cout << endl;
}

int main(){
    Node *p = NULL;
    int opcion, content;

    while (true)
    {
        cout << "1--Ingresar elemento" << endl;
        cout << "2--Mostrar lista" << endl;
        cout << "3--Quitar repetidos" << endl;
        cout << "4--Salir" << endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "¿Qué número quieres agregar?: ";
            cin >> content;
            push(&p, content);
            break;
        case 2:
            mostrar(p);
            break;
        case 3:
            deleteRepeated(&p);
            break;
        case 4:
            return 0;
        default:
            cout << "Opción inválida" << endl;
            break;
        }
    }
    
    return 0;
}