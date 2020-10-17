#include <stdio.h>
#include <string.h>

struct Indexes{
    int is_full;
    int row[15];
    int col[15];
};

int is_up_right(int row_index, int col_index, char *word, char board[][], struct Indexes *final_indexes);
int is_right(int row_index, int col_index, char *word, char board[][], struct Indexes *final_indexes);
int is_down(int row_index, int col_index, char *word, char board[][], struct Indexes *final_indexes);
int is_down_right(int row_index, int col_index, char *word, char board[][], struct Indexes *final_indexes);


int main()
{
    char arr[15][15];
    char target_word[15], reversed_target_word[15];
    char *word_to_use;
    struct Indexes target_indexes;

    // read arr content
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j)
            scanf(" %c", &arr[i][j]);

    scanf("%s", target_word);                                        // read a target word
    for(int i = 0, j = strlen(target_word)-1; j >= 0; ++i, --j)      // make the traversed target word
        reversed_target_word[i] = target_word[j];

    // traverse the array
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (arr[i][j] == target_word[0])
                word_to_use = target_word;
            else if (arr[i][j] == reversed_target_word[0])
                word_to_use = reversed_target_word;
            else
                continue;

            // check all directions; if the word is found, stop traversing
            if (is_up_right(i, j, word_to_use, arr, &target_indexes) ||
                is_right(i, j, word_to_use, arr, &target_indexes) ||
                is_down_right(i, j, word_to_use, arr, &target_indexes) ||
                is_down(i, j, word_to_use, arr, &target_indexes))
                break;
        }
    }


    return 0;
}