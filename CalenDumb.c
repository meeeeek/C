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
    char title[7];
    
};

typedef struct Nodo{
    struct Nodo*next;
    struct Nodo*prev;
    struct evento info;
}nodo;



int calculateWday(int year, int month, int day) {
    int q, t, x;

    if (month <= 2) {
        month += 12;
        year--;
    }

    q = month / 3;
    t = day + (13 * (month + 1) / 5) + year + (year / 4) - (year / 100) + (year / 400);

    x = t + (q * year) - (q * (year / 4)) + (q * (year / 100)) - (q * (year / 400));
    return x % 7;
}

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

void checkFile(nodo**head){     //funzione che legge il contenuto del file riga per riga, spezzetta il contenuto e lo immagazzina in una struct
    FILE*fptr=fopen("DATA.txt","r");
    struct evento lettura;
while (!feof(fptr)) {
    char riga[30];
    if (fgets(riga, 30, fptr) == NULL) {
        break; // Esci dal ciclo se non riesci a leggere una riga (fine file)
    }
    lettura.giorno = atoi(strtok(riga, "|"));
    lettura.mese = atoi(strtok(NULL, "|"));
    char *temp = strtok(NULL, "|");

    if (temp != NULL) {strcpy(lettura.title, temp);}
    else {   strcpy(lettura.title, ""); }
    temp = strtok(NULL, "|");
    if(temp != NULL){lettura.ora = atof(temp);}
    else {lettura.ora = 0.0;}
    temp = strtok(NULL, "|");
    if(temp != NULL) { lettura.wday = atoi(temp);}
    else {lettura.wday = 0; }
    
    //printf("\nLetto da file:\nGiorno:%d\tMese:%d\nTitle:%s\tOra:%.2f\tWday:%d\n", lettura.giorno, lettura.mese, lettura.title, lettura.ora, lettura.wday);
}


}
void newEvent(nodo**head){

    struct evento new;
    system("clear");
    printf("Inserisci nome evento:\n\t");
    scanf("%s",new.title);
    
    system("clear");
    printf("Inserisci giorno evento:\n\t");
    scanf("%d",&new.giorno);

    system("clear");
    printf("Inserisci mese evento:\n\t");
    scanf("%d",&new.mese);

    system("clear");
    printf("Inserisci ora evento:\n\t");
    scanf("%f",&new.ora);

    new.wday=calculateWday(2023,new.mese,new.giorno);

    FILE*fptr=fopen("DATA.txt","w");
    fprintf(fptr,"%d|%d|%s|%f|%d-",new.giorno,new.mese,new.titolo,new.ora,new.wday);

}   //dobbiamo dire nella stampa che se è disponibile un titolo va stampato altrimenti " " blank.


char* wdayString(int n){
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
char* strMonth(int n){
    switch(n){
        case 1: return "Gen";
        case 2: return "Feb";
        case 3: return "Mar";
        case 4: return "Apr";
        case 5: return "Mag";
        case 6: return "Giu";
        case 7: return "Lug";
        case 8: return "Aug";
        case 9: return "Sep";
        case 10: return "Ott";
        case 11: return "Nov";
        case 12: return "Dic";
    }
}

void printList(nodo**head){puts("");
    nodo*iter=*head;
int size=115;
for(int i=0;i<size;i++){
    printf("_");
    if(i==size/2){
            printf("%s",strMonth(iter->info.mese));
        };
    }
    puts("\n");
char impegno[7]="NULL";

while(iter!=NULL)   {printf("\t%d\t |",iter->info.giorno);    iter=iter->next;}   iter=*head;puts("");
while(iter!=NULL)   {printf("\t%s\t |",wdayString(iter->info.wday));    iter=iter->next;}   iter=*head;puts("");
while(iter!=NULL)   {printf("\t\t_|_");    iter=iter->next;}   iter=*head;puts("");
while(iter!=NULL)   {printf("\t%s\t |",impegno);    iter=iter->next;}   iter=*head;puts("");
while(iter!=NULL)   {printf("\t\t |");    iter=iter->next;}   iter=*head;puts("");




}

//-------------------------------------------------------------------------------------------------------

int main(){
    time_t t;
    struct tm current_time;
    
    time(&t);
    current_time = *localtime(&t);

    int month = current_time.tm_mon + 1;
    int day   = current_time.tm_mday ;
    int wday  = current_time.tm_wday ;
    int year = current_time.tm_year + 1900;

    printf("\nmonth: %d\nday: %d\nwday: %d\n", month,day,wday);
    
    nodo**head=malloc(sizeof(nodo*));

   

    createHead(head,day,month,year,wday);
    
    checkFile(head);


    printList(head);
}
