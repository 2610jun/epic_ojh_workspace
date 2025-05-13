#include "rs.h"


int main(){
    // 일단 Galois field construction이 필요함

    // Basic parameters
    Poly_mod2 p_x = {1, 0, 1, 1, 1, 0, 0, 1};// 1 + x^2 + x^3 + x^4 + x^7 
    const int m =p_x.size() - 1; // m
    display_polynomial(p_x);
    const int FIELD_SIZE = (1<<m)-1; // 2^m-1
    GF(p_x, m, FIELD_SIZE);

    //test code
    Poly_exp ex = {4,5,7,9,11};
    display_polynomial(ex);

    

}