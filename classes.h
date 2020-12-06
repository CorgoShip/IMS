/**
 *   @project:  IMS
 *   @file: classes.h 
 *   @author: Šimon Pomykal (xpomyk04), Zbyněk Lamakčka (xlamac00)
 *   @date: 5.12.2020
*/

#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include <queue> 

using namespace std;

enum StavyPopulace{
    zdravi = 0,
    nakazeni = 1,
    mrtvi = 2,
    imuni = 3
};

enum TypyPopulace{
    Predskolni = 0,
    materskaSkola = 1,
    zakladniSkola = 2,
    stredniSkola = 3,
    vysokaSkola = 4,
    mladsiPracujici = 5,
    starsiPracujici = 6,
    duchodci = 7
};

class StavPopulace {
    public:
    StavPopulace(StavyPopulace nazevStavu, int den0, int delkaPrechodu);
    StavyPopulace nazevStavu;
    vector<int> den; //pocel lidi v danem stavu v kazdem dnu
    queue<int> prechod;
    void pridatDen(int hodnota, StavyPopulace nazevStavu);
};

class TypPopulace {
    public:
        TypPopulace(TypyPopulace nazevTypu, int pocetNenakazenych, float mortalita,vector<int> kontakty);
        TypyPopulace nazevTypu;
        vector<StavPopulace> stavy; //stavy ve kterych lide mohou byt
        vector<int> kontakty; //kontakty ktere lidi denne podstoupi
        double mortalita; // s jakou pravdepodobnsti nakazeny pujde do skupiny naUmreni
};

class Populace {       
  public:             
    vector<TypPopulace> typyPopulace; //typy populace
    int pocetDni; //kolik dni vyvoje je zaznamenano

    Populace();
    int getstav(StavyPopulace nazevStavu, int cisloDne);
};

// enum na typy populace

#endif