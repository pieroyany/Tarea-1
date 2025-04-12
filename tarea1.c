#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Servivio Técnico");
  puts("========================================");

  puts("1) Registrar cliente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar clientes por prioridad");
  puts("6) Salir");
}

void registrar_cliente(List *clientes) {
  char nombre_cliente[50];
  char dispositivo;
  char fecha[10];

  printf("Registrar nuevo cliente\n");
  printf("Ingrese el nombre del cliente:\n");
  scanf("%s", nombre_cliente);
  printf("Ingrese el tipo de dispositivo\n1: smartphone\n2: laptop\n3: audífonos\n");
  scanf(" %c", &dispositivo);
  printf("Ingrese la fecha de ingreso (DD/MM/AAAA):\n");
  scanf("%s", fecha);
  
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
      // Lógica para asignar prioridad
      break;
    case '3':
      mostrar_lista_clientes(clientes);
      break;
    case '4':
      // Lógica para atender al siguiente clientes
      break;
    case '5':
      // Lógica para mostrar clientes por prioridad
      break;
    case '6':
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
