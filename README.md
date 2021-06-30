# Chess 2 : Génesis
### Estructura del código
La implementación en consola está autocontenida en [src/game](https://github.com/Dzl17/chess2/tree/master/src/game), siendo el punto de entrada el archivo [main.c](https://github.com/Dzl17/chess2/tree/master/src/game/main.c), y realiza el procesado de datos del juego.

La implementación gráfica parte de [app.cpp](https://github.com/Dzl17/chess2/tree/master/src/app.cpp), y representa los datos procesados en la parte programada en C.

### Juego
Juego para uno o dos jugadores. Cada usuario puede disponer piezas de 4 tipos en formaciones propias o por defecto, y debe lograr destruir el nexo del equipo enemigo. Cada pieza tiene un patrón de movimiento y de ataque propio, consultable dentro del juego en todo momento. Dichas piezas tienen además estadísticas diferenciadas de vida y daño.

Se permite además el guardado y cargado de tanto formaciones propias como de partidas.
