# Tarea4_AnalisisNumerico2Sem2018

LU y QR

Crear una carpeta "build" en el directorio del proyecto.

Entrar a la carpeta build.

Ejecutar en la terminal asociada a ese path :

  cmake ../ -DCMAKE_BUILD_TYPE=Debug

Luego ejecutar make



Para ejecutar los binarios es necesario entrar a la carpeta bin dentro de build y ejecutar en consola:

./tarea04          = Ejecutable del proyecto

./benchmark        = Prueba de rendimiento de los algoritmos Doolittle y Crout para diferentes dimensiones de A

./tester           = Pruebas unitarias asociadas a la multiplicacion matriz-matriz o matriz-vector , asi como 
                      pruebas de funcionamiento para los algoritmos QR, Crout y Doolittle.
