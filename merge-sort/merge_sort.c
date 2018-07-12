#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <memory.h>

#define SIZE 10
#define MAX_INT ~(1 << 31)

int *make_random_list (int);
void display_list (int*, int);
void merge_sort (int*, int, int);
void merge (int*, int, int, int);


int main (void)
{
    srand(time(0));

    int *list = make_random_list(SIZE);

    printf("Unsorted list:\n\n");
    display_list(list, SIZE);

    merge_sort(list, 0, SIZE);

    printf("Sorted list:\n\n");
    display_list(list, SIZE);

    return 0;
}


// Make a random list of numbers
int *make_random_list (int size)
{
    int *rand_list = (int*)(malloc(size * sizeof(int)));

    for (int *ptr = rand_list; ptr < rand_list + size; ptr++)
        *ptr = rand() % 100;

    return rand_list;
}

void display_list (int *list, int size)
{
    for (int *ptr = list; ptr < list + size; ptr++)
        printf("%d ", *ptr);
    printf("\n\n");
}

void merge_sort (int *list, int p, int q)
{
    if (q - p > 1)
    {
        int m = (p + q) / 2;
        merge_sort(list, p, m);
        merge_sort(list, m, q);
        merge(list, p, m, q);
    }
}

void merge (int *list, int p, int m, int q)
{
    int l_size = m - p;
    int r_size = q - m;

    int *l_list = (int*) malloc((l_size + 1) * sizeof(int));
    int *r_list = (int*) malloc((r_size + 1) * sizeof(int));

    memcpy(l_list, list + p, l_size * sizeof(int));
    memcpy(r_list, list + m, r_size * sizeof(int));

    // Assign last element of each array sentinel value of INFINITY
    l_list[l_size] = MAX_INT;
    r_list[r_size] = MAX_INT;

    //display_list(l_list, l_size + 1);
    //display_list(r_list, r_size + 1);
    //printf("\n\n");

    int i = 0, j = 0, k = p;

    while (k < q)
    {
        if (l_list[i] < r_list[j])
        {
            list[k] = l_list[i];
            i++;
        }
        else
        {
            list[k] = r_list[j];
            j++;
        }

        k++;
    }

    free(l_list);
    free(r_list);
}

