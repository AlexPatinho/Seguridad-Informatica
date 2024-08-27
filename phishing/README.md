# Pagina de robo de datos (Phishing) basada en el LOGIN de Linkedin

## Descripción.

Este proyecto está basado en la página de inicio de sesión de Linkedin. 
Estos archivos simulan ser la página de Login de Linkedin, la cual es un ataque de phishing, ya que toma los datos ingresados en el formulario y los manda a una base de datos por medio del archivo `insert.php`, donde se almacenará el correo y contraseña del usuario.  


## Vector inicial.

Un ejemplo de cómo una persona podría caer en este ataque sería el siguiente:
1. Se le envía un correo o SMS al usuario con el mensaje de que se ha encontrado una vacante que podría ser de gran interés: \n
`Nueva vacante disponible: Gerente administrativo
Para mas información consulta el siguiente link: *url del sitio falso*`

2. El usuario ingresa al link de trampa e inicia sesión. Cuando el usuario da click en **Iniciar Sesión**, lo redirijirá a la página home oficial de Linkedin para hacerle creer que pudo iniciar sesión.

