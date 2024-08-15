# Script de un Keylogger basado en lenguaje C para Lunix

Este keylogger registra lsa teclas que el usuario va presionando y lo almacena en un documento txt. Puede registrar letras, números y caracteres especiales.

# Instrucciones de uso
1. Descarga el archivo `keylogger.c` en la carpeta de tu preferencia. OJO, modificar la ruta de **LOGFILEPATH** a la del usuario en cuestión
2. Estando ubicado en esa misma carpeta, compila el programa con el comando: `gcc -o keylogger keylogger.c`
Este comando crea un archivo en lenguaje máquina que es el que ejecutará nuestro código en C 
3. Ejecuta el nuevo archivo ejecutable "keylogger" con permisos de root: `sudo ./keylogger`. El archivo no devolverá ninguna salida, pero ya estará ejecutandosé de manera indefinida hasta que el usuario lo detenga manualmente
4. Para ver lo que el keylogger está registrando en tiempo real podemos usar el siguiente comando en una ventana de terminal diferente: `tail -f keylogger.txt`
5. Para comprobar que el keylogger está registrando datos hay que escribir cualquier cosa en otra ventana y verificar que eso se esté registrando en nuestro txt

# Supuesto del programa
1. Este programa está diseñado para funcionar en sistemas operativos basados en Linux, ya que este programa espera que por defecto los dispositivos de entrada (teclado) estén ubucados en la carpeta `/dev/input`. Además, el programa asume que el dispositivo de entrada principal es un teclado que se puede identificar en `/proc/bus/input/devices` y que el evento correspondiente al teclado se obtiene mediante un comando grep.
2. El usuario debe de tener permisos de superusuario para acceder a la carpeta anterior, además de poder ejecutar el código compilado
3. El programa asume que el dispositivo de entrada principal es un teclado que se puede identificar en `/proc/bus/input/devices` y que el evento correspondiente al teclado se obtiene mediante un comando grep.
4. El programa guarda las pulsaciones de teclas en un archivo de log ubicado en una ruta definida por la constante `LOGFILEPATH`.
5. Si no se puede acceder al dispositivo de entrada o al archivo de log, el programa se cierra con un mensaje de error.

# Casos de uso 
**Monitoreo de palabras escritas por empleados de alguna empresa.**
Este keylogger puede funcionar para observar qué palabras escriben los trabajadores de una empresa y verificar que no escriban busquedas no deseadas o palabras prohibidas. En el ámbito de seguridad, puede servir para comprobar que los empleados no compartan contraseñas de ingreso de sesión con nadie y de esta forma no comprometer la seguridad de la empresa. 
