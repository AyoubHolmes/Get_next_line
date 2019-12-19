#include "get_next_line_bonus.h"

int main()
{
    int fd, res;
    char *str = NULL;


    fd = open("test", O_RDONLY);

    while ((res = get_next_line(fd, &str)) == 1)
    {
        printf("%d | %s\n", res, str);
        free(str);
        str = NULL;
    }
    printf("%d | %s", res, str);
    free(str);
}