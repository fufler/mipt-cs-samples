#include <iostream>

#include <pthread.h>

using namespace std;

typedef struct 
{
    int x;
    pthread_mutex_t* mtx;
} thread_arg;

void* thread_body(void* arg)
{
    thread_arg* _arg = (thread_arg*)arg;

    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(_arg->mtx);
        cout << _arg->x << endl;
        pthread_mutex_unlock(_arg->mtx);
    }

    return nullptr;
}

int main()
{
    pthread_t t1, t2;
    pthread_mutex_t mtx;

    int i1 = 1, i2 = 2;

    pthread_mutex_init(&mtx, nullptr);

    thread_arg arg1 = {i1, &mtx}, arg2 = {i2, &mtx};

    pthread_create(&t1, nullptr, thread_body, &arg1);
    pthread_create(&t2, nullptr, thread_body, &arg2);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    return 0;
}
