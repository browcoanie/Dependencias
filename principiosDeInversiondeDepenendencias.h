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


