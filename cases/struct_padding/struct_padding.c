#include <stdio.h>
#include <stdint.h>
#include <errno.h>

typedef struct paddingStruct 
{
    int  element_0;  /*< 4-bytes >*/
    char element_1;  /*< 1-byte (var) + 3-bytes (padding) >*/
    int  element_2;  /*< 4-bytes >*/
} padding_t;

typedef struct __attribute__((packed)) packedStruct
{
    int  element_0;  /*< 4-bytes >*/
    char element_1;  /*< 1-byte  >*/
    int  element_2;  /*< 4-bytes >*/
} packed_t;

#pragma pack(push, 1u)

typedef struct pragmaStruct
{
    int  element_0;  /*< 4-bytes >*/
    char element_1;  /*< 1-byte  >*/
    int  element_2;  /*< 4-bytes >*/
} pragma_t;

#pragma pack(pop)

static int memDumpStruct(const void *data, size_t size);

int main(int argc, char *argv[]) 
{
    padding_t struct_0;
    packed_t  struct_1;
    pragma_t  struct_2;

    struct_0.element_0 = 0x11223344;
    struct_0.element_1 = 0x55;
    struct_0.element_2 = 0xAABBCCDD;

    struct_1.element_0 = 0x11223344;
    struct_1.element_1 = 0x55;
    struct_1.element_2 = 0xAABBCCDD;
    
    struct_2.element_0 = 0x11223344;
    struct_2.element_1 = 0x55;
    struct_2.element_2 = 0xAABBCCDD;
    
    printf("\n");
    printf("=== Padding Struct ===\n");
    printf("struct_0.element_0 = 0x%08X\n", struct_0.element_0);
    printf("struct_0.element_1 = 0x%02X\n", (unsigned char)struct_0.element_1);
    printf("struct_0.element_2 = 0x%08X\n", struct_0.element_2);
    printf("\n");
    
    memDumpStruct(&struct_0, sizeof(struct_0));
    
    printf("\n");
    printf("\n=== Packed Struct ===\n");
    printf("struct_1.element_0 = 0x%08X\n", struct_1.element_0);
    printf("struct_1.element_1 = 0x%02X\n", (unsigned char)struct_1.element_1);
    printf("struct_1.element_2 = 0x%08X\n", struct_1.element_2);
    printf("\n");
    
    memDumpStruct(&struct_1, sizeof(struct_1));
    
    printf("\n");
    printf("=== Pragma Struct ===\n");
    printf("struct_0.element_0 = 0x%08X\n", struct_2.element_0);
    printf("struct_0.element_1 = 0x%02X\n", (unsigned char)struct_2.element_1);
    printf("struct_0.element_2 = 0x%08X\n", struct_2.element_2);
    printf("\n");
    
    memDumpStruct(&struct_2, sizeof(struct_2));

    return 0;
}

static int memDumpStruct(const void *data, size_t size)
{
    int ret = 0u;
    
    const unsigned char *bytes = NULL;
    size_t iterator = 0u;
    
    if (data == NULL)
    {
       ret = -ENOMEM;
       goto end_of_function;
    }
    
    bytes = (const unsigned char *)data;

    printf("Memory dump ---\n size = %zu-bytes\nBytes ---------\n", size);
    
    for (iterator = 0u; iterator < size; iterator++) 
    {
        printf("byte[%zu] = 0x%02X\n", iterator, bytes[iterator]);
    }

end_of_function:
    return ret;
}
