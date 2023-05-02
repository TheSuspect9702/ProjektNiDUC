#pragma once
#include <iostream>
#include <vector>
using namespace std;

class BCH_Decoder
{
public:
    int wagaHamminga;
    int liczbaPrzesuniec = 0;
    int t;
    int n;
    int k;
    vector<int> temp; //czesc wiadomosci ktora odkodowujemy 
    vector<int> decode(vector<int> codeword);
    vector<int> rotate(vector<int> codeword);
    BCH_Decoder(vector<int> codeword, int t, int n,int k);
    vector<vector<int>> message;
};

