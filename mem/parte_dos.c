#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parte_dos.h"

int levels;
int bits_uno, bits_dos, bits_tres, bits_cuatro, bits_cinco;


int bstr_to_dec(const char * str)
{
    int val = 0;
    while (*str != '\0')
        val = 2 * val + (*str++ - '0');
    return val;
}



char *decimal_to_binary(int n)
{
   int c, d, count;
   char *pointer;
   count = 0;
   pointer = (char*)malloc(32+1);
 
   if (pointer == NULL)
      exit(EXIT_FAILURE);
 
   for (c = 27 ; c >= 0 ; c--)
   {
      d = n >> c;
 
      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';
 
      count++;
   }
   *(pointer+count) = '\0';
 
   return  pointer;
}
TLB * crear_tlb(){
  TLB * puntero_tlb;
  puntero_tlb = malloc(sizeof(TLB));
  for (int i=0; i < 64; i ++){
    puntero_tlb -> d_virtual[i] = -1;
    puntero_tlb -> d_fisica[i] = -1;
  }
  LinkedList* list = malloc(sizeof(LinkedList));
  list -> count = 0;
  list -> first = NULL;
  list -> last = NULL;
  puntero_tlb -> lista_usadas = list;
  return puntero_tlb;

}
int determinar_saliente_TLB(TLB* puntero_tlb){
  // CASO 1: Hay menos de 64 entradas en la cola //
  if (puntero_tlb -> lista_usadas -> count < 64){ 
    for (int k=0; k < 64; k++){
      if (puntero_tlb -> d_virtual[k] == -1){
        return k;
      }
    }
  }
   // CASO 2: Hay 64 en la entrada, por lo cual hay que sacar el primero
  else {
   
    Node * salida;
    salida = puntero_tlb -> lista_usadas -> first;

    for (int k=0; k < 64; k++){
      if (puntero_tlb -> d_virtual[k] == salida -> pagina_virtual){
        return k;
      }
    }
  }
 } 



void determinar_offset(char * binario, char * offset){
  for (int i= 0; i < 8; i ++){
    offset[i] = binario[28 - i];
  }
}




void imprimir_tlb(TLB * puntero){
    if (levels == 1){
        printf("%-10s%-15s%-15s\n", "i", "n1_number", "frame_number"); 
        for (int contador= 0; contador < 64; contador++){
            if (puntero -> d_fisica[contador] != -1){
              printf("%-10i%-15i%-15i\n",contador, puntero -> d_virtual[contador], puntero -> d_fisica[contador]);
            }
            else {
              printf("%-10i%-15s%-15s\n",contador, "-",  "-");
            }
        }
    }
    else if (levels == 2){
        printf("%-10s%-15s%-15s%-15s\n", "i", "n1_number", "n2_number", "frame_number"); 
        for (int contador= 0; contador < 64; contador++){
            char * adress_entera = decimal_to_binary(puntero -> d_virtual[contador]);
            char * n1, * n2;
            n1 = malloc(sizeof(char)*bits_uno + 1);
            n2 = malloc(sizeof(char)*bits_dos + 1);
            strncpy(n1, adress_entera + 8, bits_uno);
            strncpy(n2, adress_entera + 8 + bits_uno, bits_dos);
            n1[bits_uno] = '\0';
            n2[bits_dos] = '\0';
            if (puntero -> d_fisica[contador] != -1){
              printf("%-10i%-15i%-15i%-15i\n",contador, bstr_to_dec(n1), bstr_to_dec(n2), puntero -> d_fisica[contador]);
            }
            else {
              printf("%-10i%-15s%-15s%-15s\n",contador, "-",  "-", "-");
            }
        }
        //aqui habria que dividir la direccion en 2
    }
    else if (levels == 3){
        printf("%-10s%-15s%-15s%-15s%-15s\n", "i", "n1_number", "n2_number", "n3_number", "frame_number"); 
        for (int contador= 0; contador < 64; contador++){
            char * adress_entera = decimal_to_binary(puntero -> d_virtual[contador]);
            char * n1, * n2, * n3;
            n1 = malloc(sizeof(char)*bits_uno + 1);
            n2 = malloc(sizeof(char)*bits_dos + 1);
            n3 = malloc(sizeof(char)*bits_tres + 1);
            strncpy(n1, adress_entera + 8, bits_uno);
            strncpy(n2, adress_entera + 8 + bits_uno, bits_dos);
            strncpy(n3, adress_entera + 8 + bits_uno + bits_dos, bits_tres);
            n1[bits_uno] = '\0';
            n2[bits_dos] = '\0';
            n3[bits_tres] = '\0';
            if (puntero -> d_fisica[contador] != -1){
              printf("%-10i%-15i%-15i%-15i%-15i\n",contador, bstr_to_dec(n1), bstr_to_dec(n2), bstr_to_dec(n3), puntero -> d_fisica[contador]);
            }
            else{
              printf("%-10i%-15s%-15s%-15s%-15s\n",contador, "-",  "-", "-", "-");

            }
        }
        //aqui habria que dividir la direccion en 2
    }
    else if (levels == 4){
        printf("%-10s%-15s%-15s%-15s%-15s%-15s\n", "i", "n1_number", "n2_number", "n3_number", "n4_number", "frame_number"); 
        for (int contador= 0; contador < 64; contador++){
            char * adress_entera = decimal_to_binary(puntero -> d_virtual[contador]);
            char * n1, * n2, * n3, * n4;
            n1 = malloc(sizeof(char)*bits_uno +1);
            n2 = malloc(sizeof(char)*bits_dos +1);
            n3 = malloc(sizeof(char)*bits_tres +1);
            n4 = malloc(sizeof(char)*bits_cuatro +1);
            strncpy(n1, adress_entera + 8, bits_uno);
            strncpy(n2, adress_entera + 8 + bits_uno, bits_dos);
            strncpy(n3, adress_entera + 8 + bits_uno + bits_dos, bits_tres);
            strncpy(n4, adress_entera + 8 + bits_uno + bits_dos + bits_tres, bits_cuatro);
            n1[bits_uno] = '\0';
            n2[bits_dos] = '\0';
            n3[bits_tres] = '\0';
            n4[bits_cuatro] = '\0';
            if (puntero -> d_fisica[contador] != -1){
              printf("%-10i%-15i%-15i%-15i%-15i%-15i\n",contador, bstr_to_dec(n1), bstr_to_dec(n2), bstr_to_dec(n3), bstr_to_dec(n4), puntero -> d_fisica[contador]);
            }
            else{
              printf("%-10i%-15s%-15s%-15s%-15s%-15s\n",contador, "-",  "-", "-", "-", "-");

            }
        }

    }
    else {
        printf("%-10s%-15s%-15s%-15s%-15s%-15s%-15s\n", "i", "n1_number", "n2_number", "n3_number", "n4_number", "n5_number", "frame_number"); 
        for (int contador= 0; contador < 64; contador++){
            char * adress_entera = decimal_to_binary(puntero -> d_virtual[contador]);
            char * n1, * n2, * n3, * n4, * n5;
            n1 = malloc(sizeof(char)*bits_uno+1);
            n2 = malloc(sizeof(char)*bits_dos+1);
            n3 = malloc(sizeof(char)*bits_tres+1);
            n4 = malloc(sizeof(char)*bits_cuatro+1);
            n5 = malloc(sizeof(char)*bits_cinco+1);
            strncpy(n1, adress_entera + 8, bits_uno);
            strncpy(n2, adress_entera + 8 + bits_uno, bits_dos);
            strncpy(n3, adress_entera + 8 + bits_uno + bits_dos, bits_tres);
            strncpy(n4, adress_entera + 8 + bits_uno + bits_dos + bits_tres, bits_cuatro);
            strncpy(n5, adress_entera + 8 + bits_uno + bits_dos + bits_tres + bits_cuatro, bits_cinco);
            n1[bits_uno] = '\0';
            n2[bits_dos] = '\0';
            n3[bits_tres] = '\0';
            n4[bits_cuatro] = '\0';
            n5[bits_cinco] = '\0';
            if (puntero -> d_fisica[contador] != -1){
              printf("%-10i%-15i%-15i%-15i%-15i%-15i%-15i\n",contador, bstr_to_dec(n1), bstr_to_dec(n2), bstr_to_dec(n3), bstr_to_dec(n4), bstr_to_dec(n5), puntero -> d_fisica[contador]);
            } 
            else{
              printf("%-10i%-15s%-15s%-15s%-15s%-15s%-15s\n",contador, "-",  "-", "-", "-", "-","-");
            }     
        }

    }

}

int buscar_en_tlb(TLB * puntero_tlb, int n_direccion){
  for (int i = 0; i < 64; i ++){
    if (puntero_tlb -> d_virtual[i] == n_direccion){
      return puntero_tlb -> d_fisica[i];
    }

  }
  return -1;
}

long determinar_siguiente_cantidad(int nivel_actual){
  if (nivel_actual == 1){
    return pow(2,bits_uno);
  }
  else if(nivel_actual == 2){
    return pow(2, bits_dos);
  }
  else if(nivel_actual == 3){
    return pow(2, bits_tres);
  }
  else if(nivel_actual == 4){
    return pow(2, bits_cuatro);
  }
  else {
    return pow(2, bits_cinco);
  }
}


Pagina * crear_paginas(int niveles_faltantes, int nivel_actual){
  Pagina * puntero_tabla_1;
  puntero_tabla_1 = malloc(sizeof(Pagina));
  int total_entradas = determinar_siguiente_cantidad(nivel_actual);


  if (niveles_faltantes > 1) {
    puntero_tabla_1 -> entradas = malloc(sizeof(Pagina)*total_entradas); 
    for (int i=0; i < total_entradas; i++){
      puntero_tabla_1 -> entradas[i] = crear_paginas(niveles_faltantes -1, nivel_actual + 1);
    }
  }
  else {
    puntero_tabla_1 -> entradas_fisicas = malloc(sizeof(Pagina)*total_entradas); 
    puntero_tabla_1 -> valid_bit = malloc(sizeof(int)*total_entradas);
    for (int i=0; i < total_entradas; i++){
      puntero_tabla_1 -> entradas_fisicas[i] = -1;
      puntero_tabla_1 -> valid_bit[i] = 0; //0 es "virgen", 1 es modificada

    }
  }
 
  return puntero_tabla_1;

}

int buscar_posicion(char * adress_entera, int nivel_actual){
  char * aux;

  if (nivel_actual == 1){
    aux = malloc(sizeof(char)*bits_uno+1);
    strncpy(aux, adress_entera, bits_uno);
    aux[bits_uno] = '\0';
    return (int) bstr_to_dec(aux);
  }
  else if (nivel_actual == 2){
    aux = malloc(sizeof(char)*bits_dos+1);
    strncpy(aux, adress_entera + bits_uno, bits_dos);
    aux[bits_dos] = '\0';
    return (int) bstr_to_dec(aux);
  }
  else if (nivel_actual == 3){

    aux = malloc(sizeof(char)*bits_tres+1);
    strncpy(aux, adress_entera + bits_uno + bits_dos, bits_tres);
    aux[bits_tres] = '\0';
    return (int) bstr_to_dec(aux);
  }
  else if (nivel_actual == 4){

    aux = malloc(sizeof(char)*bits_cuatro+1);
    strncpy(aux, adress_entera + bits_uno + bits_dos + bits_tres, bits_cuatro);
    aux[bits_cuatro] = '\0';
    return (int) bstr_to_dec(aux);
  }
  else {

    aux = malloc(sizeof(char)*bits_cinco+1);
    strncpy(aux, adress_entera + bits_uno + bits_dos + bits_tres + bits_cuatro, bits_cinco);
    aux[bits_cinco] = '\0';
    return (int) bstr_to_dec(aux);
  }

}

int buscar_en_pagina(Pagina * pagina_actual, char * adress_entera, int nivel_actual, int niveles_faltantes){
  if (niveles_faltantes > 1){
    int pos;
    pos = buscar_posicion(adress_entera, nivel_actual);
    return buscar_en_pagina(pagina_actual -> entradas[pos], adress_entera, nivel_actual + 1, niveles_faltantes -1);
  }
  else{
  
    int pos = buscar_posicion(adress_entera, nivel_actual);
    if (pagina_actual -> valid_bit[pos] == 0){ //retornar s
      return pagina_actual -> entradas_fisicas[pos];
    }
    else {
      return -1;
    }

  }
}

MemoriaFisica * inicializar_mf(){
  MemoriaFisica * ptr;
  ptr = malloc(sizeof(MemoriaFisica));
  for (int i = 0; i < 256; i ++){
    ptr -> frames[i] = malloc(sizeof(int)*256);
  }
  LinkedList* list = malloc(sizeof(LinkedList));
  list -> count = 0;
  list -> first = NULL;
  list -> last = NULL;
  ptr -> lista_accesos = list;
  return ptr;
}
int determinar_saliente(MemoriaFisica * ptr){
  if (ptr -> lista_accesos -> count < 256){
    return ptr -> lista_accesos -> count;
  }
  else{
  //Definimos que marco fisico es, ojo que pagina virtual es solo el nombre
    int marco_fisico = ptr -> lista_accesos -> first -> pagina_virtual;
    return marco_fisico;
  }

}

void actualizar_prioridades(MemoriaFisica * ptr_memoria_fisica, int frame_fisico){
  if (ptr_memoria_fisica -> lista_accesos -> count == 0){
    linkedlist_append(ptr_memoria_fisica -> lista_accesos, frame_fisico);
  }
  else {
    // -----------------CASO QUE SE ENCUENTRE ANTERIORMENTE---------------------//      
    Node * curr;
    int esta = 0;
    curr = ptr_memoria_fisica -> lista_accesos -> first;

    for (int i = 0; i < ptr_memoria_fisica -> lista_accesos -> count; i ++){
   
        if (curr -> pagina_virtual == frame_fisico){

            eliminar_nodo(ptr_memoria_fisica -> lista_accesos, i);
            linkedlist_append(ptr_memoria_fisica -> lista_accesos, frame_fisico);
            esta = 1;
            break;
        }
        curr = curr -> next; 
  
    }
    // --------------------FIN CASO ENCONTRADO ANTERIORMENTE -------------------//

    if (!esta){
      if (ptr_memoria_fisica -> lista_accesos -> count < 256){
        linkedlist_append(ptr_memoria_fisica -> lista_accesos, frame_fisico);
      }
      else {
        eliminar_nodo(ptr_memoria_fisica -> lista_accesos, 0);
        linkedlist_append(ptr_memoria_fisica -> lista_accesos, frame_fisico);
      }
    }

  }
}
int cargar_en_memoria_fisica(MemoriaFisica * ptr_memoria_fisica, char * adress, char * offset, int frame_a_copiar){
  FILE *fp1;
  fp1 = fopen("disco.bin", "rb");
  // Determinamos el adress:
  int numero_pagina = bstr_to_dec(adress);
  fseek(fp1, numero_pagina*pow(2,8), SEEK_SET);
  unsigned char * valor = malloc(sizeof(unsigned int)* 256);
  fread(valor, sizeof(unsigned int), 256, fp1);
  int contenido;
  int offset_entero = bstr_to_dec(offset);

  for (int k=0; k < 256; k++){
    int a = (unsigned int) valor[k];
    ptr_memoria_fisica -> frames[frame_a_copiar][k] = valor[k];
    if (k == offset_entero) {
      contenido = valor[k];
    } 
  }
  fclose(fp1);
  actualizar_prioridades(ptr_memoria_fisica, frame_a_copiar);


  return contenido;
}

void actualizar_tlb(TLB * puntero_tlb, int v_adress, int marco_fisico){
  int nueva_pos = determinar_saliente_TLB(puntero_tlb);
  puntero_tlb -> d_virtual[nueva_pos] = v_adress;
  puntero_tlb -> d_fisica[nueva_pos] = marco_fisico;
}

void actualizar_tabla_paginas(Pagina * pagina_actual, char * adress_entera, int nivel_actual, int niveles_faltantes, int n_frame){
  if (niveles_faltantes > 1){
    long pos;
    pos = buscar_posicion(adress_entera, nivel_actual);
    return actualizar_tabla_paginas(pagina_actual -> entradas[pos], adress_entera, nivel_actual + 1, niveles_faltantes -1, n_frame);
  }
  else{
    long pos;
    pos = buscar_posicion(adress_entera, nivel_actual);
    pagina_actual -> entradas_fisicas[pos] = n_frame;
    pagina_actual -> valid_bit[pos] = 0;
  }
}

void marcar_como_invalida(Pagina * pagina_actual, int curr_level, int levels_faltantes, int numero_frame){
  if (levels_faltantes > 1){
    int n_entradas = determinar_siguiente_cantidad(curr_level);
    for (int i= 0; i < n_entradas; i ++){
      marcar_como_invalida(pagina_actual -> entradas[i], curr_level + 1, levels_faltantes - 1, numero_frame);
    }
  }
  else {
    
    int n_entradas = determinar_siguiente_cantidad(curr_level);
    for (int i= 0; i < n_entradas; i ++){
      if (pagina_actual -> entradas_fisicas[i] == numero_frame) {
        pagina_actual -> valid_bit[i] = 1; //asignamos en el caso que tenga el mismo frame
      }
    }

  }
}

void actualizar_prioridades_tlb(TLB * ptr, int pagina_encontrada){
  if (ptr -> lista_usadas -> count == 0){
    linkedlist_append(ptr -> lista_usadas, pagina_encontrada);
  }
  else {
    //Revisamos que no este
    Node * curr;
    int esta = 0;
    curr = ptr -> lista_usadas -> first;
    for (int i = 0; i < ptr -> lista_usadas -> count; i ++){
        if (curr -> pagina_virtual == pagina_encontrada){
            eliminar_nodo(ptr -> lista_usadas, i);
            linkedlist_append(ptr -> lista_usadas, pagina_encontrada);
            esta = 1;
            break;
        }
        curr = curr -> next; 
    }
    if (!esta){
      if (ptr -> lista_usadas -> count < 64){
        linkedlist_append(ptr -> lista_usadas, pagina_encontrada);
      }
      else {
        eliminar_nodo(ptr -> lista_usadas, 0);
        linkedlist_append(ptr -> lista_usadas, pagina_encontrada);
      }
    }

  }
}

Node* node_init(int value)
{
  // Creo el nodo
  Node* node = malloc(sizeof(Node));

  // Le agrego el valor y le pongo next = NULL
  node -> pagina_virtual = value;
  node -> next = NULL;

  // Retorno el nodo
  return node;
}

void eliminar_nodo(LinkedList * list, int position){
  if (position == 0)
  {
    Node* first = list -> first;
    list -> first = first -> next;
    free(first);
  }
  else
  {
    Node* last = list -> first;
    for (int i = 1; i < position; i++)
    {
      last = last -> next;
    }
    Node* actual = last -> next;
    last -> next = actual -> next;
    if (position == list -> count - 1)
    {
      list -> last = last;
    }
  }

  list -> count--;
}
void linkedlist_append(LinkedList* list, int pagina_virtual)
{
  // Creo el nodo a agregar
  Node* node = node_init(pagina_virtual);

  // Si la lista esta vacia
  if (list -> count == 0)
  {
    // Hago que sea el primer nodo
    list -> first = node;
  }
  // Sino,
  else
  {
    // Hago que sea el siguiente del ultimo
    list -> last -> next = node;
  }

  // Ahora este nodo es el ultimo
  list -> last = node;

  // Agrego 1 a la cuenta
  list -> count++;
}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the null-terminator
    
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
