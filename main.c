#include <stdio.h>
#include <string.h>
#include <stdlib.h>



size_t spaces_entrances(const char *buf) {
    size_t counter = 0;
    for (int i = 0; i < strlen(buf); ++i) {
        if (buf[i] == '\n')
            counter++;
    }
    return counter;
}

int str_comparator(const void *a, const void *b) {
    const char *pa = *(const char **) a;
    const char *pb = *(const char **) b;
    return strcasecmp(pa, pb);
}

int main(void) {
    FILE *fp, *wr;
    int i = 0;
    char * deriver ="\n";

    fp = fopen("T.txt", "r");
    fseek(fp, 0L, SEEK_END);
    long int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    char *buffer = malloc(sz);
    if (buffer)
        fread(buffer, 1, sz, fp);

    size_t str_count = spaces_entrances(buffer);
//    printf("%zu\n", str_count);

    char **str_array = (char **) malloc(sizeof(char *) * str_count);
    char *tmp = strtok(buffer, deriver);
    while (tmp != NULL) {
        str_array[i] = tmp;
        ++i;
        tmp = strtok(NULL, deriver);
    }

    qsort(str_array, str_count, sizeof(char *), str_comparator);


    wr = fopen("out.txt", "w+");
    for (int j = 0; j < str_count; ++j) {
        fwrite(str_array[j], 1, strlen(str_array[j]), wr);
        fputc('\n', wr);
    }


    if (fclose(fp) == EOF)
        printf("ERROR");
    if (fclose(wr) == EOF)
        printf("ERROR");


    return 0;
}


//int main (void)
//{
//    // Массив со строкой для поиска
//    char str [30]="test1\n\n\ntest2/test3\ntest4";
//    // Набор символов, которые должны входить в искомый сегмент
//    char sep [10]="\n";
//    // Переменная, в которую будут заноситься начальные адреса частей
//    // строки str
//    char *istr;
//    printf ("Результат разбиения:\n");
//    // Выделение первой части строки
//    istr = strtok (str,sep);
//
//    // Выделение последующих частей
//    while (istr != NULL)
//    {
//        // Вывод очередной выделенной части
//        printf ("%s\n",istr);
//        // Выделение очередной части строки
//        istr = strtok (NULL,sep);
//    }
//
//    return 0;
//}