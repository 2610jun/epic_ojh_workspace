#include "rs.h"

int main(){
    // 일단 Galois field construction이 필요함

    // Basic parameters
    //Poly_mod2 p_x = {1, 0, 1, 1, 1, 0, 0, 1};// 1 + x^2 + x^3 + x^4 + x^7 
    // Poly_mod2 p_x = {1, 1, 0, 0, 1};
    // const int m =p_x.size() - 1; // m
    // //display_polynomial(p_x);
    // const int FIELD_SIZE = (1<<m)-1; // 2^m-1
    // vector<Poly_mod2> Galois = GF(p_x, m, FIELD_SIZE); // Build GF(2^m) 
    // vector<int> zech_table = make_zech_table(Galois);  // Build Zech table


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

    // basic parameters
    // int b = 1;
    // int t = 3;

    // // Generate g_x
    // Polynomial gx = generate_gx(b, t, zech_table, FIELD_SIZE);

    // //Polynomial msg({4, 5, 7}, {1, 1, 1});  // 예: α⁴ + α⁵·x + α⁷·x²
    // Polynomial msg({0, 5, -1, -1, 1, -1, -1, -1, 7}, {1, 1, 0, 0, 1, 0, 0, 0, 1});
    // int k = msg.degree(); 
    // int n = k + 2*t;
    // Polynomial codeword = encode_RS(msg, gx, zech_table, FIELD_SIZE);
    // Polynomial error = generate_random_error(t, n ,FIELD_SIZE);
    // Polynomial received = poly_add(codeword, error, zech_table, FIELD_SIZE);
    //Polynomial Syndrome = compute_syndromes(received, b, t, zech_table, FIELD_SIZE);
    /**
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     */
    // test code for syndrome verification
    // textbook 7.6
    // 과제문제의 검증된 답을 바탕으로 검증하면서 코드 짜보자
    int b_s = 1;
    int t_s = 3;
    Poly_mod2 p_x_s = {1, 0, 1, 0, 0, 1};
    cout << "[Primitive Polynomial]" << endl;
    display_polynomial(p_x_s);
    cout<<endl;
    const int m_s =p_x_s.size() - 1; // m
    display_polynomial(p_x_s);
    const int FIELD_SIZE_S = (1<<m_s)-1; // 2^m-1
    vector<Poly_mod2> Galois_S = GF(p_x_s, m_s, FIELD_SIZE_S); // Build GF(2^m) 
    vector<int> zech_table_s = make_zech_table(Galois_S);  // Build Zech table
    Polynomial r_s({2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, 7},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1});
    Polynomial syndrome_s = compute_syndromes(r_s, b_s, t_s, zech_table_s, FIELD_SIZE_S);
    auto [sigma, omega] = euclidean_algorithm(syndrome_s, t_s, zech_table_s, FIELD_SIZE_S);
    display_polynomial(sigma, "σ");
    display_polynomial(omega, "ω");

    vector<int> error_pos = chein_search(sigma, zech_table_s, FIELD_SIZE_S);

    Polynomial error_poly = compute_error_values(sigma, omega, error_pos, zech_table_s, FIELD_SIZE_S);
    Polynomial decoded = correct_errors(r_s, error_poly, zech_table_s, FIELD_SIZE_S);

    cout << "[Error Polynomial]" << endl;
    display_polynomial(error_poly, "e");

    cout << "[Corrected Codeword]" << endl;
    display_polynomial(decoded, "c_hat");




    /**
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     */
    // test code (console output)

    // test code
    // cout<< "n: " << n << endl;
    // cout<< "k: " << k << endl;
    // cout<< "b: " << b << endl;
    // cout<< "t: " << t << endl;
    // cout<<               endl;

    // cout << "[Primitive Polynomial]" << endl;
    // display_polynomial(p_x);
    // cout<<endl;

    // cout << "[Message Polynomial]" << endl;
    // display_polynomial(msg, "m");
    // cout<<endl;

    // cout << "[Generator Polynomial]" << endl;
    // display_polynomial(gx, "g");
    // cout<<endl;

    // cout << "[Encoded Codeword]" << endl;
    // display_polynomial(codeword, "c");  
    // cout<<endl; 

    // cout << "[Random error]" << endl;
    // display_polynomial(error, "e");  
    // cout<<endl;

    // cout << "[Received vector]" << endl;
    // display_polynomial(received, "r");  
    // cout<<endl;

}