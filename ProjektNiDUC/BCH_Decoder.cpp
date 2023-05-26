#include "BCH_Decoder.h"
#include "BCH_Encoder.h"
#include <iostream>
#include <vector>
using namespace std;

vector<int> rotateLeft(vector<int>& codeword)
{
	int temp;
	temp = codeword[0];
	for (int i = 0; i < codeword.size() - 1; i++) {
		codeword[i] = codeword[i + 1];
	}
	codeword[codeword.size() - 1] = temp;
	return codeword;
}

vector<int> rotateRight(vector<int>& codeword)
{
	int temp;
	temp = codeword[codeword.size() - 1];
	for (int i = codeword.size() - 1; i > 0; i--) {
		codeword[i] = codeword[i - 1];
	}
	codeword[0] = temp;
	return codeword;
}

vector<int> BCH_Decoder::decode(vector<int> codeword, vector<int> g) {
	liczbaPrzesuniec = 0;
	vector<int> syndrom;
	syndrom = divide(codeword, g);
	int wagaHamminga = 0;
	for (int i = 0; i < syndrom.size(); i++) {
		if (syndrom[i] == 1)
			wagaHamminga++;
	}
	//cout << "\n " << wagaHamminga << "\n";
	while (wagaHamminga > t) {
		rotateLeft(codeword);
		liczbaPrzesuniec++;
		wagaHamminga = 0;
		syndrom = divide(codeword, g);
		for (int i = 0; i < syndrom.size(); i++) {
			if (syndrom[i] == 1)
				wagaHamminga++;
		}
		if (liczbaPrzesuniec > n)
			break;
	}

	if (wagaHamminga <= t) {
		codeword = add(codeword, syndrom);
		while (liczbaPrzesuniec > 0) {
			liczbaPrzesuniec--;
			rotateRight(codeword);

		}
	}
	return codeword;
}

vector<int> BCH_Decoder::add(vector<int> a, vector<int> b) {
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

vector<int> BCH_Decoder::divide(vector<int> dividend, vector<int> divisor) {
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

BCH_Decoder::BCH_Decoder(vector<int> codeword, int t1, int n1,int k1)
{
	n = n1;
	t = t1;
	k = k1;
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
