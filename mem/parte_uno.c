#include <math.h>
void mejor_d(int levels, int *bits_uno, int *bits_dos, int *bits_tres, int *bits_cuatro, int *bits_cinco){
    int total;
    int digitos_1, digitos_2, digitos_3, digitos_4, digitos_5;
    int mejor_d_uno, mejor_d_dos, mejor_d_tres, mejor_d_cuatro, mejor_d_cinco = 0;
    double minima_memoria = INFINITY;
    double memoria;
    if (levels == 1){
        printf("BITS NIVEL 1: 22\n");
        printf("ESPACIO UTILIZADO: %f MB \n", pow(2,22)*11/(8*1048576));
        // ejemplo de como hacer asignaciones => *bits_uno = 15;
    }
    else if (levels == 2){
        
        for (digitos_1 = 1; digitos_1 < 22; digitos_1 ++){
            digitos_2 = 22 - digitos_1;
            memoria = pow(2, digitos_1) * digitos_2 + pow(2, digitos_2) * 11;
            if (memoria < minima_memoria){
                minima_memoria = memoria;
                mejor_d_uno = digitos_1;
            }


        }
        printf("BITS NIVEL 1: %i\n", mejor_d_uno);
        printf("BITS NIVEL 2: %i\n", 22 - mejor_d_uno);  
        printf("ESPACIO UTILIZADO: %f MB \n", minima_memoria/(8*1048576));
        *bits_uno = mejor_d_uno;
        *bits_dos = 22 - mejor_d_uno;
    }
    else if (levels == 3){
        for (digitos_1 = 1; digitos_1 < 22; digitos_1 ++){
            for (digitos_2 = 1; digitos_2 < 22 - digitos_1; digitos_2 ++){
                digitos_3 = 22 - digitos_1 - digitos_2;
                memoria = pow(2, digitos_1) * digitos_2 + pow(2, digitos_2) * digitos_3 + pow(2, digitos_3) * 11;
                if (memoria < minima_memoria){
                    minima_memoria = memoria;
                    mejor_d_uno = digitos_1;
                    mejor_d_dos = digitos_2;
                    mejor_d_tres = digitos_3;
                }
            }


        }
        printf("BITS NIVEL 1: %i\n", mejor_d_uno);
        printf("BITS NIVEL 2: %i\n", mejor_d_dos);  
        printf("BITS NIVEL 3: %i\n", mejor_d_tres);  
        printf("ESPACIO UTILIZADO: %f MB \n", minima_memoria/(8*1048576));
        *bits_uno = mejor_d_uno;
        *bits_dos = mejor_d_dos;
        *bits_tres = mejor_d_tres;

    }
    else if (levels == 4){
        for (digitos_1 = 1; digitos_1 < 22; digitos_1 ++){
            for (digitos_2 = 1; digitos_2 < 22 - digitos_1; digitos_2 ++){
                for (digitos_3 = 1; digitos_3 < 22 - digitos_1 - digitos_2; digitos_3++){
                    digitos_4 = 22 - digitos_1 - digitos_2 - digitos_3;
                    memoria = pow(2, digitos_1) * digitos_2 + pow(2, digitos_2) * digitos_3 + pow(2, digitos_3) * digitos_4 + pow(2, digitos_4) * 11;
                    if (memoria < minima_memoria){
                        minima_memoria = memoria;
                        mejor_d_uno = digitos_1;
                        mejor_d_dos = digitos_2;
                        mejor_d_tres = digitos_3;
                        mejor_d_cuatro = digitos_4;
                    }
                }
            }


        }
        printf("BITS NIVEL 1: %i\n", mejor_d_uno);
        printf("BITS NIVEL 2: %i\n", mejor_d_dos);  
        printf("BITS NIVEL 3: %i\n", mejor_d_tres);  
        printf("BITS NIVEL 4: %i\n", mejor_d_cuatro); 
        printf("ESPACIO UTILIZADO: %f MB \n", minima_memoria/(8*1048576));
        *bits_uno = mejor_d_uno;
        *bits_dos = mejor_d_dos;
        *bits_tres = mejor_d_tres;
        *bits_cuatro = mejor_d_cuatro;
    }
    else {
        
        for (digitos_1 = 1; digitos_1 < 22; digitos_1 ++){
            for (digitos_2 = 1; digitos_2 < 22 - digitos_1; digitos_2 ++){
                for (digitos_3 = 1; digitos_3 < 22 - digitos_1 - digitos_2; digitos_3++){
                    for (digitos_4 = 1; digitos_4 < 22 - digitos_1 - digitos_2 - digitos_3; digitos_4++){
                        digitos_5 = 22 - digitos_1 - digitos_2 - digitos_3 - digitos_4;
                        memoria = pow(2, digitos_1) * digitos_2 + pow(2, digitos_2) * digitos_3 + pow(2, digitos_3) * digitos_4 + pow(2, digitos_4) * digitos_5 + pow(2, digitos_5)*11;
                        if (memoria < minima_memoria){
                            minima_memoria = memoria;
                            mejor_d_uno = digitos_1;
                            mejor_d_dos = digitos_2;
                            mejor_d_tres = digitos_3;
                            mejor_d_cuatro = digitos_4;
                            mejor_d_cinco = digitos_5;
                        }
                    }
                }
            }


        }
        printf("BITS NIVEL 1: %i\n", mejor_d_uno);
        printf("BITS NIVEL 2: %i\n", mejor_d_dos);  
        printf("BITS NIVEL 3: %i\n", mejor_d_tres);  
        printf("BITS NIVEL 4: %i\n", mejor_d_cuatro); 
        printf("BITS NIVEL 5: %i\n", mejor_d_cinco); 
        printf("ESPACIO UTILIZADO: %f MB \n", minima_memoria/(8*1048576));
        *bits_uno = mejor_d_uno;
        *bits_dos = mejor_d_dos;
        *bits_tres = mejor_d_tres;
        *bits_cuatro = mejor_d_cuatro;
        *bits_cinco = mejor_d_cinco;

    }
}
