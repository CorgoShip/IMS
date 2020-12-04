#include "classes.h"

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
Populace pop_setup(){

    vector<TypPopulace> typy;

    TypPopulace PS("predskolni vek",340'400, 0.0);
    typy.push_back(PS);

    TypPopulace MS("materska skola",364'909, 0.0);
    typy.push_back(MS);

    TypPopulace ZS("zakladni skola",952'946, 0.2);
    typy.push_back(ZS);

    TypPopulace SS("stredni skola",427'674, 0.2);
    typy.push_back(SS);

    TypPopulace VS("vysoka skola", 306'869, 0.2);
    typy.push_back(VS);

    TypPopulace PVM("mladsi produktivni vek", 2'761'821,0.2);
    typy.push_back(PVM);

    TypPopulace PVS("starsi produktivni vek", 3'041'614, 0.85);
    typy.push_back(PVS);

    TypPopulace D("duchodci", 2'403'767, 8.8);
    typy.push_back(D);

    Populace ceskaPopulace;
    ceskaPopulace.typyPopulace = typy;

    return ceskaPopulace;
}

/* Tato funkce je jenom na debugg */
void popInfo(Populace pop){
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
}

int main(int argc, char* argv[]){

    Populace ceskaPopulace = pop_setup();
    ceskaPopulace.typyPopulace[0].nakazeni[0] = 1;
    popInfo(ceskaPopulace);

/*     Populace population;
    population.celkem = 100;

    const int POCET_DNI = 1000; // TODO zmenit

    int populace = 10'600'000; // class
    int pocetNakzenych = 1; // vector

    double nakazlivost_viru = 0.1; // zmenit na realne

     class kontakty */



    // int pocet_kontaktu =  


    // for (int i = 0; i < POCET_DNI; i++)
    // {
    //     /* code */
    //     // pocet nakazenych = 10 000 000;
    //     // prirustek += pocet nakazencyh * nakazlivost * pocet kontaktu;

    //     for (int j = 0; j < POCET_TYPU_POPULACE; j++)
    //     {
    //         /* code */
    //     }
        
        
    // }

    return 0;
}