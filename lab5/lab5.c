#include <stdio.h>
#include <stdlib.h>
#define MAX_EMP 6

struct employee
{
    int id;
    int total_time;
    int until_available;
};

struct customer
{
    int id;
    int coming_time;
    int processing_time;
    int waiting_time;
};

struct report_node
{
    int customer_id;
    int employee_id;
    int start;
    int finish;
    int customer_waiting;
    struct report_node *next;
};

void append_report_node(struct report_node **head, struct report_node **tail, struct report_node *new_node);
void employees_update(struct employee available_employees[], struct employee working_employees[],
                      int *ae_top, int *we_top, int time_update);
void print_report(struct report_node *head);
void print_employees(struct employee available_employees[], struct employee working_employees[], int ae_top, int we_top);
void push(struct employee employees[], int *top, struct employee emp);
struct employee pop(struct employee employees[], int *top);
struct employee peek(struct employee employees[], int top);

//---------------------------------------------------------------------------------------------------------------------

int main()
{
    // initializing *stack* of employees
    struct employee available_employees[MAX_EMP];
    struct employee working_employees[MAX_EMP];
    int ae_top = -1;
    int we_top = -1;
    for (int i = 0; i < MAX_EMP; ++i)
    {
        struct employee emp;
        emp.id = i + 1;
        emp.total_time = 0;
        emp.until_available = 0;
        push(available_employees, &ae_top, emp);
    }

    // report/linked list
    struct report_node *report = NULL;
    struct report_node *end;

    // customer variable for input
    struct customer new_customer;

    // additional counters and flags
    int current_time = -1;
    int customer_input = 1;
    int exit_check;

    while (1)
    {
        if (customer_input)
        {
            scanf("%d", &exit_check);
            if (exit_check == -1)
                break;

            new_customer.id = exit_check;
            scanf("%d %d", &new_customer.coming_time, &new_customer.processing_time);

            while (new_customer.coming_time > current_time)
            {
                employees_update(available_employees, working_employees, &ae_top, &we_top,1);
                current_time++;
            }
            new_customer.waiting_time = current_time - new_customer.coming_time;

            if (current_time == -1)
                current_time = new_customer.coming_time;
        }


        // case when all employees are busy
        if (ae_top == -1)
        {
            new_customer.waiting_time += 1;
            customer_input = 0;
            employees_update(available_employees, working_employees, &ae_top, &we_top, 1);
            current_time += 1;
        }

        else
        {
            struct employee emp = peek(available_employees, ae_top);

            // creating new report line
            struct report_node *node = (struct report_node *)malloc(sizeof(struct report_node));
            node->customer_id = new_customer.id;
            node->employee_id = emp.id;
            node->start = current_time;
            node->finish = current_time + new_customer.processing_time;
            node->customer_waiting = new_customer.waiting_time;
            node->next = NULL;
            append_report_node(&report, &end, node);

            // updating taken employee's availability
            emp.total_time += new_customer.processing_time;
            emp.until_available = new_customer.processing_time;
            push(working_employees, &we_top, emp);
            pop(available_employees, &ae_top);

            customer_input = 1;
        }
    }

    print_report(report);
    printf("\n");
    print_employees(available_employees, working_employees, ae_top, we_top);

    return 0;
}

//---------------------------------------------------------------------------------------------------------------------

void append_report_node(struct report_node **head, struct report_node **tail, struct report_node *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
        return;
    }

    (*tail)->next = new_node;
    *tail = new_node;
}

void employees_update(struct employee available_employees[], struct employee working_employees[],
                      int *ae_top, int *we_top, int time_update)
{
    for (int i = *we_top; i >= 0; --i)
    {
        working_employees[i].until_available -= time_update;
        if (working_employees[i].until_available <= 0)
        {
            push(available_employees, ae_top, working_employees[i]);
            for (int j = i; j < *we_top; ++j)
                working_employees[j] = working_employees[j + 1];
            (*we_top)--;
        }
    }
}

void print_report(struct report_node *head)
{
    struct report_node *ptr = head;
    while (ptr != NULL)
    {
        printf("%d %d %d %d %d\n", ptr->customer_id, ptr->employee_id, ptr->start, ptr->finish, ptr->customer_waiting);
        ptr = ptr->next;
    }
}

void print_employees(struct employee available_employees[], struct employee working_employees[], int ae_top, int we_top)
{
    int employees[MAX_EMP][2];

    for (int i = 0; i <= ae_top; ++i)
    {
        employees[available_employees[i].id - 1][0] = available_employees[i].id;
        employees[available_employees[i].id - 1][1] = available_employees[i].total_time;
    }

    for (int i = 0; i <= we_top; ++i)
    {
        employees[working_employees[i].id - 1][0] = working_employees[i].id;
        employees[working_employees[i].id - 1][1] = working_employees[i].total_time;
    }

    for (int i = MAX_EMP - 1; i >= 0; --i)
        printf("%d %d\n", employees[i][0], employees[i][1]);
}

void push(struct employee employees[], int *top, struct employee emp)
{
    (*top)++;
    employees[*top] = emp;
}

struct employee pop(struct employee employees[], int *top)
{
    struct employee emp = employees[*top];
    (*top)--;
    return emp;
}

struct employee peek(struct employee employees[], int top)
{
    return employees[top];
}