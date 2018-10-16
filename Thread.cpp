//Cong Meng

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

#define ARRAY_SIZE 20
#define THREAD 2

int a[ARRAY_SIZE];
int part = 0;

void merge_sort(int low, int high);
void* merge_sort(void* arg);
void merge_array(int low, int mid, int high);

int main(){
	//creating array
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++){
        a[i] = rand() % 100;
    }

    cout << "Orginal Array: ";
    for (int i = 0; i < ARRAY_SIZE; i++){
        cout << a[i] << " ";
    }

    cout << endl;

    //creating two threads
    pthread_t threads[THREAD];
    for (int i = 0; i < THREAD; i++){
        pthread_create(&threads[i], NULL, merge_sort, (void*)NULL);
    }

    // joining threads
    for (int i = 0; i < THREAD; i++){
        pthread_join(threads[i], NULL);
    }


    //merge two array
    merge_array(0, (ARRAY_SIZE - 1)/2, ARRAY_SIZE - 1);


    cout << "Sorted Array:  ";
    for (int i = 0; i < ARRAY_SIZE; i++){
        cout << a[i] << " ";
    }

    return 0;
}


// merge sort function
void merge_sort(int low, int high)
{
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high) {

        // calling first half
        merge_sort(low, mid);

        // calling second half
        merge_sort(mid + 1, high);

        // merging the two halves
        merge_array(low, mid, high);
    }
}

// thread function for multi-threading
void* merge_sort(void* arg)
{
    // which part out of 4 parts
    int thread_part = part++;

    // calculating low and high
    int low = thread_part * (ARRAY_SIZE / THREAD);
    int high = (thread_part + 1) * (ARRAY_SIZE / THREAD) - 1;

    // evaluating mid point
    int mid = low + (high - low) / 2;
    if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);

        merge_array(low, mid, high);
    }
}

// merge function for merging two parts
void merge_array(int low, int mid, int high){

    int left_size = mid - low + 1;
    int right_size = high - mid;

	//left and right part array
    int* left = new int[left_size];
    int* right = new int[right_size];

    for (int i = 0; i < left_size; i++){
        left[i] = a[i + low];
    }
    for (int i = 0; i < right_size; i++){
        right[i] = a[i + mid + 1];
    }

    int c = low;
    int i = 0;
    int j = 0;

    // merge array
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j])
            a[c++] = left[i++];
        else
            a[c++] = right[j++];
    }

    // collect rest element from left array
    while (i < left_size) {
        a[c++] = left[i++];
    }

    // collect rest element from right array
    while (j < right_size) {
        a[c++] = right[j++];
    }
}


