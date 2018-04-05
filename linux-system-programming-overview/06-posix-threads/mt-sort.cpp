#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <chrono>

#include <pthread.h>

using namespace std;

constexpr unsigned int N = 32*1024;

void sort(unsigned int* arr, unsigned int n)
{
    for (unsigned int i = 0; i < n-1; i++)
        for (unsigned int j = i+1; j < n; j++)
            if (arr[j] < arr[i])
                swap(arr[j], arr[i]);
}


void merge(unsigned int* a, unsigned int l1, unsigned int* b, unsigned int l2, unsigned int *c) {
    unsigned int p1 = 0, p2 = 0, p = 0;

    while ((p1 < l1) && (p2 < l2))
        if (a[p1] < b[p2])
            c[p++] = a[p1++];
        else
            c[p++] = b[p2++];

    while (p1 < l1)
        c[p++] = a[p1++];

    while (p2 < l2)
        c[p++] = b[p2++];
}

struct sort_arg
{
    unsigned int* data;
    unsigned int l;
};

void* sort_thread(void* _arg)
{
    auto arg = static_cast<sort_arg*>(_arg);

    sort(arg->data, arg->l);

    return nullptr;
}

struct merge_arg
{
    unsigned int* a;
    unsigned int* b;
    unsigned int* c;
    unsigned int l1;
    unsigned int l2;
};

void* merge_thread(void* _arg)
{
    auto arg = static_cast<merge_arg*>(_arg);

    merge(arg->a, arg->l1, arg->b, arg->l2, arg->c);

    return nullptr;
}

int main(int argc, char** argv)
{
    assert(argc == 2);

    int p = atoi(argv[1]);
    assert((p >= 0) && (p <= 10));

    unsigned int n = 1 << p;

    unsigned int* data = new unsigned int[N];
    unsigned int* tmp = new unsigned int[N];

    for (unsigned int i = 0; i < N; i++)
        data[i] = N-1-i;

    auto start = chrono::steady_clock::now();

    unsigned int chunk = N/n;
    pthread_t* threads = new pthread_t[n];
    sort_arg* sort_args = new sort_arg[n];
    merge_arg* merge_args = new merge_arg[1+n/2];

    for (unsigned int i = 0; i < n; i++) {
        sort_args[i] = {&data[chunk*i], chunk};
        pthread_create(&threads[i], nullptr, sort_thread, &sort_args[i]);
    }

    for (unsigned int i = 0; i < n; i++)
        pthread_join(threads[i], nullptr);

    while (chunk < N) {
        for (unsigned int i = 0; i < N / chunk / 2; i++) {
            merge_args[i] = {&data[2 * i * chunk], &data[(2 * i + 1) * chunk], &tmp[2 * i * chunk], chunk, chunk};
            pthread_create(&threads[i], nullptr, merge_thread, &merge_args[i]);
        }

        for (unsigned int i = 0; i < N / chunk / 2; i++)
            pthread_join(threads[i], nullptr);

        swap(data, tmp);
        chunk *= 2;
    }

    auto duration = std::chrono::duration_cast<chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    cout << duration.count() << endl;


    for (unsigned int i = 0; i < N; i++)
        assert(data[i] == i);

    delete[] data;
    delete[] tmp;
    delete[] threads;
    delete[] sort_args;
    delete[] merge_args;

    return 0;
}