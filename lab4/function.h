struct nodeClass
{
	int classID;
	double classMidtermAverage;
	struct nodeClass *next;
	struct nodeStudent *studentPtr;
};

struct nodeStudent
{
	int studentID;
	int midterm;
	struct nodeStudent *next;
};


// You must write all the function definitions to be used in this lab into this file.
// You may also write other functions that may be called from our functions.
// Do not make any changes to the main.c file.
// Upload function.h file to the system as StudentNumber.h.


void insert(struct nodeClass **head, int id, int midterm)
{
    // creating linked list out of nodeClasses if the one doesn't exist(first entry)
    if (!(*head))
    {
        // first node
        (*head) = (struct nodeClass *)malloc(sizeof(struct nodeClass));
        (*head)->classID = 1;
        (*head)->classMidtermAverage = 0;
        (*head)->studentPtr = NULL;

        // other nodes
        struct nodeClass *current_node = *head;
        for (int i = 2; i <= 4; ++i)
        {
            struct nodeClass *new_node = (struct nodeClass *)malloc(sizeof(struct nodeClass));
            new_node->classID = i;
            new_node->classMidtermAverage = 0;
            new_node->studentPtr = NULL;
            new_node->next = NULL;

            current_node->next = new_node;
            current_node = current_node->next;
        }
    }

    // allocate memory for nodeStudent
    struct nodeStudent *student_node = (struct nodeStudent *)malloc(sizeof(struct nodeStudent));
    student_node->studentID = id;
    student_node->midterm = midterm;
    student_node->next = NULL;

    // find corresponding nodeClass' id
    int class_id;
    switch ((int)(id / 1000))
    {
        case 66:
            class_id = 1;
            break;
        case 77:
            class_id = 2;
            break;
        case 88:
            class_id = 3;
            break;
        case 99:
            class_id = 4;
            break;
    }

    // find corresponding nodeClass
    struct nodeClass *class_node = *head;
    while (class_id != class_node->classID)
        class_node = class_node->next;

    // special case for the first element
    if (!(class_node->studentPtr))
        class_node->studentPtr = student_node;

    // special case if midterm is greater than the one at the start
    else if (midterm >= class_node->studentPtr->midterm)
    {
        // if midterms are equal, studentIDs should be in ascending order
        if (midterm == class_node->studentPtr->midterm && student_node->studentID > class_node->studentPtr->studentID)
        {
            int temp = student_node->studentID;
            student_node->studentID = class_node->studentPtr->studentID;
            class_node->studentPtr->studentID = temp;
        }

        student_node->next = class_node->studentPtr;
        class_node->studentPtr = student_node;
    }

    else
    {
        struct nodeStudent *ptr = class_node->studentPtr;
        struct nodeStudent *preptr = ptr;

        while (ptr->next != NULL)
        {
            preptr = ptr;
            ptr = ptr->next;

            // insert current node before the node with smaller midterm
            if (midterm >= ptr->midterm)
            {
                // if midterms are equal, studentIDs should be in ascending order
                if (midterm == ptr->midterm && student_node->studentID > ptr->studentID)
                {
                    int temp = student_node->studentID;
                    student_node->studentID = ptr->studentID;
                    ptr->studentID = temp;
                }

                student_node->next = ptr;
                preptr->next = student_node;
                return;
            }
        }

        // insert current node in the end of the list(the smallest midterm)
        if (!(ptr->next))
            ptr->next = student_node;
    }
}


void computeClassAverage(struct nodeClass *head)
{
    struct nodeClass *class_ptr = head;
    while (class_ptr != NULL)
    {
        double numerator = 0;
        int denominator = 0;

        struct nodeStudent *student_ptr = class_ptr->studentPtr;
        while (student_ptr != NULL)
        {
            numerator += student_ptr->midterm;
            denominator += 1;
            student_ptr = student_ptr->next;
        }

        if (denominator)
            class_ptr->classMidtermAverage = numerator / denominator;

        class_ptr = class_ptr->next;
    }
}


void printAll(struct nodeClass *head)
{
    struct nodeClass *class_ptr = head;
    while (class_ptr != NULL)
    {
        printf("%d %0.2lf\n", class_ptr->classID, class_ptr->classMidtermAverage);
        struct nodeStudent *student_ptr = class_ptr->studentPtr;
        while (student_ptr != NULL)
        {
            printf("%d %d\n", student_ptr->studentID, student_ptr->midterm);
            student_ptr = student_ptr->next;
        }
        class_ptr = class_ptr->next;
    }
}
