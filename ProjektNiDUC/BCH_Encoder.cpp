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

    //wyznaczWarstwyCyklotomiczne(alpha_to);

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
vector<int> BCH_Encoder::multiply_poly(vector<int>& A, vector<int>& B) {
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

