#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parte_uno.c"
#include "parte_dos.c"




int main(int argc, char ** argv){
    char* archivo;
    levels = atoi(argv[1]);
    bits_uno, bits_dos, bits_tres, bits_cuatro, bits_cinco = 0;
    int *bits_uno_ptr = &bits_uno;
    int *bits_dos_ptr = &bits_dos;
    int *bits_tres_ptr = &bits_tres;
    int *bits_cuatro_ptr = &bits_cuatro;
    int *bits_cinco_ptr = &bits_cinco;
    mejor_d(levels, bits_uno_ptr, bits_dos_ptr, bits_tres_ptr, bits_cuatro_ptr, bits_cinco_ptr);
    printf("bits_uno_en main: %i \n", *bits_uno_ptr);	
    //FIN PARTE 1 //

    //INICIO PARTE 2 //
    //PRIMERO CREAMOS LAS TABLAS //
    Pagina * puntero_tabla_uno;
    //puntero_tabla_uno = construir_paginas();

    TLB * puntero_tlb;
    puntero_tlb = malloc(sizeof(TLB));


    archivo = argv[2];
    FILE *fp1;
    char buff[255];
    fp1= fopen (archivo, "r");
    char *ptr;
    long numero; ;
    while (fgets(buff, 255, (FILE*)fp1) != NULL){
        numero = strtol(buff,&ptr, 10);
        printf("Leyendo direccion virtual: %li \n",numero);
        int en_tlb;
        en_tlb = buscar_en_tlb(puntero_tlb, 1);
        char *binario;
        binario = decimal_to_binary(numero);
        char *offset[8];
        printf("1\n");
        determinar_offset(binario, offset);
        printf("Binario: %s\n",binario);
        printf("Offset %s \n", offset);

        // if (en_tlb == -1) {
        //     //buscar_en_paginas(, direccion)
        // }
    }
}