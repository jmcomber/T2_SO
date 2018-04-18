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
	char *path = argv[1];
	int n = atoi(argv[2]);

	int m = n_lines(path);
	printf("Hay que correr %d tareas\n", m);
	// char* tasks[m] = input_read(path);
}