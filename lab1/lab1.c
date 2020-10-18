#include <stdio.h>
#include <string.h>

struct Indexes{
    int is_full;
    int row[15];
    int col[15];
};

int is_up(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes); // +
int is_up_right(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes);
int is_right(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes);  // +
int is_down(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes);   // +
int is_down_right(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes); //+
int is_left(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes);
int is_up_left(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes);
int is_down_left(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes);

//--------------------------------------------------------------------------------------------------------------

int main()
{
    char arr[15][15];
    char target_word[15];
    struct Indexes target_indexes = {.is_full = 0};
    int flag = 0;

    // read arr content
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j)
            scanf(" %c", &arr[i][j]);

    // read target word
    scanf("%s", target_word);

    // traverse the array
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (arr[i][j] != target_word[0]) continue;

            // check all directions; if the word is found, stop traversing
            if (is_up(i, j, target_word, arr, &target_indexes) ||
                is_right(i, j, target_word, arr, &target_indexes) ||
                is_up_right(i, j, target_word, arr, &target_indexes) ||
                is_down_right(i, j, target_word, arr, &target_indexes) ||
                is_down(i, j, target_word, arr, &target_indexes) ||
                is_left(i, j, target_word, arr, &target_indexes) ||
                is_up_left(i, j, target_word, arr, &target_indexes) ||
                is_down_left(i, j, target_word, arr, &target_indexes))
            {
                flag = 1;
                break;
            }
        }
        if (flag) break;
    }

    if (target_indexes.is_full)     // test
        for (int i = 0; i < strlen(target_word); ++i)
            printf("row index: %d, col: index %d\n", target_indexes.row[i], target_indexes.col[i]);
    printf("%s\n", target_word);


    return 0;
}

//--------------------------------------------------------------------------------------------------------------

int is_right(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes)
{
    // check the boundaries
    if (15 - col_index >= strlen(word))
    {
        char word_to_compare[15];
        // record the word to compare with and save its indexes
        for (int i = col_index, j = 0; j < strlen(word); ++i, ++j)
        {
            word_to_compare[j] = board[row_index][i];
            final_indexes->col[j] = i;
            final_indexes->row[j] = row_index;
        }
        // if words are same, the target word is found
        if (!strcmp(word, word_to_compare))
            final_indexes->is_full = 1;
    }
    return final_indexes->is_full;
}

int is_down(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes)
{
    if (15 - row_index >= strlen(word))
    {
        char word_to_compare[15];
        for (int i = row_index, j = 0; j < strlen(word); ++i, ++j)
        {
            word_to_compare[j] = board[i][col_index];
            final_indexes->col[j] = col_index;
            final_indexes->row[j] = i;
        }
        if (!strcmp(word, word_to_compare))
            final_indexes->is_full = 1;
    }
    return final_indexes->is_full;
}

int is_down_right(int row_index, int col_index, char *word, char board[][15], struct Indexes *final_indexes)
{
    if (15 - row_index >= strlen(word) && 15 - col_index >= strlen(word))
    {
        char word_to_compare[15];
        for (int i = row_index, j = col_index, k = 0; k < strlen(word); ++i, ++j, ++k)
        {
            word_to_compare[k] = board[i][j];
            final_indexes->row[k] = i;
            final_indexes->col[k] = j;
        }
        if (!strcmp(word, word_to_compare))
            final_indexes->is_full = 1;
    }
    return final_indexes->is_full;
}

int is_up(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes)
{
    if (row_index+1 >= strlen(word))
    {
        char word_to_compare[15];
        for (int i = row_index, j = 0; j < strlen(word); --i, ++j)
        {
            word_to_compare[j] = board[i][col_index];
            final_indexes->col[j] = col_index;
            final_indexes->row[j] = i;
        }
        if (!strcmp(word, word_to_compare))
            final_indexes->is_full = 1;
    }
    return final_indexes->is_full;
}

int is_up_right(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes)
{
    if (row_index+1 >= strlen(word) && 15 - col_index >= strlen(word))
    {
        char word_to_compare[15];
        for (int i = row_index, j = col_index, k = 0; k < strlen(word); --i, ++j, ++k)
        {
            word_to_compare[k] = board[i][j];
            final_indexes->row[k] = i;
            final_indexes->col[k] = j;
        }
        if (!strcmp(word, word_to_compare))
            final_indexes->is_full = 1;
    }
    return final_indexes->is_full;
}

int is_left(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes)
{
    if (col_index+1 >= strlen(word))
    {
        char word_to_compare[15];
        for (int i = col_index, j = 0; j < strlen(word); --i, ++j)
        {
            word_to_compare[j] = board[row_index][i];
            final_indexes->col[j] = i;
            final_indexes->row[j] = row_index;
        }
        if (!strcmp(word, word_to_compare))
            final_indexes->is_full = 1;
    }
    return final_indexes->is_full;
}

int is_up_left(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes)
{
    if (row_index+1 >= strlen(word) && col_index+1 >= strlen(word))
    {
        char word_to_compare[15];
        for (int i = row_index, j = col_index, k = 0; k < strlen(word); --i, --j, ++k)
        {
            word_to_compare[k] = board[i][j];
            final_indexes->row[k] = i;
            final_indexes->col[k] = j;
        }
        if (!strcmp(word, word_to_compare))
            final_indexes->is_full = 1;
    }
    return final_indexes->is_full;
}

int is_down_left(int row_index, int col_index, char word[], char board[][15], struct Indexes *final_indexes)
{
    if (15 - row_index >= strlen(word) && col_index+1 >= strlen(word))
    {
        char word_to_compare[15];
        for (int i = row_index, j = col_index, k = 0; k < strlen(word); --i, ++j, ++k)
        {
            word_to_compare[k] = board[i][j];
            final_indexes->row[k] = i;
            final_indexes->col[k] = j;
        }
        if (!strcmp(word, word_to_compare))
            final_indexes->is_full = 1;
    }
    return final_indexes->is_full;
}