#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "procs.h"
#include "utils.c"


#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

/* Global vars start*/
int m;
struct timespec inicio, termino;
Process* procesos[100];
/* Global vars end*/

void imprimir_proc(Process* proc) {
	printf("Instrucción: %s\n", proc -> task);
	printf("Exit code: %d\n", proc -> exit_status);
	printf("Output: %s\n", proc -> output);
	printf("\n");
}

void imprimir_estadisticas();


void terminar() {
	// terminar procesos que están corriendo
	Process* aux = procesos[0];
	int u = 0;
	while (aux != NULL) {
		if (!aux -> terminated) {
			kill(aux -> pid, SIGKILL);
		}
		aux = procesos[++u];
	}

	imprimir_estadisticas();
	exit(0);
}	



int main(int argc, char * argv []) {
	
	signal(SIGINT, terminar);

	char *path = argv[1];
	int n = atoi(argv[2]);

	m = n_lines(path);
	printf("Hay que ejecutar %d tareas\n", m);
	char tasks[m][255];
	input_read(tasks, path, m);
	
	int cont_procs = 0;
	int cont_tasks = 0;

	clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);
	
	/*Procs array*/
	Process* procs[m];
	Process* aux;
	aux -> terminated = -1;
	aux -> exit_status = -1;
	for (int i = 0; i < m; i++)
	{
		procs[i] = aux;
		procesos[i] = aux;
	}
	
	

	while (cont_tasks < m) {
		int pipes[2];
		pipe(pipes); // Create the pipes			
		cont_procs++;
		cont_tasks++;
		pid_t pid = fork();

		if (pid != 0) {
			/*Start init proc*/
			Process* proc = malloc(sizeof(Process));
			strcpy(proc -> task, tasks[cont_tasks - 1]);
			clock_gettime(CLOCK_MONOTONIC_RAW, &proc -> start_t);
			// printf("En proceso %s start_t es %lu ns\n", proc -> task, proc -> start_t.tv_nsec);
			proc -> pid = pid;
			proc -> terminated = 0;
			procs[cont_tasks - 1] = proc;
			procesos[cont_tasks - 1] = proc;
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
					clock_gettime(CLOCK_MONOTONIC_RAW, &procs[i] -> end_t);
					// printf("Al final de proceso %s end_t es %lu ns\n", procs[i] -> task, procs[i] -> end_t.tv_nsec);
					procs[i] -> terminated = 1;
					procs[i] -> exit_status = WEXITSTATUS(status);
					close(pipes[1]);
					char* foo = calloc(16384, sizeof(char));
					int nbytes = read(pipes[0], foo, 16384);
					procs[i] -> output = foo;
					cont_procs--;
				}
			}
		}

		/* Quedar pegado si es que estamos con el máximo de procesos */
		while (cont_procs == n) {
			printf("CONT_PROCS == N\n");
			for (int i=0; i<m; i++) {
				int status;
				if (procs[i] -> pid > 0 && !procs[i] -> terminated && waitpid(procs[i] -> pid, &status, 1) == 0) { /*Si terminó, liberar cupo y setear end_t */
					clock_gettime(CLOCK_MONOTONIC_RAW, &procs[i] -> end_t);
					procs[i] -> terminated = 1;
					procs[i] -> exit_status = WEXITSTATUS(status);
					close(pipes[1]);
					char* foo = calloc(16384, sizeof(char));
					int nbytes = read(pipes[0], foo, 16384);
					procs[i] -> output = foo;
					cont_procs--;
				}
			}
		}
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &termino);
	imprimir_estadisticas();

}

void imprimir_estadisticas() {
	int u = 0;
	Process* aux = procesos[0];
	while (procesos[u] != NULL) {
		if (procesos[u] -> exit_status != -1) {
			imprimir_proc(procesos[u++]);
		} else {
			printf("El resto de los procesos no alcanzó a comenzar\n");
			break;
		}
	} 

	long long int suma_tiempos = 0;
	for (int i = 0; i < m; i++) {
		unsigned int delta_aux = (procesos[i] -> end_t.tv_sec - procesos[i] -> start_t.tv_sec) * 1000000 + (procesos[i] -> end_t.tv_nsec - procesos[i] -> start_t.tv_nsec) / 1000;
		suma_tiempos += delta_aux;
	}
	unsigned int delta_us = (termino.tv_sec - inicio.tv_sec) * 1000000 + (termino.tv_nsec - inicio.tv_nsec) / 1000;

	printf("Tiempo secuencial de ejecución (microsegs): %lld\n", suma_tiempos);
	printf("Tiempo real de ejecución (microsegs): %u\n", delta_us);
}
