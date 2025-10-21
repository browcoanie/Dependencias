
#include <iostream>
using namespace std;


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



void pushButtom(Node **p, int value){
    if(isVoid(*p)) push(p, value);
    int currentValue = pop(p);
    pushButtom(p,value);
    push(p, currentValue);
}


bool existInQ(Node **p, int value){
    if(isVoid(*p)) return false;
    if(top(*p) == value) return true;
    int currentValue = pop(p);
    int counter = pop(p);
    bool result = existInQ(p, value);
    push(p,counter);
    push(p,currentValue);
    return result;
}

int count(Node **p, int value){
    if(isVoid(*p)) return 0;
    int currentValue = pop(p);
    int counter = count(p, value);
    if(currentValue == value) counter ++;
    push(p, currentValue);
}

void makeStack(Node **p, Node **q){
    if(isVoid(*p)) return;
    int value = pop(p);
    if(!existInQ(q, value)){
        int counter = count(p, value) +1;
        pushButtom(q,value);
        pushButtom(q,counter);
    }
    makeStack(p,q);
    push(p, value);
    
}




int main(){

}