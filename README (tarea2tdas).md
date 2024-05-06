# Sistema Buscador de Peliculas.

## Descripción

Este sistema permite a los usuarios acceder a una base de datos con peliculas. Los usuarios pueden cargar las peliculas, buscar una pelicula en especifica ingresando su ID, buscar en la base de datos un director y que muestre todas las peliculas dirigidas por el, al ingresar un genero que muestre todas las peliculas que pertenecen a ese genero, mostrar todas las peliculas pertenecientes a una decada ingresada por el usuario y finalmente mostrar las peliculas de una decada y genero en especifico.

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/YosoyelDario/Tarea-2-Dario-Fuentes.git`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. En la pestaña "Configurate Repl", sección "Configure the Compile Command", escriba o pegue de preferencia el siguiente comando "gcc tdas/*.c main.c -Wno-unused-result -o main" y presione "done".
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.
## Funcionalidades 

### Funcionando correctamente:


- Cargar peliculas y mostrar su respectiva informacion.
- Buscar una pelicula por su id y que muestre toda su informacion correspondiente.
- Ingresar un director y que muestre todas las peliculas dirigidas por el(Funciona en mayor parte).
- Ingresar un genero y que muestre todas las peliculas de ese respectivo genero.
- Ingresar una decada y que muestre todas las pelicudas estrenadas en esa decada.
- Ingresar una decada y un genero, para posteriormente mostrar las peliculas que cumplen las 2 condiciones.

### Problemas conocidos:

- Si una pelicula la dirigen 2 o mas directores, esta no se guarda como que fue dirigida por cada director, osea que al momento de mostrarla cuando se ingresa un director(funcionalidad 3) esta pelicula no aparecera.
- Al ingresar un genero o un director, se tiene que tener en cuenta los espacios que se ingresen luego de terminar de ingresar el dato, ya que no lo procesa y mostrara que no hay peliculas respectivos a ese genero. Por ejemplo en el genero "Horror" hay 23 peliculas en total, pero si se ingresa "Horror  "(1 o mas espacios luego de ingresar el genero), el programa no lo reconoce y dira que no hay peliculas de ese genero, osea que el programa no lo detectaria.
  

### A mejorar:

- Implementar una interfaz de usuario más amigable.
- Implementar que luego de cierto tiempo en una opcion, si no se han ingresado datos, volver al menu principal.
- Mejorar la lectura de datos para aceptar errores del usuario.
- Implementar una validacion que al ingresar numeros al ingresar un genero o director, no lo permita.
- Implementar la funcion "Buscar por rango de calificaciones".

## Ejemplo de uso:
### EL USUARIO NO SE EQUIVOCARA AL INGRESAR LOS RESPECTIVOS DATOS DURANTE LA EJECUCION DE TODO EL PROGRAMA.

#### Paso 1: CARGAR PELICULAS

Se comienza cargando las peliculas del archivo csv.
````
-----Pelicula numero: 1 -------

ID: tt0068646, Título: The Godfather, Año: 1972, Director/es: Francis Ford Coppola
Generos : Crime Drama

-----Pelicula numero: 2 -------

ID: tt0034583, Título: Casablanca, Año: 1942, Director/es: Michael Curtiz
Generos : Drama Romance War

..............................

````
El sistema procesara las 1500 peliculas del archivo CSV y para cada pelicula mostrara su Id, Titulo, Año de estreno(Año en pantalla), Director o Directores.
Ademas de mostrar sus respectivos generos.

#### Paso 2: Buscar por ID

El usuario quiere buscar la pelicula con el id tt0068646
````
Opción seleccionada: 2) Buscar por id
Ingrese el id de la película: tt0068646

Título: The Godfather, Año: 1972
Director/es: Francis Ford Coppola
Generos : Crime Drama

````
El sistema mostrara toda la informacion correspondiente a la pelicula que corresponde al respectivo id. 

#### Paso 3: Buscar por Director.

El usuario quiere buscar las peliculas del director "Michael Curtiz".
````
Opción seleccionada: 3) Buscar por director

Ingrese el nombre del director: Michael Curtiz

-----Pelicula numero: 1 -------
ID: tt0034583, Título: Casablanca, Año: 1942
Generos : Drama Romance War

-----Pelicula numero: 2 -------
ID: tt0037913, Título: Mildred Pierce, Año: 1945
Generos : Crime Drama Film-Noir Mystery Romance

-----Pelicula numero: 3 -------
ID: tt0029870, Título: Angels with Dirty Faces, Año: 1938
Generos : Crime Drama Film-Noir Thriller

-----Pelicula numero: 4 -------
ID: tt0031235, Título: Dodge City, Año: 1939
Generos : Western

-----Pelicula numero: 5 -------
ID: tt0035575, Título: Yankee Doodle Dandy, Año: 1942
Generos : Biography Drama Family Music Musical

-----Pelicula numero: 6 -------
ID: tt0026174, Título: Captain Blood, Año: 1935
Generos : Action Adventure History Romance

-----Pelicula numero: 7 -------
ID: tt0038776, Título: Night and Day, Año: 1946
Generos : Biography Drama Musical

-----Pelicula numero: 8 -------
ID: tt0037166, Título: Passage to Marseille, Año: 1944
Generos : Adventure Drama Romance War

-----Pelicula numero: 9 -------
ID: tt0024210, Título: The Kennel Murder Case, Año: 1933
Generos : Crime Drama Mystery

Cantidad total de peliculas del director ingresado son: 9
````
El programa muestra todas las peliculas dirigidas por el director "Michael Curtiz".

#### Paso 4: Buscar por Genero.
El usuario quiere buscar todas las peliculas del genero "Horror". (Para no mostrar las 23 peliculas mostrare algunas al principio y otras al final)
````
Opción seleccionada: 4) Buscar por género

Ingrese el genero deseado a buscar: Horror
-----Pelicula numero: 1 -------
ID: tt0054215, Título: Psycho, Año: 1960

-----Pelicula numero: 2 -------
ID: tt0046911, Título: Les diaboliques, Año: 1955

-----Pelicula numero: 3 -------
ID: tt0081505, Título: The Shining, Año: 1980

-----Pelicula numero: 4 -------
ID: tt0024216, Título: King Kong, Año: 1933

-----Pelicula numero: 5 -------
ID: tt0010323, Título: Das Cabinet des Dr. Caligari, Año: 1920

-----Pelicula numero: 6 -------
ID: tt0021884, Título: Frankenstein, Año: 1931

-----.......................................-----

-----Pelicula numero: 21 -------
ID: tt0086541, Título: Videodrome, Año: 1983

-----Pelicula numero: 22 -------
ID: tt0079641, Título: Nosferatu - Phantom der Nacht, Año: 1979

-----Pelicula numero: 23 -------
ID: tt0093773, Título: Predator, Año: 1987

Cantidad total de peliculas del genero ingresado son: 23
````
El sistema muestra los datos de cada pelicula perteneciente al genero horror, para las 23 peliculas en este caso muestra su Id, Titulo y Año.

#### Paso 5: Buscar por Decada
El usuario quiere buscar todas las peliculas pertenecientes a la decada de 2010. (Mostrare algunas al principio y otras al final)
````
Opción seleccionada: 5) Buscar por década

Ingrese la decada deseada a buscar (ejemplo: 1960, 2000): 2010
-----Pelicula numero: 1 -------
ID: tt1375666, Título: Inception, Año: 2010

-----Pelicula numero: 2 -------
ID: tt0947798, Título: Black Swan, Año: 2010

-----Pelicula numero: 3 -------
ID: tt1853728, Título: Django Unchained, Año: 2012

-----Pelicula numero: 4 -------
ID: tt1605783, Título: Midnight in Paris, Año: 2011

-----Pelicula numero: 5 -------
ID: tt1311071, Título: Kill Your Darlings, Año: 2013

-----Pelicula numero: 6 -------
ID: tt1120985, Título: Blue Valentine, Año: 2010

-----.......................................-----

-----Pelicula numero: 64 -------
ID: tt1403177, Título: Hesher, Año: 2010

-----Pelicula numero: 65 -------
ID: tt1758692, Título: Like Crazy, Año: 2011

-----Pelicula numero: 66 -------
ID: tt2027064, Título: Blue Caprice, Año: 2013

Cantidad total de peliculas de la decada ingresada: 66
````
El sistema muestra los datos de cada pelicula perteneciente a la decada de 2010, para las 66 peliculas en este caso muestra su Id, Titulo y Año de estreno.

#### Paso 6: Buscar por década y género.
El usuario desea buscar todas las peliculas del genero "Horror" de la decada del 2000.
````
Opción seleccionada: 7) Buscar por década y género

Ingrese la decada deseada a buscar (ejemplo: 1960, 2010): 2000
Ingrese el genero deseado a buscar: Horror
-----Pelicula numero: 1 -------
ID: tt0144084, Título: American Psycho, Año: 2000

-----Pelicula numero: 2 -------
ID: tt0408236, Título: Sweeney Todd: The Demon Barber of Fleet Street, Año: 2007

Cantidad total de peliculas de la decada ingresada respecto al genero pedido: 2
````
El sistema muestra los datos de las 2 peliculas en este caso que pertenecen al genero y decada requerido, muestra el Id, Titulo y Año para cada pelicula.

#### Paso 7: Salir del programa
Al momento de querer dejar de usar el programa, el usuario selecciona la opción de salir.
````
Opción seleccionada: 8) Salir
Hasta luego!
````
Se muestra un mensaje de despedida.

