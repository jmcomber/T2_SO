



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


// char** input_read(char* path) {
// 	FILE *fp1;
//     char buff[255];
//     char* pch;
//     fp1 = fopen (path, "r");

//     while (fgets(buff, 255, (FILE*)fp1) != NULL){
//     	char** params;
//     	params = (char**) calloc(20, sizeof(char*))
//     	pch = strtok(buff, " ");
//     	int contador = 0;
//         while (pch != NULL) {
//         	params[contador] = pch;
//         	pch = strtok(NULL, " ");
//         }
//     }
// }
