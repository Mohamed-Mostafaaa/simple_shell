#include "shell.h"

/**
 * main - entry point
 * @ec: arg cout
 * @ev: arg vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int ec, char **ev)
{
    info_t info[] = {INFO_INIT};
    int fd = 2;

    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(fd)
        : "r"(fd));
    if (ec == 2)
    {
        fd = open(ev[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
            {
                exit(126);
            }
            if (errno == ENOENT)
            {
                _eputs(ev[0]);
                _eputs(": 0: Can't open ");
                _eputs(ev[1]);
                _eputschar('\n');
                _eputschar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        info->readfd = fd;
    }
    pop_env_list(info);
    read_hist(info);
    hsh(info, ev);
    return (EXIT_SUCCESS)
}