/**
 *   @project:  IMS
 *   @file: classes.cpp
 *   @author: Šimon Pomykal (xpomyk04), Zbyněk Lamakčka (xlamac00)
 *   @date: 5.12.2020
*/

#include "classes.h"

StavPopulace::StavPopulace(StavyPopulace nazevStavu, int den0, int delkaPrechodu){
    this->nazevStavu = nazevStavu;
    this->den.push_back(den0);
    
    for (int i = 0; i < delkaPrechodu; i++)
    {
        this->prechod.push(0);
    }
}

TypPopulace::TypPopulace(TypyPopulace nazevTypu, int pocetNenakazenych, float mortalita, vector<int> kontakty){
    this->mortalita = mortalita;
    this->nazevTypu = nazevTypu;
    
    this->stavy.push_back(StavPopulace(zdravi,pocetNenakazenych,0));
    this->stavy.push_back(StavPopulace(nakazeni,0,14));
    this->stavy.push_back(StavPopulace(mrtvi,0,0));
    this->stavy.push_back(StavPopulace(imuni,0,90));

    this->kontakty = kontakty;

}

Populace::Populace(){
    this->pocetDni = 0;
    this->typyPopulace.push_back(TypPopulace(Predskolni,        340'400,    0.0,    vector<int>{0, 0, 0, 0, 0, 0, 0}));
    this->typyPopulace.push_back(TypPopulace(materskaSkola,     364'909,    0.0,    vector<int>{5, 1, 0, 0, 1, 0, 0}));
    this->typyPopulace.push_back(TypPopulace(zakladniSkola,     952'946,    0.2,    vector<int>{6, 2, 1, 1, 1, 0, 0}));
    this->typyPopulace.push_back(TypPopulace(stredniSkola,      427'674,    0.2,    vector<int>{5, 2, 1, 1, 1, 1, 2}));
    this->typyPopulace.push_back(TypPopulace(vysokaSkola,       306'869,    0.2,    vector<int>{3, 1, 1, 1, 1, 1, 2}));
    this->typyPopulace.push_back(TypPopulace(mladsiPracujici,   2'761'821,  0.2,    vector<int>{0, 2, 2, 2, 1, 1, 2}));
    this->typyPopulace.push_back(TypPopulace(starsiPracujici,   3'041'614,  0.85,   vector<int>{0, 2, 2, 1, 2, 1, 1}));
    this->typyPopulace.push_back(TypPopulace(duchodci,          2'403'767,  8.8,    vector<int>{0, 2, 1, 0, 1, 1, 0}));
}


int Populace::getstav(StavyPopulace nazevStavu, int cisloDne){
    int suma = 0;

    for(TypPopulace typ : this->typyPopulace)
    {
        for(StavPopulace stav : typ.stavy){
            if(stav.nazevStavu == nazevStavu)
            {
                suma += stav.den[cisloDne];
            }
        }
    }

    return suma;
}

void StavPopulace::pridatDen(int hodnota){
        int predchoziNE = this->den.back();
        this->den.push_back(predchoziNE + hodnota);
}

