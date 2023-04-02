#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class BCH_Encoder {
private:
    int n; // d³ugoœæ s³owa kodowego
    int k; // iloœæ bitów informacyjnych
    int m; // iloœæ bitów korekcyjnych
    int d; // minimalna odleg³oœæ Hamminga
    int t; //zdolnosc korekcyjna
    vector<int> alpha_to; // tablica pierwiastków
    vector<int> index_of; // tablica indeksów pierwiastków
    vector<int> g; // wielomian generuj¹cy

    void generate_g() {
        g.clear();
        g.push_back(1);
        minimalne[0].insert(minimalne[0].begin(), 1);
        minimalne[0].insert(minimalne[0].begin(), 1);
        minimalne[1].insert(minimalne[1].begin(), 1);
        minimalne[1].insert(minimalne[1].begin(), 0);
        minimalne[1].insert(minimalne[1].begin(), 0);
        minimalne[1].insert(minimalne[1].begin(), 1);
        minimalne[1].insert(minimalne[1].begin(), 1);
        minimalne[2].insert(minimalne[2].begin(), 1);
        minimalne[2].insert(minimalne[2].begin(), 1);
        minimalne[2].insert(minimalne[2].begin(), 1);
        minimalne[2].insert(minimalne[2].begin(), 1);
        minimalne[2].insert(minimalne[2].begin(), 1);
        minimalne[3].insert(minimalne[3].begin(), 1);
        minimalne[3].insert(minimalne[3].begin(), 1);
        minimalne[3].insert(minimalne[3].begin(), 1);
        minimalne[4].insert(minimalne[4].begin(), 1);
        minimalne[4].insert(minimalne[4].begin(), 1);
        minimalne[4].insert(minimalne[4].begin(), 0);
        minimalne[4].insert(minimalne[4].begin(), 0);
        minimalne[4].insert(minimalne[4].begin(), 1);

        /*for (int i = 1; i <= 2 * m; i++) {
            int gi = 1;
            for (int j = 0; j < g.size(); j++) {
                gi ^= alpha_to[(i * j) % n];
                gi %= 2;
            }
            g.push_back(gi);
        }*/
        for (int i = 1; i < 4; i++)
           g = multiply_poly(g, minimalne[i]);
    }
    vector<int>* minimalne = new vector<int>[5]; //zmienic 5 na odpowiednia zmienna
    vector<int> multiply_poly(vector<int>& A, vector<int>& B) {
        int n = A.size();
        int m = B.size();
        vector<int> C(n + m - 1, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                C[i + j] ^= A[i] & B[j];
            }
        }
        return C;
    }

    int tab[15][4] = {};
public:
    BCH_Encoder(int _n, int _k, int _t) {
        t = _t;
        n = _n;
        k = _k;
        m = (int)ceil(log2(n + 1 - k));
        d = 2 * m + 1;
        alpha_to.resize(n + 1);
        index_of.resize(n + 1);
        //vector<int> minimalny(m, 0);
        ////DODAC WCZYTYWANIE FUNKCJI MINIMALNYCH
        //minimalny[1] = 1;
        //minimalny[0] = 1;
        //alpha_to[0] = 1;
        //tab[0][0] = 1;
        //for (int i = 1; i < n; i++) {
        //    if (i < m) {
        //        for (int j = 3; j >= 0; j--) {
        //            if (tab[i - 1][j] != 0) {
        //                alpha_to[i] = alpha_to[j] * 2;
        //                tab[i][j] = tab[i - 1][j] + 1;
        //                if (tab[i][j] == 2) {
        //                    if (j == 3) {
        //                        tab[i][0]++;
        //                        tab[i][1]++;
        //                        for (int k = 0; k < 4; k++) {
        //                            if (tab[i][k] == 2) {
        //                                tab[i][k] = 0;
        //                                tab[i][k + 1]++;
        //                            }
        //                        }
        //                    }
        //                    tab[i][j] = 0;
        //                    tab[i][j + 1]++;
        //                }
        //            }
        //        }
        //    }
        //    else {
        //        if (i == m) {
        //            for (int k = 0; k < m; k++) {
        //                if (minimalny[k] != 0) {
        //                    tab[i][k] = 1;
        //                    tab[i][k] = 1;
        //                }
        //            }
        //            for (int k = 0; k < m; k++)
        //                if (tab[i][k] != 0)
        //                alpha_to[i] += alpha_to[k];
        //        }
        //        else if(alpha_to[i-1]*2<16) {
        //            alpha_to[i] = alpha_to[i - 1] * 2;
        //        }
        //        
        //        else {

        //        }

        //    }  // DO DOKONCZENIA EWENTUALNIE BLAGAM NIE
        //}
        alpha_to[0] = 1;
        alpha_to[1] = 2;
        alpha_to[2] = 4;
        alpha_to[3] = 8;
        alpha_to[4] = 3;
        alpha_to[5] = 6;
        alpha_to[6] = 12;
        alpha_to[7] = 11;
        alpha_to[8] = 5;
        alpha_to[9] = 10;
        alpha_to[10] = 7;
        alpha_to[11] = 14;
        alpha_to[12] = 15;
        alpha_to[13] = 13;
        alpha_to[14] = 9;

        for (int i = 0; i < n; i++) {
            index_of[alpha_to[i]] = i;
        }

        g.resize(m + 1);
        generate_g();
    }
    vector<int> add(vector<int> a, vector<int> b) {
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
    vector<int> divide(vector<int> dividend, vector<int> divisor) {
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
    vector<int> encode(vector<int> message) {
        vector<int> codeword;
        for(int i = 0;i<message.size();i++)
            if (i % 5 == 4) {
                vector<int>result(k, 0);
                vector<int> rest;
                int x = 0;
                for (int j = i-4; j <= i; j++) {
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
        return codeword;
    }
};

int main() {
    int k, n,t;
    k = 5;
    n = 15;
    t = 3; 
    BCH_Encoder bch(n, k, t);
    vector<int> message = {0,0,1,1,0,0,1,0,0};
    while (message.size() % k != 0 && message.size() > 0)
        message.push_back(0);
    vector<int> codeword = bch.encode(message);
    for (int i = 0; i < codeword.size(); i++) {
        cout << codeword[i];
    }
    return 0;
}
