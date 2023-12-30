
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

/*

FUNCTIONS:
access - check access (used in pipex)
execve - exec cmd (used in pipex)
fork - divide process in 2. Child and parent.
getpwd - get pwd
open - open file
opendir - open specific directory
pipe - pipe (learned in pipex)
dup2 - duplicate FD and change (learned in pipex)
read - read from a file descriptor
readline - waiting prompt 
signal - change the process, by signal passed. Take other action.
rl_* - handler with prompt
add_history - add cmd in history
waitpid - wait child exec
chdir - change directory
stat - get properties from path
unlink - drop a file
strerror - describes error
getenv - get environment variables 

THINGS TO IMPLEMENT:
- prompt display
- command history (up and down arrows)
- system executables available from the environment (ls, cat, grep, etc.)
- builtin commands:
    - echo: allow option -n
    - cd: relative or absolute path
    - pwd: no args
    - export: export variables in bash
    - unset: no args
    - env: no options. no args.
    - exit: allow exit number
- pipes: | which redirect output from one command to input for the next
- redirections:
    - < should redirect input
    - > should redirect output
    - << DELIMITER displays a new prompt. HereDoc DELIMITER redirects user input to command input
    - >> redirects output in append mode
    - $? expands to the exit status of the most recently executed foreground pipeline
- signals:
    - ctrl-c: displays a new prompt line. SIGINT: SIGINT resets the user input prompt to a new blank line
    - ctrl-d: exit
    - ctrl-\: does nothing

MATERIAL:
Whats a token?
Tokens in compiler design are the sequence of characters which represents a unit of information in the source program
*/