#include <sys/time.h>



struct proc {
	pid_t pid;
	char task[255];
	struct timespec start_t;
	struct timespec end_t;
	int exit_status;
	char* output;
	char terminated;
};
typedef struct proc Process;