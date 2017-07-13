#include <stdio.h>
#include <stdlib.h>

#define ITOA_S(in) ITOA_SI(in)
#define ITOA_SI(in) #in

int main() 
{
    #define CPPVARSSCANF_IGNORECHARACTERS 64
    printf("%s", ITOA_S((CPPVARSSCANF_IGNORECHARACTERS - 1)));

    const char* txt = malloc(128 * sizeof(char));
    int res = scanf("%*1[^#]%*2c%s%*[^\n]", txt);
    if (res == 0) printf("N");
    printf(txt);
    return 0;
}
