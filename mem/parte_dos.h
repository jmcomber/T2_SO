int levels;
int bits_uno, bits_dos, bits_tres, bits_cuatro, bits_cinco;



struct tlb{
    int d_virtual[64];
    int d_fisica[64];  
};
typedef struct tlb TLB;

struct pagina
{
    int total_entradas;
    int count_entradas_usadas;
    long *entradas_fisicas; //solo si estamos en el ultimo
    struct pagina* entradas;
 
};
typedef struct pagina Pagina;

void getBin(int num, char *str);
Pagina *  construir_paginas();
void imprimir_tlb();