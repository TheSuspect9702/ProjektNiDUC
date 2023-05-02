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
    vector<int> codeword = bch.encode(message);
    for (int i = 0; i < codeword.size(); i++) {
        cout << codeword[i];
    }
    BCH_Decoder bchDecode(codeword, t, n, k);
    return 0;
}
//101111000100110011101100101000
//001111000000110001101100101000
//1100000001
//3
//111111000100110001101100101000
//3