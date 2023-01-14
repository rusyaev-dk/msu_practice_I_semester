#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 100

int read_from_file(const char* filename, char** string, char** substring, int* string_size, int* substring_size)
{
    FILE* fin;
    fin = fopen(filename, "r");
    if (fin)
    {   
        *string = (char*)malloc(sizeof(char) * MAX_STRING_LENGTH);
        int i = 0;
        while (i < MAX_STRING_LENGTH && ( *(*string+i) = fgetc(fin) ) != '\n')
        {   
            // string[i] = fgetc(fin)
            i++;
        }
        if (i == 0)
        {
            free(*string);
            free(*substring);
            fclose(fin);
            return -2;
        }
        else if (i < MAX_STRING_LENGTH)
        {
            *string = (char*)realloc(*string, sizeof(char) * i);
        }
        
        *substring = (char*)malloc(sizeof(char) * MAX_STRING_LENGTH);
        int c = 0;
        while (c < MAX_STRING_LENGTH && (*(*substring+c) = fgetc(fin)) != EOF)
        {   
            c++;
        }
        if (c == 0)
        {
            free(*string);
            free(*substring);
            fclose(fin);
            return -3;
        }
        else if (c < MAX_STRING_LENGTH)
        {
            *substring = (char*)realloc(*substring, sizeof(char) * c);
        }

        *string_size = i;
        *substring_size = c;
        fclose(fin);
        return 0;
    }
    return -1;
}

int write_to_file(const char* filename, int result)
{
    FILE* fout;
    fout = fopen(filename, "w");
    if (fout)
    {
        fprintf(fout, "%d", result);
        fclose(fout);
        return 0;
    }
    return -1;
}

int substring_counter(char* string, char* substring, int string_size, int substring_size)
{   
    int result = 0, counter = 0;
    for(int i = 0; i < string_size; i++) 
    {
        counter = substring_size;
        for(int j = i; j < i + substring_size; j++) 
        {
            if(string[j] != substring[j - i]) 
            {
                counter--;
                break;
            }
        }
        if(counter == substring_size) 
        {
            result++;
        }
    }
    return result;
}

int main()
{
    const char filename_in[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/task_9/input.txt";
    const char filename_out[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/task_9/output.txt";
    int read_err, write_err, string_size, substring_size;
    char* string, *substring;

    read_err = read_from_file(filename_in, &string, &substring, &string_size, &substring_size);
    if (read_err == 0)
    {       
        printf("string: ");
        for (int i = 0; i < string_size; i++)
        {
            printf("%c", string[i]);
        }
        printf("\n");
        printf("substring: ");
        for (int i = 0; i < substring_size; i++)
        {
            printf("%c", substring[i]);
        }
        printf("\n");
       
        int result = substring_counter(string, substring, string_size, substring_size);
        write_err = write_to_file(filename_out, result);
        //printf("string size: %d\n", string_size);
        //printf("substring size: %d\n", substring_size);
        printf("result = %d", result);
    }
    else if (read_err == -3 || read_err == -2)
    {
        write_err = write_to_file(filename_out, 0);
    }

    if (write_err == 0)
    {
        return 0;
    }
	return -1;
}