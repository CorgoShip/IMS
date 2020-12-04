#include "classes.h"

int Populace::getPocetNakazenych(){
    int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.pocetNakazenych.back();
    }    

    return suma;
}


int Populace::getPocetLidi(){
    int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.pocetLidi.back();
    }    

    return suma;
}

int Populace::getPocetVylecenych(){
    int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.pocetVylecenych.back();
    }    

    return suma;
}

int Populace::getPocetMrtvych(){
    int suma = 0;

    for (auto item : this->typyPopulace)
    {
        suma += item.pocetMrtvych.back();
    }    

    return suma;
}

