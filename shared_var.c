#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;
void* sum(void *p_arg){
    unsigned long *v=(int *)p_arg;
    pthread_mutex_lock(&lock);
    for(int i=0;i<1000000000;i++){
            //pthread_mutex_lock(&lock);
            (*v)++;
            //pthread_mutex_unlock(&lock);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}
int main()
{
    pthread_mutex_init(&lock,NULL);
    pthread_t q,e;
    int v=0;
    pthread_create(&q,NULL,sum,&v);
    pthread_create(&e,NULL,sum,&v);

    pthread_join(q,NULL);
    pthread_join(e,NULL);
    pthread_mutex_destroy(&lock);
    printf("%d\n",v);
}
