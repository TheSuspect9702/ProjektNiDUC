#include <iostream>
#include "BCH_Encoder.h"
#include "BCH_Decoder.h"
#include <vector>
#include <cmath>

using namespace std;

int main() {
    srand(time(NULL));
    int k, n, t;
    k = 5;
    n = 15;
    t = 3;
    BCH_Encoder bch(n, k, t);
    vector<int> message = { 0,0,1,1,0,0,1,0,0 };
    while (message.size() % k != 0 && message.size() > 0)
        message.push_back(0);
    {
        vector<int> codeword = bch.encode(message);
        //jeden bit w polu kontrolnym na początku
        vector<int> codeword0 = bch.insertError(codeword, 0);
        //jeden bit w polu kontrolnym w srodku
        vector<int> codeword1 = bch.insertError(codeword, 1);
        //jeden bit w polu kontrolnym na koncu
        vector<int> codeword2 = bch.insertError(codeword, 2);
        //jeden bit poza polem kontrolnym
        vector<int> codeword3 = bch.insertError(codeword, 3);
        //jeden bit poza polem kontrolnym w srodku
        vector<int> codeword8 = bch.insertError(codeword, 8);
        //jeden bit w czesci z wiadomoscia
        vector<int> codeword11 = bch.insertError(codeword, 11);
        //dwa bity w czesci kontrolnej
        vector<int> codeword0_1 = bch.insertError(codeword0, 1);
        //dwa bity w czesci kontrolnej
        vector<int> codeword0_2 = bch.insertError(codeword0, 2);
        //dwa bity poza czescia kontrolna
        vector<int> codeword8_9 = bch.insertError(codeword8, 9);
        //dwa bity w czesci informacyjnej
        vector<int> codeword11_12 = bch.insertError(codeword11, 12);
        //trzy bity w czesci kontrolnej
        vector<int> codeword0_1_2 = bch.insertError(codeword0_1, 2);
        //trzy bity poza kontrolna
        vector<int> codeword8_9_7 = bch.insertError(codeword8_9, 7);
        //trzy bity w czesci informacyjnej
        vector<int> codeword11_12_14 = bch.insertError(codeword11_12, 14);
        //piec bitow 2 w kontrolnej 3 poza nia
        vector<int> codeword0_1_8_9_6 = bch.insertError(codeword0_1, 8);
        codeword0_1_8_9_6 = bch.insertError(codeword0_1_8_9_6, 9);
        codeword0_1_8_9_6 = bch.insertError(codeword0_1_8_9_6, 6);
        for (int i = 0; i < codeword.size(); i++) {
            cout << codeword[i];
        }
        cout << endl;
        for (int i = 0; i < codeword0.size(); i++) {
            cout << codeword0[i];
        }
        cout << endl;
        for (int i = 0; i < codeword1.size(); i++) {
            cout << codeword1[i];
        }
        cout << endl;
        for (int i = 0; i < codeword2.size(); i++) {
            cout << codeword2[i];
        }
        cout << endl;
        for (int i = 0; i < codeword3.size(); i++) {
            cout << codeword3[i];
        }
        cout << endl;
        for (int i = 0; i < codeword8.size(); i++) {
            cout << codeword8[i];
        }
        cout << endl;
        for (int i = 0; i < codeword11.size(); i++) {
            cout << codeword11[i];
        }
        cout << endl;
        for (int i = 0; i < codeword0_1.size(); i++) {
            cout << codeword0_1[i];
        }
        cout << endl;
        for (int i = 0; i < codeword0_2.size(); i++) {
            cout << codeword0_2[i];
        }
        cout << endl;
        for (int i = 0; i < codeword8_9.size(); i++) {
            cout << codeword8_9[i];
        }
        cout << endl;
        for (int i = 0; i < codeword11_12.size(); i++) {
            cout << codeword11_12[i];
        }
        cout << endl;
        for (int i = 0; i < codeword0_1_2.size(); i++) {
            cout << codeword0_1_2[i];
        }
        cout << endl;
        for (int i = 0; i < codeword8_9_7.size(); i++) {
            cout << codeword8_9_7[i];
        }
        cout << endl;
        for (int i = 0; i < codeword11_12_14.size(); i++) {
            cout << codeword11_12_14[i];
        }
        cout << endl;
        for (int i = 0; i < codeword0_1_8_9_6.size(); i++) {
            cout << codeword0_1_8_9_6[i];
        }

        BCH_Decoder bchDecode(codeword0_1_8_9_6, t, n, k);
        for (int i = 0; i < bchDecode.message.size(); i++) {
            bchDecode.message[i] = bchDecode.decode(bchDecode.message[i], bch.g);
            for (int j = bchDecode.message[i].size() - 1; j > bchDecode.message[i].size() - 1 - k; j--) {
                cout << " " << bchDecode.message[i][j] << " ";
            }
        }
    }
    return 0;
}
