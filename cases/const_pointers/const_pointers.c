#include <stdio.h>
#include <string.h>
#include <errno.h>

static int constPointer(void);

int main(int argc, char *argv[]) 
{
    constPointer();

    return 0;
}

static int constPointer(void)
{
    int ret = 0u;
    
    int variable_a = 32u;
    int variable_b = 32u;
    
    const int * const all_const_pointer = NULL;
    
    const int *const_val_pointer        = &variable_a;
    int * const const_addr_pointer      = &variable_b;
    
    /*< Here you can change the address, but not the value >*/
    const_val_pointer++;
    // (*const_val_pointer)++;
    
    /*< Here you can change the value, but not the address >*/
    (*const_addr_pointer)++;
    // const_addr_pointer++;
    
    /*< Here you can't change anything >*/
    // (*all_const_pointer)++;
    // all_const_pointer++;

end_of_function:
    return ret;
}
