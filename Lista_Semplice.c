#include<stdio.h>
#include<stdlib.h>
#define size 5

typedef struct Nodo{
    struct Nodo*next;
    int data;
}nodo;

void inserimento(nodo**head,int num){
    
    nodo*new=malloc(sizeof(nodo));  //  Alloco memoria per il nuovo nodo
    new->data=num;                  //  Assegno al nuovo nodo il valore passato tramite la funzione
    if(*head==NULL){                //  Se la lista è vuota, il nuovo nodo sarà la testa
        *head=new;
        return;
    }

    nodo*iter=*head;                //  Creo l'iteratore di tipo nodo, servirà a scorrere la lista fino ad arrivare all'ultimo elemento
    while(iter->next!=NULL){
        iter=iter->next;
    }
    iter->next=new;                 //  Una volta arrivati all'ultimo nodo, lo collego con il nuovo nodo.
    return;

    
}

void printList(nodo**head){
    nodo*iter=*head;
    while(iter!=NULL){
        printf("[%d]",iter->data);
        iter=iter->next;
    }
}
int main(){

nodo**head=malloc(sizeof(nodo));

inserimento(head,10);
inserimento(head,6);
inserimento(head,8);
printList(head);
}