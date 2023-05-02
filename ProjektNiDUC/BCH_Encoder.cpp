#include <iostream>
#include <vector>
#include <cmath>
#include "BCH_Encoder.h"
using namespace std;

void BCH_Encoder::generate_alphato(int minimalny) {
    alpha_to[0] = 1;
    for (int i = 1; i < n; i++) {
        alpha_to[i] = (alpha_to[i - 1] << 1);
        if (alpha_to[i] >= pow(2, m)) {
            alpha_to[i] ^= minimalny;
        }
    }
}
bool BCH_Encoder::didntOccur(int e, vector<vector<int>> warstwy) {
    for (int i = 0; i < warstwy.size(); i++) {
        for (int j = 0; j < warstwy[i].size(); j++) {
            if (warstwy[i][j] == e) return false;
        }
    }
    return true;
}
void BCH_Encoder::wyznaczWarstwyCyklotomiczne(vector<int> alpha_to) {
    vector<int> v;
    v.push_back(0);
    warstwy.push_back(v);
    v.clear();
    int nrWarstwy = 1;
    int first = 0;

    int p;
    for (int i = 1; i < n; i++) {
        first = i;
        if (didntOccur(i, warstwy)) {
            p = i;
            do {
                v.push_back(p);
                p = (p * 2) % n;
            } while (p != first);
            warstwy.push_back(v);
            v.clear();
            nrWarstwy++;

        }
    }
}
void BCH_Encoder::generate_g() {
    g.clear();
    g.push_back(1);

    wyznaczWarstwyCyklotomiczne(alpha_to);

    //minimalne[0].insert(minimalne[0].begin(), 1);
    //minimalne[0].insert(minimalne[0].begin(), 1);
    //minimalne[1].insert(minimalne[1].begin(), 1);
    //minimalne[1].insert(minimalne[1].begin(), 0);
    //minimalne[1].insert(minimalne[1].begin(), 0);
    //minimalne[1].insert(minimalne[1].begin(), 1);
    //minimalne[1].insert(minimalne[1].begin(), 1);
    //minimalne[2].insert(minimalne[2].begin(), 1);
    //minimalne[2].insert(minimalne[2].begin(), 1);
    //minimalne[2].insert(minimalne[2].begin(), 1);
    //minimalne[2].insert(minimalne[2].begin(), 1);
    //minimalne[2].insert(minimalne[2].begin(), 1);
    //minimalne[3].insert(minimalne[3].begin(), 1);
    //minimalne[3].insert(minimalne[3].begin(), 1);
    //minimalne[3].insert(minimalne[3].begin(), 1);
    //minimalne[4].insert(minimalne[4].begin(), 1);
    //minimalne[4].insert(minimalne[4].begin(), 1);
    //minimalne[4].insert(minimalne[4].begin(), 0);
    //minimalne[4].insert(minimalne[4].begin(), 0);
    //minimalne[4].insert(minimalne[4].begin(), 1);

    for (int i = 3; i <= t; i++)
        g = multiply_poly(g, warstwy[i]);

}
vector<int> BCH_Encoder::multiply_poly(vector<int>& g, vector<int>& warstwy) {

    vector<int> tempWynik;
    vector<int> temp;
    vector<int> temp1;
    vector<int> nawias;
    tempWynik.push_back(0);
    tempWynik.push_back(warstwy[0]);
    nawias.push_back(0);
    nawias.push_back(warstwy[1]);
    int k;
    for (int i = 1; i < warstwy.size(); i++) {
        nawias[1] = warstwy[i];
        k = 1;
        temp.clear();
        temp1.clear();
        for (int x = 0; x < nawias.size(); x++) {   // mnozenie nawias razy to co dotychczas 
            for (int z = 0; z < tempWynik.size(); z++) {
                if (x == 0)
                    temp.push_back(((nawias[x] + tempWynik[z]) % 15));      
                else {
                    temp1.push_back(((nawias[x] + tempWynik[z]) % 15));
                }
            }
        }
        temp.push_back(0);              //branie pod uwage przeniesienia ze x razy cokolwiek nigdy nie bedzei sama alpha 
        tempWynik.insert(tempWynik.begin(), 0);             //ustawianie potegi o jeden wyzej
        for (int j = 1; j < temp.size(); j++) {
            if (j != temp1.size())
                tempWynik[k] = whichAlpha(alpha_to[temp[j]] ^ alpha_to[temp1[j - 1]]);
            else
                tempWynik[k] = temp1[j - 1];
            k++;
        }
    }
    for (int i = 0; i < tempWynik.size(); i++) {    //zapis obliczonego wielomianu do g im wyzszy indeks tym wieksza potega przy x
        if (tempWynik[i] == 15)
            g.push_back(0);
        else
            g.push_back(alpha_to[tempWynik[i]]);
    }
    g.erase(g.end()-1); //czyszczenie nadmiarowego miejsca w g 
    cout << g.size(); //to tak zeby moc wyswietlic co jest w g 



    //tempWynik.push_back(0); //
    //tempWynik.push_back(1); //jest jakis x

    //alfy.push_back(warstwy[0]); 
    //alfy.push_back(0);

    //int x;
    //int len;
   
    // for (int i = 1; i < warstwy.size(); i++) {
    //    len = tempWynik.size();
    //    for (int j = 0; j < len-1; j++) {

    //        if (alfy[j + 1] == 0) {
    //            alfy[j + 1] = alfy[j];
    //            alfy[j + 1] %= 15;
    //        }
    //        else {
    //            x = alpha_to[alfy[j]] ^ alpha_to[alfy[j + 1]];
    //            x = whichAlpha(x);
    //            alfy[j + 1] = x;
    //        }
    //        if (j == 0) {
    //            alfy[j] += warstwy[i];
    //            alfy[j] %= 15;
    //        }
    //        else{
    //            x = alpha_to[alfy[j]] ^ alpha_to[alfy[j] + warstwy[i]];
    //            x = whichAlpha(x);
    //            alfy[j] = x;
    //        }
    //        





    //        //if (j == 0) {
    //        //    if (alfy[1] == 0) {
    //        //        alfy[1] += alfy[0];
    //        //    }
    //        //    else {
    //        //        x = alpha_to[alfy[1]] ^ alpha_to[alfy[0]];
    //        //        x = whichAlpha(x);
    //        //        alfy[1] = x; //xor   
    //        //    }
    //        //    alfy[j] += warstwy[i];
    //        //    alfy[j] %= 15;
    //        //    continue;
    //        //}
    //        //
    //        //tempWynik.push_back(1);
    //        //x = alpha_to[alfy[j]] ^ alpha_to[warstwy[i]];
    //        ////jakie alfa ma wartosc x i wrzucic ten indeks do alfy[j]
    //        //x = whichAlpha(x);
    //        //alfy[j] = x;
    //    }
    //    //ostatni znak bo zakres do len -1 
    //    tempWynik.push_back(1);
    //    if (alfy[len - 1] == 0) {
    //        alfy[len - 1] = warstwy[i];
    //    }
    //    else {
    //        x = alpha_to[alfy[len - 1]] ^ alpha_to[warstwy[i]];
    //        x = whichAlpha(x);
    //        alfy[len - 1] = x;
    //    }
    //    alfy.push_back(0);
    //}

    return g;
}

int BCH_Encoder::whichAlpha(int x) {
    for (int i = 0; i < alpha_to.size(); i++) {
        if (alpha_to[i] == x) return i;
    }
}
BCH_Encoder::BCH_Encoder(int _n, int _k, int _t) {
    int wielomianMinimalny = 19; // 0001  0001  1101 285
    t = _t;
    n = _n;
    k = _k;
    m = (int)ceil(log2(n + 1 - k));
    d = 2 * m + 1;
    alpha_to.resize(n);
    index_of.resize(n + 1);
    generate_alphato(wielomianMinimalny);
    g.resize(m + 1);
    generate_g();
}

vector<int> BCH_Encoder::add(vector<int> a, vector<int> b) {
    vector<int> result;
    int n = max(a.size(), b.size());
    result.resize(n);
    for (int i = 0; i < n; i++) {
        int ai = i < a.size() ? a[i] : 0;
        int bi = i < b.size() ? b[i] : 0;
        result[i] = ai ^ bi;
    }
    return result;
}
vector<int> BCH_Encoder::divide(vector<int> dividend, vector<int> divisor) {
    vector<int> quotient;
    while (dividend.size() >= divisor.size()) {
        int degree_diff = dividend.size() - divisor.size();
        quotient.push_back(1 << degree_diff);
        for (int i = 0; i < divisor.size(); i++) {
            dividend[degree_diff + i] ^= divisor[i];
        }
        while (!dividend.empty() && dividend.back() == 0) {
            dividend.pop_back();
        }
    }
    return dividend;
}
vector<int> BCH_Encoder::encode(vector<int> message) {
    vector<int> codeword;
    for (int i = 0; i < message.size(); i++)
        if (i % 5 == 4) {
            vector<int>result(k, 0);
            vector<int> rest;
            int x = 0;
            for (int j = i - 4; j <= i; j++) {
                result[x] = message[j];
                x++;
            }
            for (int j = n - k; j > 0; j--)
                result.insert(result.begin(), 0);
            rest = divide(result, g);
            result = add(result, rest);
            for (int j = 0; j < result.size(); j++)
                codeword.push_back(result[j]);
        }
    for (int i = 0; i < codeword.size(); i++) {
        if (i %n == 0) {
            codeword[i]++;
            codeword[i] %= 2;
        }
    }
    return codeword;
}

