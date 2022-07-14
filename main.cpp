#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <memory.h>
#include <exception>

//NOTE: this isn't actually supposed to be code that does anything, it's just so I can test the theme.

int main()
{
    char buffer[256];

    printf("Enter the name of the file you're about to create : ");

    fgets(buffer, sizeof(buffer), stdin);

    if (buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
    }

    FILE* file = fopen(buffer, "w+");

    if (file == nullptr)
    {
        printf("File Couldn't be created\n");

        exit(EXIT_FAILURE);
    }

    int title_size = strlen(buffer) + 1 + 1 + 1;

    char* title = (char*)malloc(title_size);

    strcpy(title, buffer);

    title[(title_size - 3)] = ':';
    title[(title_size - 2)] = '\0';

    fputs(title, file);

    if (fclose(file) != 0)
    {
        perror("File Close Failed : ");
        exit(EXIT_FAILURE);
    }

    if (fopen(buffer, "r") == nullptr)
    {
        perror("File Open Failed :");
    }

    if (fopen(buffer, "r") != nullptr)
        printf("Waiting for newly created file \"%s\" to be closed\n", buffer);

    if (fclose(file) != 0)
    {
        perror("File Close Failed ");

        exit(EXIT_FAILURE);
    }

    printf("Wrote \"%s\" to file\n", buffer);

    char program_name[] = "notepad ";

    int output_file_name_size = (strlen(buffer) + 2) * sizeof(char);

    char* output_file_name = (char*)malloc(output_file_name_size);

    output_file_name[0] = '\"'; // prepending " character to output_file_name.

    for (size_t index = 0; index < strlen(buffer); index++)
    {
        output_file_name[1 + index] = buffer[index];
    }

    output_file_name[output_file_name_size - 1] = '\"';

    output_file_name[output_file_name_size] = '\0';

    char* program_name_cat = strncat(program_name, output_file_name, strlen(buffer) + 1);

    printf("Running Command : ~%s~\n", program_name_cat);

    system(program_name);

    file = fopen(buffer, "r");

    if (ferror(file) != 0)
    {
        printf("Die\n");

        exit(EXIT_FAILURE);
    }

    if (file == nullptr)
    {
        perror("File Open Failed ");

        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);

    int length = ftell(file);

    printf("Length Of File : %i\n", length);

    char* read_back_buffer = (char*)malloc(length * sizeof(char));

    rewind(file);

    for (size_t i = 0; i < length; i++)
        read_back_buffer[i] = fgetc(file);

    read_back_buffer[length - 1] = '\0';

    if (read_back_buffer == nullptr)
    {
        printf("Couldn't Read Back File Contents\n");

        exit(EXIT_FAILURE);
    }

    printf("\n~~~~ Contents Written --> \n%s\n~~~~\n", read_back_buffer);
}