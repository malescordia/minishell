/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:46 by gude-cas          #+#    #+#             */
/*   Updated: 2023/12/31 17:08:51 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

void print_env(char **env)
{
    int i = 0;
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

void print_echo(char *str)
{
    int i = 5;
    while(str[i])
    {
        printf("%c", str[i]);
        i++;
    }
    printf("\n");
}

int main(int ac, char **av, char **env)
{
    (void)av;
    char *input;

    if(ac == 1)
    {
        while(1)
        {
            input = readline("GUIGUISHELL> ");
            add_history(input);
            if(ft_strcmp(input, "pwd") == 0)
            {
                printf("%s\n", getenv("PWD"));
            }
            else if(ft_strcmp(input, "env") == 0)
            {
                print_env(env);
            }
            else if(ft_strncmp(input, "echo ", 5) == 0)
            {
                print_echo(input);
            }
        }
    }
    else
    {
        printf("Invalid number of arguments.\n");
    }
    return(0);
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
getcwd - get current directory
add_history - adds a line to the history list, it allows us to recall and reuse previously entered command lines

BUILTIN COMMANDS:
- cd (changes the working directory of the current shell execution environment and updates the environment varuables 'PWD' and 'OLDPWD'.
Without arguments it changes the working directory to the home directory. 'cd -' changes the directory to the 'OLDPWD' (not to confuse with
'cd ..' which changes to the parent directory of the one we are at))
- echo (displays a line of text) (theres an optional argument which is 'echo -n', in this case we are not supposed to display the new line))
- env (displays the environment variables)
- exit (terminates the shell. Accepts optional argument 'exit n' which sets the exit status to 'n')
- export (accepts arguments 'name[=value]'. Adds name to the environment. Set's value of name to 'value'. If no arguments is given, displays
list of exported variables)
- pwd (shows the current directory as an absolute path)
- unset (Accepts argument 'name'. Removes the variable 'name' from the environment)

THINGS TO IMPLEMENT:
- prompt display
- command history (up and down arrows)
- system executables available from the environment (ls, cat, grep, etc.)
- builtin commands:
    - echo: allow option -n
    - cd: relative or absolute path
    - pwd: no args
    - export: export variables in bash
    - unset
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
----------------------------------------------------------------------------------------------------------------------------------------
Whats a token?
Tokens in compiler design are the sequence of characters which represents a unit of information in the source program
----------------------------------------------------------------------------------------------------------------------------------------
Parts of a Shell Program:
    The Parser:
    - Is the software camponent that reads the command line such as "ls -al" and puts it into a data structure called Command Table
    that will store the commands that will be executed.
    The Executor:
    - Will take the command table generated by the parser and for every SimpleCommand in the array it will crete a new process.
    It will alsi if necessary create pipes to communicate the output of one process to the input of the next one. Additianlly, it
    will redirect the standard input, standard output, and standard error if there are any redirections.
----------------------------------------------------------------------------------------------------------------------------------------
*/