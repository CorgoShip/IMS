/**
 *   @project:  IMS
 *   @file: model.cpp
 *   @author: Šimon Pomykal (xpomyk04), Zbyněk Lamakčka (xlamac00)
 *   @date: 5.12.2020
*/

#include "classes.h"
#include <ctime>

#define RIZIKO_PRENOSU 4 //šance přenosu v procentech
#define POCET_TYPU_KONTAKTU 9 // zmenit
#define POCET_TYPU_POPULACE 8
#define POCET_STAVU_POPULACE 10

/*
    Předškolní věk  (340_400)

	Studenti  (2_052_398)
		MS (364_909) viz [1]
		ZS (952_946) viz [1]
		SS (423_838) + Konzervator (3_836) viz [1]
		VS (288_915) + VOS (17_954) viz [1] a [4]

	Produktivní věk (5_803_435)
		mladší (20-39) 2_761_821
		starší (40-64) 3_041_614 (40-65) [3]

	Důchodci(65+) (2_403_767) [2]
*/

/*     TODO: zkontrolovat, upravit, hlavne u duchodcu a 40-64
        mortality by age:
            0-9: 0
            10-20:0.2%
            0-39: 0.2%
            40-64: 0,85%
            65+: 8,8% */

/* Tato funkce je jenom na debugg */
/* void popInfo(Populace pop){
    cout << "-----------------------------------------------------\n";
    
    cout << "Populace - nenakazeni: " << pop.getNenakazeni() << '\n';
    cout << "Populace - vystaveni: " << pop.getVystaveni() << '\n';
    cout << "Populace - nakazeni: " << pop.getNakazeni() << '\n';
    cout << "Populace - detekovaniNakazeni: " << pop.getDetekovaniNakazeni() << '\n';
    cout << "Populace - nedetekovaniNakazeni: " << pop.getNedetekovaniNakazeni() << '\n';
    cout << "Populace - naUmreni: " << pop.getNaUmreni() << '\n';
    cout << "Populace - mrtvi: " << pop.getMrtvi() << '\n';
    cout << "Populace - detekovaniUzdraveni: " << pop.getDetekovaniUzdraveni() << '\n';
    cout << "Populace - nedetekovaniUzdraveni: " << pop.getNedetekovaniUzdraveni() << '\n';
    

    for(auto item : pop.typyPopulace){
        cout << '\n';
        cout << item.nazev << '\n';
        cout << "   nenakazeni: " << item.nenakazeni.back() << '\n';
        cout << "   vystaveni: " << item.vystaveni.back() << '\n';
        cout << "   nakazeni: " << item.nakazeni.back() << '\n';
        cout << "   detekovaniNakazeni: " << item.detekovaniNakazeni.back() << '\n';
        cout << "   nedetekovaniNakazeni: " << item.nedetekovaniNakazeni.back() << '\n';
        cout << "   naUmreni: " << item.naUmreni.back() << '\n';
        cout << "   mrtvi:: " << item.mrtvi.back() << '\n';
        cout << "   detekovaniUzdraveni: " << item.detekovaniUzdraveni.back() << '\n';
        cout << "   nedetekovaniUzdraveni: " << item.nedetekovaniUzdraveni.back() << '\n';
        cout << "   mortalita: " << item.mortalita << '\n';
    }

    cout << "-----------------------------------------------------\n";
} */

/**
 * Funkce která vrátí True s šancí x, jinak vrátí false (max 2 desetinná místa!!!)
 * @param x šance v procentech
 */
bool chance(float x ){
    float max = 10000;
    x = 100*x;
    int nahodneCislo = rand() % 10000;
    cout << x << " " << nahodneCislo << "\n";

    if(nahodneCislo <= x){
        cout << "true\n";
        return true;
    }

    else{
        cout << "false\n";
        return false;
    }
}

// Funkce vraci soucet prvnich n hodnot ve Vectoru, vector musi obsahovat inty!!
int getVectorSum(vector<int> vec, int pocetHodnot){

    if (vec.size() < pocetHodnot)
    {
        cout << "ERROR: getVectorSum: Vector nesmi byt kratsi nez pocet scitanych hodnot\n";
        exit(1);
    }

    int sum = 0;

    for (int i = 0; i < pocetHodnot; i++)
    {
        sum += vec[i];
    }
    
    return sum;    
}

/**
 *  Funkce vrati index nakazene skupiny
 * @param vec Vektor sanci nakazeni urcite skupiny
 */
int chooseOneFromEight(vector<int> vec){
    int nahodneCislo = rand() % 100;

    // vec.

    if (vec.size() != 8)
    {
        cout << "ERROR: chooseOneFromEight: Vector musi mit delku 8\n";
        exit(1);
    }
    
    if (nahodneCislo < getVectorSum(vec, 1))
    {
        return 0;
    }
    else if (nahodneCislo < getVectorSum(vec, 2))
    {
        return 1;
    }
    else if (nahodneCislo < getVectorSum(vec, 3))
    {
        return 2;
    }
    else if (nahodneCislo < getVectorSum(vec, 4))
    {
        return 3;
    }
    else if (nahodneCislo < getVectorSum(vec, 5))
    {
        return 4;
    }
    else if (nahodneCislo < getVectorSum(vec, 6))
    {
        return 5;
    }
    else if (nahodneCislo < getVectorSum(vec, 7))
    {
        return 6;
    }
    else if (nahodneCislo < getVectorSum(vec, 8))
    {
        return 7;
    }
    else
    {
        cout << "ERROR: chooseOneFromEight: Vysla nam pravepodobnost mimo rozsah\n";
        exit(1);
    }
}

/**
 * Změna v populaci za jeden den
 * @param pop populace
 */

/* void denniZmena(Populace &pop){
    for(auto popTyp : pop.typyPopulace){
        switch (popTyp.nazev){
            case vystaveni:
                break;
            case nakazeni:
                break;
            

            case nenakazeni:
            default:
                break;
        }
    }
} */

int main(int argc, char* argv[]){

    /* initialize random seed: */
    srand (time(NULL));

    Populace ceskaPopulace = Populace();
    cout << "celkem nenakazeni:" << ceskaPopulace.getstav(nenakazeni,1) << '\n';


    vector<int> test{10, 10, 20, 10, 30, 10, 5, 5};
    vector<int> vysledky(8, 0);
    // test.push_back(5);
    for (size_t i = 0; i < 1000; i++)
    {
        int result = chooseOneFromEight(test);
        vysledky[result]++;

    }
    
    cout << "VYSLEDKY:\n";
    for (auto item : vysledky)
    {
        cout << item << "\n";
    }
    
    
    //denniZmena(ceskaPopulace);
    //popInfo(ceskaPopulace);

    return 0;
}