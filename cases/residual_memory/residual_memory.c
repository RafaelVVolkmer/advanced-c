#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_PASSWORD_LEN 16U

typedef enum clearBufferOptions
{
    NOT_CLEAR_BUFFER    = 0u,
    CLEAR_BUFFER_DATA   = 1u,
    MAX_CLEAR_OPTIONS   = 2u
} clear_buffer_t;

static int Password_setSenstiveData(clear_buffer_t clear_buffer);
static int Stack_readData(clear_buffer_t clear_buffer);

int main(int argc, char *argv[]) 
{
    printf("Result of the operation without clearing the buffer: \n");
    Password_setSenstiveData(NOT_CLEAR_BUFFER);
    Stack_readData(NOT_CLEAR_BUFFER);

    printf("\n");

    printf("Result of the operation without clearing the buffer: \n");
    Password_setSenstiveData(CLEAR_BUFFER_DATA);
    Stack_readData(NOT_CLEAR_BUFFER);

    return 0;
}

static int Password_setSenstiveData(clear_buffer_t clear_buffer) 
{
    int ret = 0u;

    char sensitive_data[MAX_PASSWORD_LEN] = 
            {[0u ... (MAX_PASSWORD_LEN - 1u)] = ' '};

    strncpy(sensitive_data, "MySecretPassword", 
                            (MAX_PASSWORD_LEN - 1u));

    sensitive_data[MAX_PASSWORD_LEN - 1u] = '\0';

    printf("-> Sensitive data: %.16s\n", sensitive_data);

    if (clear_buffer == CLEAR_BUFFER_DATA) 
    {
        if(memset(sensitive_data, 0, sizeof(sensitive_data)) == NULL)
        {
            ret = -ENOMEM;
            goto end_of_function;
        }
    }
    
end_of_function:
    return ret;
}

static int Stack_readData(clear_buffer_t clear_buffer) 
{
    int ret = 0u;

    char buffer[MAX_PASSWORD_LEN];


    if (clear_buffer == CLEAR_BUFFER_DATA) 
    {
        if(memset(buffer, 0, sizeof(buffer)) == NULL)
        {
            ret = -ENOMEM;
            goto end_of_function;
        }
    }

    printf("-> Residual memory on the stack: %s\n", buffer);

end_of_function:
    return ret;
}
