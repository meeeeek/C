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
        newNodo->next=NULL;


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
          //Collegamenti
            
            newNodo->info.wday=i+wday;
            newNodo->info.mese=month;
            newNodo->prev=iter;
            iter->next=newNodo;
            iter=iter->next;
            
          //Incremento giorno e condizioni mese
            int prevDay=newNodo->prev->info.giorno;
            int prevMonth=newNodo->prev->info.mese;
            int prevWday=newNodo->prev->info.wday;
            
           if(prevWday==7){
            newNodo->info.wday=1;
           }
           else {
            newNodo->info.wday=newNodo->prev->info.wday+1;
           }

            if(prevDay==30){    //  scatto Prossimo mese
                newNodo->info.giorno=1;
                newNodo->info.mese=prevMonth+1;
                prevMonth++;
                }

            else{
            newNodo->info.giorno=prevDay+1;
            newNodo->info.mese=prevMonth;

               }
            
            
            }
            

           }

    

}


struct evento createStruct(){
    struct evento new;
    return new;
}

char* gsettString(int n){
    char*giorno;
    switch(n){
        case 1: return "Lun";
        case 2: return "Mar";
        case 3: return "Mer";
        case 4: return "Gio";
        case 5: return "Ven";
        case 6: return "Sab";
        case 7: return "Dom";
    }
}

void printList(nodo**head){puts("");
    nodo*iter=*head;


while(iter!=NULL){    printf("\t%d\t",iter->info.giorno);    iter=iter->next;}
iter=*head;puts("");
while(iter!=NULL){    printf("\t%s\t",gsettString(iter->info.wday));    iter=iter->next;}
iter=*head;
puts("\n");


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


    printList(head);
}
