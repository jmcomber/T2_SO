## TAREA 2

### Integrantes:

- José Manuel Comber
- Felipe Vandeputte

#### doer

Se ocupó una _struct proc_ que contiene todos los datos relevantes (output, exit code, la instrucción, si terminó, etc.). Para captar el output se ocupó _pipe()_ y se leía a un _buffer_ (más rápido que con, por ejemplo, un file.tmp).

Si bien es poco intuitivo en un comienzo que el tiempo secuencial sea mucho menor que el tiempo real, esto se debe a que las labores de "administración" son comparativamente más lentas que la ejecución de una instrucción de terminal como _ls -al_.


#### simulator

No hay mayores decisiones de diseño que comentar.