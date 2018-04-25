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
    puntero_tabla_uno = crear_paginas(levels, 1);

    TLB * puntero_tlb;
    puntero_tlb = crear_tlb();

    Pagina * puntero_pagina_inicial;
  
    puntero_pagina_inicial = crear_paginas(levels, 1);
 
    MemoriaFisica * ptr_mf;
    ptr_mf = inicializar_mf();
    
    

    archivo = argv[2];
    FILE *fp1;
    char buff[255];
    fp1= fopen (archivo, "r");
    char *ptr;
    long numero;
    int contador_miss, contador_hit = 0;
    while (fgets(buff, 256, (FILE*)fp1) != NULL){
        numero = strtol(buff,&ptr, 10);
        printf("Leyendo direccion virtual: %li \n",numero);
        char *binario, *offset, *v_adress;
        binario = decimal_to_binary(numero);
        
        offset = malloc(sizeof(char)*8);
        v_adress = malloc(sizeof(char)*20);

        strncpy(offset, binario + 20, 8);
        strncpy(v_adress, binario, 20);
        int n_dvirtual = bstr_to_dec(v_adress);
        int esta = buscar_en_tlb(puntero_tlb, n_dvirtual);
        printf("Página virtual: %i, offset: %i \n",n_dvirtual, bstr_to_dec(offset) );



        if (esta == -1){
            //Estamos en presencia de un TLB miss
            contador_miss ++;
            printf("TLB MISS\n");
            int c = buscar_en_pagina(puntero_pagina_inicial, v_adress, 1, levels);
            


            if (c == -1){
                // CON UNA PAGE FAULT
                printf("PAGE FAULT\n");
                unsigned int contenido;
                int nuevo_frame_fisico =  determinar_saliente(ptr_mf);
                contenido = cargar_en_memoria_fisica(ptr_mf, v_adress, offset);
                printf("Contenido: %i \n", contenido);
                //actualizar_tlb(puntero_tlb, bstr_to_dec(v_adress), ptr_mf -> contador);
                actualizar_tabla_paginas(puntero_pagina_inicial, v_adress, 1, levels, nuevo_frame_fisico);
                //marcar_como_sucia(puntero_pagina_inicial, 1, levels, ptr_mf -> contador);
    

            }


            else {
                // EN C está la direccion fisica donde se encuentra, en este caso el marco
                //Aqui buscamos en el marco 
                printf("PAGE HIT\n");
                int contenido = ptr_mf -> frames[c][bstr_to_dec(offset)];
                printf("Contenido: %i \n", contenido);

            }

        }
        else {
            printf("TLB HIT\n");
            int contenido = ptr_mf -> frames[esta][bstr_to_dec(offset)];
            printf("Contenido: %i \n", contenido);
        }
        printf("\n\n\n\n\n\n");







        // if (en_tlb == -1) {
        //     //buscar_en_paginas(, direccion)
        // }
    }
    for(int i; i < 256; i++){
            printf("Prioridad [%i]: %i \n", i, ptr_mf -> prioridades[i]);
        }
}