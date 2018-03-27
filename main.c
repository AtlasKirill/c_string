#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//it is neccesary to use double quotes,
//because strtok need a symbol of the end of the string,
//which is added to the end automatically
const char *devider = "\n";

size_t spaces_entrances(const char *buf);

int str_comparator(const void *a, const void *b);

//returns number of chars into file
size_t sizeof_file(FILE *fp);

void splitter(char **str_array, char *buffer);


int main(void) {
    //fp - file we are reading from
    //wr - file we are writing into
    FILE *fp, *wr;
    fp = fopen("/home/kirill/programms/c++_ded_classes/c_strings/T.txt", "r");

    size_t file_size = sizeof_file(fp);

    //allocate memory with size of file
    char *buffer = malloc(file_size);
    if (buffer)
        fread(buffer, 1, file_size, fp);
    else
        printf("Error when allocating the memory");

    //count number of spaces in file (in order to know how much strings in file)
    size_t str_count = spaces_entrances(buffer);


    //create array of pointers to strings which will be sorted
    char **str_array = (char **) malloc(sizeof(char *) * str_count);

    //split buffer into strings
    splitter(str_array, buffer);

    qsort(str_array, str_count, sizeof(char *), str_comparator);


    wr = fopen("/home/kirill/programms/c++_ded_classes/c_strings/out.txt", "w");
    //write a result into output file
    int j = 0;
    for (j = 0; j < str_count; ++j) {
        size_t h = fwrite(str_array[j], 1, strlen(str_array[j]), wr);
        fputc('\n', wr);
    }


    if (fclose(fp) == EOF)
        printf("ERROR");
    if (fclose(wr) == EOF)
        printf("ERROR");

    return 0;
}


int str_comparator(const void *a, const void *b) {
    const char *pa = *(const char **) a;
    const char *pb = *(const char **) b;
    return strcasecmp(pa, pb);
}


size_t spaces_entrances(const char *buf) {
    size_t counter = 0;
    for (int i = 0; i < strlen(buf); ++i) {
        if (buf[i] == '\n' && i == strlen(buf) - 1) {
            counter++;
            continue;
        }
        if (buf[i] == '\n') {
            if (buf[i + 1] == '\n')
                continue;
            counter++;
        }
    }
    return counter;
}

size_t sizeof_file(FILE *fp) {
    fseek(fp, 0L, SEEK_END);
    size_t sz = (size_t) ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}


void splitter(char **str_array, char *buffer) {
    int i = 0;
    char *tmp = strtok(buffer, devider);
    while (tmp != NULL) {
        str_array[i] = tmp;
        ++i;
        tmp = strtok(NULL, devider);
    }
}