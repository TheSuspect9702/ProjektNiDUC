#define BCH_ENCODER_H

#include <iostream>
#include <vector>
using namespace std;
class BCH_Encoder {
public:
    vector<int> g; // wielomian generuj¹cy
    vector<int> minimalny; // wielomian minimalny
    BCH_Encoder(int _n, int _k, int _t);
    vector<int> add(vector<int> a, vector<int> b);
    vector<int> divide(vector<int> dividend, vector<int> divisor);
    vector<int> encode(vector<int> message);
private:
    int n; // d³ugoœæ s³owa kodowego
    int k; // iloœæ bitów informacyjnych
    int m; // iloœæ bitów korekcyjnych
    int d; // minimalna odleg³oœæ Hamminga
    int t; //zdolnosc korekcyjna
    vector<int> alpha_to; // tablica pierwiastków
    vector<int> index_of; // tablica indeksów pierwiastków
    vector<vector<int>> warstwy;

    void generate_alphato(int minimalny);
    bool didntOccur(int e, vector<vector<int>> warstwy);
    void wyznaczWarstwyCyklotomiczne(vector<int> alpha_to);
    void generate_g();
    int whichAlpha(int k);
    vector<int> alfy;
    vector<int>* minimalne = new vector<int>[5]; //zmienic 5 na odpowiednia zmienna
    vector<int> multiply_poly(vector<int>& A, vector<int>& B);
    vector<int> mul(vector<int> min, vector<int> g);
};