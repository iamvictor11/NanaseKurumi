#include <stdio.h>
#include <stdint.h>

uint16_t compressed[] = {
    0x0000
};
int main()
{
    printf("\x1b%%G");
    printf("你好，世界！\n");
    printf("Hello, 世界！\n");
    printf("🌍 🌎 🌏\n");
    
    // for (int i = 0; compressed[i] != 0; i++)
    // {
    //     uint8_t count = compressed[i] >> 8;
    //     uint8_t ch = compressed[i] & 0x00FF;
    //     for (int j = 0; j < count; j++)
    //         putchar(ch);
    // }
    
    fflush(stdout);
    char ch;
    scanf("%c", &ch);
    
    return 0;
}