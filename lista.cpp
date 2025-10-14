#include <iostream>
#include "list.h"

using namespace std;  

void show_list(Node *p){
    if(p == NULL){
        cout << "La lista està vacìa";
        return;
    }
    Node *aux = p;
    cout << "Elementos de la lista: ";
    while(aux != NULL){
        cout << aux->value << " ";
        // Previene bucles infinitos si hay un ciclo accidental
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
    int opcion,content;

    while (true){
        cout << "MENÙ "<< "\n";
        cout << "1--INSERTAR POR CABEZA "<< "\n";
        cout << "2--INSERTAR POR COLA "<< "\n";
        cout << "3--ELIMINAR "<< "\n";
        cout << "4--CONTAR "<< "\n";
        cout << "5--MOSTRAR"<< "\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout<< "¿Què nùmero quieres agregar?: ";
            cin >> content;
            insert_head(&p, content);
            break;
        case 2:
            cout<< "¿Què nùmero quieres agregar?: ";
            cin >> content;
            insert_back(&p, content);
            break;
        case 3:
            cout<< "¿Què nùmero quieres eliminar?: ";
            cin >> content;
            if (delete_node(&p,content)){
                cout << "Elemento " << content << " eliminado de la lista.\n";
            } else {
                cout << "Elemento " << content << " no encontrado en la lista.\n";
            }
            break;
        case 4:
            cout << "La lista tiene "<< count(p) << " elementos." << endl;
            break;
        case 5:
            show_list(p);
            break;
        case 6:
            cout << "Saliendo del programa." << endl;
            delete_list(p);
            return 0;
            break;
        default:
            cout << "Opcion no valida";
            break;
            }
        }
delete_list(p);
return 0;
}

    
