#include "BCH_Decoder.h"
#include <iostream>
#include <vector>
using namespace std;

vector<int> BCH_Decoder::rotate(vector<int> codeword)
{
	vector<int> rotated;
	return rotated;
}
vector<int> BCH_Decoder::decode(vector<int> codeword) {
	vector<int> decoded;
	return decoded;
}

BCH_Decoder::BCH_Decoder(vector<int> codeword, int t, int n,int k)
{
	n = n;
	t = t;
	k = k;
	message.push_back(vector<int>());
	int x = 0;
	for (int i = codeword.size() - 1; i >= 0; i--) {
		if (i % n == n - 1 && i != codeword.size() - 1) {
			x++;
			message.push_back(vector<int>());
		}
		message[x].insert(message[x].begin(), codeword[i]);
	}


}








//BCH_Decoder::BCH_Decoder() {
//    syndrom = bch.divide(codeword, bch.g);
//    int wagaHamminga = 0;
//    cout << endl;
//    for (int i = 0; i < syndrom.size(); i++) {
//        if (syndrom[i] == 1)
//            wagaHamminga++;
//        cout << syndrom[i];
//    }
//}
//int liczbaPrzesuniec = 0;
//vector<int> temp = codeword;
//cout << endl << wagaHamminga;
//while (wagaHamminga > t) {
//    if (temp.size() == 0)
//        break;
//    temp.pop_back();
//    syndrom = bch.divide(temp, bch.g);
//    for (int i = 0; i < syndrom.size(); i++)
//        if (syndrom[i] == 1)
//            wagaHamminga++;
//    liczbaPrzesuniec++;
//}
//temp = bch.add(temp, syndrom);
//while (liczbaPrzesuniec != 0) {
//    liczbaPrzesuniec--;
//    temp.push_back(0);
//}
//codeword = temp;
//cout << endl;
//for (int i = 0; i < codeword.size(); i++)
//    cout << codeword[i];
//cout << endl << wagaHamminga;

