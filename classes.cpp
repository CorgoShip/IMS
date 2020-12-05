/**
 *   @project:  IMS
 *   @file: classes.cpp
 *   @author: Šimon Pomykal (xpomyk04), Zbyněk Lamakčka (xlamac00)
 *   @date: 5.12.2020
*/

#include "classes.h"

Kontakt::Kontakt(string nazev,int pocetKontaktu, double koeficient){
    this->nazev = nazev;
    this->pocetKontaktu = pocetKontaktu;
    this->koeficient = koeficient;
}

StavPopulace::StavPopulace(StavyPopulace nazevStavu, int den0){
    this->nazevStavu = nazevStavu;
    this->den.push_back(den0);
}

TypPopulace::TypPopulace(TypyPopulace nazevTypu, int pocetNenakazenych, float mortalita){
    this->mortalita = mortalita;
    this->nazevTypu = nazevTypu;
    
    this->stavy.push_back(StavPopulace(nenakazeni,pocetNenakazenych));
    this->stavy.push_back(StavPopulace(vystaveni,0));
    this->stavy.push_back(StavPopulace(nakazeni,0));
    this->stavy.push_back(StavPopulace(naUmreni,0));
    this->stavy.push_back(StavPopulace(mrtvi,0));
    this->stavy.push_back(StavPopulace(detekovaniNakazeni,0));
    this->stavy.push_back(StavPopulace(nedetekovaniNakazeni,0));
    this->stavy.push_back(StavPopulace(detekovaniUzdraveni,0));
    this->stavy.push_back(StavPopulace(nedetekovaniUzdraveni,0));
    this->stavy.push_back(StavPopulace(vNemocnici,0));
}

Populace::Populace(){
    this->pocetDni = 1;
    this->typyPopulace.push_back(TypPopulace(Predskolni,340'400, 0.0));
    this->typyPopulace.push_back(TypPopulace (materskaSkola,364'909, 0.0));
    this->typyPopulace.push_back(TypPopulace(zakladniSkola,952'946, 0.2));
    this->typyPopulace.push_back(TypPopulace(stredniSkola,427'674, 0.2));
    this->typyPopulace.push_back(TypPopulace(vysokaSkola,306'869, 0.2));
    this->typyPopulace.push_back(TypPopulace(mladsiPracujici,2'761'821, 0.2));
    this->typyPopulace.push_back(TypPopulace(starsiPracujici,3'041'614, 0.85));
    this->typyPopulace.push_back(TypPopulace(duchodci,2'403'767, 8.8));
}


int Populace::getstav(StavyPopulace nazevStavu, int cisloDne){
        int suma = 0;

    for(TypPopulace typ : this->typyPopulace)
    {
        for(StavPopulace stav : typ.stavy){
            if(stav.nazevStavu == nazevStavu)
            {
                suma += stav.den[cisloDne-1];
            }
        }
    }

    return suma;
}


