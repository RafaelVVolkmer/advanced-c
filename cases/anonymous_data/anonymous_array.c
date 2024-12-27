#include <stdio.h>
#include <errno.h>

static int vetSum (int array[], size_t arr_size);

int main(int argc, char *argv[])
{
    int total_sum = 0u;
    
    total_sum = vetSum( (int[]){1u, 2u, 3u, 4u, 5u}, 5u );

    printf("Total sum: %d\n", total_sum);
    
    return 0;
}

static int vetSum (int array[], size_t arr_size)
{
    int ret         = 0u;
    int result      = 0u;
    
    size_t iterator = 0u;
    
    if (array == NULL)
    {
        ret = -ENOMEM;
        goto end_of_function;
    }
    
    for (iterator = 0u; iterator < arr_size; iterator++)
    {
        result += array[iterator];
    }
    
    ret = result;
    
end_of_function:
    return ret;
}
