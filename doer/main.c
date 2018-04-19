#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "utils.c"



void imprimir_estadisticas() {

}


void terminar() {
	// terminar procesos que están corriendo
	imprimir_estadisticas();
	exit(0);
}	



int main(int argc, char * argv []) {
	signal(SIGINT, terminar);
	// char cmd[10] = "echo";
	// char *args[] = {cmd, "sss", NULL};
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

    // char** aux = str_split(tasks[0], ' ');
    
    
    


    /* En tasks tenemos un string por cada tarea, pero como string, no como arreglo */
}