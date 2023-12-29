
#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    int i = 0;
    while(env[i])
    {
        printf("%d - %s\n", i, env[i]);
        i++;
    }
}