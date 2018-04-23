
struct proc {
	pid_t pid;
	char task[255];
	long long int start_t;
	long long int end_t;
	int exit_status;
	char* output;
	char terminated;
};
typedef struct proc Process;