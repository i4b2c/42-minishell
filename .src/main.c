#include "../include/header.h"

pid_t pid;

// void handler(int signal)
// {
// 	if(pid == 0)
// 	{
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		//rl_on_new_line();
// 		//rl_replace_line("", 0);
// 		//rl_redisplay();
// 		//kill(pid,SIGTERM);
// 		_exit(0);
// 	}
// }

// int execute(char **envp)
// {
// 	char *input;
// 	pid_t pid_exec;

// 	while((input = readline("\033[0;32mminishell $>\033[0m ")) != NULL)
// 	{
// 		if(strcmp(input,"exit") == 0)
// 		{
// 			free(input);
// 			return 1;
// 			break;
// 		}
// 		pid_exec = fork();
// 		if(pid_exec == (pid_t) 0)
// 		{
// 			// if(check_pipe(input))
// 			// 	pipex_mult(input);
// 			// else
// 			exec(input,envp);
// 			return 0;
// 		}
// 		else
// 			waitpid(pid_exec,NULL,0);
// 		add_history(input);
// 		free(input);
// 	}
// }

// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	struct sigaction sig;
// 	sig.sa_handler = handler;
// 	sigemptyset(&sig.sa_mask);
// 	sig.sa_flags = 0;
// 	sigaction(SIGINT,&sig,NULL);
// 	signal(SIGQUIT, SIG_IGN);

// 	int end = 0;
// 	while(1)
// 	{

// 		// if(!end)
// 		// {
// 		// 	pid = fork();
// 		// 	if(pid == (pid_t) 0)
// 		// 		end = execute(envp);
// 		// 	if(end)
// 		// 		exit(0);
// 		// 	else
// 		// 		waitpid(pid,NULL,0);
// 		// }
// 		// else
// 		// {
// 		// 	exit(0);
// 		// 	break;
// 		// }
// 	}
// }

// volatile int teste = 0;



// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// pid_t child_pid1 = -1; // Filho do main
// pid_t child_pid2 = -1; // Filho do filho do main

// void kill_child(int sig) {
//     if (child_pid2 > 0) {
//         kill(child_pid2, SIGKILL);
//         waitpid(child_pid2, NULL, 0); // Espera pelo processo filho do filho terminar
//         printf("Processo filho do filho encerrado.\n");
//         child_pid2 = -1; // Define o pid do filho do filho para -1, indicando que não há processo em execução
//     } else if (child_pid1 > 0) {
//         kill(child_pid1, SIGKILL);
//         waitpid(child_pid1, NULL, 0); // Espera pelo processo filho do main terminar
//         printf("Processo filho do main encerrado.\n");
//         child_pid1 = -1; // Define o pid do filho do main para -1, indicando que não há processo em execução
//     }
// }

// void program() {
//     /* Coloque o código do programa aqui, se necessário */
//     while (1) {
//         printf("Processo filho do filho em execucao.\n");
//         sleep(1);
//     }
// }

// int main(int argc, char *argv[]) {
//     signal(SIGINT, kill_child);

//     while (1) {
//         if (child_pid2 == -1) {
//             // Cria o processo filho do filho apenas se não houver um em execução
//             child_pid2 = fork();
//             if (child_pid2 == 0) {
//                 /* Filho do filho do main */
//                 program();
//                 exit(0); // Encerra corretamente o processo filho do filho após a execução do programa
//             }
//         }

//         if (child_pid1 == -1) {
//             // Cria o processo filho do main apenas se não houver um em execução
//             child_pid1 = fork();
//             if (child_pid1 == 0) {
//                 /* Filho do main */
//                 printf("Processo filho do main criado.\n");
//                 wait(NULL); // Espera pelo filho do filho do main terminar
//                 exit(0); // Encerra corretamente o processo filho do main após a espera
//             }
//         }

//         sleep(1); // Pequena pausa para evitar criação excessiva de processos
//     }

//     return 0;
// }


//manipulacao de diretorios
/*
int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char **cmd;
    cmd = malloc(sizeof(char *));
    cmd[0] = malloc(sizeof(char) * 100);
    ft_strcpy(cmd[0],"ls");
    cmd[1] = malloc(sizeof(char) * 100);
    cmd[1] = NULL;
    if(chdir("..") == -1)
    {
        perror("chdir");
        return -1;
    }
    execve("/bin/ls",cmd,envp);
    return 0;
}
*/

// pid_t pid = -1;

// int main(int ac, char **av, char **envp)
// {
//     pid = fork();
//     if(pid == 0)
//     {

//     }
//     else
//         waitpid(pid,NULL,0);
// }
