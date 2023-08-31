#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

size_t get_user_input(char **line_p)
{
    printf("Enter Password:");

    size_t buffer_size = 0;
    size_t len;
    if ((len = getline(line_p, &buffer_size, stdin)) != -1)
        return len - 1;

    exit(EXIT_FAILURE);
}

/*------------ longer than 8, one upper, lower, special, numeric character ------------*/
int check_password(char *line_p, size_t password_len)
{
    unsigned char checks = 0b00000000;

    /*------------ uppper lower ------------*/
    for (int i = 0; i < password_len; ++i)
    {
        if (isalpha(line_p[i]) != 0)
        {
            if (isupper(line_p[i]) != 0)
                checks |= 0b00000001;
            else
                checks |= 0b00000010;

            if (checks & 0b00000011)
                break;
        }
    }

    /*------------ special ------------*/
    for (int i = 0; i < password_len; ++i)
    {
        char c = line_p[i];
        if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
        {
            checks |= 0b00000100;
            break;
        }
    }

    /*------------ numeric ------------*/
    for (int i = 0; i < password_len; ++i)
    {
        if (isdigit(line_p[i]) != 0)
        {
            checks |= 0b00001000;
            break;
        }
    }

    return checks == 15;
}

int main()
{
    char *line = NULL;
    size_t len = get_user_input(&line);

    clock_t begin = clock();

    int is_valid = check_password(line, len);
    free(line);

    clock_t end = clock();
    double time_spent = (double)(end - begin) * 1000000.0 / CLOCKS_PER_SEC;

    printf("microsecond: %f\n", time_spent);
    printf("validity: %d\n", is_valid);
}
