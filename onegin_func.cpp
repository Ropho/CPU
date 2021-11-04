#include "onegin.h"

int TEXT_struct_fillin (TEXT* text, FILE *in_binary) {

    assert (text != NULL);
    assert (in_binary != NULL);


    text->filesize = FILESIZE_FUNC_FSTAT (in_binary);


    if ((text->buffer = (char*)calloc(text->filesize + 1, sizeof(char))) == NULL)
        return ERROR_IN_FILLIN_BUFFER;



    if (fread (text->buffer, sizeof(char), text->filesize, in_binary) != text->filesize)
      return ERROR_IN_READING_FROM_FILE;



    text->number_lines = number_lines_in_buffer (text->buffer);

    text->buffer[text->filesize] = '\0';
    text->array_pointers = (JOJO*)calloc(text->number_lines, sizeof (JOJO));

    if (text->array_pointers == NULL) {

      return ALLOCATION_MEMORY_ERROR;
    }

    pointers_struct_fillin (text->buffer, text->array_pointers, text->number_lines);
    return 0;
}


size_t FILESIZE_FUNC_FSTAT (FILE *in) {

    assert (in != NULL);

    struct stat buff = {};

    fstat (fileno (in), &buff);

    return buff.st_size;
}


size_t number_lines_in_buffer (char* str) {

    assert (str != NULL);

    int num_of_lines = 0;

    while (strchr (str, '\n') != NULL) {

        ++num_of_lines;
        str = strchr (str, '\n') + 1;
    }

    return num_of_lines + 1;
}


void pointers_struct_fillin (char* str, JOJO* array_sort, int number_lines) {

    assert (str != NULL);
    assert (array_sort != NULL);

    char *start  = str;
    char *finish = NULL;

    for (int i = 0; i < number_lines - 1; ++i) {

        char *finish = strchr (start, '\n');

        *finish = '\0';

        array_sort[i].str = start;
        array_sort[i].len_str = finish - start;

        start = finish + 1;
    }

    array_sort[number_lines - 1].str = start;
    array_sort[number_lines - 1].len_str = strlen (array_sort[number_lines - 1].str);
}


void pointers_struct_BUBBLE (JOJO *str, int lines, int (*comparator)(const void*, const void*)) {

    assert (str != NULL);

    JOJO s = {};

    for (int i = 1; i < lines; ++i) {

        for (int j = 0; j < lines - i; ++j) {

            if (comparator (&str[j], &str[j + 1]) == 1) {

                s = str[j];
                str[j] = str[j + 1];
                str[j + 1] = s;
            }
        }
    }
}


void qss (JOJO *a, int number_lines, int (*comparator)(const void*, const void*)) {

        int left = 0, right = number_lines - 1;

        JOJO middle = a[number_lines / 2];

        JOJO tmp = {};

        do
        {
           while (comparator (&a[left], &middle) < 0){
                left++;
             }
            while  (comparator (&a[right], &middle) > 0)
                right--;
            if (left <= right)

            {
                tmp = a[left];
                a[left] = a[right];
                a[right] = tmp;

                left++;
                right--;
            }
        } while (left <= right);

        if (right > 0)
            qss (a, right + 1, comparator);

        if (left < number_lines)
            qss (a + left, number_lines - left, comparator);
}



char *find_alnum (char *ch) {

    assert (ch != NULL);

        while (1) {

            if (isalnum ((int)(unsigned char)*ch) && *ch != '\0' && *ch != ' ')
                    return ch;

            else
                ++ch;
        }
}


int comp_void (const void *first, const void *second) {

    assert (first  != NULL);
    assert (second != NULL);

    char *str1 = ((JOJO *)first)  -> str;
    char *str2 = ((JOJO *)second) -> str;

    if (strcmp (str1, str2) == 0)
        return 0;

    while (*str1 != '\0' && *str2 != '\0') {

            str1 = find_alnum (str1);
            str2 = find_alnum (str2);

            if (*str1 > *str2) {

                return 1;
            }

            else if (*str1 < *str2) {

                return -1;
            }
            else {

                ++str1;
                ++str2;
            }

    }

    if (*str1 == '\0') {

         return -1;
    }
    else return 1;
}


int comp_void_reverse (const void *first, const void *second) {

    assert (first  != NULL);
    assert (second != NULL);

    char *uno = ((JOJO *)first) -> str;
    char *duo = ((JOJO *)second)-> str;


    if (strcmp (uno, duo) == 0)
        return 0;

    char *str1 = uno + ((JOJO *)first) ->len_str - 1;
    char *str2 = duo + ((JOJO *)second)->len_str - 1;


    while (str1 != uno && str2 != duo) {


            str1 = find_alnum_reverse (str1, uno);
            str2 = find_alnum_reverse (str2, duo);

            if (isalnum (*str1) == 0)
                return 1;
            if (isalnum (*str2) == 0)
                return -1;

            if (*str1 > *str2) {

                return 1;
            }

            else if (*str1 < *str2) {

                return -1;
            }
            else {

                --str1;
                --str2;
            }

    }


    if (*str1 > *str2) {

         return 1;
    }
    else return -1;
}



char *find_alnum_reverse (char *ch, char *endo) {

    assert (ch != NULL);

        while (1) {

           if (isalnum ((int)(unsigned char)*ch) && *ch != '\0')
                    return ch;

            else {

                if (ch == endo)
                    return ch;

                    --ch;
            }
        }
}


void output_sorted (JOJO *str, int num_lines, FILE *out) {

    assert (str != NULL);
    assert (out != NULL);

    for (int i = 0; i < num_lines; ++i) {

        fputs (str[i].str, out);
        //fputc ('\n', out);
    }
    return;
}


void output_ne_sorted (char* str, int num_lines, FILE *out) {

    assert (str != NULL);
    assert (out != NULL);

    for (int i = 0; i < num_lines; ++i) {

        fputs (str, out);
        fputc ('\n', out);
        str = strchr (str, '\0') + 1;
    }
    //fputc ('\n', out);

    return;
}

void output_separation (FILE *out) {

    assert (out != NULL);

    fputs ("\n*********************************************************************************"
           "*******************************************************\n"
           "***********************************************************************************"
           "*****************************************************\n\n", out);
}


void TEXT_struct_destructor (TEXT *text) {

    free (text->buffer);
    free (text->array_pointers);

    text->filesize = 0;
    text->number_lines = 0;
}