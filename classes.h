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

using namespace std;

class Kontakt {
    public:
        string nazev; //nazev kontaktu např školství
        int pocetKontaktu; //kolik kontaktů daného typu osoba má
        double koeficient; //jaký je koeficient rizika přenosu (default 1, ale např sťísněné prostory, atd. může být větší)
        Kontakt(string nazev,int pocetKontaktu, double koeficient);
};

enum StavyPopulace{
    nenakazeni = 0,
    vystaveni = 1,
    nakazeni = 2,
    naUmreni = 3,
    mrtvi = 4,
    detekovaniNakazeni = 5,
    nedetekovaniNakazeni = 6,
    detekovaniUzdraveni = 7,
    nedetekovaniUzdraveni = 8,
    vNemocnici =9
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
    StavPopulace(StavyPopulace nazevStavu, int den0);
    StavyPopulace nazevStavu;
    vector<int> den; //pocel lidi v danem stavu v kazdem dnu
};

class TypPopulace {
    public:
        TypPopulace(TypyPopulace nazevTypu, int pocetNenakazenych, float mortalita);
        TypyPopulace nazevTypu;
        vector<StavPopulace> stavy; //stavy ve kterych lide mohou byt
        vector<Kontakt> kontakty; //kontakty ktere lidi denne podstoupi
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