#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------------------
typedef struct {
  char dia[3];
  char mes[3];
  char anio[5];
} fecha;

typedef struct {
  char nombre[50];
  char dispositivo[20];
  fecha fecha;
  char prioridad;
} Cliente;
//------------------------------------------------------------------------------------------------
// funcion para usar sortedinsert
int lower_than(void *data1, void *data2) {
  Cliente *a = (Cliente *)data1;
  Cliente *b = (Cliente *)data2;

  // Comparar prioridad
  if (a->prioridad != b->prioridad)
      return a->prioridad > b->prioridad;

  // misma prioridad, comparar fecha
  int anioA = atoi(a->fecha.anio);
  int anioB = atoi(b->fecha.anio);
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
  puts("     Sistema de Servicio Tecnico");
  puts("========================================");

  puts("1) Registrar cliente");
  puts("2) Mostrar lista de espera");
  puts("3) Atender al siguiente paciente");
  puts("4) Salir");
}

void registrar_cliente(List *clientes) {
  //reservar memoria para el nuevo cliente
  Cliente *nuevo_cliente = (Cliente *)malloc(sizeof(Cliente));
  if (nuevo_cliente == NULL) {
    printf("Error al asignar memoria\n");
    return;
  }
  strcpy(nuevo_cliente->fecha.anio, "2025"); // año fijo para simplificar
  //rellenar los datos del cliente
  printf("Registrar nuevo cliente\n");
  printf("Ingrese el nombre del cliente:\n");
  scanf("%s", &nuevo_cliente->nombre);

  char temp; // variable temporal para asignar el dispositivo comodamente
  printf("Ingrese el tipo de dispositivo\n1: smartphone\n2: laptop\n3: audifonos\n4: otro\n");
  scanf(" %c", &temp);
  if (temp == '1') {
    strcpy(nuevo_cliente->dispositivo, "smartphone");
  } else if (temp == '2') {
    strcpy(nuevo_cliente->dispositivo, "laptop");
  } else if (temp == '3') {
    strcpy(nuevo_cliente->dispositivo, "audifonos");
  } else if (temp == '4') {
    strcpy(nuevo_cliente->dispositivo, "otro");
  } else {
    printf("Dispositivo no valido\n");
    free(nuevo_cliente);
    return;
  }
  // input individual para dia y mes para mayor comodidad del usuario
  printf("Ingrese el dia de ingreso (01 - 31):\n");
  scanf("%s", &nuevo_cliente->fecha.dia);
  if (atoi(nuevo_cliente->fecha.dia) < 1 || atoi(nuevo_cliente->fecha.dia) > 31) {
    printf("Dia no valido\n");
    free(nuevo_cliente);
    return;
  }
  printf("Ingrese el mes de ingreso (01 - 12):\n");
  scanf("%s", &nuevo_cliente->fecha.mes);
  if (atoi(nuevo_cliente->fecha.mes) < 1 || atoi(nuevo_cliente->fecha.mes) > 12) {
    printf("Mes no valido\n");
    free(nuevo_cliente);
    return;
  }
  
  printf("Ingrese la prioridad de atención del cliente (1-3):\n");
  scanf(" %c", &nuevo_cliente->prioridad);
  if (nuevo_cliente->prioridad != '1' && nuevo_cliente->prioridad != '2' && nuevo_cliente->prioridad != '3') {
    printf("Prioridad no valida\n");
    free(nuevo_cliente);
    return;
  }
  //una vez rellenados los datos, se inserta el cliente en la lista, ordenado primero por prioridad y despues por fecha
  list_sortedInsert(clientes, nuevo_cliente, lower_than);
}

void mostrar_lista_clientes(List *clientes) {
  // Comprobar si la lista está vacía
  if (list_size(clientes) == 0) {
    puts("No hay clientes en espera.");
    return;
  }
  // Mostrar clientes en la cola de espera
  printf("Clientes en espera: \n");
  Cliente *cliente = (Cliente *)list_first(clientes);
  int i = 1;
  while (cliente != NULL) {
    printf("Cliente %d: %s, Dispositivo: %s, Fecha: %s/%s/%s, Prioridad: %c\n",
           i, cliente->nombre, cliente->dispositivo,
           cliente->fecha.dia, cliente->fecha.mes, cliente->fecha.anio,
           cliente->prioridad);
    cliente = (Cliente *)list_next(clientes); // avanzamos al siguiente
    i++;
  }
}

int main() {
  char opcion;
  List *clientes = list_create(); // puedes usar una lista para gestionar los clientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      registrar_cliente(clientes);
      
      break;

    case '2':
      mostrar_lista_clientes(clientes);
      
      break;

    case '3':
      if (list_size(clientes) > 0) {
        Cliente *cliente_atendido = (Cliente *)list_popFront(clientes);
        printf("Atendiendo a: %s, Dispositivo: %c, Fecha: %s/%s/%s, Prioridad: %c\n", cliente_atendido->nombre, cliente_atendido->dispositivo, cliente_atendido->fecha.dia, cliente_atendido->fecha.mes, cliente_atendido->fecha.anio, cliente_atendido->prioridad);
        free(cliente_atendido); // liberar memoria del cliente atendido

      } else {
        puts("No hay clientes en espera.");
      }
      break;
    case '4':
      puts("Saliendo del sistema de servicio tecnico...");
      break;
    default:
      puts("Opción no valida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '4');

  list_clean(clientes);
  free(clientes); // liberar memoria de la lista
  return 0;
}
