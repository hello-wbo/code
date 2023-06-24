#include <stdio.h>
#include <assert.h>
#include <pthread.h>

pthread_t thr;
pthread_mutex_t mutex;
pthread_cond_t cond;
int done = 0;

void* mythread(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("this is my thread---%c------\n", *(char*)arg);
    done = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void join() {
    pthread_mutex_lock(&mutex);
    while (done == 0) {
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[]) {
    pthread_t p[10];
    int rc;
    printf("main: begin\n");
    char a[21] = "abcdefghi";
    for (int i = 0; i < 9; i++) {
        rc = pthread_create(&p[i], NULL, mythread, (void*)&a[i]);
        assert(rc == 0);
    }

    join();

    printf("main: end\n");
    return 0;
}
