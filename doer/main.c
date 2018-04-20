#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "utils.c"


#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

void imprimir_estadisticas() {

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
	printf("tasks quedó como:\n");
    for (int j = 0; j < m; j++)
    {
    	printf("%d: %s", j, tasks[j]);
    }
    printf("\n");
    
    int cont_procs = 0;
    int cont_tasks = 0;

    while (cont_tasks < m && cont_procs < n) {
    	pid_t pid = fork();
    	if (pid != 0) {
    		cont_procs++;
    		cont_tasks++;
    		// printf("[P] aumentando cont_procs a %d\n", cont_procs);
    	}
    	if (pid == 0) {
    		// printf("[CH] vamos a ejecutar task n° %d, %s\n", cont_tasks, tasks[cont_tasks]);
    		char** aux = str_split(tasks[cont_tasks++], ' ');
    		char* cmd = aux[0];
    		// printf("cmd es %s\n", cmd);
    		// printf("(%d) Aux es ", NELEMS(aux));
    		// for (int j=0; j<NELEMS(aux); j++) {
    		// 	if (aux[j] == NULL) {
    		// 		printf("NULL-");
    		// 	} else {
    		// 		printf("%s-", aux[j]);
    		// 	}
    		// }
    		// printf("\n");
    		sleep(1);
			execvp(cmd, aux);
    	}
    	sleep(2);
    }
    // exit(0);

    /* En tasks tenemos un string por cada tarea, pero como string, no como arreglo */
}