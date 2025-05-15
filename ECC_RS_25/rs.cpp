#include "rs.h"

int main(){
    // 일단 Galois field construction이 필요함

    // Basic parameters
    //Poly_mod2 p_x = {1, 0, 1, 1, 1, 0, 0, 1};// 1 + x^2 + x^3 + x^4 + x^7 
    Poly_mod2 p_x = {1, 1, 0, 0, 1};
    const int m =p_x.size() - 1; // m
    //display_polynomial(p_x);
    const int FIELD_SIZE = (1<<m)-1; // 2^m-1
    vector<Poly_mod2> Galois = GF(p_x, m, FIELD_SIZE); // Build GF(2^m) 
    vector<int> zech_table = make_zech_table(Galois);  // Build Zech table


    // test code
    // Poly_exp ex = {4,5,7,9,11};
    // Polynomial ex ({4, -1, 7, 9, 11}, {1, 0, 1, 1, 1});
    // Polynomial 다항식 ({계수}, {마스크})
    // display_polynomial(ex);
    // 예시 출력
    // for (int i = 0; i < zech_table.size(); ++i) {
    //     cout << "Zech[" << i << "] = " << zech_table[i] << endl;
    // }
    // Polynomial A({4, -1, 7}, {1, 0, 1});  // α^4 + α^7·x²
    // Polynomial B({-1, 5, 8}, {0, 1, 1});  // α⁵·x + α^7·x^

    // test code
    // Polynomial C = poly_add(A, B, zech_table, FIELD_SIZE);
    // display_polynomial(C); // 출력 예시: P(x) = α⁴ + α⁵·x
    // Polynomial D = poly_add(B, ex, zech_table, FIELD_SIZE);
    // display_polynomial(D); // 출력 예시: P(x) = α⁴ + α⁵·x

    //Polynomial A({4, -1, 7}, {1, 0, 1});  // α⁴ + α⁷·x²
    //Polynomial B({2, 6},     {1, 1});     // α² + α⁶·x

    // Polynomial C = poly_mul(A, B, zech_table, FIELD_SIZE);
    // display_polynomial(C);

    // Generate g_x
    int b = 1;
    int t = 3;


    Polynomial gx = generate_gx(b, t, zech_table, FIELD_SIZE);

    //Polynomial msg({4, 5, 7}, {1, 1, 1});  // 예: α⁴ + α⁵·x + α⁷·x²
    Polynomial msg({0, 5, -1, -1, 1, -1, -1, -1, 7}, {1, 1, 0, 0, 1, 0, 0, 0, 1}); //
    Polynomial codeword = encode_RS(msg, gx, zech_table, FIELD_SIZE);

    cout << "[Message Polynomial]" << endl;
    display_polynomial(msg, "m");

    cout << "[Generator Polynomial]" << endl;
    display_polynomial(gx, "g");

    cout << "[Encoded Codeword]" << endl;
    display_polynomial(codeword, "c");   

}