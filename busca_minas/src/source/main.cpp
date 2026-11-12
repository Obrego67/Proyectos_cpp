#include "../headers/Tablero.h"

using namespace std;

int main()
{
    Tablero tablero;
    int nBombas;
    char opcion;
    cout << "Introduce el numero de bombas: ";
    cin >> nBombas;

    tablero.setNMinas(nBombas);

    tablero.inicializarTablero();
    tablero.añadirMinas();
    while (true)
    {
        cout << "marcar(m)/revelar(r)/salir(e):";
        cin >> opcion;

        switch (opcion)
        {
        case 'm':
            tablero.pedirPosicionAMarcar();
            break;
        case 'r':
            tablero.casillaClicada(tablero.PedirPosicionAClickar());
            break;
        case 'e':
            exit(0);
            break;
        }
        tablero.imprimiTablero();
        tablero.comprovarVictoria();
    }
}