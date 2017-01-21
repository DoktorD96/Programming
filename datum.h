#ifndef DATUM_H
#define DATUM_H

#include <iostream>
//#include <string> nije neophodno
using namespace std;
class Datum
{
    public:
        //prva varijanta konstruktora (moze neograniceno)
        Datum(unsigned short d, unsigned short m, unsigned short g);
        //druga varijanta - preopterecen konstruktor, za sistemski datum
        Datum();
        static const unsigned short dani[2][12]; // brojevi dana po mesecima u godini
        static const string imeD[7], imeM[12]; // Imena dana u sedmici i meseca u godini
        unsigned short Getd() const { return m_d; }
        void Setd(unsigned short val) { m_d = val; }
        unsigned short Getm() const { return m_m; }
        void Setm(unsigned short val) { m_m = val; }
        unsigned short Getg() const { return m_g; }
        void Setg(unsigned short val) { m_g = val; }
        void SetSysDate(); //postavlja sistemski datum
        string poredi(Datum& dat); // dat u proslosti
        bool pre(const Datum& dat) const; // da li je primerak klase pre, < dat
        //provera da li postoji datum
        static bool postoji(unsigned short d, unsigned short m, unsigned short g);
        static bool prestupna(unsigned short g) {return g%4 == 0 && g%100 != 0 || g%400 == 0;}
        bool prestupna() const {return prestupna(m_g);/*poziva staticku funkciju*/}
        bool citaj() { // pokusa se inline kada postoji implementacija u .h !
            unsigned short d, m, g;
            cin >> d >> m >> g;
            if(!postoji(d, m, g)) return false;
            *this = Datum(d, m, g);
            return true;
        }
        static Datum citajS();
        void prikaz(string format = "m" /*m - broj meseca; mm - ime mes.*/);
        unsigned short danUGod() const { return danaDoMes(m_m, m_g) + m_d;}
        unsigned short danUSedm() const { return (ukDan() + 6) % 7 + 1;}
        unsigned short duzMes() const { return dani[prestupna()][m_m - 1];}
        void sutra(); // pretvara tekuci u sutrasnji datum
        void juce(); // pretvara tekuci u jucerasnji datum
        void dodaj(unsigned short d); // pomeranje d dana unapred
        void oduzmi(unsigned short d); // pomeranje d dana unazad
        long ukDan() const; // redni broj dana od 01.01.0001.
        friend long razlikaD(Datum dat1, Datum dat2) { return dat1.ukDan() - dat2.ukDan();}
        string imeDan() const { return imeD[danUSedm() - 1];} // ime dana u sedmici
        string imeMes() const { return imeM[m_m - 1];} // ime dana u sedmici
    protected:
    private:
        unsigned short m_d;
        unsigned short m_m;
        unsigned short m_g;
        static unsigned short danaDoMes(unsigned short m, unsigned short g);
};

#endif // DATUM_H
