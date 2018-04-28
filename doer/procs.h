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

struct linked_list
{
  Process *puntero_inicio;
  Process *puntero_final;
  int count;
};
typedef struct linked_list LinkedList;