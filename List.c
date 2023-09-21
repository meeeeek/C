#include<stdio.h>
#include<stdlib.h>

typedef struct Nodo{
    int data;
    struct Nodo*next;
}nodo;

void Insert(nodo**head,int num){
    nodo*new=malloc(sizeof(nodo));
    new->data=num;
    nodo*iter=*head;

    if(*head==NULL){
        *head=new;
        return;
    }
    while(iter->next!=NULL){
        iter=iter->next;
    }
   iter->next=new;
   return;
}

void Remove(nodo**head,int num){
    nodo*iter=(*head);
    nodo*prev=NULL;
    while(iter->data!=num){
        prev=iter;
        iter=iter->next;
    }
    prev->next=iter->next;
    free(iter);
    
}

void printList(nodo**head){
    puts("");
    nodo*iter=*head;
    while(iter!=NULL){
        printf("[%d]",iter->data);
        iter=iter->next;
    }
    puts("");
}

int main(){
    
    nodo**head=malloc(sizeof(nodo*));
    Insert(head,10);
    Insert(head,1);
    Insert(head,5);
    printList(head);
    Remove(head,1);
    printf("\nRimozione del nodo contenente 1");
    printList(head);

}