/**
 *   @project: IMS (Discord bot)
 *   @file: extractor.h 
 *   @author: Šimon Pomykal (xpomyk04)
 *   @date: 18.11.2020
*/

#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>

#define POCET_TYPU_KONTAKTU 8 // zmenit
#define POCET_TYPU_POPULACE 8

using namespace std;

class TypPopulace {
    public:
        string nazev;
        TypPopulace(string jmeno, int pocetNenakazenych, float mortalita);
        vector<int> nenakazeni; // lide, kteri se mohou nakazit COVID
        vector<int> vystaveni; // lide, kteri maji COVID v inkubacni dobe
        vector<int> nakazeni; // lide, u kterych COVID propukl
        
        vector<int> naUmreni; //lide, kteri jsou v nemocnici a na konci nemoci umrou na COVID
        vector<int> mrtvi; // lide, kteri umreli na COVID

        vector<int> detekovaniNakazeni; // lide, kteri maji COVID, jsou detekovani siri tedy COVID s mensi pravdepodobnosti (karantena, omezeni atd.)
        vector<int> detekovaniUzdraveni; // lide, kteri prodelali COVID, byli detekovani a jsou jiz imunni

        vector<int> nedetekovaniNakazeni; // lide, kteri maji COVID, nejsou detekovani a siri tedy COVID s normlani pravdepodobnosti
        vector<int> nedetekovaniUzdraveni; // nedetekovani lide, kteri uz jsou uzdraveni a jsou imunni

        int poctyKontaktu[POCET_TYPU_KONTAKTU]; // Pocet kontaktu pro jednotlive typy
        double mortalita; // s jakou pravdepodobnsti kde
};

class TypKontaktu {
    public:
        double nakazeniTypuPopulace[POCET_TYPU_POPULACE]; // S 
};

class Populace {       
  public:             
    vector<TypPopulace> typyPopulace;

    Populace();
    Populace(vector<TypPopulace> typy);
    int getNenakazeni();
    int getVystaveni();
    int getNakazeni();
    int getNaUmreni();
    int getMrtvi();
    int getDetekovaniNakazeni();
    int getDetekovaniUzdraveni();
    int getNedetekovaniNakazeni();
    int getNedetekovaniUzdraveni();
};

// enum na typy populace

#endif