#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "filem.h"

void clearStdin();
void halfBoard(char* espaces);
void chooseForm(int f);
void play(Game game,char c1[2],char c2[2]);

int main() {
    printf("MENU PRINCIPAL: \n");
    printf("1) Jugar en local: \n");
    printf("2) Crear una formacion: \n");
    printf("3) Cargar partida: \n");
    printf("0) Salir: \n");
    int option;
    printf("Introduzca opcion: ");
    scanf("%d", &option);
    clearStdin();
    while (option!= 0){
        if (option == 1) {
            chooseForm(1);  // Dibujado de las formaciones que se leen de archivo
            chooseForm(2);
            chooseForm(3);
            Game game;
            char form;
            printf("Escoger formacion: ");
            scanf("%d", &form);
            clearStdin();
            printf("\n");
            char *f1 = loadForm(form);
            char *f2 = loadForm(4);
            startGame(&game, f1, f2);  // Se inicia partida con las formacion seleccinada
            free(f1);
            free(f2);
            //system("cls"); // Para consola
            printf("Juego iniciado.\n\n");
            printBoard(game);
            char c1[2]; // Para los movimientos
            char c2[2];
            play(game,c1,c2);   // Iniciar partida
            printf("Partida terminada.\n");
            if ((c1[0] != 's' && c1[1] != 'g') && (c1[0] != 'm')) printf("Gana el equipo %d\n", game.turn % 2); // Si la partida se detiene por guardado o porque el jugador la deja
        } else if (option == 2) {
            printf("\n");
            char pieceArr[] = "ssssggwwwaaa";   // Las piezas que se tienen que ir colocando
            char spaces[] = "eeeeeeeeeeeeeeeeeeeee"; // La formacion

            char c1[2];
            int x;
            int y;
            int p = 0;
            while (p < 12) {
                halfBoard(spaces);  // Dibujado
                printf("Donde quieres colocar %c\n", pieceArr[p]);
                scanf("%c%c", &c1[0], &c1[1]);
                clearStdin();
                x = c1[1] - '0' - 1;    // Cambio de formato ajedrez a posicion en el array
                y = c1[0] - 'a';
                int pos = y + (x * 3);
                if (spaces[pos] == 'e' && (x >= 0 && x < 7) && (y >= 0 && y < 3) && pos!=9){    // Si el espacio esta disponible se coloca la pieza
                    spaces[pos] = pieceArr[p];
                    p++;
                } else {
                    printf("No se puede colocar en esa casilla\n");
                }
            }
            halfBoard(spaces);
            printf("Formacion terminada\n");
            saveForm(1, spaces);    // Se guarda la formacion en el fichero 1

        } else if (option == 3){
            int **data = loadGame(); // Cargado de los datos de la partida

            Game game;
            game.time = 0;  // Asignacion de los datos generales
            game.turn = data[0][0];
            game.nexus1hp = data[0][1];
            game.nexus2hp = data[0][2];
            for (int i = 1; i < 25; ++i) {
                game.pieces[i-1] = (Piece) {data[i][0], data[i][1], getBaseDmg(data[i][0])};    //Asignacion al array de piezas
            }
            game.pieces[24] = (Piece) {25, data[0][1]};
            game.pieces[25] = (Piece) {26, data[0][2]};

            for (int i = 0; i < B_ROWS; i++) {
                for (int j = 0; j < B_COLUMNS; j++) {   // Limpiado del teclado
                    game.data[i][j] = 0;
                }
            }
            game.data[3][0] = 25;
            game.data[3][10] = 26;
            for (int i = 1; i < 25; i++) {
                if (game.pieces[i-1].hp > 0){
                    game.data[data[i][2]][data[i][3]] = data[i][0]; // Asignar al tablero
                }
            }
            printf("Juego iniciado.\n\n");  // Reanudar la partida
            printBoard(game);
            char c1[2];
            char c2[2];
            play(game,c1,c2);
            printf("Partida terminada.\n");
            if ((c1[0] != 's' && c1[1] != 'g') && (c1[0] != 'm')) printf("Gana el equipo %d\n", game.turn % 2);
        }
        //system("cls"); // Para consola
        printf("MENU PRINCIPAL: \n");
        printf("1) Jugar en local: \n");
        printf("2) Crear una formacion: \n");
        printf("3) Cargar partida: \n");
        printf("0) Salir: \n");
        int option;
        printf("Introduzca opcion: ");
        scanf("%d", &option);
        clearStdin();
        if (option==0){
            break;
        }
    }

    return 0;
}

void clearStdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void halfBoard(char* espaces)
{
    int seg = 0;

    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 3; j++) {
            if (seg==9) printf("N|");
            else if (espaces[seg] == 'e') printf(" |");
            else printf("%c|",espaces[seg]);
            seg++;
        }
        printf("\n"); // Formateo
    }
    printf("     "); // Formateo
    for (int i = 0; i < 3; i++) {
        printf("^ "); // Formateo
    }

    printf("\n     "); // Formateo
    for (int i = 0; i < 3; i++) {
        printf("%c ", 'a' + i);
    }
    printf("\n");
}

void chooseForm(int f)
{
    printf("Formacion %d:\n",f);
    char *form = loadForm(f);   // Lectura y visualizacion desde fichero
    int seg = 0;
    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 3; j++) {
            char unit = form[3 * i + j];
            if (unit == 'e') printf(" |");
            else if (unit == 'N') printf("N|");
            else if (unit == 's' || unit == 'w' || unit == 'a' || unit == 'g') printf("%c|", form[seg]);
            seg++;
        }
        printf("\n"); // Formateo
    }
    printf("     "); // Formateo
    for (int i = 0; i < 3; i++) {
        printf("^ "); // Formateo
    }

    printf("\n     "); // Formateo
    for (int i = 0; i < 3; i++) {
        printf("%c ", 'a' + i);
    }
    printf("\n");
}
void play(Game game,char c1[2],char c2[2])
{
    while (game.nexus1hp > 0 && game.nexus2hp > 0) {

        printf("%d:%d, T%d, %c\n", game.nexus1hp, game.nexus2hp, game.turn, game.turn % 2 ? 'D' : 'I');
        printf("Casilla origen: ");
        scanf("%c%c", &c1[0], &c1[1]);
        if (c1[0] == 'm') break; // Salir del juego
        else if (c1[0] == 'h' && c1[1] == 'p') { // Ver vida de las piezas
            clearStdin();
            //system("cls");
            printf("Vida de las piezas.\n\n");
            printLifeBoard(game);
            printf("Pulse 'enter' para salir. ");
            scanf("%c");
            clearStdin();
            //system("cls");
            printf("Elegir movimiento.\n\n");
            printBoard(game);
            printf("Casilla origen: ");
            scanf("%c%c", &c1[0], &c1[1]);
        } else if (c1[0] == 's' && c1[1] == 'g') { // Guardar partida
            int sapieces[24][4];
            for (int i = 0; i < 24; ++i) {  // Se guardan las posiciones de las piezas
                sapieces[i][0] = game.pieces[i].id;
                sapieces[i][1] = game.pieces[i].hp;
                if (game.pieces[i].hp < 1){ // Piezas muertas
                    sapieces[i][2] = -2;
                    sapieces[i][3] = -2;
                } else {
                    int *ids;
                    ids = getPiecePos(game, game.pieces[i].id); //Localizar y asignar piezas vivas
                    sapieces[i][2] = ids[0];
                    sapieces[i][3] = ids[1];
                }
            }
            saveGame(game.turn, game.nexus1hp, game.nexus2hp, sapieces);
            break;
        } else if (c1[0] == '?' && c1[1] == '?') { // Ver información de las piezas
            clearStdin();
            //system("cls");
            printf("Movimiento y ataque de las piezas.\n\n");
            printf("Lanceros (s): Se mueven 1 o 2 casillas para adelante y atacan en 3 casillas verticales al frente\n");
            printf("Mago (w): Se mueven 1 casilla en todas las direcciones y atacan a distancia de 2 casillas\n");
            printf("Golem (g): Se mueven y atacan a 1 casilla en todas las direcciones\n");
            printf("Asesino (a): Se mueven y atacan a 3 casillas en vertical y horizontal. Ademas pueden atravesar piezas para moverse\n\n");
            printf("Pulse 'enter' para salir. ");
            scanf("%c");
            clearStdin();
            //system("cls");
            printf("Elegir movimiento.\n\n");
            printBoard(game);
            printf("Casilla origen: ");
            scanf("%c%c", &c1[0], &c1[1]);
        }
        clearStdin();
        printf("Casilla destino: ");
        scanf("%c%c", &c2[0], &c2[1]);
        clearStdin();
        //system("cls"); // Para consola
        // Extraer y convertir posiciones
        int originX = c1[1] - '0' - 1;
        int originY = c1[0] - 'a';
        int destinyX = c2[1] - '0' - 1;
        int destinyY = c2[0] - 'a';
        int jugada = updatePiece(&game, originX, originY, destinyX, destinyY);
        if (jugada > 0) game.turn++;
        printf("\n");
        printBoard(game);
    }
}
