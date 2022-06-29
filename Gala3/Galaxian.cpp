#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <list>
#include <time.h>

using namespace std;

#define IZQUIERDA 75 //Definir el número de las flechas
#define DERECHA 77
#define AZUL 1 //Definir el número de los colores
#define ROJO 4
#define BLANCO 15
#define VERDE 2
#define CIAN 3
#define AMARILLO 6


void situarCursor(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cPunto;
    cPunto.X = x;
    cPunto.Y = y;
    SetConsoleCursorPosition(hCon, cPunto);
}

void ocultarCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cInfo;
    cInfo.dwSize = 2;
    cInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cInfo);
}
void pintarLimites() //Dibujar el marco de juego
{

    for (int i = 3; i < 22; i++)
    {
        situarCursor(2, i); printf("%c", 186);
        situarCursor(60, i); printf("%c", 186);
    }

}

//Crear la nave
class NAVE  
{
    int x, y;
    int corazones;
    int vidas;
public:
    NAVE(int _x, int _y, int _corazones, int _vidas) :x(_x), y(_y), corazones(_corazones), vidas(_vidas) {}
    void pintar();
    void borrar();
    void mover();
    void pintarCorazones();
    void pintarTeclas();
    void morir();
    void restarCorazon() { corazones--; }
    int X() { return x; }
    int Y() { return y; }
    int VIDAS() { return vidas; }
};

void NAVE::pintar() //Se dibuja la nave
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, AZUL);
    
    situarCursor(x, y); printf("  %c", 30);
    situarCursor(x, y + 1); printf(" %c%c%c", 91, 2, 93);
    situarCursor(x, y + 2); printf("%c%c %c%c", 30, 190, 190, 30);
}
void NAVE::borrar() //Para que el movimiento de la nave no provoque que se duplique
{
    situarCursor(x, y); printf("          ");
    situarCursor(x, y + 1); printf("          ");
    situarCursor(x, y + 2); printf("          ");
}

void NAVE::mover() //Movimiento de la nave
{
    if (_kbhit())
    {
        char tecla = _getch();
        borrar();
        if (tecla == IZQUIERDA && x > 3) { x--; }
        if (tecla == DERECHA && x < 50) { x++; }


        pintar();

    }
}

void NAVE::pintarCorazones()  //Corazones de la vida de la nave y salud
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, ROJO);
    situarCursor(50, 2);
    printf("Vidas: %d", vidas);
    

    situarCursor(63, 2);
    printf("Salud");
    situarCursor(69, 2);
    printf("       ");
    for (int i = 0; i < corazones; i++)
    {
        situarCursor(69 + i, 2);
        printf("%c", 3);
    }

}

void NAVE::pintarTeclas()  //Instrucciones sobre como funciona la nave en el juego
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, BLANCO);
    //Controles del juego
    situarCursor(23, 0);
    printf("Disparar: Espacio");
    situarCursor(23, 1);
    printf("Mover:    <-   ->");
}
void NAVE::morir()  //Forma de la nave cuando pierde 1 vida
{
    if (corazones == 0)
    {
        borrar();
        situarCursor(x, y);   printf("   **   ");
        situarCursor(x, y + 1); printf("  ***  ");
        situarCursor(x, y + 2); printf("   **   ");
        Sleep(200);
        borrar();
        situarCursor(x, y);   printf(" * ** * ");
        situarCursor(x, y + 1); printf("* *** *");
        situarCursor(x, y + 2); printf("* ** *");
        Sleep(200);
        borrar();
        vidas--;
        corazones = 3;
        pintarCorazones();
        pintar();
    }
}

//Crear los marcianos
class MAR
{
    //int x, y;
public:
    int x, y, cat;
    MAR(int _x, int _y, int _cat) :x(_x), y(_y), cat(_cat) {}
    void pintar();
    void mover();
    void limpiar();

    int X() { return x; }
    int Y() { return y; }
    int Cat() { return cat; }
};

void MAR::pintar() //Dibuja los marcianos en la pantalla
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, VERDE);
    situarCursor(x, y);
    printf("%c", 30);
    
}
void MAR::limpiar() //Elimina los duplicados de los marcianos al bajar
{
    situarCursor(x, y); printf(" ");
}
void MAR::mover() //Movimiento de los marcianos
{

    situarCursor(x, y); printf(" ");

    pintar();
}

//Crear asteroides
class AST
{
    int x, y;
public:
    AST(int _x, int _y) :x(_x), y(_y) {}
    void pintar();
    void mover();
    void choque(class NAVE& N);
    int X() { return x; }
    int Y() { return y; }
};

void AST::choque(class NAVE& N) //Colisión entre asteroide y nave
{
    if (x >= N.X() && x <= N.X() + 5 && y >= N.Y() && y <= N.Y() + 2)
    {
        N.restarCorazon();
        N.pintar();
        N.pintarCorazones();
        x = rand() % 48 + 4;
        y = 4;
    }
}

void AST::pintar() //Dibuja los asteroides
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, BLANCO);
    situarCursor(x, y); printf("%c", 184);

}
void AST::mover() //Movimiento de los asteroides
{
    situarCursor(x, y); printf(" ");
    y++;
    if (y > 20)
    {
        x = rand() % 48 + 4;
        y = 4;
    }
    pintar();
}

//Crear las balas de la nave
class BALA
{
    int x, y;
public:
    BALA(int _x, int _y) :x(_x), y(_y) {}
    void mover();
    bool fuera();
    int X() { return x; }
    int Y() { return y; }

};

void BALA::mover() //Movimiento de la bala
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, AMARILLO);
    situarCursor(x, y); printf(" ");
    if (y > 0) { y--; }
    situarCursor(x, y); printf("|");
}

bool BALA::fuera() //Límite de altura en la bala al no colisionar
{
    if (y == 3)
    {
        return true;
    }
    return false;
}

int main()
{
    int contadoravance = 0; //Para ajustar el movimiento de los marcianos
    int puntos = 0; //Para contar los puntos del juego
    int catMar = 0; 
    //Ejecuta las funciones prototipo
    pintarLimites(); 
    ocultarCursor();
    NAVE N(30, 19, 3, 3);
    N.pintar();
    N.pintarCorazones();
    N.pintarTeclas();

    list<MAR*> A;
    list<MAR*>::iterator Ait;
    list<AST*> C;
    list<AST*>::iterator Cit;

    //Generar las columnas de marcianos
    for (int i = 8; i != 4; i--)
    {
        A.push_back(new MAR(9, i, catMar));
        A.push_back(new MAR(13, i, catMar));
        A.push_back(new MAR(17, i, catMar));
        A.push_back(new MAR(21, i, catMar));
        A.push_back(new MAR(25, i, catMar));
        A.push_back(new MAR(29, i, catMar));
        A.push_back(new MAR(33, i, catMar));
        A.push_back(new MAR(37, i, catMar));
        A.push_back(new MAR(41, i, catMar));
        A.push_back(new MAR(45, i, catMar));
        A.push_back(new MAR(49, i, catMar));
        A.push_back(new MAR(53, i, catMar));
        catMar++;//0-3
    }
    C.push_back(new AST(rand() % 48 + 3, rand() % 5 + 4));


    list<BALA*> B;
    list<BALA*>::iterator it;

    bool game_over = false; //Inicia el juego
    while (!game_over)
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, CIAN);
        situarCursor(4, 2); printf("Puntos: %d", puntos); //Puntuación

        if (_kbhit()) //Disparar las balas
        {
            char tecla = _getch();
            if (tecla == ' ')
            {
                B.push_back(new BALA(N.X() + 2, N.Y() - 1));
                B.push_back(new BALA(N.X() + 3, N.Y() - 1));
            }
        }

        //Borrar la bala y el marciano cuando colisionan, y el asteroide cuando choca con la nave
        for (it = B.begin(); it != B.end();) 
        {
            (*it)->mover();
            if ((*it)->fuera())
            {
                situarCursor((*it)->X(), (*it)->Y());
                printf(" ");
                delete(*it);
                it = B.erase(it);
            }
            else it++;

        }
        for (Cit = C.begin(); Cit != C.end(); Cit++) 
        {
            (*Cit)->mover();
            (*Cit)->choque(N);
        }


        for (Ait = A.begin(); Ait != A.end(); Ait++)
        {
            (*Ait)->mover();

            if ((*Ait)->Y() == 19)
            {
                game_over = true;
                break;
            }
        }

        //Desplazamiento de los marcianos
        contadoravance++;
        if (contadoravance == 50)
        {
            for (Ait = A.begin(); Ait != A.end(); Ait++)//Avanzar
            {
                (*Ait)->limpiar();
                (*Ait)->y++;
                (*Ait)->mover();
            }
            contadoravance = 0;
        }

        //detectar colisiones entre bala y asteroides
        for (Ait = A.begin(); Ait != A.end(); Ait++)
        {
            for (it = B.begin(); it != B.end(); )
            {
                if ((*Ait)->X() == (*it)->X() && ((*Ait)->Y() == (*it)->Y() || (*Ait)->Y() == (*it)->Y()))
                {
                    if ((*Ait)->X() == 53 && (*Ait)->Y() == 5)
                    {
                        break;
                    }


                    situarCursor((*it)->X(), (*it)->Y()); printf(" ");
                    delete(*it);
                    it = B.erase(it);


                    delete(*Ait);
                    Ait = A.erase(Ait);
                    puntos += 100;
                    if ((*Ait)->Cat() == 3)
                        puntos += 300;
                    if ((*Ait)->Cat() == 2)
                        puntos += 200;
                    if ((*Ait)->Cat() == 1)
                        puntos += 100;



                }

                else
                {



                    it++;

                }
            }

        }

        if (N.VIDAS() == 0) //Al perder todas las vidas
        {
            game_over = true;
        }

        if (puntos == 12000) //Al eliminar a todos los marcianos
        {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, ROJO);
            situarCursor(24, 10);
            printf("HAS GANADO");
            game_over = true;
        }

        if (game_over == true) //Al terminar el juego
        {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, ROJO);
            situarCursor(20, 12);
            printf("EL JUEGO HA TERMINADO\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            if (puntos < 12000)
            {
                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, ROJO);
                situarCursor(24, 10);
                printf("HAS PERDIDO\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }

        }


        N.morir();
        N.mover();
        Sleep(30);

    }
    return 0;

}