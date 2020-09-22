#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <time.h>
using namespace std;
const int Ckiek = 100;
const char Cduom[] = "tel.txt";
const char Crez[] = "loterija.txt";
void ivedimas(const char fv[],int sar[], int& kiek);
void isvedimas(const char fv[],int sar[], int laim[], int kiek,int kiek2);
void MaxMin(int sk[], int kiek);
void KasLaimejo(int sar[], int laim[], int kiek, int& kiek2,int rand);
int RandomSkaicius();
bool ArLaimejo(int telNr, int randomSk);
int KiekNumeriuZuikenuose(int sar[], int kiek);

int main() {
	int nr[Ckiek];
	int laimetojai[Ckiek];
	int kiek = 0;
	int	kiek2=0;
	srand((int)time(0));
	ivedimas(Cduom,nr, kiek);
	MaxMin(nr, kiek);
	isvedimas(Crez,nr,laimetojai, kiek, kiek2);
	return 0;
};
void ivedimas(const char fv[], int sar[], int& kiek) {
	ifstream fd(fv);
	while (!fd.eof()) {
		fd>> sar[kiek];
		kiek++;
	}
	fd.close();
}
void isvedimas(const char fv[], int sar[], int laim[], int kiek, int kiek2) {
	ofstream fr(fv);
	bool pralose = true;
	int randomSk;
	int kaimas2;
	kaimas2=KiekNumeriuZuikenuose(sar, kiek);
	
	fr << "***Zuikenai***" << endl;
	for (int i = 0; i < kaimas2; i++) 
		fr << sar[i] << endl;
	fr << "***Meskenai***" << endl;
	for (int i = kaimas2; i < kiek; i++)
		fr << sar[i] << endl;

	while (pralose) {
		randomSk = RandomSkaicius();
		KasLaimejo(sar, laim, kiek, kiek2,randomSk);	
		if (kiek2 > 0) {
			fr << "Sugeneruotas skaicius " << randomSk << ".Yra " << kiek2 << " laimetojai(as)." << endl;
			fr << "***Laimetojai***" << endl;
			for (int i = 0; i < kiek2; i++) {
				fr << laim[i] << endl;
			}
			pralose = false;
		}
		else {
			fr << "Sugeneruotas skaicius " << randomSk << ". Niekas nelaimejo." << endl;
		}
	}
	
	fr.close();
}
void MaxMin(int sk[], int kiek) {
	int did;
	for (int i = 0; i < kiek-1; i++){
		for (int j = i+1; j < kiek; j++) {
			if (sk[j] > sk[i] ){
				did = sk[j];
				sk[j] = sk[i];
				sk[i] = did;
			}
		}
	}
}
int RandomSkaicius() {
	return rand() % 45 + 1;
}
bool ArLaimejo(int telNr , int randomSk) {
	int suma = 0;
	int sk;
	while (telNr >= 1) {
		sk = telNr % 10;
		suma += sk;
		telNr /= 10;
	}
	if (suma == randomSk)
		return true;
	else
		return false;
}
void KasLaimejo(int sar[], int laim[], int kiek, int& kiek2,int rand) {
	for (int i = 0; i < kiek; i++) {
		if (ArLaimejo(sar[i], rand) == true) {
			laim[kiek2] = sar[i];
			kiek2++;
		}
	}
}
int KiekNumeriuZuikenuose(int sar[], int kiek) {
	int km2 = 0;
	int pirmasSk;
	for (int i = 0; i < kiek; i++) {
		pirmasSk = sar[i];
		while (pirmasSk >= 10)
			pirmasSk /= 10;
		if (pirmasSk == 2)
			km2++;
	}
	return km2;
}