#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



int n_lines(char* path) {
	FILE *fp = fopen(path,"r");
	int ch=0;
	int lines=0;
	while(!feof(fp)) {
	  ch = fgetc(fp);
	  if(ch == '\n')
	  {
	    lines++;
	  }
	}
	lines++;
	/* Cuidado: no sé si tira error en otra plataforma */
	if (ch == '\n') {
		lines--;
	}
	return lines;
}


void input_read(char tasks[][255], char* path, int m) {
	FILE *fp1;
    char buff[255];
    char* pch;
    fp1 = fopen (path, "r");
    int i = 0;

    while (fgets(buff, 255, (FILE*)fp1) != NULL){
    	strcpy(tasks[i++], buff);
    	// printf("buff es %s\n", buff);
    }

}



char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}



