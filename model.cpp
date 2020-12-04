#include <iostream>
#include <vector>

#define POCET_TYPU_KONTAKTU
#define POCET_TYPU_POPULACE 8

using namespace std;

class Populace {       
  public:             
    int celkem = 10'600'000;        
    int pocetNakazenych;
    int pocetVylecenych;
    int pocetMrtvych;
    int pocetTezkychPrubehu;  
};

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
        int pocetLidi;
        int poctyKontaktu[POCET_TYPU_KONTAKTU]; // Pocet kontaktu pro jednotlive typy
        vector<int> pocetNakazenych; // Pocet nakazenych v jednotlivych dnech,
        double mortalita;


}

class TypKontaktu {
    public:
        double nakazeniTypuPopulace[POCET_TYPU_POPULACE]; // S 
}

// enum na typy populace

int main(int argc, char* argv[]){

    const int POCET_DNI = 1000; // TODO zmenit

    int populace = 10_600_000; // class
    int pocetNakzenych = 1; // vector

    double nakazlivost_viru = 0.1; // zmenit na realne

    // class kontakty



    int pocet_kontaktu =  


    for (int i = 0; i < POCET_DNI; i++)
    {
        /* code */
        pocet nakazenych = 10 000 000;
        prirustek += pocet nakazencyh * nakazlivost * pocet kontaktu;

        for (int j = 0; j < POCET_TYPU_POPULACE; j++)
        {
            /* code */
        }
        
        
    }
    



    cout << "Testovaci output";
    return 0;
}