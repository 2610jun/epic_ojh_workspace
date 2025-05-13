#ifndef RS_H
#define RS_H

// Basic headers
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <map>

using namespace std;
using Poly_mod2 = vector<bool>;

using GFElement = int; // a^i로 표현됨. (i = 0 ~ i = m-1)
using Poly_exp = vector<GFElement>; // GF의 게수를 지수로 표현한 다항식.

/**
 * 유틸 함수
 * 
 */


// x^i용 superscript 변환용 map (선택적으로 사용)
string superscript(int n) {
    static map<int, string> supers = {
        {0, "⁰"}, {1, "¹"}, {2, "²"}, {3, "³"}, {4, "⁴"},
        {5, "⁵"}, {6, "⁶"}, {7, "⁷"}, {8, "⁸"}, {9, "⁹"}
    };

    string result;
    string digits = to_string(n);
    for (char d : digits) result += supers[d - '0'];
    return result;
}

void display_polynomial(const Poly_mod2& poly) {
    bool first = true;
    int deg = poly.size() - 1;

    for (int i = 0; i <= deg; ++i) {
        if (poly[i]) {
            if (!first) cout << " + ";
            if (i == 0) {
                cout << "1";
            } else if (i == 1) {
                cout << "x";
            } else {
                cout << "x" << superscript(i);
            }
            first = false;
        }
    }

    if (first) cout << "0"; // zero polynomial
    cout << endl;
}


void display_polynomial(const Poly_exp& poly, const string& name = "P") {
    bool first = true;
    int deg = poly.size();

    cout << name << "(x) = ";

    for (int i = 0; i < deg; ++i) {
        if (poly[i] == -1) continue; // 0 계수는 생략

        if (!first) cout << " + ";

        // 계수 출력
        if (poly[i] == 0) cout << "1";
        else cout << "α^" << poly[i];

        // 차수 출력
        if (i == 1) cout << "·x";
        else if (i > 1) cout << "·x" << superscript(i);

        first = false;
    }

    if (first) cout << "0"; // 전부 0일 때
    cout << endl;
}


// poly_add
// poly_multi
// Generate GF(2^7) using p(x)
vector<Poly_mod2> GF(const Poly_mod2& p_x, const int m, const int FIELD_SIZE){
    // int size = m; // m의 크기를 갖는 tabel vector element
    // 1로 초기화
    Poly_mod2 buf(m, 0);
    buf[0] = 1;
    
    // GF 출력할 벡터 초기화
    vector<Poly_mod2> gf (FIELD_SIZE, Poly_mod2(m, 0));
    gf[0] = buf; 

    Poly_mod2 p_x_cat(p_x.begin(), p_x.end()-1);
    display_polynomial(p_x_cat);
    // Loop 1. # of the Field element
    for(int i = 1; i<FIELD_SIZE; i++){
        // 맨 끝 element가 1인지 확인하기
        bool msb = buf[m-1];

        // 오른쪽 shift
        for(int j = m-1; j>=1; j--){
            buf[j]=buf[j-1];
        }
        buf[0] = 0;
        if(msb==1){
            // 맞으면 shift 해주고, 10111001 더해주기 
            for(int k = 0; k<m; k++){
                buf[k]=buf[k]^p_x_cat[k];
            }
        }

        gf[i] = buf;

        // test code
        cout<<i<<"th power's polynomial: ";
        display_polynomial(gf[i]);
    }
    return gf;
}
// vector<bool> poly_add (const vector<bool>& a, const vector<bool>& b){

// }

// vector<bool> poly_mul(const vector<bool>& a, const vector<bool>& b){

// }


// After implementation of the GF, addition should be implemented by Zech's algorithm
#endif // 