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

/*
    Předškolní věk (0-4) (340_400)

	Studenti  (2_052_398)
		MS (364_909) viz [1]
		ZS (952_946) viz [1]
		SŠ (423_838) + Konzervator (3_836) viz [1]
		VŠ (288_915) + VOS (17_954) viz [1] a [4]

	Produktivní věk (5_803_435)
		mladší 2_761_821
		starší 3_041_614 (40-65) [3]

	Důchodci(65+) (2_403_767) [2]
*/

class TypPopulace {
    public:
        vector<int> pocetLidi;
        int poctyKontaktu[POCET_TYPU_KONTAKTU]; // Pocet kontaktu pro jednotlive typy
        vector<int> pocetNakazenych; // Pocet nakazenych v jednotlivych dnech,
        double mortalita;
        vector<int> pocetVylecenych;
        vector<int> pocetMrtvych;
};

class TypKontaktu {
    public:
        double nakazeniTypuPopulace[POCET_TYPU_POPULACE]; // S 
};

class Populace {       
  public:             
    vector<TypPopulace> typyPopulace;

    int getPocetNakazenych();
    int getPocetLidi();
    int getPocetVylecenych();
    int getPocetMrtvych();
};

// enum na typy populace

#endif