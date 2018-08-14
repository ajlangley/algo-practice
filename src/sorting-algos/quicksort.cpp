// Created by AJ Langley on 13 August, 2018

#include <iostream>
#include <new>
#include <cmath>
#include <ctime>

int *make_rand_array(int);
bool test_q_sort(int);
void quicksort(int*, int, int);
int partition(int*, int, int);
void swap(int*, int, int);

using namespace std;

int main()
{
    int sizes[5] = {1, 2, 3, 10, 11};

    srand(time(0));

    for (int *ptr = sizes; ptr < sizes + 5; ptr++)
        if (!test_q_sort(*ptr))
        {
            cout << "Test failed for size " << *ptr << endl << endl;
            exit(1);
        }

    return 0;
}

int *make_rand_array(int size)
{
    int *arr = new int[size];

    for (int *ptr = arr; ptr < arr + size; ptr++)
        *ptr = rand() % 1000;

    return arr;
}

/*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*
    Verify the quick sort algorithm using
    an array of length size. Return false
    if the result is incorrect, true
    otherwise.
*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*/
bool test_q_sort(int size)
{
    int *arr = make_rand_array(size);

    quicksort(arr, 0, size);

    for (int *ptr = arr; ptr < arr + size - 1; ptr++)
        if (*ptr > *(ptr + 1))
        {
            delete [] arr;

            return false;
        }

    delete [] arr;

    return true;
}

void quicksort(int *arr, int start, int end)
{
    if (start < end - 1)
    {
        int pivot = partition(arr, start, end - 1);
        quicksort(arr, start, pivot);
        quicksort(arr, pivot + 1, end);
    }
}

int partition(int *arr, int start, int end)
{
    int i = start - 1;

    for (int j = start; j < end; j++)
        if (arr[j] <= arr[end])
            swap(arr, ++i, j);

    swap(arr, ++i, end);

    return i;
}

void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
