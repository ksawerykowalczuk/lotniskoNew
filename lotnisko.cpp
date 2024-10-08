#include <iostream>
using namespace std;

struct Punkt
{
    int x, y;
};

struct PoczatekIKonec
{
    Punkt poczatek, konec;
};

void drukuj(PoczatekIKonec *lotniska, int rozmiarTabeli, bool zmien)
{
    for (int i = 0; i < rozmiarTabeli; i++)
    {
        cout << "start = (" << lotniska[i].poczatek.x << ", " << lotniska[i].poczatek.y << ") koniec = (" << lotniska[i].konec.x << ", " << lotniska[i].konec.y << ")" << endl;
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
    PoczatekIKonec *lotniska = (PoczatekIKonec *)malloc(0 * sizeof(PoczatekIKonec));
    for (int i = 0; i < bokA; i++)
    {
        cin >> pole[i];
    }
    // szukanie w poziomie (tak:__________ jebany dyslektyku)
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

                        rozmiarTabeli++;
                        lotniska = (PoczatekIKonec *)realloc(lotniska, rozmiarTabeli * sizeof(PoczatekIKonec));
                        lotniska[rozmiarTabeli - 1].poczatek.y = y;
                        lotniska[rozmiarTabeli - 1].poczatek.x = x;
                    }

                    if (x == bokA - 1)
                    {
                        lotniska[rozmiarTabeli - 1].konec.y = y;
                        lotniska[rozmiarTabeli - 1].konec.x = x;
                    }
                }
                else
                {
                    rozmiarTabeli++;
                    lotniska = (PoczatekIKonec *)realloc(lotniska, rozmiarTabeli * sizeof(PoczatekIKonec));
                    lotniska[rozmiarTabeli - 1].poczatek.y = y;
                    lotniska[rozmiarTabeli - 1].poczatek.x = x;
                }
            }
            else
            {
                if (x > 0)
                {
                    if (pole[y][x - 1] == '.')
                    {
                        lotniska[rozmiarTabeli - 1].konec.y = y;
                        lotniska[rozmiarTabeli - 1].konec.x = x - 1;
                    }
                }
            }
        }
    }
    // szukanie w pionie (tak inaczej ze zgory na dol jebany dyslektyku)
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
                        rozmiarTabeli++;
                        lotniska = (PoczatekIKonec *)realloc(lotniska, rozmiarTabeli * sizeof(PoczatekIKonec));
                        lotniska[rozmiarTabeli - 1].poczatek.y = y;
                        lotniska[rozmiarTabeli - 1].poczatek.x = x;
                    }

                    if (y == bokA - 1)
                    {
                        lotniska[rozmiarTabeli - 1].konec.y = y;
                        lotniska[rozmiarTabeli - 1].konec.x = x;
                    }
                }
                else
                {
                    rozmiarTabeli++;
                    lotniska = (PoczatekIKonec *)realloc(lotniska, rozmiarTabeli * sizeof(PoczatekIKonec));
                    lotniska[rozmiarTabeli - 1].poczatek.y = y;
                    lotniska[rozmiarTabeli - 1].poczatek.x = x;
                }
            }
            else
            {
                if (y > 0)
                {
                    if (pole[y - 1][x] == '.')
                    {
                        lotniska[rozmiarTabeli - 1].konec.y = y - 1;
                        lotniska[rozmiarTabeli - 1].konec.x = x;
                    }
                }
            }
        }
    }
    bool zmien = true;
    // drukowanie tego co mamy
    drukuj(lotniska, rozmiarTabeli,zmien);
}