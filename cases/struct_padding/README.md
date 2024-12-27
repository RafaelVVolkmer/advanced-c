## STRUCT PADDING

<img src="excalidraw/struct_padding.svg" alt="Struct Padding" style="width: 800%; border: none;"/>

```c
typedef struct paddingStruct 
{
    int  element_0;
    char element_1;
    int  element_2;
} padding_t;

```

```c
typedef struct __attribute__((packed)) packedStruct 
{
    int  element_0;
    char element_1;
    int  element_2;
} packed_t;

```

```c
#pragma pack(push, 1u)

typedef struct pragmaStruct 
{
    int  element_0;
    char element_1;
    int  element_2;
} pragma_t;

#pragma pack(pop)
```
