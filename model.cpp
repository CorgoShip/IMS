/**
 *   @project:  IMS
 *   @file: model.cpp
 *   @author: Šimon Pomykal (xpomyk04), Zbyněk Lamakčka (xlamac00)
 *   @date: 5.12.2020
*/

#include "classes.h"
#include <ctime>
#include <fstream>
#include <iterator>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <deque>

#define RIZIKO_PRENOSU 3 //šance přenosu v procentech
#define POCET_TYPU_POPULACE 8
#define POCET_STAVU_POPULACE 4
#define POCET_TYPU_KONTAKTU 7

/* vector<vector<double>> pes {
    {1.0,0.95,0.9,0.9,0.85,0.80},
    {1.0,0.95,0.80,0.70,0.10,0.05},
    {1.0,1.0,0.5,0.25,0,0},
    {1.0,0.8,0.6,0.2,0.1,0.05},
    {1.0,0.85,0.80,0.75,0,0},
    {1.0,0.95,0.5,0.3,0.13,0.8},
    {1.0,0.9,0.8,0.5,0.05,0.05}
} */

/* Tato funkce je jenom na debugg */


void vystup(Populace pop ,vector<int> pes,string folder){

    //vytvoreni slozky
    if (mkdir(folder.c_str(),0) == 0){
        chmod(folder.c_str(),0775);
    }

    //celkovy pocet nakazenych
    vector<int> pocetNakazenych;
    for(int i = 0; i <= pop.pocetDni; i++){
        pocetNakazenych.push_back(pop.getstav(nakazeni,i));
    }


    ofstream outfile;
    outfile.open(folder + "/celkovy_pocet_nakazenych.csv");
    outfile << "Počet nakažených" << '\n';
    for(int value : pocetNakazenych){
        outfile << value << '\n';
    }

    outfile.close();

    //celkovy pocet zdravych
    vector<int> pocetZdravych;
    for(int i = 0; i <= pop.pocetDni; i++){
        pocetZdravych.push_back(pop.getstav(zdravi,i));
    }

    outfile.open(folder + "/celkovy_pocet_zdravych.csv");
    outfile << "Počet zdravých" << '\n';
    for(int value : pocetZdravych){
        outfile << value << '\n';
    }

    outfile.close();

    //celkovy pocet imunich
    vector<int> pocetImunich;
    for(int i = 0; i <= pop.pocetDni; i++){
        pocetImunich.push_back(pop.getstav(imuni,i));
    }

    outfile.open(folder + "/celkovy_pocet_imunich.csv");
    outfile << "Počet imunních" << '\n';
    for(int value : pocetImunich){
        outfile << value << '\n';
    }

    outfile.close();

    //celkovy pocet mrtvych
    vector<int> pocetMrtvch;
    for(int i = 0; i <= pop.pocetDni; i++){
        pocetMrtvch.push_back(pop.getstav(mrtvi,i));
    }

    outfile.open(folder + "/celkovy_mrtvych.csv");
    outfile << "Počet mrtvých" << '\n';
    for(int value : pocetMrtvch){
        outfile << value << '\n';
    }

    outfile.close();

    //histogram PES
    outfile.open(folder + "/PES_stav.csv");
    outfile << "Úrověn PES" << '\n';
    for(int value : pes){
        outfile << value << '\n';
    }

    outfile.close();

}

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
    float max = 10'000'000;
    x = 100'000*x;
    int nahodneCislo = rand() % 10'000'000;
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

int pes_vypocet(int prirustek, int prirustek65, double r_cislo, double pozitivita_pop){
    int score = 0;

    if (prirustek < 10)
    {
        score += 0;
    }
    else if (prirustek < 25)
    {
        score += 2;
    }
    else if (prirustek < 50)
    {
        score += 4;
    }
    else if (prirustek < 120)
    {
        score += 7;
    }
    else if (prirustek < 240)
    {
        score += 10;
    }
    else if (prirustek < 480)
    {
        score += 13;
    }
    else if (prirustek < 960)
    {
        score += 16;
    }
    else
    {
        score += 20;
    }


    if (prirustek65 < 10)
    {
        score += 0;
    }
    else if (prirustek65 < 25)
    {
        score += 2;
    }
    else if (prirustek65 < 50)
    {
        score += 4;
    }
    else if (prirustek65 < 120)
    {
        score += 7;
    }
    else if (prirustek65 < 240)
    {
        score += 10;
    }
    else if (prirustek65 < 480)
    {
        score += 13;
    }
    else if (prirustek65 < 960)
    {
        score += 16;
    }
    else
    {
        score += 20;
    }


    if (r_cislo < 0.8)
    {
        score += 0;
    }
    else if (r_cislo < 1.0)
    {
        score += 5;
    }
    else if (r_cislo < 1.2)
    {
        score += 10;
    }
    else if (r_cislo < 1.4)
    {
        score += 15;
    }
    else if (r_cislo < 1.6)
    {
        score += 20;
    }
    else if (r_cislo < 1.9)
    {
        score += 25;
    }
    else 
    {
        score += 30;
    }


    if (pozitivita_pop < 3)
    {
        score += 0;
    }
    else if (pozitivita_pop < 7)
    {
        score += 3;
    }
    else if (pozitivita_pop < 11)
    {
        score += 7;
    }
    else if (pozitivita_pop < 15)
    {
        score += 11;
    }
    else if (pozitivita_pop < 19)
    {
        score += 15;
    }
    else if (pozitivita_pop < 23)
    {
        score += 20;
    }
    else if (pozitivita_pop < 26)
    {
        score += 25;
    }
    else 
    {
        score += 30;
    }


    if (score < 21)
    {
        return 1;       
    }
    else if (score < 41)
    {
        return 2;
    }
    else if (score < 61)
    {
        return 3;
    }
    else if (score < 76)
    {
        return 4;
    }
    else
    {
        return 5;
    }
}



/**
 * Změna v populaci za jeden den
 * @param pop populace
 */
void denniZmena(Populace &pop, deque<int> &pes_prirustek,deque<int> &pes_prirustek65, int &posledni_prirustek, int &pes_hodnota){
    vector<vector<double>> pes {
    {1.0,0.95,0.9,0.9,0.85,0.80},
    {1.0,0.95,0.80,0.70,0.10,0.05},
    {1.0,1.0,0.5,0.25,0,0},
    {1.0,0.8,0.6,0.2,0.1,0.05},
    {1.0,0.85,0.80,0.75,0,0},
    {1.0,0.95,0.5,0.3,0.13,0.8},
    {1.0,0.9,0.8,0.5,0.05,0.05}
};

    double podilZdravych = pop.getstav(zdravi,pop.pocetDni) / 10600000.0;

    vector<int> prirustek_nakazeni(POCET_TYPU_POPULACE,0);
    vector<int> prirustek_zdravi(POCET_TYPU_POPULACE,0);
    vector<int> prirustek_imuni(POCET_TYPU_POPULACE,0);
    vector<int> prirustek_mrtvi(POCET_TYPU_POPULACE,0);

    //double procentoZdravych = pop.getstav(zdravi,0) / 10'600'600;
    //cout << "PROCENTO ZDRAVYCH" << procentoZdravych << '\n';

    /* Nakaženi populace */
    //typy populace
    for(TypPopulace &popTyp : pop.typyPopulace){
        //nakazeni
        for(int i = popTyp.stavy[nakazeni].den.back(); i > 0; i--){
            //typykontaktu
            for(int j = 0; j < POCET_TYPU_KONTAKTU;j++){
                //pocetkontaktu
                for (int y = 0; y < popTyp.kontakty[j];y++){
                    if(chance(RIZIKO_PRENOSU*podilZdravych*pes[j][pes_hodnota])){
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
        int pocet = popTyp.stavy[nakazeni].prechod.front(); 
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
        
        popTyp.stavy[nakazeni].prechod.pop(); 

        // imnuni -> zdravi (delka imunity)
        prirustek_zdravi[popTyp.nazevTypu] += popTyp.stavy[imuni].prechod.front();
        prirustek_imuni[popTyp.nazevTypu] -= popTyp.stavy[imuni].prechod.front();
        popTyp.stavy[imuni].prechod.pop(); 
    }

    //vypocet PES
    //1.
    int prirustek = getVectorSum(prirustek_nakazeni,8);
    pes_prirustek.push_back(prirustek);
    pes_prirustek.pop_front();
    
    int prirustek14 = 0;
    for(int value : pes_prirustek){
        prirustek14 += value;
    }

    //2.
    int prirustek65 = prirustek_nakazeni[duchodci];
    pes_prirustek65.push_back(prirustek65);
    pes_prirustek65.pop_front();

    int prirustek6514 = 0;
    for(int value : pes_prirustek65){
        prirustek6514 += value;
    }

    //3. 
    //cout << "---------------\n";
    //cout << prirustek << '\n';
    //cout << posledni_prirustek << '\n';


    double r_cislo;
    if(posledni_prirustek == 0){
        r_cislo = prirustek;
    }
    else{
        r_cislo = prirustek / (double)posledni_prirustek;
    }
    posledni_prirustek = prirustek;

    //4.
    double podil_nakazenych = pop.getstav(nakazeni,pop.pocetDni) / 10600000.0; 

    //cout << prirustek14 << '\n';
    //cout << prirustek6514 << '\n';
    //cout << r_cislo << '\n';
    //cout << podil_nakazenych << '\n';
    //cout << "---------------\n";


    pes_hodnota = pes_vypocet(prirustek14,prirustek6514,r_cislo,podil_nakazenych);


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
    
    Populace ceskaPopulace = Populace();

    /* initialize random seed: */
    srand (time(NULL));

    ceskaPopulace.typyPopulace[mladsiPracujici].stavy[nakazeni].den[ceskaPopulace.pocetDni] = 1;
    popInfo(ceskaPopulace,0);

    //promenne pro vypocet PES
    deque<int> pes_prirustek;
    deque<int> pes_prirustek65;
    int posledni_prirustek = 1;
    int pes = 1;
    vector<int> pes_vector;
    pes_vector.push_back(pes);

    for(int i = 0; i < 14;i++){
        pes_prirustek.push_back(0);
        pes_prirustek65.push_back(0);
    }

    for (int i = 0; i < 120; i++){
        
        if(argc > 1){
            pes = 0;
        }
        
        denniZmena(ceskaPopulace,pes_prirustek,pes_prirustek65,posledni_prirustek,pes);

        if(argc > 1){
            pes = 0;
        }

        if(ceskaPopulace.getstav(zdravi, ceskaPopulace.pocetDni) <= 0){
            cout << "Dne " << ceskaPopulace.pocetDni << " byla nakazena cela populace cr, simulace ukoncena\n";

            break;
        }
        pes_vector.push_back(pes);
        cout << "den " << ceskaPopulace.pocetDni << '\n';
        cout << "Populace - zdravi: " << ceskaPopulace.getstav(zdravi, ceskaPopulace.pocetDni) << '\n';
        cout << "Populace - nakazeni: " << ceskaPopulace.getstav(nakazeni, ceskaPopulace.pocetDni) << '\n';
        cout << "Populace - imuni: " << ceskaPopulace.getstav(imuni, ceskaPopulace.pocetDni) << '\n';
         cout << "Populace - mrtvi: " << ceskaPopulace.getstav(mrtvi, ceskaPopulace.pocetDni) << '\n';
        cout << "pes " << pes << '\n';
    }
    
    if(argc > 1){
        vystup(ceskaPopulace,pes_vector,"vysledky_pes");
    }
    else{
        vystup(ceskaPopulace,pes_vector,"vysledky_pes");
    }
  

    //denniZmena(ceskaPopulace);
    //popInfo(ceskaPopulace,100);

    return 0;
}