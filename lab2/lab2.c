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

int any_point(struct Point *points, int amount);
int are_compatible(struct Point point1, struct Point point2);
void sort_blobs(int *arr, int size);
void swap(int *i1, int *i2);

//---------------------------------------------------------------------------------------------------------------------

int main()
{
    // greed size
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    struct Point *points_arr = (struct Point *)malloc(sizeof(struct Point) * rows*cols);
    struct Blob working_blob;
    working_blob.points = (struct Point *)malloc(sizeof(struct Point) * rows*cols);
    working_blob.counter = 0;
    int *blobs_values = (int *)malloc(sizeof(int) * (int)(rows*cols/2));
    int blob_counter = 0;
    int point_counter = 0;
    int flag;

    // input of points indexes
    for (int i = 0;; ++i)
    {
        scanf("%d", &points_arr[i].row);
        if (points_arr[i].row == -1)
            break;
        scanf("%d", &points_arr[i].col);

        point_counter++;
    }

    // traversing points_arr until all points are eliminated
    while (any_point(points_arr, point_counter))
    {
        flag = 1;
        for (int i = 0; i < point_counter; ++i)
        {
            // skipping already used point
            if (points_arr[i].row == -1)
                continue;

            // special case with the start of a new blob
            if (working_blob.counter == 0)
            {
                working_blob.points[0].row = points_arr[i].row;
                working_blob.points[0].col = points_arr[i].col;
                working_blob.counter++;
                points_arr[i].row = -1;
                flag = 0;
                continue;
            }

            // check for compatibility
            for (int j = 0; j < working_blob.counter; ++j)
            {
                if (are_compatible(points_arr[i], working_blob.points[j]))
                {
                    working_blob.points[working_blob.counter].row = points_arr[i].row;
                    working_blob.points[working_blob.counter].col = points_arr[i].col;
                    points_arr[i].row = -1;
                    working_blob.counter++;
                    flag = 0;
                    break;
                }
            }
        }
        
        if (flag)
        {
            blobs_values[blob_counter++] = working_blob.counter;
            working_blob.counter = 0;
        }
    }

    // add the last blob from working_blob
    blobs_values[blob_counter++] = working_blob.counter;

    // cleaning1
    free(points_arr);
    free(working_blob.points);

    // sort and print
    sort_blobs(blobs_values, blob_counter);
    printf("%d", blob_counter);
    for (int i = 0; i < blob_counter; ++i)
        printf(" %d", blobs_values[i]);
    printf("\n");

    // cleaning2
    free(blobs_values);

    return 0;
}

//---------------------------------------------------------------------------------------------------------------------

int any_point(struct Point *points, int amount)
{
    for(int i = 0; i < amount; ++i)
        if (points[i].row != -1)
            return 1;

    return 0;
}

int are_compatible(struct Point point1, struct Point point2)
{
    if (point1.row >= point2.row - 1 && point1.row <= point2.row + 1 &&
        point1.col >= point2.col - 1 && point1.col <= point2.col + 1)
        return 1;

    return 0;
}

void sort_blobs(int *arr, int size)
{
    for (int i = 0; i < size-1; ++i)
        for (int j = 0; j < size-1-i; ++j)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

void swap(int *i1, int *i2)
{
    int temp = *i1;
    *i1 = *i2;
    *i2 = temp;
}
