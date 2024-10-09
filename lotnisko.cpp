#include <iostream>
using namespace std;

struct Punkt
{
    int x, y;
};

struct PoczatekIKonec
{
    Punkt poczatek, konec;
    int dlugosc;
};

// Funkcja do obliczania długości lotniska
int obliczDlugosc(PoczatekIKonec lotnisko)
{
    if (lotnisko.poczatek.x == lotnisko.konec.x)
        return lotnisko.konec.y - lotnisko.poczatek.y + 1;  // pionowe
    else
        return lotnisko.konec.x - lotnisko.poczatek.x + 1;  // poziome
}

void sortuj(PoczatekIKonec *lotniska, int rozmiarTabeli)
{
    for (int i = 0; i < rozmiarTabeli - 1; i++)
    {
        for (int j = 0; j < rozmiarTabeli - i - 1; j++)
        {
            if (lotniska[j].dlugosc < lotniska[j + 1].dlugosc)
            {
                PoczatekIKonec temp = lotniska[j];
                lotniska[j] = lotniska[j + 1];
                lotniska[j + 1] = temp;
            }
        }
    }
}

//dwa najdłuższe lotniska
void drukuj2Najdluzsze(PoczatekIKonec *lotniska, int rozmiarTabeli, bool zmien)
{
    int iloscDoDrukowania = (rozmiarTabeli < 2) ? rozmiarTabeli : 2; // Jeśli mniej niż 2 lotniska, wypisz wszystkie

    for (int i = 0; i < iloscDoDrukowania; i++)
    {
        cout << "start = (" << lotniska[i].poczatek.x << ", " << lotniska[i].poczatek.y << ") koniec = ("
             << lotniska[i].konec.x << ", " << lotniska[i].konec.y << ") dlugosc = " << lotniska[i].dlugosc << endl;
    }
}

int main()
{
    // wczytywanie
    int bokA;
    int iloscLotnisk;
    int rozmiarTabeli = 0;
    cin >> bokA >> iloscLotnisk;
    string pole[bokA];
    PoczatekIKonec *lotniskaPoziome = (PoczatekIKonec *)malloc(0 * sizeof(PoczatekIKonec));
    PoczatekIKonec *lotniskaPionowe = (PoczatekIKonec *)malloc(0 * sizeof(PoczatekIKonec));
    int rozmiarPoziome = 0, rozmiarPionowe = 0;

    for (int i = 0; i < bokA; i++)
    {
        cin >> pole[i];
    }

    // szukanie w poziomie
    for (int y = 0; y < bokA; y++)
    {
        for (int x = 0; x < bokA; x++)
        {
            if (pole[y][x] == '.')
            {
                if (x > 0)
                {
                    if (pole[y][x - 1] == 'X')
                    {
                        rozmiarPoziome++;
                        lotniskaPoziome = (PoczatekIKonec *)realloc(lotniskaPoziome, rozmiarPoziome * sizeof(PoczatekIKonec));
                        lotniskaPoziome[rozmiarPoziome - 1].poczatek.y = y;
                        lotniskaPoziome[rozmiarPoziome - 1].poczatek.x = x;
                    }

                    if (x == bokA - 1)
                    {
                        lotniskaPoziome[rozmiarPoziome - 1].konec.y = y;
                        lotniskaPoziome[rozmiarPoziome - 1].konec.x = x;
                    }
                }
                else
                {
                    rozmiarPoziome++;
                    lotniskaPoziome = (PoczatekIKonec *)realloc(lotniskaPoziome, rozmiarPoziome * sizeof(PoczatekIKonec));
                    lotniskaPoziome[rozmiarPoziome - 1].poczatek.y = y;
                    lotniskaPoziome[rozmiarPoziome - 1].poczatek.x = x;
                }
            }
            else
            {
                if (x > 0)
                {
                    if (pole[y][x - 1] == '.')
                    {
                        lotniskaPoziome[rozmiarPoziome - 1].konec.y = y;
                        lotniskaPoziome[rozmiarPoziome - 1].konec.x = x - 1;
                    }
                }
            }
        }
    }

    // szukanie w pionie
    for (int x = 0; x < bokA; x++)
    {
        for (int y = 0; y < bokA; y++)
        {
            if (pole[y][x] == '.')
            {
                if (y > 0)
                {
                    if (pole[y - 1][x] == 'X')
                    {
                        rozmiarPionowe++;
                        lotniskaPionowe = (PoczatekIKonec *)realloc(lotniskaPionowe, rozmiarPionowe * sizeof(PoczatekIKonec));
                        lotniskaPionowe[rozmiarPionowe - 1].poczatek.y = y;
                        lotniskaPionowe[rozmiarPionowe - 1].poczatek.x = x;
                    }

                    if (y == bokA - 1)
                    {
                        lotniskaPionowe[rozmiarPionowe - 1].konec.y = y;
                        lotniskaPionowe[rozmiarPionowe - 1].konec.x = x;
                    }
                }
                else
                {
                    rozmiarPionowe++;
                    lotniskaPionowe = (PoczatekIKonec *)realloc(lotniskaPionowe, rozmiarPionowe * sizeof(PoczatekIKonec));
                    lotniskaPionowe[rozmiarPionowe - 1].poczatek.y = y;
                    lotniskaPionowe[rozmiarPionowe - 1].poczatek.x = x;
                }
            }
            else
            {
                if (y > 0)
                {
                    if (pole[y - 1][x] == '.')
                    {
                        lotniskaPionowe[rozmiarPionowe - 1].konec.y = y - 1;
                        lotniskaPionowe[rozmiarPionowe - 1].konec.x = x;
                    }
                }
            }
        }
    }

    // liczenie długości
    for (int i = 0; i < rozmiarPoziome; i++)
    {
        lotniskaPoziome[i].dlugosc = obliczDlugosc(lotniskaPoziome[i]);
    }
    for (int i = 0; i < rozmiarPionowe; i++)
    {
        lotniskaPionowe[i].dlugosc = obliczDlugosc(lotniskaPionowe[i]);
    }

    //Sortowanie
    sortuj(lotniskaPoziome, rozmiarPoziome);
    sortuj(lotniskaPionowe, rozmiarPionowe);

    cout << "poziome" << endl;
    drukuj2Najdluzsze(lotniskaPoziome, rozmiarPoziome, true);

    cout << "pionowe" << endl;
    drukuj2Najdluzsze(lotniskaPionowe, rozmiarPionowe, true);

    free(lotniskaPoziome);
    free(lotniskaPionowe);

}
