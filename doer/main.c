#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void imprimir_estadisticas() {

}


int main(int argc, char * argv []) {
	signal(SIGINT, imprimir_estadisticas);
	char *path = argv[1];
	int n = atoi(argv[2]);
}