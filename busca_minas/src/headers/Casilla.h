#ifndef CASILLA_H
#define CASILLA_H

namespace hola
{
    enum tipo
    {
        MINA = 0,
        VACIO = 1,
    };

    enum visitada{
        VISITADA = true,
        NO_VISITADA = false,
    };

    enum marcarCasilla{
        MARCADA = true,
        NO_MARCADA = false,
    };
}

using namespace hola;

class Casilla
{
public:
    Casilla() : m_tipoCasilla(VACIO), m_estado(NO_VISITADA), icono(' '), nMinasPeriferia(0), marcado(NO_MARCADA) {}
    ~Casilla() {}

    tipo getTipo() const { return m_tipoCasilla; }
    bool getEstado() const { return m_estado; }
    int getMinasPeriferia() const { return nMinasPeriferia; }
    char getIcono() const { return icono; }
    bool getMarcado() const {return marcado; }

    void setTipo(const tipo &t) { m_tipoCasilla = t; }
    void setEstado(const bool &e) { m_estado = e; }
    void setIcono(char c) { icono = c; }
    void setMarcado(const bool &b){marcado = b;}

    void resetMinasPeriferia() { nMinasPeriferia = 0; }
    void sumarMinaPeriferia() { nMinasPeriferia++; }

private:
    tipo m_tipoCasilla; // el tipo que es
    bool m_estado;      // si esta rebelada o no
    char icono;
    int nMinasPeriferia;
    bool marcado;
};

#endif
