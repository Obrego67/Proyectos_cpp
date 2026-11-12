#include "../headers/Tablero.h"

using namespace std;

void Tablero::imprimiTablero() const
{
    cout << "    | ";
    for (int j = 0; j < ancho; j++)
    {
        cout << static_cast<char>('a' + j) << " | ";
    }
    cout << endl;

    for (int i = 0; i < ancho; i++)
    {
        if (i < 9)
            cout << i + 1 << ".  | ";
        else
            cout << i + 1 << ". | ";

        for (int j = 0; j < ancho; j++)
        {
            if (m_tablero[i][j].getEstado() == NO_VISITADA && m_tablero[i][j].getMarcado() == NO_MARCADA)
                cout << "O";
            else if (m_tablero[i][j].getMarcado() == MARCADA)
            {
                cout << "M";
            }
            else
            {
                if (m_tablero[i][j].getTipo() == VACIO)
                    cout << m_tablero[i][j].getIcono();
                else
                    cout << "X";
            }

            cout << " | ";
        }
        cout << endl;
    }
    cout << endl;
}
void Tablero::inicializarTablero() const
{
    string Titulo = "\n"
                    "    ------------------------------\n"
                    "             BUSCA MINAS\n"
                    "    ------------------------------\n";

    cout << Titulo << endl;

    imprimiTablero();
}
Posicio Tablero::convertirAij(const string s)
{
    Posicio p;
    p.x = stoi(s.substr(0, s.size() - 1)) - 1;
    p.y = s.back() - 'a';

    return p;
}
Posicio Tablero::PedirPosicionAClickar()
{
    string posicionS;
    Posicio posicionInt;

    cout << "Posicion a rebelar:";
    cin >> posicionS;

    if (posicionS == "ñ")
        exit(0);
    posicionInt = convertirAij(posicionS);
    while (m_tablero[posicionInt.x][posicionInt.y].getEstado() == VISITADA)
    {
        cout << "posicion ya rebelada, introduce una nueva: ";
        cin >> posicionS;

        if (posicionS == "ñ")
            exit(0);
        posicionInt = convertirAij(posicionS);
    }

    return posicionInt;
}
void Tablero::casillaClicada(const Posicio &p)
{
    m_tablero[p.x][p.y].setEstado(VISITADA);
    imprimiTablero();
    if (m_tablero[p.x][p.y].getTipo() == MINA)
        acabarPartida();
    else
    {
        rebelarCasillasRec1(p);
    }
}
vector<Posicio> Tablero::generarPosicionMinas()
{
    vector<Posicio> minas;

    for (int i = 0; i < nMinas; i++)
    {
        Posicio p;
        p.x = rand() % 15;
        p.y = rand() % 15;
        minas.push_back(p);
    }
    return minas;
}
void Tablero::añadirMinas()
{
    vector<Posicio> minas = generarPosicionMinas();
    for (Posicio &p : minas)
        m_tablero[p.x][p.y].setTipo(MINA);
}
void Tablero::acabarPartida() const
{
    cout << "FIN DEL GUEGO" << endl;
    exit(0);
}
bool Tablero::dentroDelTablero(const Posicio &p) const
{
    return (p.x >= 0 && p.x < 16 && p.y >= 0 && p.y < 16);
}
void Tablero::contarMinasPeriferia(const Posicio &p)
{
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            Posicio paux;
            paux.x = p.x + i;
            paux.y = p.y + j;
            if (dentroDelTablero(paux))
            {
                if (m_tablero[paux.x][paux.y].getTipo() == MINA)
                    m_tablero[p.x][p.y].sumarMinaPeriferia();
            }
        }
    }
}
void Tablero::rebelarCasillasRec1(const Posicio &p)
{
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            Posicio paux;
            paux.x = p.x + i;
            paux.y = p.y + j;
            if (dentroDelTablero(paux))
            {
                if (m_tablero[paux.x][paux.y].getTipo() == VACIO && m_tablero[paux.x][paux.y].getEstado() == NO_VISITADA)
                {
                    m_tablero[paux.x][paux.y].setEstado(VISITADA);
                    contarMinasPeriferia(paux);
                    int minesCasillaAux = m_tablero[paux.x][paux.y].getMinasPeriferia();

                    if (minesCasillaAux != 0)
                    {
                        char a = static_cast<char>('0' + minesCasillaAux);
                        m_tablero[paux.x][paux.y].setIcono(a);
                    }
                    else
                    {
                        rebelarCasillasRec1(paux);
                    }
                }
            }
        }
    }
}
void Tablero::marcarBomba(const Posicio &p)
{
    m_tablero[p.x][p.y].setMarcado(MARCADA);
}
void Tablero::pedirPosicionAMarcar()
{
    string s;
    cout << "Introduxe la posicion a marcar: ";
    cin >> s;

    marcarBomba(convertirAij(s));
}
void Tablero::comprovarVictoria()
{
    int minasMarcadas = 0;

    for (int i = 0; i < ancho; i++)
        for (int j = 0; j < ancho; j++)
        {
            if (m_tablero[i][j].getTipo() == MINA && m_tablero[i][j].getMarcado() == MARCADA)
                minasMarcadas++;
        }
    if (minasMarcadas == nMinas)
    {
        cout << "VICTORIA!!!" << endl;
        cout << "'e' para salir"<<endl;
        char a;
        cin >> a;
        if (a == 'e')
            exit(0);
    }
}