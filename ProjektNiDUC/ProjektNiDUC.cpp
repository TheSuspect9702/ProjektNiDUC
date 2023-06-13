#include <iostream>
#include "BCH_Encoder.h"
#include "BCH_Decoder.h"
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    srand(time(NULL));
    int k, n, t;
    k = 115; //wieksze lub rowne n-m*t m = 8 t =20 czesc informacyjna na koncu wektora
    n = 255;
    t = 20;
    string wiadomosc;
    BCH_Encoder bch(n, k, t);
    cout << "Podaj wiadomosc do zakodowania (maks 14 znakow): ";
    getline(cin, wiadomosc);
    vector<int> message;
    for (int i = 0; i < wiadomosc.size(); i++) {
        for (int j = 7; j >= 0; j--) {
            message.insert(message.end(),(wiadomosc[i] >> j & 1));
        }
    }
    while (message.size() % k != 0 && message.size() > 0)
        message.push_back(0);
    {
        vector<int> codeword = bch.encode(message);
        vector<int> codeword10 = bch.insertError(codeword, 1);
        vector<int> codeword20 = bch.insertError(codeword, 2);

        vector<int> codeword80 = bch.insertError(codeword, 8);
        vector<int> codeword160 = bch.insertError(codeword, 16);
        vector<int> codeword200 = bch.insertError(codeword, 20);
        vector<int> codeword210 = bch.insertError(codeword, 21);
        vector<int> codeword300 = bch.insertError(codeword, 30);
        vector<int> codeword999 = bch.insertErrorIndex(codeword, 10);
        /*
            wiecej błędów również wymieszane i zrobic kazdy mozliwy blad
            dekoder pelny
            zaczac sprawozdanie
            sprawozdanie:
            wyniki testow i dlaczego tak jest
            co o tym myslimy itp.
            nie opisywac teori kodera i dekodera itp
            pokazac ze zrozumielismy jak dziala kod
            i pokazac ze zrozumielismy jak dziala dekoder pelny
        */
        double poprawne;
        string odczyt;
        char znak;
        int x;
        vector<int> codeword40;
        ofstream zapis("result1.txt");
        for (int z = 1; z < 26; z++) {
            poprawne = 0;
            for (int c = 1000; c > 0; c--) {
                odczyt.clear();
                codeword40 = bch.insertError(codeword, z);
                BCH_Decoder bchDecode(codeword40, t, n, k);
                for (int i = 0; i < bchDecode.message.size(); i++) {
                    bchDecode.message[i] = bchDecode.decode(bchDecode.message[i], bch.g);
                }
                znak = 0;
                x = 7;
                for (int i = bchDecode.message.size() - 1; i >= 0; i--) {
                    for (int j = k - 1; j >= 0; j--) {
                        if (x == -1) {
                            if (znak != 0)
                                odczyt += znak;
                            znak = 0;
                            x = 7;
                        }

                        znak += bchDecode.message[i][bchDecode.message[i].size() - j - 1] * pow(2, x);
                        x--;
                    }
                }
                if (znak != 0)
                    odczyt += znak;
                if (odczyt == wiadomosc)
                    poprawne++;
            }
            zapis << z << " " << poprawne/10 << endl;
            cout << z << endl;
        }
    }
    return 0;
}