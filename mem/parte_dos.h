int levels;
int bits_uno, bits_dos, bits_tres, bits_cuatro, bits_cinco;

struct node
{
  /** Siguiente nodo */
  struct node* next;
  /** Valor del nodo */
  int pagina_virtual;
};

typedef struct node Node;

/** Estructura de una lista ligada */
struct linked_list
{

  Node* first;

  Node* last;

  int count;
};


typedef struct linked_list LinkedList;

struct tlb{
    int d_virtual[64]; 
    int d_fisica[64];  
    int contador;
    LinkedList * lista_usadas;
};
typedef struct tlb TLB;

struct pagina
{
    long *entradas_fisicas; //solo si estamos en el ultimo
    struct pagina ** entradas;
    int * valid_bit;
 
};
typedef struct pagina Pagina;



struct memoria_fisica {
    unsigned int * frames[256];
    LinkedList * lista_accesos;
};
typedef struct memoria_fisica MemoriaFisica;

void getBin(int num, char *str);
int bstr_to_dec(const char * str);
void imprimir_tlb();
Pagina * crear_paginas(int niveles_faltantes, int nivel_actual);
long determinar_siguiente_cantidad(int nivel_actual);
int buscar_posicion(char * adress_entera, int nivel_actual);
int buscar_en_pagina(Pagina * pagina_actual, char * adress_entera, int nivel_actual, int niveles_faltantes);
MemoriaFisica * inicializar_mf();
int cargar_en_memoria_fisica(MemoriaFisica * ptr, char * adress, char * offset, int frame_a_copiar);
void marcar_como_invalida(Pagina * pagina_actual, int curr_level, int levels_faltantes, int numero_frame);
int determinar_saliente(MemoriaFisica * ptr);
void actualizar_prioridades(MemoriaFisica * ptr_memoria_fisica, int recien);
int determinar_saliente_TLB(TLB* ptr);
void actualizar_tlb(TLB * puntero_tlb, int v_adress, int pagina_virtual);
void actualizar_prioridades_tlb(TLB * ptr, int pagina_virtual);  
Node * node_init(int value);
void linkedlist_append(LinkedList* list, int marco_fisico);
void eliminar_nodo(LinkedList * list, int position);
char* concat(const char *s1, const char *s2);
