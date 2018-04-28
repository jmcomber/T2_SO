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
    printf("\n\n");
    //FIN PARTE 1 //

    //INICIO PARTE 2 //
    //PRIMERO CREAMOS LAS TABLAS //

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
    int contador_page_fault = 0;
    int contador_hit = 0;
    int contador_total = 0;
    while (fgets(buff, 256, (FILE*)fp1) != NULL){
        numero = strtol(buff,&ptr, 10);
        printf("-%li-\n",numero);
        contador_total ++;
        char *binario;
        char *offset, *v_adress;
        binario = decimal_to_binary(numero);
        
        offset = malloc(sizeof(char)*8 + 1);
        v_adress = malloc(sizeof(char)*20 + 1);
        strncpy(offset, binario + 20, 8);
        strncpy(v_adress, binario, 20);
        offset[8] = '\0';
        v_adress[20] = '\0';


    

        int n_dvirtual = bstr_to_dec(v_adress);
        int esta;
        esta = buscar_en_tlb(puntero_tlb, n_dvirtual);
        //printf("Página virtual: %i, offset: %i \n",n_dvirtual, bstr_to_dec(offset));



        if (esta == -1){
            //Estamos en presencia de un TLB miss
            
            //printf("TLB MISS\n");
            // en c guardamos el marco fisico
            int c = buscar_en_pagina(puntero_pagina_inicial, v_adress, 1, levels);



            if (c == -1){
                // CON UNA PAGE FAULT
                //printf("PAGE FAULT\n");
                contador_page_fault ++;
                unsigned int contenido;
                int nuevo_frame_fisico =  determinar_saliente(ptr_mf);
                contenido = cargar_en_memoria_fisica(ptr_mf, v_adress, offset, nuevo_frame_fisico);
                char * dir_fisica = concat(decimal_to_binary(nuevo_frame_fisico), offset);
                printf("Direccion Fisica: %i\n", bstr_to_dec(dir_fisica));
                printf("Contenido: %i \n", contenido);
                //------------ MANEJO TLB -------------------------------------------------//
                //------------ me encargo de agregar el par () ----------------------------//
                actualizar_tlb(puntero_tlb, n_dvirtual, nuevo_frame_fisico);
                //------------ y de appendear a la lista LRU-- ----------------------------//
                actualizar_prioridades_tlb(puntero_tlb, n_dvirtual);
                //------------ FIN MANEJO TLB ----------------------------------------------//
                marcar_como_invalida(puntero_pagina_inicial, 1, levels, nuevo_frame_fisico);
                actualizar_tabla_paginas(puntero_pagina_inicial, v_adress, 1, levels, nuevo_frame_fisico);
                
                //actualizar_prioridades(ptr_mf, nuevo_frame_fisico);


            }


            else {
                // EN C está la direccion fisica donde se encuentra, en este caso el marco
                //Aqui buscamos en el marco 
                //printf("PAGE HIT\n");
                int contenido = ptr_mf -> frames[c][bstr_to_dec(offset)];
                char * dir_fisica = concat(decimal_to_binary(c), offset);
                printf("Direccion Fisica: %i\n", bstr_to_dec(dir_fisica));
                printf("Contenido: %i \n", contenido);
                actualizar_prioridades(ptr_mf, c); //memoria fisica

                //------------ MANEJO TLB ----------------------------------------------//
                actualizar_tlb(puntero_tlb, bstr_to_dec(v_adress), c);
                actualizar_prioridades_tlb(puntero_tlb, n_dvirtual);
                //------------ FIN MANEJO TLB ----------------------------------------------//

                

            }

        }
        else {
            //printf("TLB HIT\n");
            contador_hit ++;
            int contenido = ptr_mf -> frames[esta][bstr_to_dec(offset)];
            char * dir_fisica = concat(decimal_to_binary(esta), offset);
            printf("Direccion Fisica: %i\n", bstr_to_dec(dir_fisica));
            printf("Contenido: %i \n", contenido);
            actualizar_prioridades(ptr_mf, esta); //memoria fisica
            //------------ MANEJO TLB ----------------------------//
            actualizar_prioridades_tlb(puntero_tlb, n_dvirtual);
            //------------ FIN MANEJO TLB ------------------------//
        }
        
        // Node * curr;
        // curr =  puntero_tlb -> lista_usadas -> first;
        // printf("Imprimiendo lista ligada\n");
        // for (int i=0; i < puntero_tlb -> lista_usadas -> count; i ++){
        //     printf("Posicion [%i] esta %i \n",i, curr -> pagina_virtual);
        //     curr = curr -> next;;
        // }
        // Node * curr;
        // curr =  ptr_mf -> lista_accesos -> first;
        // printf("Imprimiendo lista accesos_a_marco \n");
        // printf("Contador de marcos: %i \n", ptr_mf -> lista_accesos -> count);
        // for (int i=0; i < ptr_mf -> lista_accesos -> count; i ++){
        //     printf("Posicion [%i] esta %i \n",i, curr -> pagina_virtual);
        //     curr = curr -> next;;
        // }

        printf("\n\n");
        free(offset);
        free(v_adress);
        free(binario);
            // if (en_tlb == -1) {
        //     //buscar_en_paginas(, direccion)
        // }
    }
    printf("PORCENTAJE_PAGE_FAULTS = %d %%\n", 100*contador_page_fault/contador_total);
    printf("PORCENTAJE_TLB_HITS =  %d %%\n", 100*contador_hit/contador_total);
    imprimir_tlb(puntero_tlb);
    // free(bits_uno_ptr);
    // free(bits_dos_ptr);
    // free(bits_tres_ptr);
    // free(bits_cuatro_ptr);
    // free(bits_cinco_ptr);
    free(puntero_tlb -> lista_usadas);
    free(ptr_mf -> lista_accesos);
    free(puntero_pagina_inicial);



}