

#include <iostream>
using namespace std;


struct Node{
    int value;      
    Node *next;     
};

void insert_back(Node **p,int element){
    Node *newElement = new Node;      
    newElement -> value = element;    
    newElement ->next = NULL;         
    if(*p == NULL){                   
        *p = newElement;              
    } else{
        Node *aux = *p;               
        while(aux && aux-> next != NULL){ 
            aux = aux -> next;
        }
        aux -> next = newElement;     
    }
}


bool existsInQ(Node *p, int value){
    Node *aux = p;
    while (aux)
    {
        if (aux -> value == value) return true;
        aux = aux -> next -> next;
    }
    return false;
    

}

Node *makeList(Node *p){
    Node *aux = p, *q=NULL, *aux2 = NULL;
    while (aux)
    {
        if(!existsInQ(q,aux -> value)){
        int counter = count(aux -> next, aux -> value)+1;
        Node *el = new Node, *e = new Node;
        el -> value = aux -> value;
        e-> value = counter;
        el -> next = e;
        e -> next = NULL;
        if (!q)
        {
            q = el, aux2 = e;
        }
        else{
            aux2 -> next = el;
            aux2 = e;
        }
        

        }

        aux = aux -> next;
    }
    return q;
}

int count(Node *p, int value){
    if(!p) return 0;
    Node *aux = p;
    int counter = 0;
    while (aux)
    {
        if (aux -> value == value) counter ++;
        aux = aux -> next;
        
    }
    return counter;
    
}


int main(){

}