#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct evento{
    int giorno;
    char titolo[15];
    float ora;
    int wday;
    int mese;
};

typedef struct Nodo{
    struct Nodo*next;
    struct Nodo*prev;
    struct evento info;
}nodo;





void createHead (nodo**head,int day,int month,int year, int wday){
    
    nodo*iter=*head;

    for(int i=0;i<7;i++){

        nodo*newNodo=malloc(sizeof(nodo));

        if(i==0){               //  Creazione della testa - giorno corrente
            
            struct evento new;
            new.giorno=day;
            new.mese=month;
            new.wday=wday;


            newNodo->info=new;
            *head=newNodo;
            (*head)->prev=NULL;
            iter=*head;
            
        }

        if(i>0){
            int temp=0;
            if(day+i==30 && month==9){newNodo->info.giorno+=day+i;}
            else{newNodo->info.giorno=day+i;}

            newNodo->info.wday=i+wday;
            newNodo->info.mese=month;

            iter->next=newNodo; 
            iter=iter->next;
            iter->prev=newNodo;
           }

    }

}


struct evento createStruct(){
    struct evento new;
    return new;
}



void printList(nodo**head){puts("");
    nodo*iter=*head;

for(int i=0;i<7;i++){
printf("\nGiorno:\t%d\nMese:\t%d\nGSett:\t%d\n",iter->info.giorno,iter->info.mese,iter->info.wday);
    iter=iter->next;
                printf("\tPREV = %d\n",iter->prev->info.giorno);

}

}

//-------------------------------------------------------------------------------------------------------

int main(){
    time_t t;
    struct tm current_time;
    
    // Ottenere l'orario corrente
    time(&t);
    current_time = *localtime(&t);
    
    // Aggiungere 1 al mese (per ottenere il numero del mese da 1 a 12)
    int month = current_time.tm_mon + 1;
    int day   = current_time.tm_mday ;
    int wday  = current_time.tm_wday ;
    int year = current_time.tm_year + 1900;


    printf("\nmonth: %d\nday: %d\nwday: %d\n", month,day,wday);
    
    nodo**head=malloc(sizeof(nodo*));
    createHead(head,day,month,year,wday);

/*
    printf("\n%d\n%d\n%d\n",(*head)->info.giorno,(*head)->info.mese,(*head)->info.wday);
    printf("\n%d\n%d\n%d\n",(*head)->next->info.giorno,(*head)->next->info.mese,(*head)->next->info.wday);
    printf("\n%d\n%d\n%d\n",(*head)->next->next->info.giorno,(*head)->next->next->info.mese,(*head)->next->next->info.wday);
*/
    printList(head);
}
