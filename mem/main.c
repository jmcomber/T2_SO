#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parte_uno.c"

int main(int argc, char ** argv){
    int levels;
    char* archivo;
    levels = atoi(argv[1]);
    int bits_uno, bits_dos, bits_tres, bits_cuatro, bits_cinco = 0;
    int *bits_uno_ptr = &bits_uno;
    int *bits_dos_ptr = &bits_dos;
    int *bits_tres_ptr = &bits_tres;
    int *bits_cuatro_ptr = &bits_cuatro;
    int *bits_cinco_ptr = &bits_cinco;
    mejor_d(levels, bits_uno_ptr, bits_dos_ptr, bits_tres_ptr, bits_cuatro_ptr, bits_cinco_ptr);
    printf("bits_uno_en main: %i \n", *bits_uno_ptr);	
}