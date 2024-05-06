#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 100

char **leer_linea_csv(FILE *archivo, char separador)
{
  static char linea[MAX_LINE_LENGTH];
  static char *campos[MAX_FIELDS];
  char *ptr, *start;
  int idx = 0;

  if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
    return NULL; // No hay más líneas para leer
  }

  ptr = start = linea;
  while (*ptr)
  {
    if (idx >= MAX_FIELDS - 1)
      break;

    if (*ptr == '\"') { // Inicio de un campo entrecomillado
      start = ++ptr;    // Saltar la comilla inicial
      while (*ptr && !(*ptr == '\"' && *(ptr + 1) == separador))
        ptr++;
    } else { // Campo sin comillas
      start = ptr;
      while (*ptr && *ptr != separador)
        ptr++;
    }

    if (*ptr) {
      *ptr = '\0'; // Reemplazar comilla final o separador por terminación
      ptr++;
      if (*ptr == separador)
        ptr++;
    }

    // Quitar comilla final si existe
    if (*(ptr - 2) == '\"') {
      *(ptr - 2) = '\0';
    }

    campos[idx++] = start;
  }

  campos[idx] = NULL; // Marcar el final del array
  return campos;
}

typedef struct {
  char id[100]; //Id de la pelicula(clave)
  char title[100];//Titulo de la pelicula
  List *genres; //Lista de generos de la pelicula
  char director[300]; //Director o directores de la pelicula
  float rating; //Rating Imdb de la pelicula
  int year; //Año en el cual salio la pelicula
} Film;

int is_equal_str(void *key1, void *key2)
{
  return strcmp((char *)key1, (char *)key2) == 0;
}

int is_equal_int(void *key1, void *key2)
{
  return *(int *)key1 == *(int *)key2;
}

// Función para limpiar la pantalla
void limpiarPantalla(){ system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

void convertirMinuscula(char *cadena)
{
  for(int i = 0; cadena[i]; i++)
  {
    cadena[i] = tolower(cadena[i]);
  }
}
// Menú principal
void mostrarMenuPrincipal()
{
  limpiarPantalla();
  puts("========================================");
  puts("     Base de Datos de Películas");
  puts("========================================");

  puts("1) Cargar Películas");
  puts("2) Buscar por id");
  puts("3) Buscar por director");
  puts("4) Buscar por género");
  puts("5) Buscar por década");
  puts("6) Buscar por rango de calificaciones");
  puts("7) Buscar por década y género");
  puts("8) Salir");
}

void quitarComillas(char *cadena) //Funcion que quita las comillas iniciales y finales de una cadena.
{
  int largo = strlen(cadena);
  if(cadena[0] == '"')
  {
    memmove(cadena, cadena+1, largo);
    largo--;
  } 
  if(largo >0 && cadena[largo -1] == '"'){
    cadena[largo-1] = '\0';
  }
}

char *quitarEspacios(char *cadena)//Funcion para quitar los espacios en blanco de una cadena, y retornar la cadena.
{
  while(isspace((unsigned char)*cadena)) cadena++;
  return cadena;
}

void quitarUltimaLinea(char *cadena) //Se utiliza la funcion que elimina el caracter de salto de linea al final de la cadena, si este existe
{
  //Eliminacion del caracter de salto de linea, si este existe.
  int largo = strlen(cadena); 
  //Si el largo de la cadena es mayor a 0 y el ultimo caracter es un salto de linea.
  if(largo > 0 && cadena[largo -1] == '\n')
  {
    cadena[largo-1] = '\0'; //Se reemplaza el salto de linea por el caracter nulo.
  }
}

void mostrarGenero(List *generos) //Funcion para mostrar los generos por pelicula.
{
  List *aux = list_first(generos);
  printf("Generos :");
  while(aux != NULL)
  {
    printf(" %s", (char*)aux);
    aux = list_next(generos);
  }
}

void cargarPeliculas(Map *pelisMap)
{
  FILE *archivo = fopen("data/Top1500.csv", "r");
  //FILE *archivo = fopen("data/IMDbTop250.csv", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  char **campos;
  campos = leer_linea_csv(archivo, ','); //Leer encabezados
  //Lee cada linea del archivo CSV hasta llegar al final.
  while ((campos = leer_linea_csv(archivo, ',')) != NULL)
  {
    //Crear una nueva estructura de tipo Film y almacenar los datos de cada pelicula.
    Film *peli = (Film *)malloc(sizeof(Film)); 
    
    strcpy(peli->id, campos[1]);
    strcpy(peli->title, campos[5]);
    strcpy(peli->director, campos[14]);
    peli->year = atoi(campos[10]);
    peli->rating = strtof(campos[8], NULL);
    peli->genres = list_create();

    quitarComillas(campos[11]); //Quitar comillas iniciales y finales del campo genero en el archivo CSV
    //token generos y insertar pelisGenero
    char *tokenGeneros = strtok(campos[11], ",");
    while(tokenGeneros != NULL)
    {
      char *tokenLimpio = quitarEspacios(tokenGeneros);
      //quitarComillas(tokenLimpio);
      list_pushBack(peli->genres, strdup(tokenLimpio));
      tokenGeneros = strtok(NULL, ",");
    }
    
    //insertar pelisMap
    map_insert(pelisMap, peli->id, peli);
  }
  fclose(archivo);
  //Se muestran los respectivos datos de las peliculas.
  MapPair *pair = map_first(pelisMap);
  printf("\n");
  int contador = 1; //Contador para saber el numero de la peliculas(1-1500).
  while (pair != NULL) {
    Film *peli = pair->value;
    printf("-----Pelicula numero: %d -------\n\n", contador);
    printf("ID: %s, Título: %s, Año: %d, ", peli->id, peli->title, peli->year);
    //printf("\n");
    printf("Director/es: %s", peli->director);
    //printf("\n");
    mostrarGenero(peli->genres);
    printf("\n\n");
    pair = map_next(pelisMap); //Pasar a la siguiente pelicula.
    contador++; //Se aumenta el contador.
  }
}

void buscarPorId(Map *pelisMap)
{
  char id[10];
  printf("Ingrese el id de la película: ");
  scanf("%s", id);

  MapPair *pair = map_search(pelisMap, id);
  if (pair != NULL)
  {
    //Se muestran los datos de la pelicula.
    Film *peli = pair->value;
    printf("\n");
    printf("Título: %s, Año: %d\n", peli->title, peli->year);
    printf("Director/es: %s", peli->director);
    mostrarGenero(peli->genres);
    printf("\n\n");
  } else
    printf("La película con id %s no existe\n", id);
}

void buscarPorDirector(Map *pelisDirector) // Muestra todas las películas que pertenecen al director ingresado.
{
  char director[200]; //Almacena el nombre del director ingresado por el usuario
  printf("Ingrese el nombre del director: "); //Se solicita el nombre del director.
  //Se lee el nombre del director ingresado por el usuario.
  fgets(director, 200, stdin);

  //Se utiliza la funcion que elimina el caracter de salto de linea, si este existe.
  quitarUltimaLinea(director);
  //Se valida la entrada.
  while(strlen(director) == 0) //Si el largo de la cadena es 0, se vuelve a pedir el nombre del director.
  {
    //printf("Ingrese un nombre valido");
    fgets(director, sizeof(director), stdin);
  }

  //Creacion de variable con tal de almacenar el director como directamente fue ingresado.  
  char directorEntrada[200]; 
  strcpy(directorEntrada, director);
  //Se convierte el director ingresado en minusculas
  convertirMinuscula(director); //Se trabaja con el director ingresado pero en minusculas.
  
  //Variables locales, contador para el numero de peliculas encontradas, y otro para indicar si se encontraron.
  int contadorPelis = 1;
  int encontrado = 0;

  //Se recorre el mapa de peliculas.
  MapPair *pair = map_first(pelisDirector);
  printf("\n");
  while(pair != NULL)  
  {
    //Obtencion de la pelicula actual y su director.
    Film *peli = pair->value;
    char directorBuscado[200];
    strcpy(directorBuscado, peli->director);
    //Conversion a minusculas.
    convertirMinuscula(directorBuscado);
    //Se compara el director ingresado por el usuario con el director de la pelicula.
    if(strcmp(directorBuscado, director) == 0)
    {
      //Si se encuentra, muestra la informacion de la pelicula.
      printf("-----Pelicula numero: %d -------\n", contadorPelis);
      printf("ID: %s, Título: %s, Año: %d\n", peli->id, peli->title, peli->year);
      mostrarGenero(peli->genres);
      printf("\n\n");
      //Se actualiza el indicador ya que se encontro una pelicula, y se aumenta el contador de peliculas.
      encontrado = 1;
      contadorPelis++;
    }
    //Se avanza al siguiente par en el mapa.
    pair = map_next(pelisDirector);
  }
  //Si no se encontro ninguna pelicula, se muestra un mensaje.
  if (encontrado == 0)
  { 
    printf("No se encontraron peliculas dirigidas por: %s\n", directorEntrada);
  }
  else
  {
    //Si se encontro al menos una pelicula, se muestra el numero de peliculas encontradas.
    printf("Cantidad total de peliculas del director ingresado son: %d\n", contadorPelis -1);
  }
}

/*
Generos posibles y contador(colab)
Genre  Count
0       Drama    981
1      Comedy    568
2     Romance    428
3    Thriller    359
4       Crime    341
5   Adventure    228
6      Action    201
7     Mystery    164
8   Biography    131
9     Fantasy    107
10     Family    106
11        War     94
12    Musical     85
13     Sci-Fi     84
14    History     80
15    Western     72
16  Film-Noir     60
17      Sport     55
18      Music     51
19  Animation     43
20     Horror     23
*/ //Comentario cantidad total de generos
void buscarPorGenero(Map *pelisGenero) // Muestra todas las películas que pertenecen al género ingresado.
{
  char genero[200]; //Variable para almacenar el genero ingresado por el usuario.
  printf("Ingrese el genero deseado a buscar: "); //Se solicita el genero.
  //Se consume cualquier entrada pendiente en el buffer de entrada.
  int caracter;
  while((caracter = getchar()) != '\n' && caracter != EOF) {}
  //Se lee el genero ingresado por el usuario.
  fgets(genero, 200, stdin);
  //Eliminacion del caracter de salto de linea, si este existe.
  quitarUltimaLinea(genero);

  char genEntrada[200];//Se guarda el genero de entrada para printf
  strcpy(genEntrada, genero);
  convertirMinuscula(genero);//Se convierte a minusculas el genero a trabajar.
  
  //Variables locales, contador para el numero de peliculas encontradas, y otro para indicar si se encontraron
  int contadorPelis = 1;
  int encontrado = 0;
  
  MapPair *pair = map_first(pelisGenero);
  while(pair != NULL)  
  {
    Film *peli = pair->value;
    void *aux = list_first(peli->genres);
    while(aux != NULL)
    {
      //Conversion del genero actual de la pelicula a minuscula para comparar.
      char auxGenActual[200];
      strcpy(auxGenActual, (char*)aux);
      convertirMinuscula(auxGenActual);

      if(strcmp(auxGenActual, genero) == 0)
      {
        //Si se encuentra, muestra informacion de la pelicula y se actualiza los contadores.
        printf("-----Pelicula numero: %d -------\n", contadorPelis);
        printf("ID: %s, Título: %s, Año: %d\n\n", peli->id, peli->title, peli->year);
        contadorPelis++;
        encontrado = 1;
        break;
      }
      aux = list_next(peli->genres);
    }
    //Avanzar al siguiente par en el mapa.
    pair = map_next(pelisGenero);
  }

  //Se muestran mensajes de salida en caso de que no se encuentren peliculas del genero, o si se encuentra que se muestren la cantidad total.
  if(encontrado == 0){
    printf("No se encontraron peliculas del genero ingresado: %s\n", genEntrada);
  }
  else{
    printf("Cantidad total de peliculas del genero ingresado son: %d\n", contadorPelis-1);
  }
}
  
void buscarPorDecada(Map *pelisDecada)
{
  //Se crea una variable para almacenar la decada que se le pedira al usuario.
  char decada[5]; 
  printf("Ingrese la decada deseada a buscar (ejemplo: 1960, 2000): ");

  //Se lee la decada ingresada por el usuario.
  fgets(decada, 5, stdin);
  //Se elimina el caracter de nueva linea del final de la cadena, si este existe
  quitarUltimaLinea(decada);
  //Se verifica si la cadena esta vacia, y se solicita una nueva entra si es asi.
  while(strlen(decada) == 0)
  {
    //printf("Ingrese un nombre valido");
    fgets(decada, 5, stdin);
  }

  //Convertir la cadena de decada a un numero entero.
  int numDecadaPedida = atoi(decada);
   //Variables locales, contador para el numero de peliculas encontradas, y otro para indicar si se encontraron
  int contadorPelis = 1;
  int encontrado = 0;
  
  MapPair *pair = map_first(pelisDecada);
  while(pair != NULL)
  {
    Film *peli = pair->value;
    //Calcular la decada de estreno de la pelicula actual.
    int numDecadaEstreno = (peli->year / 10) * 10;
    //Si la decada de estreno de la pelicula actual es igual a la decada ingresada por el usuario.
    if(numDecadaEstreno == numDecadaPedida)
    {
      //Si se encuentra, muestra informacion de la pelicula de la decada y se actualiza los contadores.
      printf("-----Pelicula numero: %d -------\n", contadorPelis);
      printf("ID: %s, Título: %s, Año: %d\n\n", peli->id, peli->title, peli->year);
      contadorPelis++;
      encontrado = 1;
    }
    //Avanzar al siguiente par.
    pair = map_next(pelisDecada);
  }
  //Se muestran mensajes de salida en caso de que no se encuentren peliculas de la decada, o si se encuentran que se muestren la cantidad total.
  if(encontrado == 0){
    printf("No se encontraron peliculas de la siguiente decada ingresada: %s\n", decada);
  }
  else{
    printf("Cantidad total de peliculas de la decada ingresada: %d\n", contadorPelis -1);
  }
}

void buscarDecadaGenero(Map *pelisDecadaGen)
{
  //Declaracion de variables para almacenar la decada y el genero que ingrese el usuario.
  char decada[5];
  char genero[100];
  //Solicitar la decada a buscar
  printf("Ingrese la decada deseada a buscar (ejemplo: 1960, 2010): ");
  //Se lee la decada ingresada por el usuario.
  fgets(decada, 5, stdin);
  //Funcion para quitar el caracter de nueva linea del final de la cadena, si este existe.
  quitarUltimaLinea(decada);
  // Verificar si la cadena está vacía y solicitar una nueva entrada si es así
  while(strlen(decada) == 0)
  {
    //printf("Ingrese un nombre valido");
    fgets(decada, 5, stdin);
  }
  //Conversion la cadena decada a un numero entero
  int numDecadaPedida = atoi(decada);
  //Solicitar el genero a buscar
  printf("Ingrese el genero deseado a buscar: ");
  
  //Se consume cualquier entrada pendiente en el buffer de entrada.
  int caracter;
  while((caracter = getchar()) != '\n' && caracter != EOF) {}
  //Se lee el genero ingresado por el usuario.
  fgets(genero, 200, stdin);
  //Funcion para quitar el caracter de salto de linea.
  quitarUltimaLinea(genero);

  char genEntrada[200]; //Para guardar la cadena de entrada, posteriormente para printf
  strcpy(genEntrada, genero); //Se guarda la cadena de entrada
  convertirMinuscula(genero);//Se convierte a minuscula la cadena a trabajar
  
  int contadorPelis = 1; //Contador de peliculas
  int encontrado = 0; //Contador para saber si se encontraron peliculas
  
  MapPair *pair = map_first(pelisDecadaGen);
  while(pair != NULL)
  {
    Film *peli = pair->value;
    //Calcular la decada de estreno de la peli actual.
    int numDecadaEstreno = (peli->year / 10) * 10;

    if(numDecadaEstreno == numDecadaPedida)
    {
      //Si coinciden, pasar a trabajar con la lista de generos.
      List *aux = list_first(peli->genres);
      while(aux != NULL)
      {
        char auxGenActual[200];
        strcpy(auxGenActual, (char*)aux);
        convertirMinuscula(auxGenActual);
        if(strcmp(auxGenActual, genero) == 0)
        {
          //Si coincide el genero actual con el pedido, finalmente se muestran los datos de la pelicula.
          printf("-----Pelicula numero: %d -------\n", contadorPelis);
          printf("ID: %s, Título: %s, Año: %d\n\n", peli->id, peli->title, peli->year);
          contadorPelis++;
          encontrado = 1;
          break;
        }
        aux = list_next(peli->genres); //Avanar al siguiente genero de la lista de generos de la pelicula actual.
      }  
    }
    pair = map_next(pelisDecadaGen); //Avanzar al siguiente par.
  }
   // Mostrar mensajes de salida si no se encontraron películas, o si se encontraron mostrar la cantidad total.
  if(encontrado == 0){
    printf("No se encontraron peliculas de la decada %s, del genero %s\n", decada, genEntrada);
  }
  else{
    printf("Cantidad total de peliculas de la decada ingresada respecto al genero pedido: %d\n", contadorPelis -1);
  }
  
}
int main()
{
  char opcion;
  Map *pelisMap = map_create(is_equal_str);
  //Map *pelisDirector = map_create(is_equal_str);
  //Map *pelisGenero = map_create(is_equal_str);
  //Map *pelis = map_create(is_equal_str);
  // Recuerde usar un mapa por criterio de búsqueda

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargarPeliculas(pelisMap);
      break;
    case '2':
      buscarPorId(pelisMap);
      break;
    case '3':
      //cargarMapaDirectores(pelisMap, pelisDirector);
      buscarPorDirector(pelisMap);
      break;
    case '4':
      //cargarMapaGeneros(pelisMap, pelisGenero);
      buscarPorGenero(pelisMap);
      break;
    case '5':
      buscarPorDecada(pelisMap);
      break;
    case '6':
      //buscarPorRangoCalificaiones(pelisMap);
      break;
    case '7':
      buscarDecadaGenero(pelisMap);
      break;
    default:
      puts("Hasta luego!\n");  
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}