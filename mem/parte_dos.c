#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <parte_dos.h>







int levels;
int bits_uno, bits_dos, bits_tres, bits_cuatro, bits_cinco;

Pagina *  construir_paginas(){
    if (levels == 1) {
        Pagina * puntero_tabla_1;
        puntero_tabla_1 = malloc(sizeof(Pagina));
        puntero_tabla_1 -> total_entradas = pow(2, 20);
        puntero_tabla_1 -> entradas_fisicas = malloc(sizeof(long) * 
            puntero_tabla_1 -> total_entradas);
        puntero_tabla_1 -> count_entradas_usadas = 0;
    }

    else if (levels == 2){
        Pagina * puntero_tabla_1;
        puntero_tabla_1 = malloc(sizeof(Pagina));
        puntero_tabla_1 -> total_entradas = pow(2, bits_uno);
        puntero_tabla_1 -> entradas = malloc(sizeof(Pagina)*pow(2, bits_uno));
        for (int i =0; i < puntero_tabla_1-> total_entradas; i ++){
            entradas[i] -> total_entradas = pow(2, bits_dos);
            entradas[i] -> entradas_fisicas = malloc(sizeof(long)*entradas[i] -> total_entradas);
            entradas[i] -> count_entradas_usadas = 0;
        }

    }
};



void imprimir_tlb(TLB * puntero){
    if (levels == 1){
        printf("i      n1_number      frame_number\n");
        for (int contador= 0; contador < 64; contador++){
            printf("%i      %i              %i\n",contador, puntero -> d_virtual[contador], puntero -> d_fisica[contador]);
        }
    }
    else if (levels == 2){
        //aqui habria que dividir la direccion en 2
    }
}
long buscar_en_tlb(TLB * puntero_tlb, long direccion){
    for (int i=0; i < 64; i ++){
        if (puntero_tlb -> d_virtual[i]){
            return puntero_tlb -> d_fisica[i];
        }
    }
    return -1;
}
