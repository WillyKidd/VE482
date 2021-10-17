# include "list.h"
// # include "list.c"

int getOrder(char* file_name)
{
    unsigned int pos = 0;
    int order = -1;
    for(; pos < strlen(file_name); pos++)
    {
        if(file_name[pos] == '_')
        {
            file_name[pos] = '\0';
            break;
        }
    }
    if(!strcmp(file_name, "inc")) order = INC;
    else if(!strcmp(file_name, "dec")) order = DEC;
    else if(!strcmp(file_name, "rand")) order = RAN;
    if(pos > 0) file_name[pos] = '_';
    return order;
}

int getType(char* file_name)
{
    char arg[MAX_ARG], *type;
    strcpy(arg, file_name);
    type = strtok(arg, "_");
    type = strtok(NULL, ".");
    if(!strcmp(type, "int")) return INT;
    if(!strcmp(type, "double")) return DOUBLE;
    if(!strcmp(type, "string")) return STRING;
    return -1;
}

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        printf("error: too few arguments.\n");
        return 0;
    }
    List *l = listInit(argv[1], getType(argv[1]));
    char output_fname[MAX_LINE] = "";
    strcat(output_fname, argv[2]);
    strcat(output_fname, "_");
    strcat(output_fname, DTYPE[getType(argv[1])]);
    strcat(output_fname, ".txt");
    listSort(l, getType(argv[1]), getOrder(argv[2]));
    listPrintToFile(l, output_fname, getType(argv[1]));
    return 0;
}
