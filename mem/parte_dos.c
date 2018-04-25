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
  }
  return puntero_tlb;

}

void determinar_offset(char * binario, char * offset){
  for (int i= 0; i < 8; i ++){
    offset[i] = binario[28 - i];
  }
}




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
int buscar_en_tlb(TLB * puntero_tlb, int n_direccion){
    for (int i=0; i < 64; i ++){
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
    puntero_tabla_1 -> dirty_bit = malloc(sizeof(int)*total_entradas);
    for (int i=0; i < total_entradas; i++){
      puntero_tabla_1 -> entradas_fisicas[i] = -1;
      puntero_tabla_1 -> dirty_bit[i] = 0; //0 es "virgen", 1 es modificada

    }
  }
 
  return puntero_tabla_1;

}

int buscar_posicion(char * adress_entera, int nivel_actual){
  char * aux;
  if (nivel_actual == 1){
    aux = malloc(sizeof(char)*bits_uno);
    strncpy(aux, adress_entera + 20 - bits_uno, bits_uno);
    return (int) bstr_to_dec(aux);
  }
  else if (nivel_actual == 2){
    aux = malloc(sizeof(char)*bits_dos);
    strncpy(aux, adress_entera + 20 - bits_uno -bits_dos, bits_dos);
    return (int) bstr_to_dec(aux);
  }
  else if (nivel_actual == 3){

    aux = malloc(sizeof(char)*bits_tres);
    strncpy(aux, adress_entera + 20 - bits_uno -bits_dos -bits_tres, bits_tres);
    return (int) bstr_to_dec(aux);
  }
  else if (nivel_actual == 4){

    aux = malloc(sizeof(char)*bits_cuatro);
    strncpy(aux, adress_entera + 20 - bits_uno -bits_dos -bits_tres - bits_cuatro, bits_cuatro);
    return (int) bstr_to_dec(aux);
  }
  else {

    aux = malloc(sizeof(char)*bits_cinco);
    strncpy(aux, adress_entera , bits_cinco);
    return (int) bstr_to_dec(aux);
  }

}

long buscar_en_pagina(Pagina * pagina_actual, char * adress_entera, int nivel_actual, int niveles_faltantes){
  if (niveles_faltantes > 1){
    long pos;
    pos = buscar_posicion(adress_entera, nivel_actual);
    return buscar_en_pagina(pagina_actual -> entradas[pos], adress_entera, nivel_actual + 1, niveles_faltantes -1);
  }
  else{
    long pos;
    pos = buscar_posicion(adress_entera, nivel_actual);
    if (pagina_actual -> dirty_bit[pos] == 0){ //retornar solo no esta sucio
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
    ptr -> prioridades[i] = 0;
  }
  return ptr;
}
 int determinar_saliente(MemoriaFisica * ptr){
  int minima;
  for (int k = 0; k < 256; k ++){
    if (ptr -> prioridades[k] == 0){
      return k;
    }
    
  }
  printf("DANGEEER\n");
 } //me retorna el con prioridad 0

void actualizar_prioridades(MemoriaFisica * ptr_memoria_fisica, int recien){
  for (int i; i < 255; i ++){
    if (ptr_memoria_fisica -> prioridades[i] > 0) {
      if (i != recien) {
        ptr_memoria_fisica -> prioridades[i] --;
      }
    }
  }
  ptr_memoria_fisica -> prioridades[recien] = 255;
}
int cargar_en_memoria_fisica(MemoriaFisica * ptr_memoria_fisica, char * adress, char * offset){
  FILE *fp1;
  fp1 = fopen("disco", "rb");
  // Determinamos el adress:
  int numero_pagina = bstr_to_dec(adress);
  fseek(fp1, numero_pagina*pow(2,8), SEEK_SET);
  unsigned char * valor = malloc(sizeof(unsigned int)* 256);
  fread(valor, sizeof(unsigned int), 256, fp1);
  int contenido;
  int offset_entero = bstr_to_dec(offset);
  int saliente = determinar_saliente(ptr_memoria_fisica);

  for (int k=0; k < 256; k++){
    int a = (unsigned int) valor[k];
    ptr_memoria_fisica -> frames[saliente][k] = valor[k];
    if (k == offset_entero) {
      contenido = valor[k];
    } 
  }
  fclose(fp1);
  actualizar_prioridades(ptr_memoria_fisica, saliente);
  return contenido;
}

void actualizar_tlb(TLB * puntero_tlb, int v_adress, int marco_fisico){
  // Esto es provisorio, por implementar: LRU
  puntero_tlb -> d_virtual[puntero_tlb -> contador] = v_adress;
  puntero_tlb -> d_fisica[puntero_tlb -> contador] = marco_fisico;

  puntero_tlb -> contador ++;
  if (puntero_tlb -> contador > 63){
    puntero_tlb -> contador = 0;
  }
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
  }
}

void marcar_como_sucia(Pagina * pagina_actual, int curr_level, int levels_faltantes, int numero_frame){
  if (levels_faltantes > 1){
    int n_entradas = determinar_siguiente_cantidad(curr_level);
    for (int i= 0; i < n_entradas; i ++){
      marcar_como_sucia(pagina_actual -> entradas[i], curr_level + 1, levels_faltantes - 1, numero_frame);
    }
  }
  else {
    
    int n_entradas = determinar_siguiente_cantidad(curr_level);
    for (int i= 0; i < n_entradas; i ++){
      if (pagina_actual -> entradas_fisicas[i] == numero_frame) {
        pagina_actual -> dirty_bit[i] = 1; //asignamos en el caso que tenga el mismo frame
      }
    }

  }
}
