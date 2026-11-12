#ifndef TABLERO_H
#define TABLERO_H

#include "Casilla.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

typedef struct
{
    int x;
    int y;
} Posicio;

using namespace std;

class Tablero
{
public:
    Tablero() : ancho(16), alto(16), primeraJugada(false), nMinas(0)
    {
        m_tablero = new Casilla *[ancho];

        for (int i = 0; i < ancho; i++)
            m_tablero[i] = new Casilla[alto];
    }
    Tablero(int x, int y) : ancho(x), alto(y), primeraJugada(false)
    {
        m_tablero = new Casilla *[x];

        for (int i = 0; i < x; i++)
            m_tablero[i] = new Casilla[y];
    }
    ~Tablero()
    {
        for (int i = 0; i < ancho; i++)
            delete[] m_tablero[i];

        delete[] m_tablero;
    }

    int getNMinas() const { return nMinas; }
    void setNMinas(int s){nMinas = s;}

    // funciones del control del juego
    void imprimiTablero() const;
    void inicializarTablero() const;
    Posicio PedirPosicionAClickar();

    // funciones de la logica interna del jeugo
    void añadirMinas();
    std::vector<Posicio> generarPosicionMinas();
    void acabarPartida() const;
    void casillaClicada(const Posicio &p);
    void rebelarCasillasRec1(const Posicio &p);    // funcion recursiva para enseñar cumulo de  casillas al clickar una
    bool dentroDelTablero(const Posicio &p) const; // funcion par ahacer el codigo menos feo
    void contarMinasPeriferia(const Posicio &p);   // funcio auxiliar per mirar les mines del voltant d'una casella
    Posicio convertirAij(const std::string s);

    void pedirPosicionAMarcar();
    void marcarBomba(const Posicio &p);
    void comprovarVictoria();

private:
    Casilla **m_tablero;
    int nMinas;
    int ancho;
    int alto;
    bool primeraJugada;
};

#endif
