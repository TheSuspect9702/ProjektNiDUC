#include <iostream>
#include "BCH_Encoder.h"
#include "BCH_Decoder.h"
#include <vector>
#include <cmath>
#include <string>
#include <conio.h>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    srand(time(NULL));
    int k, n, t;
    k = 115; 
    n = 255;
    t = 20;
    string wiadomosc;
    BCH_Encoder bch(n, k, t);
    char opt;
    do {
        cout << "Podaj wiadomosc do zakodowania (maks 14 znakow): ";
        getline(cin, wiadomosc);
        vector<int> message;
        for (int i = 0; i < wiadomosc.size(); i++) {
            for (int j = 7; j >= 0; j--) {
                message.insert(message.end(), (wiadomosc[i] >> j & 1));
            }
        }
        while (message.size() % k != 0 && message.size() > 0)
            message.push_back(0);
        {   
            vector<int> codeword = bch.encode(message);
            string odczyt;
            char znak;
            int x;
            vector<int> codeword40;
            BCH_Decoder bchDecode(codeword, t, n, k);
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
            cout << "\nWiadomosc przed zakodowaniem: ";
            for (int A : message)
                cout << A;
            cout << "\nWielomian generujacy: ";
            for (int A : bch.g)
                cout << A;
            cout << "\nZakodowana wiadomosc: ";
            for (int A : codeword)
                cout << A;
            cout << "\nOdkodowana wiadomosc: " << odczyt;
            cout << "\nJesli chcesz zakonczyc program kliknij 0, w innym przypadku kliknij dowolny przycisk. ";
            cout << "Twoj wybor: ";
            opt = _getche();
            cout << endl;
        }
    } while (opt != '0');
    return 0;
}