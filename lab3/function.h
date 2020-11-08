struct nodeFB
{
	int id;
	int age;
	struct nodeFB *next;
};

struct nodeGS
{
	int id;
	struct nodeGS *next;
};

struct newNodeFB
{
	int id;
	int age;
	struct newNodeGS *next;
};

struct newNodeGS
{
	int id;
	struct newNodeFB *next;
};


void insertFB(struct nodeFB **startFB, int id, int age)
{
    // special case for the first element
    if (!(*startFB))
    {
        struct nodeFB *new_node = (struct nodeFB *)malloc(sizeof(struct nodeFB));
        new_node->id = id;
        new_node->age = age;
        new_node->next = NULL;
        *startFB = new_node;
    }

    // special case if id is smaller than the one at the start
    else if (id < (*startFB)->id)
    {
        struct nodeFB *new_node = (struct nodeFB *)malloc(sizeof(struct nodeFB));
        new_node->id = id;
        new_node->age = age;
        new_node->next = *startFB;
        *startFB = new_node;
    }

    else
    {
        struct nodeFB *ptr = *startFB;
        struct nodeFB *preptr = ptr;
        struct nodeFB *new_node = NULL;

        while (ptr->next != NULL)   // this part doesn't work properly
        {
            preptr = ptr;
            ptr = ptr->next;

            // inserting element before note with the greater id
            if (id < ptr->id)
            {
                new_node = (struct nodeFB *)malloc(sizeof(struct nodeFB));
                new_node->id = id;
                new_node->age = age;
                new_node->next = ptr;
                preptr->next = new_node;
                break;
            }
        }

        // inserting an element in the end of the list
        if (!new_node)
        {
            new_node = (struct nodeFB *)malloc(sizeof(struct nodeFB));
            new_node->id = id;
            new_node->age = age;
            new_node->next = NULL;
            ptr->next = new_node;
        }
    }
}

void printFB(struct nodeFB *startFB)
{
    struct nodeFB *ptr = startFB;
    while (ptr != NULL)
    {
        printf("%d %d\n", ptr->id, ptr->age);
        ptr = ptr->next;
    }
    printf("\n");
}



// You must write all the function definitions to be used in this lab into this file. 
// You may also write other functions that may be called from our functions.
// Do not make any changes to the main.c file.
// Upload function.h file to the system as StudentNumber.h.
