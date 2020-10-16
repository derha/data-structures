#include <stdio.h>

int main()
{
    char arr[15][15];
    char word[15];

    for (int i = 0; i < 15; ++i)        // read arr content
        for (int j = 0; j < 15; ++j)
            scanf(" %c", &arr[i][j]);

    scanf("%s", word);                  // read target word


    return 0;
}