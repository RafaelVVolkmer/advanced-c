#include <stdio.h>
#include <string.h>
#include <errno.h>

static int arrSize(const int array[ ], size_t num_total_bytes);
static int strSize(const char string[ ], size_t __attribute__((unused)) dummy_arg);

#define GET_VET_SIZE(vet)       \
    _Generic( (vet),            \
        int *   : arrSize,      \
        char *  : strSize       \
    ) (vet, sizeof(vet))

int main(int argc, char *argv[]) 
{
    int main_ret = 0u;
    
    int  arr[] = {1u, 2u, 3u, 4u, 5u};
    char str[] = "Hello, World!";
    
    size_t arr_size = 0u;
    size_t str_size = 0u;
    
    arr_size = GET_VET_SIZE(arr);
    if(arr_size <= 0u)
    {
        main_ret = -EINVAL;
        goto end_of_function;
    }
    
    str_size = GET_VET_SIZE(str);
    if(str_size <= 0u)
    {
        main_ret = -EINVAL;
        goto end_of_function;
    }
    
    printf("Size of array:  %zu \n", arr_size);
    printf("Size of string: %zu \n", str_size);

end_of_function:
    return main_ret;
}

static int arrSize(const int array[ ], size_t num_total_bytes) 
{
    int ret = 0u;
    
    size_t num_type_bytes   = 0u;
    size_t total_size       = 0u;
    
    if(array == NULL)
    {
        ret = -ENOMEM;
        goto end_of_function;
    }
    
    num_type_bytes = sizeof(array[0u]);
    if(num_type_bytes <= 0u)
    {
        ret = -EINVAL;
        goto end_of_function;
    }
    
    total_size = (num_total_bytes / num_type_bytes);
    
    ret = (int)(total_size);

end_of_function:
    return ret;
}

static int strSize(const char string[ ], size_t __attribute__((unused)) dummy_arg)
{
    int ret = 0u;
    
    size_t string_size = 0u;
    
    if(string == NULL)
    {
        ret = -ENOMEM;
        goto end_of_function;
    }
    
    string_size = strlen(string);
    if(string_size <= 0u)
    {
        ret = -EINVAL;
        goto end_of_function;
    }
    
    ret = (int)(string_size);
    
end_of_function:
    return ret;
}
