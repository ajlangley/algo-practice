#include <iostream>
#include <ctime>

using namespace std;

int find_max_subarray_brute_force(int*, int&, int&, int);
int *find_max_subarray_recursive(int*, int, int);
int *find_max_crossing_subarray(int*, int, int, int);
int *find_max_sum(int*, int*, int*);
int *generate_array(int, int);
void calculate_recursive_advantage(int);

int main()
{
    const int MAX_ENTRY = 50;

    srand(time(0));

    calculate_recursive_advantage(MAX_ENTRY);

    return 0;
}

int find_max_subarray_brute_force(int *arr, int &left_index, int &right_index, int size)
{
    int max_sum = arr[0], sum = 0;
    left_index = 0, right_index = 0;

    for (int i = 0; i < size; i++)
    {
        sum = 0;

        for (int j = i; j < size; j++)
        {
            sum += arr[j];

            if (sum > max_sum)
            {
                left_index = i;
                right_index = j;
                max_sum = sum;
            }
        }
    }

    return max_sum;
}

int *find_max_subarray_recursive(int *arr, int left_index, int right_index)
{
    if (left_index == right_index)
        return new int[3] {left_index, right_index, arr[left_index]};

    int mid = (left_index + right_index) / 2;

    return find_max_sum(find_max_subarray_recursive(arr, left_index, mid),
                        find_max_subarray_recursive(arr, mid + 1, right_index),
                        find_max_crossing_subarray(arr, left_index, mid, right_index));
}

int *find_max_crossing_subarray(int *arr, int left_index, int mid, int right_index)
{
    int left_sum = arr[mid], right_sum = arr[mid + 1], sum = left_sum, max_left = mid, max_right = mid + 1;

    for (int i = mid - 1; i >= left_index; i--)
    {
        sum += arr[i];

        if (sum > left_sum)
        {
            left_sum = sum;
            max_left = i;
        }
    }

    sum = right_sum;

    for (int i = mid + 2; i <= right_index; i++)
    {
        sum += arr[i];

        if (sum > right_sum)
        {
            right_sum = sum;
            max_right = i;
        }
    }

    return new int[3] {max_left, max_right, left_sum + right_sum};
}

int *find_max_sum(int *left_result, int *right_result, int *cross_result)
{
    int left_sum = left_result[2], right_sum = right_result[2], cross_sum = cross_result[2],
    max_left = left_result[0], max_right = left_result[1], max_sum = left_sum;

    if (right_sum > max_sum)
    {
        max_sum = right_sum;
        max_left = right_result[0];
        max_right = right_result[1];
    }
    if (cross_sum > max_sum)
    {
        max_sum = cross_sum;
        max_left = cross_result[0];
        max_right = cross_result[1];
    }

    delete [] left_result;
    delete [] right_result;
    delete [] cross_result;

    return new int[3] {max_left, max_right, max_sum};
}

int *generate_array(int size, int max_entry)
{
    int *arr = new int[size], *ptr = arr - 1;

    while (ptr++, ptr < arr + size)
        *ptr = (rand() % (2 * max_entry)) - max_entry;

    return arr;
}

// Return the problem size for which the recursive solution
// outperforms the quadratic time one.
void calculate_recursive_advantage(int max_entry)
{
    int *arr, *result, n = 0, left_index, right_index, sum;

    // Loop to a large number to compare running times for
    // different values of n.
    while (++n, n < 1000)
    {
        left_index = 0;
        right_index = n;

        arr = generate_array(n, max_entry);

        clock_t start = clock();

        sum = find_max_subarray_brute_force(arr, left_index, right_index, n);

        clock_t quad_time = clock() - start;
        start = clock();

        result = find_max_subarray_recursive(arr, 0, n - 1);

        clock_t recursive_time = clock() - start;


        delete [] arr;
        delete [] result;

        printf("n: %d\tRecursive time:%d\tQuadratic time:%d\n", n, recursive_time, quad_time);

        //if (recursive_time <= quad_time)
         //   return n;
    }
}
