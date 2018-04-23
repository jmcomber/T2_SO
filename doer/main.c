#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include "procs.h"
#include "utils.c"
#include <sys/time.h>



long long current_timestamp() {
	struct timeval te; 
	gettimeofday(&te, NULL); // get current time
	printf("te.tv_usec es %ld\n", te.tv_usec);
	long long mseconds = 1000000 * te.tv_sec + te.tv_usec; // calculate mseconds
	// printf("mseconds: %lld\n", mseconds);
	return mseconds;
}


// int my_time() {
// 	struct timespec tp;
// 	clockid_t clk_id;
// 	clk_id = CLOCK_MONOTONIC;
// 	int result = clock_gettime(clk_id, &tp);
// 	printf("Result es %d\n", result);
// 	return result;
// }

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

void imprimir_estadisticas() {

}

void imprimir_proc(Process* proc) {
	printf("Instrucción: %s\n", proc -> task);
	// printf("Tiempo secuencial de ejecución (microsegs): %ld\n", proc -> end_t - proc -> start_t);
	printf("Exit code: %d\n", proc -> exit_status);
	printf("Output: %s\n", proc -> output);
	printf("\n");
}


void terminar() {
	// terminar procesos que están corriendo
	imprimir_estadisticas();
	exit(0);
}	



int main(int argc, char * argv []) {
	signal(SIGINT, terminar);
	
	// char cmd[10] = "ls";
	// char *args[] = {cmd, "-al", NULL};
	// execvp(cmd, args);

	char *path = argv[1];
	int n = atoi(argv[2]);

	int m = n_lines(path);
	printf("Hay que ejecutar %d tareas\n", m);
	char tasks[m][255];
	input_read(tasks, path, m);
	
	int cont_procs = 0;
	int cont_tasks = 0;

	long long int inicio = current_timestamp();
	
	/*Procs array*/
	Process* procs[m];
	Process* aux = malloc(sizeof(Process*));
	aux -> terminated = -1;
	aux -> pid = -1;
	aux -> exit_status = -1;
	for (int i = 0; i < m; i++)
	{
		procs[i] = aux;
	}

	while (cont_tasks < m) {
		// sleep(2);
		int pipes[2];
		pipe(pipes); // Create the pipes
		cont_procs++;
		cont_tasks++;
		// printf("Vamos a ejecutar task n° %d, proceso n° %d\n", cont_tasks, cont_procs);
		pid_t pid = fork();

		if (pid != 0) {
			/*Start init proc*/
			Process* proc = malloc(sizeof(Process*));
			strcpy(proc -> task, tasks[cont_tasks - 1]);
			proc -> start_t = current_timestamp();
			proc -> pid = pid;
			proc -> terminated = 0;
			procs[cont_tasks - 1] = proc;

			/* End init proc */
		}

		if (pid == 0) {
			dup2(pipes[1], STDOUT_FILENO);
			close(pipes[0]);
			close(pipes[1]);

			char** args = str_split(tasks[cont_tasks - 1], ' ');
			execvp(args[0], args);
		}
		else {
			for (int i=0; i<m; i++) {
				int status;
				if (procs[i] -> pid > 0 && !procs[i] -> terminated && waitpid(procs[i] -> pid, &status, 1) == 0) { /*Si terminó, liberar cupo y setear end_t */
					procs[i] -> end_t = current_timestamp();
					procs[i] -> terminated = 1;
					procs[i] -> exit_status = WEXITSTATUS(status);
					close(pipes[1]);
					char* foo = calloc(16384, sizeof(char));
					int nbytes = read(pipes[0], foo, 16384);
					// printf("foo es %s\n", foo);
					// printf("------------------------------\n");
					procs[i] -> output = foo;
					// strcpy(procs[i] -> output, foo);
					cont_procs--;
				}
			}
			// close(pipes[1]);
		}

		/* Quedar pegado si es que estamos con el máximo de procesos */
		while (cont_procs == n) {
			printf("CONT_PROCS == N\n");
			for (int i=0; i<m; i++) {
				int status;
				if (procs[i] -> pid > 0 && !procs[i] -> terminated && waitpid(procs[i] -> pid, &status, 1) == 0) { /*Si terminó, liberar cupo y setear end_t */
					procs[i] -> end_t = current_timestamp();
					procs[i] -> terminated = 1;
					procs[i] -> exit_status = WEXITSTATUS(status);
					close(pipes[1]);
					char* foo = calloc(16384, sizeof(char));
					int nbytes = read(pipes[0], foo, 16384);
					// printf("foo es %s\n", foo);
					// printf("------------------------------\n");
					procs[i] -> output = foo;
					cont_procs--;
				}
			}
		}

	}
	long long int termino = current_timestamp();
	printf("Inicio es %lld\n", inicio);
	printf("Término es %lld\n", termino);
	// imprimir_estadisticas();
	// por ahora, imprimimos a mano

	for (int i = 0; i < m; i++) {
		imprimir_proc(procs[i]);
	}

	long long int suma_tiempos = 0;
	for (int i = 0; i < m; i++) {
		printf("Sumándole %lld - %lld\n", procs[i] -> end_t, procs[i] -> start_t);
		suma_tiempos += procs[i] -> end_t - procs[i] -> start_t;
	}

	printf("Tiempo secuencial de ejecución: %lld\n", suma_tiempos);
	printf("Tiempo real de ejecución (microsegs): %lld\n", termino - inicio);


}