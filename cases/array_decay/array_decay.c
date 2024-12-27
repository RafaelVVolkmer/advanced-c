#include <stdio.h>
#include <string.h>
#include <errno.h>

static int arrayDecay(void);
static int helperFunction(int array[]);

int main(int argc, char *argv[]) 
{
    arrayDecay();

    return 0;
}

static int arrayDecay(void)
{
    int ret = 0u;

    int array[] = { 0u, 1u, 2u, 3u,4u };

    printf("- Array memory size: %i-bytes\n", sizeof(array));

    ret = helperFunction(array);
    if(ret < 0u)
    {
        ret = -EINVAL;
        goto end_of_function;
    }
    
end_of_function:
    return ret;
}

static int helperFunction(int array[])
{
    int ret = 0u;

    if(array == NULL)
    {
        ret = -ENOMEM;
        goto end_of_function;
    }

    printf("- Array memory size: %i-bytes \n", sizeof(array));

end_of_function:
    return ret;
}
