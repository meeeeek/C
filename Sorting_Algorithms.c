#include<stdio.h>
#include<stdlib.h>

void swap       (int*a,int*b){
    int temp;
    temp=*a;
    *a=*b;
    *b= temp;
    return; }
void bubblesort (int*A,int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size-1; j++){
            if(A[j]>A[j+1]){
                swap(&A[j],&A[j+1]);
            }
        }
    }}
void selectSort (int*A,int size){

    for(int i=0;i<size;i++){
        int min = i;
        for(int j=i+1;j<size;j++){
            if(A[j]<A[min])
                min=j;
        }
        swap(&A[i],&A[min]);
    }
    
    }
void insertSort(int*A,int size){
    int j=0;
    int temp;
    for(int i=1;i<size;i++){
        j=i-1;
        temp=A[i];
        while(j>=0 && A[j]>temp){
            A[j+1]=A[j];
            j--;
            }
A[j+1]=temp;
        }
    }
void print      (int*A,int size){   
    puts("");
    for(int i=0;i<size;i++){
        printf("[%d]",A[i]);
    }}

int  main       (int argc,char*argv[]){
    int size=atoi(argv[1]);
    int*A=malloc(sizeof(int)*size);
    for(int i=0;i<size;i++){
        A[i]=rand()%9;
    }
    print(A,size);
    //bubblesort(A,size);
    //selectSort(A,size);
    insertSort(A,size);
    print(A,size);
}
