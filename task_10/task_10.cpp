#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define epsilon 0.0000001

int are_equal(double num_1, double num_2)
{
    if (fabs(num_1 - num_2) < epsilon)
    {
        return 1;
    }
    return 0;
}

struct List_Unit
{
    double num;
    List_Unit *next;
    List_Unit *previous;
};

List_Unit *list_initialization(double num)
{
    List_Unit *root_node;
    root_node = (List_Unit*)malloc(sizeof(List_Unit));
    root_node->num = num;
    root_node->next = NULL;
    root_node->previous = NULL;
    return root_node;
}

List_Unit* add_unit(List_Unit* unit, double num)
{
    List_Unit* new_unit, *buffer;
    new_unit = (List_Unit*)malloc(sizeof(List_Unit));
    buffer = unit->next;
    unit->next = new_unit;

    new_unit->num = num;
    new_unit->next = buffer;
    new_unit->previous = unit;

    if (buffer != NULL)
    {
        buffer->previous = new_unit;
    }
    return new_unit;
}

List_Unit* delete_root(List_Unit* root)
{
    List_Unit* new_root;
    new_root = root->next;
    new_root->previous = NULL;
    free(root);
    return new_root;
}

List_Unit* delete_unit(List_Unit* unit)
{
    List_Unit* previous, *next;
   
    previous = unit->previous;
    if (previous != NULL)
    {
        previous->next = unit->next;
    }

    next = unit->next;
    if (next != NULL)
    {
        next->previous = unit->previous;
    }

    free(unit);
    return previous;
}

List_Unit* unit_search(List_Unit* root, double num)
{
    List_Unit* buffer = root;
    while (buffer != NULL)
    {
        if (are_equal(buffer->num, num))
        {
            return buffer;
        }
        buffer = buffer->next;
    }
    return NULL;
}

List_Unit* edit_list(List_Unit* root, double to_delete_num)
{
    List_Unit* buffer = root, *unit;
    int counter = 0;
    while (buffer != NULL)
    {
        counter++;
        buffer = buffer->next;
    }
    for (int i = 0; i < counter; i++)
    {   
        unit = unit_search(root, to_delete_num);
        if (unit == root)
        {
            root = delete_root(root);
        }
        else if (unit)
        {
            delete_unit(unit);
        }
    }
    return root;
}

void print_list(List_Unit* root)
{
    List_Unit* buffer; // IMPORTANT TO CREATE THE BUFFER
    buffer = root;
    printf("\n");
    while (buffer != NULL)
    {
        printf("%.1lf ", buffer->num);
        buffer = buffer->next;
    }
    printf("\n");
}

void free_list(List_Unit* root)
{
    List_Unit* buffer_1 = root;
    List_Unit* buffer_2;
    while(buffer_1 != NULL)
    {
        buffer_2 = buffer_1;
        buffer_1 = buffer_1->next;
        free(buffer_2);
    }
    free(root);
}

int read_from_file(const char* filename, List_Unit** root, double* to_delete_num)
{
    FILE* fin;
    fin = fopen(filename, "r");
    if (fin)
    {   
        double num;
        List_Unit *first_unit, *new_unit;
        if (fscanf(fin, "%lf", &num) > 0) // ROOT NUM
        {
            *root = list_initialization(num);
            first_unit = *root;
            char c;
            while (fscanf(fin, "%lf", &num) > 0)
            {      
                new_unit = add_unit(first_unit, num);
                first_unit = new_unit;
                fscanf(fin, "%c", &c);
                if (c == '\n')
                {
                    break;
                }
            }
            fscanf(fin, "%lf", to_delete_num);
            fclose(fin);
            return 0;
        }
        return -2;
    }
    return -1;
}

int write_to_file(const char* filename, List_Unit* root)
{
    FILE* fout;
    fout = fopen(filename, "w");
    if (fout)
    {
        if (root)
        {
            List_Unit* buffer = root;
            while (buffer != NULL)
            {
                fprintf(fout, "%.1lf ", buffer->num);
                buffer = buffer->next;
            }
            fclose(fout);
            return 0;
        }
        fprintf(fout, "%.1lf", 0.);
        fclose(fout);
        return 0;
    }
    return -1;
}

int main()
{
    const char filename_in[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/task_10/input.txt";
    const char filename_out[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/task_10/output.txt";
    int read_err, write_err;
    double to_delete_num;
    List_Unit* root;
    read_err = read_from_file(filename_in, &root, &to_delete_num);
    if (read_err == 0)
    {     
        //print_list(root);
        if (to_delete_num)
        {   
            //printf("To delete: %.1lf\n\n", to_delete_num);
            root = edit_list(root, to_delete_num);
        }
        //print_list(root);
        write_err = write_to_file(filename_out, root);
        free_list(root);
    }
    else if (read_err == -2)
    {   
        write_err = write_to_file(filename_out, NULL);       
    }
    
    if (write_err == 0)
    {
        return 0;
    }
	return -1;
}