/**
 *   @project:  IMS
 *   @file: model.cpp
 *   @author: Šimon Pomykal (xpomyk04), Zbyněk Lamakčka (xlamac00)
 *   @date: 5.12.2020
*/

#include "classes.h"
#include <ctime>

#define RIZIKO_PRENOSU 4.0 //šance přenosu v procentech
#define POCET_TYPU_KONTAKTU 9 // zmenit
#define POCET_TYPU_POPULACE 8
#define POCET_STAVU_POPULACE 4
#define POCET_TYPU_KONTAKTU 7

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
void popInfo(Populace pop, int den){
    cout << "-----------------------------------------------------\n";
    
    cout << "Populace - zdravi: " << pop.getstav(zdravi, den) << '\n';
    cout << "Populace - nakazeni: " << pop.getstav(nakazeni, den) << '\n';
    cout << "Populace - mrtvi: " << pop.getstav(mrtvi, den) << '\n';
    cout << "Populace - imuni: " << pop.getstav(imuni, den) << '\n';

    

    for(TypPopulace typ: pop.typyPopulace){
        cout << '\n';
        cout << typ.nazevTypu << '\n';
        cout << "   zdravi: " << typ.stavy[zdravi].den[den] << '\n';
        cout << "   nakazeni: " << typ.stavy[nakazeni].den[den] << '\n';
        cout << "   mrtvi:: " << typ.stavy[mrtvi].den[den] << '\n';
        cout << "   detekovaniUzdraveni: " << typ.stavy[imuni].den[den] << '\n';
        cout << "   mortalita: " << typ.mortalita << '\n';
    }

    cout << "-----------------------------------------------------\n";
} 

/**
 * Funkce která vrátí True s šancí x, jinak vrátí false (max 2 desetinná místa!!!)
 * @param x šance v procentech
 */
bool chance(float x ){
    float max = 10000;
    x = 100*x;
    int nahodneCislo = rand() % 10000;
    //cout << x << " " << nahodneCislo << "\n";

    if(nahodneCislo <= x){
        //cout << "true\n";
        return true;
    }

    else{
        //cout << "false\n";
        return false;
    }
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

void denniZmena(Populace &pop){

    vector<int> prirustek_nakazeni(POCET_TYPU_POPULACE,0);
    vector<int> prirustek_zdravi(POCET_TYPU_POPULACE,0);
    vector<int> prirustek_imuni(POCET_TYPU_POPULACE,0);
    vector<int> prirustek_mrtvi(POCET_TYPU_POPULACE,0);

    /* Nakaženi populace */
    //typy populace
    for(TypPopulace &popTyp : pop.typyPopulace){
        //nakazeni
        for(int i = popTyp.stavy[nakazeni].den.back(); i > 0; i--){
            //typykontaktu
            for(int j = 0; j < POCET_TYPU_KONTAKTU;j++){
                //pocetkontaktu
                for (int y = 0; y < popTyp.kontakty[j];y++){
                    if(chance(RIZIKO_PRENOSU)){
                        int index = chooseOneFromEight(vector<int>{12,12,13,13,13,13,12,12});
                        prirustek_nakazeni[index] += 1;
                        prirustek_zdravi[index] -= 1;
                    }
                }
            }
            
        }
    }

    /*Přechody mezi stavy dané časem*/
    for(TypPopulace &popTyp : pop.typyPopulace){
        // nakažení -> imuni (delka nemoci)
        //           -> mrtví
        int pocet = popTyp.stavy[nakazeni].prechod.front; 
        for (int i = 0; i < pocet; i++)
        {
            prirustek_nakazeni[popTyp.nazevTypu] -= 1;
            //umrti
            if(chance(popTyp.mortalita)){
                prirustek_mrtvi[popTyp.nazevTypu] += 1;
            }

            else{
                prirustek_imuni[popTyp.nazevTypu] += 1;
            }
        }
        
        popTyp.stavy[nakazeni].prechod.pop; 

        // imnuni -> zdravi (delka imunity)
        prirustek_zdravi[popTyp.nazevTypu] += popTyp.stavy[imuni].prechod.front;
        prirustek_imuni[popTyp.nazevTypu] -= popTyp.stavy[imuni].prechod.front;
        popTyp.stavy[imuni].prechod.pop; 
    }

    /*PUSH front*/
    for(TypPopulace &popTyp : pop.typyPopulace){
        popTyp.stavy[nakazeni].prechod.push(prirustek_nakazeni[popTyp.nazevTypu]);
        popTyp.stavy[imuni].prechod.push(prirustek_imuni[popTyp.nazevTypu]);

        popTyp.stavy[zdravi].pridatDen(prirustek_zdravi[popTyp.nazevTypu]);
        popTyp.stavy[nakazeni].pridatDen(prirustek_nakazeni[popTyp.nazevTypu]);
        popTyp.stavy[imuni].pridatDen(prirustek_imuni[popTyp.nazevTypu]);
        popTyp.stavy[mrtvi].pridatDen(prirustek_mrtvi[popTyp.nazevTypu]);
    }

    pop.pocetDni++;
}

int main(int argc, char* argv[]){

    /* initialize random seed: */
    srand (time(NULL));

    Populace ceskaPopulace = Populace();

    ceskaPopulace.typyPopulace[mladsiPracujici].stavy[nakazeni][ceskaPopulace.pocetDni] = 1;
    popInfo(ceskaPopulace,0);

    for (int i = 0; i < 30; i++){
        denniZmena(ceskaPopulace);
        cout << "den " << ceskaPopulace.pocetDni << '\n';
        cout << "Populace - zdravi: " << ceskaPopulace.getstav(zdravi, ceskaPopulace.pocetDni) << '\n';
        cout << "Populace - nakazeni: " << ceskaPopulace.getstav(nakazeni, ceskaPopulace.pocetDni) << '\n';
    }
    
    //denniZmena(ceskaPopulace);
    //popInfo(ceskaPopulace,0);

    return 0;
}