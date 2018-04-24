int levels;
int bits_uno, bits_dos, bits_tres, bits_cuatro, bits_cinco;



struct tlb{
    int d_virtual[64]; 
    int d_fisica[64];  
    int contador;
};
typedef struct tlb TLB;

struct pagina
{
    long *entradas_fisicas; //solo si estamos en el ultimo
    struct pagina ** entradas;
 
};
typedef struct pagina Pagina;

struct memoria_fisica {
    unsigned int * frames[256];
    int contador;
};
typedef struct memoria_fisica MemoriaFisica;

void getBin(int num, char *str);
int bstr_to_dec(const char * str);
void imprimir_tlb();
Pagina * crear_paginas(int niveles_faltantes, int nivel_actual);
long determinar_siguiente_cantidad(int nivel_actual);
int buscar_posicion(char * adress_entera, int nivel_actual);
long buscar_en_pagina(Pagina * pagina_actual, char * adress_entera, int nivel_actual, int niveles_faltantes);
MemoriaFisica * inicializar_mf();
unsigned int cargar_en_memoria_fisica(MemoriaFisica * ptr, char * adress, char * offset);