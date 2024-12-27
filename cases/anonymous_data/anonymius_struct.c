#include <stdio.h>
#include <errno.h>

typedef struct __attribute__ ((packed)) numbers
{
    int num0;
    int num1;
} nums_t;

static int structSum (nums_t nums);

int main(int argc, char *argv[])
{
    int total_sum = 0u;
    
    total_sum = structSum((nums_t){2u, 4u});

    printf("Total sum: %d\n", total_sum);
    
    return 0;
}

static int structSum (nums_t nums)
{
    int result = 0u;
    
    result = (int)(nums.num0 + nums.num1);
    
    return result;
}
