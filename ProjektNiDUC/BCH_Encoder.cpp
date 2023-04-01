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
    vector<int> alpha_to; // tablica pierwiastków
    vector<int> index_of; // tablica indeksów pierwiastków
    vector<int> g; // wielomian generuj¹cy

    void generate_g() {
        g.clear();
        g.push_back(1);
        for (int i = 1; i <= 2 * m; i++) {
            int gi = 1;
            for (int j = 0; j < g.size(); j++) {
                gi ^= alpha_to[(i * j) % n];
                gi %= 2;
            }
            g.push_back(gi);
        }
    }
    int operacjaModulo(int i) {
        
    }
    int tab[15][4] = {};
public:
    BCH_Encoder(int _n, int _k) {
        n = _n;
        k = _k;
        m = (int)ceil(log2(n + 1 - k));
        d = 2 * m + 1;
        alpha_to.resize(n + 1);
        index_of.resize(n + 1);
        vector<int> minimalny(m + 1, 0);
        //DODAC WCZYTYWANIE FUNKCJI MINIMALNYCH
        minimalny[0] = 4;
        minimalny[4] = 0;
        minimalny[3] = 1;
        alpha_to[0] = 1;
        tab[0][0] = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 3; j >= 0; j--) {
                if (tab[i - 1][j] != 0) {
                    if (i < 4) {
                        alpha_to[i] = alpha_to[j] * 2;
                        tab[i][j] = tab[i - 1][j] + 1;
                        if (tab[i][j] == 2) {
                            if (j == 3) {
                                tab[i][0]++;
                                tab[i][1]++;
                                for (int k = 0; k < 4; k++) {
                                    if (tab[i][k] == 2) {
                                        tab[i][k] = 0;
                                        tab[i][k + 1]++;
                                    }
                                }
                            }
                            tab[i][j] = 0;
                            tab[i][j + 1]++;
                        }
                    }
                    else {
                        tab[i][j] = tab[i - 1][j] + 1;
                        if (tab[i][j] == 2) {
                            if (j == 3) {
                                tab[i][0]++;
                                tab[i][1]++;
                                for (int k = 0; k < 4; k++) {
                                    if (tab[i][k] == 2) {
                                        tab[i][k] = 0;
                                        tab[i][k + 1]++;
                                    }
                                }
                            }
                            tab[i][j] = 0;
                            tab[i][j + 1]++;
                        }
                        alpha_to[i] += alpha_to[j];
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            index_of[alpha_to[i]] = i;
        }

        g.resize(m + 1);
        generate_g();
    }
    
    vector<int> encode(vector<int> message) {
        vector<int> codeword(n, 0);
        for (int i = 0; i < k; i++) {
            codeword[i] = message[i];
        }
        for (int i = k; i < n; i++) {
            int gi = 0;
            for (int j = 0; j < k; j++) {
                gi ^= alpha_to[(i - k + 1) * j % n];
                gi %= 2;
            }
            for (int j = 1; j <= m; j++) {
                codeword[i] ^= (gi * g[j]) % 2;
            }
        }
        return codeword;
    }
};

int main() {
    BCH_Encoder bch(15, 5);
    vector<int> message = { 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1 };
    vector<int> codeword = bch.encode(message);
    for (int i = 0; i < codeword.size(); i++) {
        cout << codeword[i];
    }
    return 0;
}
