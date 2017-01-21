#include "datum.h"
#include <ctime> //za sistemski datum
#include <cstdlib> //za funkciju exit
#include <string> //zbog teksta...
#include <sstream> //... i konverzije broja u tekst

// PREPORUKA: sve staticke promenljive definisati u .cpp
const unsigned short Datum::dani[2][12] = {
    {31,28,31,30,31,30,31,31,30,31,30,31},
    {31,29,31,30,31,30,31,31,30,31,30,31}
};

const string Datum::imeD[7] = {"ponedeljak","utorak","sreda","cetvrtak","petak","subota",
    "nedelja"};

const string Datum::imeM[12] = {"januar","februar","mart","april","maj","juni","jul","avgust",
    "septembar","oktobar","novembar","decembar"};

Datum::Datum(unsigned short d, unsigned short m, unsigned short g)
{
    if(postoji(d, m, g)) {
        m_d = d; m_m = m; m_g = g;}
    else // postavi vazeci datum
        SetSysDate();
}

void Datum::SetSysDate() {
    // koristi se definisano u ctime
    time_t rawtime;
    tm *dt;
    time(&rawtime);
    dt = localtime(&rawtime);
    m_d = dt->tm_mday;
    m_m = 1 + dt->tm_mon;
    m_g = 1900 + dt->tm_year;
}

Datum::Datum() {
    SetSysDate();
}

bool Datum::postoji(unsigned short d, unsigned short m, unsigned short g) {
// m_d = Setd(d); m_m = Setm(m); m_g = Setg(g); ne moze u statickoj f-ji!
// jer nema objekta - staticka funkcija se ne poziva iz objekta,
// vec direktno iz klase -> mora da se ispitaju g, m, d > 0
    return g > 0 && m > 0 && d > 0 && m <= 12 && d <= dani[prestupna(g)][m-1];
}

string Datum::poredi(Datum& dat) {
    ostringstream rezultat; // da bi licilo na cout - automatski prikazalo brojeve
    unsigned int d1 = m_d, m1 = m_m, g1 = m_g; // za datum primerka klase
    // od datuma dat sa kojim se poredi primerak klase
    unsigned int d2 = dat.Getd(), m2 = dat.Getm(), g2 = dat.Getg();;
    if(d1 < d2) { //prebaci u prethodni mesec
        d1 += dani[prestupna(g1)][m1-2]; //za m1 - 1
        m1--;
    }
    if(m1 < m2) { //dodaj 12 meseci i smanji g1 za 1
        m1 += 12;
        g1--;
    }
    rezultat << g1 - g2 << "god., " << m1 - m2 << "mes. i " << d1 - d2 << " dana";
    return rezultat.str();
}

bool Datum::pre(const Datum& dat) const {
    bool rez;
    rez = (m_g  == dat.Getg());
    if (rez)
        rez = (m_m == dat.Getm());
    else
        return (m_g  < dat.Getg());
    if (rez)
        return (m_d < dat.Getd());
    else
        return (m_m < dat.Getm());
}

Datum Datum::citajS() {
    unsigned short d, m, g;
    while(true) {
        cin >> d >> m >> g;
        if(postoji(d, m, g)) break;
        cout << endl << "Neispravan datum. Unesite ponovo:";
    }
    return Datum(d, m, g);
}

void Datum::prikaz(string format /*m - broj meseca; mm - ime mes.*/) { /*sa vodecom nulom*/
        if(format == "m")
            cout << m_d/10 << m_d%10 << '.' << m_m/10 << m_m%10 << '.' << m_g << '.';
        else
            cout << m_d/10 << m_d%10 << '.' << imeM[m_m - 1] << ' ' << m_g << '.';
    }

unsigned short Datum::danaDoMes(unsigned short m, unsigned short g) {
    unsigned short sum = 0;
    if(m <= 12) {
        for(unsigned short i = 0; i < m - 1; ++i)
            sum += dani[prestupna(g)][i];
        return sum;
    }
    return 0;
}

long Datum::ukDan() const {
    unsigned short g = m_g - 1;
    return g*365L + g/4 - g/100 + g/400 + danUGod();
}

void Datum::sutra() {
    if(m_d < duzMes()) m_d++;
    else {
        m_d = 1;
        if(m_m < 12) m_m++;
        else {m_m = 1; m_g++;}
    }
}

void Datum::juce() {
    if(m_d > 1) m_d--;
    else {
        if(m_m > 1) m_m--;
        else {m_m = 12; m_g--;}
        m_d = duzMes();
    }
}

void Datum::dodaj(unsigned short d) { for(unsigned short i = 0; i < d; i++) sutra();}

void Datum::oduzmi(unsigned short d) { for(unsigned short i = 0; i < d; i++) juce();}
