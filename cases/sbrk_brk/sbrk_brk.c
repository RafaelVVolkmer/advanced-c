#include <stdio.h>
#include <stdint.h>
#include <errno.h>

static char heap_area[64u * 1024u] __attribute__((section(".heap_section"))) __attribute__((aligned(8u)));

static char *heap_brk = heap_area;
static char *heap_end = (char *)(heap_area + sizeof(heap_area));

static void *customSbrk (intptr_t increment);
static int customBrk (volatile const void *addr);

int main (int argc, char *argv[]) 
{
    void *addr_0 = NULL;
    void *addr_1 = NULL;
    
    printf("Initial Heap: %p\n", heap_area);
    printf("Final Heap: %p\n", heap_end);

    addr_0 = customSbrk(1024);
    if (addr_0 == (void *)-ENOMEM) 
    {
        perror("ERROR: sbrk [ENOMEM]");
        return 1;
    }
    
    printf("New Heap after sbrk(1024): %p\n", heap_brk);

    addr_1 = customSbrk(2048);
    if (addr_1 == (void *)-ENOMEM) 
    {
        perror("ERROR: sbrk [ENOMEM]");
        return 1;
    }
    
    printf("New Heap after sbrk(2048): %p\n", heap_brk);

    return 0;
}

static void *customSbrk (intptr_t increment) 
{
    void *prev_break = NULL;
    void *new_break = NULL;
    
    prev_break = heap_brk;
    new_break = (void *)(heap_brk + increment);

    if (new_break > (void *)heap_end) 
    {
        prev_break = (void *) -ENOMEM;
        goto function_output;
    }

    heap_brk = new_break;

function_output:
    return prev_break;
}

static int customBrk (volatile const void *addr) 
{
    int ret = 0;

    if (addr == NULL) 
    {
        ret = -ENOMEM;
        goto function_output;
    }

    if (addr < (void *)heap_brk) 
    {
        ret = -EINVAL;
        goto function_output;
    }

    heap_brk = (char *)addr;

function_output:
    return ret;
}
