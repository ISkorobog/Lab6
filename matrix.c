#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
typedef struct arguments{
int *A;
int *B;
int *C;
int l1,l2,m,k;
}arguments;
void * dotprod(void* p_arg){

    arguments* arg=(arguments*)p_arg;
    int i,j;
    for(int l=arg->l1;l<arg->l2;l++){i=l/arg->k; j=l%arg->k;
    for(int q=0;q<arg->m;q++)(arg->C)[i*arg->k+j]+=(arg->A)[i*arg->m+q]*(arg->B)[q*arg->k+j];
    //printf("thread:%ul ,C[%d][%d]=%d\n",pthread_self(),i,j,arg->C[i*arg->k+j]);
    }
    return NULL;
}
int main()
{
    int n=1000;
    int m=1000;
    int k=1000;
    int nthread=50;
    int *A=malloc(sizeof(n)*n*m);
    int *B=malloc(sizeof(n)*m*k);
    int *C=malloc(sizeof(n)*n*k);
    srand(time(NULL));
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        A[i*m+j]=rand()%10;
    }
    for(int i=0;i<m;i++)for(int j=0;j<k;j++){
        B[i*k+j]=rand()%10;
    }
    pthread_t* threads=malloc(sizeof(pthread_t)*nthread);
    int *usage=malloc(sizeof(n)*nthread);
    arguments* arg=malloc(sizeof(arguments)*n*k);
    for(int i=0;i<nthread;i++){
        arg[i].A=A;
        arg[i].B=B;
        arg[i].m=m;
        arg[i].k=k;
        arg[i].l1=i*((n*k)/nthread);
        arg[i].l2=((i+1)*((n*k/nthread)));
        if(i==nthread-1)arg[i].l2=n*k;
        arg[i].C=C;

        pthread_create(threads+i,NULL,dotprod,&arg[i]);
    }
    for(int i=0;i<nthread;i++){
            pthread_join(*(threads+i),NULL);}
    /*for(int i=0;i<n;i++){for(int j=0;j<m;j++){
        printf("%d ",A[i*m+j]);
    }printf("\n");}
    printf("\n");
    for(int i=0;i<m;i++){for(int j=0;j<k;j++){
        printf("%d ",B[i*k+j]);
    }printf("\n");}
    printf("\n");
    for(int i=0;i<n;i++){for(int j=0;j<k;j++){
        printf("%d ",C[i*k+j]);
    }printf("\n");}*/
}
