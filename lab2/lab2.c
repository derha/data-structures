#include <stdio.h>

struct Point
{
    int row;
    int col;
};

struct Blob
{
    // point array and counter for those points
};

int main()
{
    // greed size
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    struct Point input_point;

    for (int i = 0;; ++i)
    {
        scanf("%d", &input_point.row);
        if (input_point.row < 0) break;
        scanf("%d", &input_point.col);


    }
    return 0;
}