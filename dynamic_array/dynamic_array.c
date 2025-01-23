#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define SUCCESS (uint8_t)(0u)

typedef struct
{
    int *elements;
    int count;
    int capacity;
} dynamic_array_t;
    
void *MEM_safeRealloc (void **pointer, size_t new_size);
int DYNAMIC_changeArraySize (dynamic_array_t *array, size_t new_size);

int main (int argc, char *argv[]) 
{
    int ret = SUCCESS;
    
    dynamic_array_t array;
    
    size_t array_size   = 0u;
    size_t iterator     = 0u;
    
    array_size = 10u;
    
    memset(&array, 0, sizeof(array));
    
    ret = DYNAMIC_changeArraySize(&array, array_size);
    if (ret != SUCCESS)
    {
        if (ret == -ENOMEM)
        {
            free(array.elements);
            array.elements = NULL;
        }
      
        goto main_output;
    }
    
    for (iterator = 0u; iterator < array_size; ++iterator)
    {
        array.elements[array.count++] = iterator;
    }
    
    for(iterator = 0u; iterator < array.count; ++iterator)
    {
        printf("%d\n", array.elements[iterator]);
    }

main_output:
    return ret;
}

void *MEM_safeRealloc (void **pointer, size_t new_size)
{
    void *new_addr = NULL;
    
    if (pointer == NULL || new_size <= 0u)
    {
        new_addr = NULL;
        goto function_output;
    }
    
     new_addr = (void *)realloc(*pointer, new_size);
     if (new_addr != NULL)
     {
        *pointer = new_addr;
     }

function_output:
     return new_addr;
}

int DYNAMIC_changeArraySize (dynamic_array_t *array, size_t new_size)
{
    int output = SUCCESS;
    
    size_t iterator = 0u;
    
    if (array == NULL)
    {
        output = -EINVAL;
        goto function_output;
    }
    
    if (new_size <= 0u)
    {
        output = -EINVAL;
        goto function_output; 
    }
    
    for (iterator = 0u; iterator < new_size; ++iterator)
    {
        if(array->count >= array->capacity)
        {
            array->capacity = (array->capacity == 0u) ? 256u :
                              (array->capacity != 0u) ? (array->capacity * 2u) : 0u;
          
            array->elements =                                                 \
              MEM_safeRealloc(                                                \
                                (void **)&array->elements,                    \
                                (array->capacity * sizeof(*array->elements))  \
                             );
          
            if (array->elements == NULL)
            {
                output = -ENOMEM;
                goto function_output;
            }
        }
    }
 
 function_output:  
    return output;
}
