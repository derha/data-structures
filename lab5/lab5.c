#include <stdio.h>
#include <stdlib.h>
#define MAX_EMP 6

struct employee
{
    int id;
    int total_time;
    int available;
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
void employees_update(struct employee employees[], int time_update);
void print_report(struct report_node *head);
void print_employees(struct employee employees[]);


int main()
{
    // initializing *stack* of employees
    struct employee employees[MAX_EMP];
    for (int i = 0; i < MAX_EMP; ++i)
    {
        employees[i].id = i + 1;
        employees[i].total_time = 0;
        employees[i].available = 1;
        employees[i].until_available = 0;
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

            if (new_customer.coming_time > current_time)
            {
                employees_update(employees, new_customer.coming_time - current_time);
                current_time = new_customer.coming_time;
            }
            new_customer.waiting_time = current_time - new_customer.coming_time;

            if (current_time == -1)
                current_time = new_customer.coming_time;
        }

        // traversing employees from the end
        for (int i = MAX_EMP - 1; i >= 0; --i)
        {
            // case when all employees are busy
            if (i == 0 && !(employees[i].available))
            {
                new_customer.waiting_time += 1;
                customer_input = 0;
                employees_update(employees, 1);
                current_time += 1;
            }

            if (employees[i].available)
            {
                // creating new report line
                struct report_node *node = (struct report_node *)malloc(sizeof(struct report_node));
                node->customer_id = new_customer.id;
                node->employee_id = employees[i].id;
                node->start = current_time;
                node->finish = current_time + new_customer.processing_time;
                node->customer_waiting = new_customer.waiting_time;
                node->next = NULL;
                append_report_node(&report, &end, node);

                // updating taken employee's availability
                employees[i].total_time += new_customer.processing_time;
                employees[i].available = 0;
                employees[i].until_available = new_customer.processing_time;

                customer_input = 1;
                break;
            }
        }
    }

    print_report(report);
    printf("\n");
    print_employees(employees);

    return 0;
}


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

void employees_update(struct employee employees[], int time_update)
{
    for (int i = 0; i < MAX_EMP; ++i)
    {
        if (!(employees[i].available))
        {
            employees[i].until_available -= time_update;
            if (employees[i].until_available <= 0)
                employees[i].available = 1;
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

void print_employees(struct employee employees[])
{
    for (int i = MAX_EMP - 1; i >= 0; --i)
        printf("%d %d\n", employees[i].id, employees[i].total_time);
}