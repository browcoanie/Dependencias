#include <iostream>
#include "principiosDeInversiondeDepenendencias.h"
using namespace std;

void showStack(Node *p){
    if (isVoid(p))
    {
        cout << "La lista esta vacia";
        return;
    }
    
    Node *current = p;
    cout << "Tope->";
    while(current != nullptr){
        cout << current -> value;
        if(current -> next != nullptr) cout << "->";
        current = current -> next;
    }   
    cout << "->Fondo" << endl;

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
