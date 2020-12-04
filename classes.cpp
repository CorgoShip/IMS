#include "classes.h"

TypPopulace::TypPopulace(string jmeno, int pocetNenakazenych, float mortalita){
    nazev = jmeno;
    this->mortalita = mortalita;
    nenakazeni.push_back(pocetNenakazenych);
    vystaveni.push_back(0);
    nakazeni.push_back(0);
    naUmreni.push_back(0);
    mrtvi.push_back(0);
    detekovaniNakazeni.push_back(0);
    detekovaniUzdraveni.push_back(0);
    nedetekovaniNakazeni.push_back(0);
    nedetekovaniUzdraveni.push_back(0);
}

Populace::Populace(){
    
}

Populace::Populace(vector<TypPopulace> typy){
    typyPopulace = typy;
}

int Populace::getNenakazeni(){
        int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.nenakazeni.back();
    }    

    return suma;
}

int Populace::getVystaveni(){
            int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.vystaveni.back();
    }    

    return suma;
}

int Populace::getNakazeni(){
            int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.nakazeni.back();
    }    

    return suma;
}

int Populace::getNaUmreni(){
            int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.naUmreni.back();
    }    

    return suma;
}

int Populace::getMrtvi(){
            int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.mrtvi.back();
    }    

    return suma;
}

int Populace::getDetekovaniNakazeni(){
            int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.detekovaniNakazeni.back();
    }    

    return suma;
}

int Populace::getDetekovaniUzdraveni(){
            int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.detekovaniUzdraveni.back();
    }    

    return suma;
}

int Populace::getNedetekovaniNakazeni(){
            int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.nedetekovaniNakazeni.back();
    }    

    return suma;
}

int Populace::getNedetekovaniUzdraveni(){
            int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.nedetekovaniUzdraveni.back();
    }    

    return suma;
}


