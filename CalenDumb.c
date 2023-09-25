#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*
struct tm {int tm_min;          minutes, range 0 to 59           
   int tm_hour;        hours, range 0 to 23             
   int tm_mday;        day of the month, range 1 to 31  
   int tm_mon;         month, range 0 to 11            
int tm_wday;         day of the week, range 0 to 6    
    }

    struct tm current_time;
    time_t t;

    // Ottieni il tempo corrente.
    time(&t);

    // Converte il tempo in una struttura tm.
    current_time = *localtime(&t);

    // Ottieni il giorno del mese dalla struttura tm.
    size_t month_day = current_time.tm_mday;
*/

    


char filename[25]="DATA.txt";

struct schedule{
    int     ggmm;
    char    title[25];
    float   ora;
    char     gsett[15];

};
typedef struct Nodo{
    struct Nodo*next;
    struct schedule info;
}nodo;

int     calcolaGiornoSettimana(int giorno, int mese, int anno) {
    if (mese < 3) {
        mese += 12;
        anno--;
    }
    
    int K = anno % 100;
    int J = anno / 100;
    
    int giornoSettimana = (giorno + 13 * (mese + 1) / 5 + K + K / 4 + J / 4 - 2 * J) % 7;
    
    if (giornoSettimana < 0) {
        giornoSettimana += 7;
    }
    
    return giornoSettimana;
}


void    inserimento             (nodo**head, struct schedule info){
   
    nodo*new=malloc(sizeof(nodo));
    new->info=info;
    new->next=NULL;

    
    if(*head==NULL){
        *head=new;
        //strcpy(new->info.gsett,"Lun");
        return;
    }
//  iter->info.gsett si può aggiorna mediante una formula
//  
//
        nodo*iter=*head;

    while(iter->next != NULL){
        iter=iter->next;
    }

    iter->next=new;
}
struct  schedule scheduleStruct (char*riga){
    struct schedule new;
    
    char*token=strtok(riga,"|"); 

    new.ggmm=atoi(token);
    token=strtok(NULL,"|");

    strcpy(new.title,token);
    token=strtok(NULL,"|");

    new.ora=atof(token);
    token=strtok(NULL,"-");

    strcpy(new.gsett,token);
    //printf("\nRiga\t//%s//\n",token);
    

    return new;
}
void    newEvent(nodo**head){
        int day,month;
        float hours;
        char title[25];
        system("clear");
        printf("\n\n\t\tInserisci giorno e mese in numeri:\t");
        scanf("%d",&day);
        scanf("%d",&month);
        system("clear");
        printf("\n\n\t\tInserisci Titolo:\t");
        scanf("%s",title); 
        system("clear");
        printf("\n\n\t\tInserisci Orario:\t");
        scanf("%f",&hours); 

        struct schedule new;
        new.ggmm=day*100+month;
        strcpy(new.title,title);
        new.ora=hours;
        printf("%s",filename);
        FILE*fptr=fopen(filename,"a"); if(fptr==NULL){fprintf(stderr,"ERRORE\nFiLE FILENAME\n");}
        fprintf(fptr,"%d|%s|%.2f|%s-\n\n",new.ggmm,new.title,new.ora,new.gsett);
        inserimento(head,new);

    }
//          Stampa

    void    linea(){for(int i=0;i<160;i++){printf("_");}puts("");}
    char*   numDivider(int num){
        int a=num%100;        
        int b=(num-a)/100;
        char*data=malloc(sizeof(char)*6);
        snprintf(data, sizeof(data), "%d", num);
                
                data[5]=data[4];
                data[4]=data[3];
                data[3]=data[2];
                data[2]='-';
        

        return data;
}
    void    printLine(nodo**head){
    nodo*iter=*head;
    while(iter!=NULL){
    printf("\t%s\t\t|",iter->info.gsett);
        iter=iter->next;

    }

    linea();
    iter=*head;

    while(iter!=NULL){
        char*data=numDivider(iter->info.ggmm);
        printf("\t%s\t\t|",data);
        iter=iter->next;
    }
    iter=*head;
    puts("");

    while(iter!=NULL){
        if(strcmp("NULL",iter->info.title)==0){printf("\t\t\t|");}
        else{
            printf("\t%s\t\t|",iter->info.title);

        }
        iter=iter->next;
    }
    iter=*head;
    puts("");

    while(iter!=NULL){
        if(iter->info.ora==0){printf("\t\t\t|");}
        else{
            printf("\t%.2f\t\t|",iter->info.ora);
        }
        iter=iter->next;
    }

}

//          Inserimento
   

int main(){


system("clear");
 /*struct tm current_time;
    time_t t;
    current_time = *localtime(&t);
    size_t month_day = current_time.tm_mday;

printf("month_day:%lud",month_day);
*/
FILE*fptr=fopen("DATA.txt","r");    if(fptr==NULL){fprintf(stderr,"Errore\tApertura file fallita\n");exit(1);}
char riga[120];

nodo**head=malloc(sizeof(nodo*));

while(fgets(riga, sizeof(riga), fptr)){
    struct schedule new=scheduleStruct(riga);
    inserimento(head,new);
}
printLine(head);
int digit;
printf("\n\n\tPer nserire un nuovo evento digita 1\t");
scanf("%d",&digit);
if(digit==1){newEvent(head);}

puts("\n");
}