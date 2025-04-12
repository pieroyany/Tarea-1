#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------------------
typedef struct {
  char nombre[50];
  char dispositivo;
  fecha fecha;
  char prioridad;
} Cliente;

typedef struct {
  char dia[2];
  char mes[2];
  char año[4];
} fecha;
//------------------------------------------------------------------------------------------------
// funcion para usar sortedinsert
int lower_than(char *data1, char *data2) {
  Cliente *a = (Cliente *)data1;
  Cliente *b = (Cliente *)data2;

  // Comparar prioridad
  if (a->prioridad != b->prioridad)
      return a->prioridad > b->prioridad;

  // misma prioridad, comparar fecha
  int anioA = atoi(a->fecha.año);
  int anioB = atoi(b->fecha.año);
  if (anioA != anioB) return anioA < anioB;

  int mesA = atoi(a->fecha.mes);
  int mesB = atoi(b->fecha.mes);
  if (mesA != mesB) return mesA < mesB;

  int diaA = atoi(a->fecha.dia);
  int diaB = atoi(b->fecha.dia);
  return diaA < diaB;
}
//------------------------------------------------------------------------------------------------
// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Servivio Técnico");
  puts("========================================");

  puts("1) Registrar cliente");
  puts("2) Mostrar lista de espera");
  puts("3) Atender al siguiente paciente");
  puts("4) Mostrar clientes por prioridad");
  puts("5) Salir");
}

void registrar_cliente(List *clientes) {
  Cliente *nuevo_cliente = (Cliente *)malloc(sizeof(Cliente));
  if (nuevo_cliente == NULL) {
    printf("Error al asignar memoria\n");
    return;
  }

  printf("Registrar nuevo cliente\n");
  printf("Ingrese el nombre del cliente:\n");
  scanf("%s", &nuevo_cliente->nombre);

  printf("Ingrese el tipo de dispositivo\n1: smartphone\n2: laptop\n3: audífonos\n");
  scanf(" %c", &nuevo_cliente->dispositivo);

  printf("Ingrese la fecha de ingreso (DD/MM/AAAA):\n");
  scanf("%s/%s/%s", &nuevo_cliente->fecha.dia, &nuevo_cliente->fecha.mes, &nuevo_cliente->fecha.año);
  
  printf("Ingrese la prioridad de atención del cliente (1-3):\n");
  scanf(" %c", &nuevo_cliente->prioridad);

  list_sortedInsert(clientes, nuevo_cliente, lower_than);
}

void mostrar_lista_cliente(List *clientes) {
  // Mostrar clientes en la cola de espera
  printf("Clientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los clientes
}

int main() {
  char opcion;
  List *clientes = list_create(); // puedes usar una lista para gestionar los clientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_cliente(clientes);
      break;
    case '2':
      mostrar_lista_clientes(clientes);
      break;
    case '3':
      // Lógica para atender al siguiente clientes
      break;
    case '4':
      // Lógica para mostrar clientes por prioridad
      break;
    case '5':
      puts("Saliendo del sistema de servicio técnico...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(clientes);

  return 0;
}
