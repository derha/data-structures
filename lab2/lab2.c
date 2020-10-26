#include <stdio.h>
#include <stdlib.h>

struct Point
{
    int row;
    int col;
};

struct Blob
{
    struct Point *points;
    int counter;
};

// int find_blob(struct Blob *blobs, int blobs_num, struct Point point);
// int is_blob(struct Blob *blob, struct Point point);

//---------------------------------------------------------------------------------------------------------------------

int main()
{
    // greed size
    int rows, cols;
    scanf("%d %d", &rows, &cols);



    return 0;
}

//---------------------------------------------------------------------------------------------------------------------

/*int find_blob(struct Blob *blobs, int blobs_num, struct Point point)
{
    for (int i = 0; i < blobs_num; ++i)
        if (is_blob(&blobs[i], point))
        {
            printf("Blob index: %d\n", i); //delete
            return 1;
        }

    return 0;
}

int is_blob(struct Blob *blob, struct Point point)
{
    for (int i = 0; i < blob->counter; ++i)
    {
        if (point.row >= blob->points[i].row - 1 && point.row <= blob->points[i].row + 1 &&
            point.col >= blob->points[i].col - 1 && point.col <= blob->points[i].col + 1)
        {
            blob->points[blob->counter] = point;
            blob->counter++;
            printf("Point: %d %d | ", blob->points[blob->counter-1].row, blob->points[blob->counter-1].col); // delete
            printf("Current blob counter: %d | ", blob->counter); // delete
            return 1;
        }
    }

    return 0;
}
*/