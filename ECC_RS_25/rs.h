#ifndef RS_H
#define RS_H

// Basic headers
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <map>
#include <random>
#include <set>

using namespace std;
using Poly_mod2 = vector<bool>;

/**
 * 여기에 들어가는 각종 유니코드들
 * Compart: Superscript characters
 * 
 * https://www.compart.com/en/unicode/block/U+2070
 * 
 * 위 사이트에서 복붙해와서 코드의 가독성을 높였습니다...
 * 
 * VSCODE 기준으로 UTF-8 encoder 사용해야 깨지지 않고 잘 보입니다...
 */

// using GFElement = int; // a^i로 표현됨. (i = 0 ~ i = m-1)
// using Poly_exp = vector<GFElement>; // GF의 게수를 지수로 표현한 다항식.

/**
 * 구조체.. non-binary polynomial을 다루기 위한 구조체와 함수들
 */
struct Polynomial {
    vector<int> coeffs;     // α^i 형태로 계수 저장, -1은 0으로 간주
    vector<bool> mask;      // 해당 항이 존재하면 true, 없으면 false

    Polynomial(int deg = 0) {
        coeffs = vector<int>(deg + 1, -1);  // 기본값 -1 (즉, 0)
        mask = vector<bool>(deg + 1, false);
    }
    // 사용자 정의 생성자: coeffs와 mask를 직접 전달할 때
    Polynomial(const vector<int>& coeffs_, const vector<bool>& mask_) {
        if (coeffs_.size() != mask_.size()) {
            throw invalid_argument("coeffs and mask must be the same size");
        }
        coeffs = coeffs_;
        mask = mask_;
    }

    int degree() const {
        return coeffs.size() - 1;
    }
};

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


void display_polynomial(const Poly_mod2& poly, const string& name = "p") {
    bool first = true;
    int deg = poly.size() - 1;

    cout << name << "(x) = ";

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




void display_polynomial(const Polynomial& poly, const string& name = "P") {
    bool first = true;
    int deg = poly.coeffs.size();

    cout << name << "(x) = ";

    for (int i = 0; i < deg; ++i) {
        if (!poly.mask[i] || poly.coeffs[i] == -1) continue;

        if (!first) cout << " + ";

        // 계수 출력
        if (poly.coeffs[i] == 0) {
            cout << "1";
        } else {
            cout << "α" << superscript(poly.coeffs[i]);  // 여기가 포인트
        }

        // 차수 출력
        if (i == 1) cout << "·x";
        else if (i > 1) cout << "·x" << superscript(i);

        first = false;
    }

    if (first) cout << "0";
    cout << endl;
}



// Generate GF(2^7) using p(x)
vector<Poly_mod2> GF(
    const Poly_mod2& p_x, 
    const int m, 
    const int FIELD_SIZE
) {
    // int size = m; // m의 크기를 갖는 tabel vector element
    // 1로 초기화
    Poly_mod2 buf(m, 0);
    buf[0] = 1;
    
    // GF 출력할 벡터 초기화
    vector<Poly_mod2> gf (FIELD_SIZE, Poly_mod2(m, 0));
    gf[0] = buf; 

    // temp 선언해서 간섭 x
    Poly_mod2 temp(m, 0);
    
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
        // cout<<i<<"th power's polynomial: ";
        // display_polynomial(gf[i]);
    }
    return gf;
}

vector<int> make_zech_table(const vector<Poly_mod2>& gf){  
    int FIELD_SIZE = gf.size();
    vector<int> zech(FIELD_SIZE, -1); // Z(i) 값을 저장
    const Poly_mod2& one = gf[0];     // α⁰ = 1

    // 그냥 0번째는 제끼자
    for (int i = 1; i < FIELD_SIZE; ++i) {
        // sum = 1 + α^i
        Poly_mod2 sum(gf[i].size(), 0);
        for (int j = 0; j < sum.size(); ++j) {
            sum[j] = one[j] ^ gf[i][j]; // XOR
        }

        // sum == α^k 인 k를 찾기
        for (int k = 0; k < FIELD_SIZE; ++k) {
            if (gf[k] == sum) {
                zech[i] = k;
                break;
            }
        }

        // 예외처리 (찾지 못한 경우)
        if (zech[i] == -1) {
            cerr << "Zech value undefined for i = " << i << endl;
        }
    }

    return zech;
}

Polynomial poly_add(
    const Polynomial& a,
    const Polynomial& b,
    const vector<int>& zech_table,
    int FIELD_SIZE
) {
    int max_deg = max(a.degree(), b.degree());
    Polynomial result(max_deg);

    for (int i = 0; i <= max_deg; ++i) {
        // 계수 받아오는 과정. 0인지 아닌지 확인해야함
        // 계수가 0인 경우를 고려해주는 addition을 수행해야한다.
        int ai = (i <= a.degree() && a.mask[i]) ? a.coeffs[i] : -1;
        int bi = (i <= b.degree() && b.mask[i]) ? b.coeffs[i] : -1;

        if (ai == -1 && bi == -1) {
            result.coeffs[i] = -1;
            result.mask[i] = false;
        }
        else if (ai == -1) {
            result.coeffs[i] = bi;
            result.mask[i] = true;
        }
        else if (bi == -1) {
            result.coeffs[i] = ai;
            result.mask[i] = true;
        }
        else if (ai == bi) {
            // α^i + α^i = 0
            result.coeffs[i] = -1;
            result.mask[i] = false;
        }
        else {
            int delta = (FIELD_SIZE + bi - ai) % FIELD_SIZE;
            int z = zech_table[delta];
            if (z == -1) {
                cerr << "Zech table undefined for delta = " << delta << " (α^" << ai << " + α^" << bi << ")" << endl;
                exit(1);
            }
            result.coeffs[i] = (ai + z) % FIELD_SIZE;
            result.mask[i] = true;
        }
    }

    return result;
}

// g(x) 형성할때 필요함.
Polynomial poly_mul(
    const Polynomial& a,
    const Polynomial& b,
    const vector<int>& zech_table,
    int FIELD_SIZE
) {
    int deg_a = a.degree();
    int deg_b = b.degree();
    int deg_result = deg_a + deg_b;

    Polynomial result(deg_result); // 초기화: coeffs = -1, mask = false

    for (int i = 0; i <= deg_a; ++i) {
        if (!a.mask[i] || a.coeffs[i] == -1) continue;

        for (int j = 0; j <= deg_b; ++j) {
            if (!b.mask[j] || b.coeffs[j] == -1) continue;

            int coeff_sum = (a.coeffs[i] + b.coeffs[j]) % FIELD_SIZE;
            int deg = i + j;

            if (!result.mask[deg]) {
                result.coeffs[deg] = coeff_sum;
                result.mask[deg] = true;
            } else {
                // α^x + α^y = α^z via Zech
                int old = result.coeffs[deg];
                if (old == coeff_sum) {
                    result.coeffs[deg] = -1;
                    result.mask[deg] = false;
                } else {
                    int delta = (FIELD_SIZE + coeff_sum - old) % FIELD_SIZE;
                    int z = zech_table[delta];
                    if (z == -1) {
                        cerr << "Zech undefined for delta = " << delta << " at deg " << deg << endl;
                        exit(1);
                    }
                    result.coeffs[deg] = (old + z) % FIELD_SIZE;
                    result.mask[deg] = true;
                }
            }
        }
    }

    return result;
}

Polynomial poly_mul_xk(const Polynomial& poly, int k) {
    int new_deg = poly.degree() + k;
    Polynomial result(new_deg);

    for (int i = 0; i <= poly.degree(); ++i) {
        if (!poly.mask[i] || poly.coeffs[i] == -1) continue;

        result.coeffs[i + k] = poly.coeffs[i];
        result.mask[i + k] = true;
    }

    return result;
}

pair<Polynomial, Polynomial> poly_divmod(
    Polynomial dividend,
    const Polynomial& divisor,
    const std::vector<int>& zech_table,
    int FIELD_SIZE
) {
    int deg_divisor = divisor.degree();
    Polynomial quotient(std::max(0, dividend.degree() - deg_divisor));

    while (dividend.degree() >= deg_divisor) {
        int i = dividend.degree();
        int j = deg_divisor;

        if (!dividend.mask[i] || dividend.coeffs[i] == -1) {
            // 잘못된 항 (0) → 생략
            dividend.coeffs.pop_back();
            dividend.mask.pop_back();
            continue;
        }

        int lead_diff = (FIELD_SIZE + dividend.coeffs[i] - divisor.coeffs[j]) % FIELD_SIZE;
        int deg_diff = i - j;

        // quotient 항 저장
        quotient.coeffs[deg_diff] = lead_diff;
        quotient.mask[deg_diff] = true;

        // temp = divisor * α^lead_diff · x^deg_diff
        Polynomial temp = poly_mul_xk(divisor, deg_diff);
        for (int k = 0; k <= temp.degree(); ++k) {
            if (temp.mask[k]) {
                temp.coeffs[k] = (temp.coeffs[k] + lead_diff) % FIELD_SIZE;
            }
        }

        // dividend = dividend - temp
        dividend = poly_add(dividend, temp, zech_table, FIELD_SIZE);
    }

    return {quotient, dividend}; // 나머지가 바로 parity
}


/**
 * Encoding
 */

Polynomial generate_gx(
    int b, 
    int t,
    const vector<int>& zech_table,
    int FIELD_SIZE
) {
    Polynomial g(0); 
    g.coeffs[0]=0;
    g.mask[0]=true; // degree = 0, 초기값 g_x = 1로 시작한다.

    // (x + a^i) 다 곱해줌. i = b ~ i = b + 2t -1
    for(int i =0; i<2*t; i++){
        Polynomial g_buf = g;
        int exp = (b + i) % FIELD_SIZE; // 이거 생각 못할뻔...

        Polynomial temp({exp, 0},{true, true});

        g = poly_mul(g_buf, temp, zech_table, FIELD_SIZE);
    }

    return g;
}


Polynomial encode_RS(
    const Polynomial& message,
    const Polynomial& generator,
    const std::vector<int>& zech_table,
    int FIELD_SIZE
) {
    int n = FIELD_SIZE; // 전체 코드 길이 (필드 최대값 사용 시 n = 2^m - 1)
    int parity_len = generator.degree(); // n - k

    // message shift
    Polynomial shifted = poly_mul_xk(message, parity_len);

    // divide by generator
    auto [quot, rem] = poly_divmod(shifted, generator, zech_table, FIELD_SIZE);

    // build final codeword
    Polynomial codeword = shifted;
    for (int i = 0; i <= rem.degree(); ++i) {
        codeword.coeffs[i] = rem.coeffs[i];
        codeword.mask[i] = rem.mask[i];
    }

    return codeword;
}

Polynomial generate_random_error(int t, int n, int FIELD_SIZE){
    random_device rd;
    mt19937 gen(rd());

    // Setting random distribution 
    uniform_int_distribution<> error_count_dist(1, t); // # of errors
    uniform_int_distribution<> pos_dist(0, n-1);       // pos of errors
    uniform_int_distribution<> coeff_dist(0, FIELD_SIZE-1); // coeff a^i ( i=0 ~ i= 2^m-2)
    
    // 에러 개수 설정
    int num_errs = error_count_dist(gen);
    // cout<<"# of errors: "<< num_errs << endl; // test code

    // 에러 위치 설정 (중복 없이 선택해야함)
    set<int> positions;// 중복 허락 안하는, 집합 컨테이너
    while(positions.size() < num_errs){
        positions.insert(pos_dist(gen));
    }

    // 에러 coeff 결정하고 최종적으로 에러패턴 만들어내기
    Polynomial error_poly(n-1); // degree는 n-1
    for(int pos : positions){
        int coeff = coeff_dist(gen);
        error_poly.coeffs[pos] = coeff;
        error_poly.mask[pos] = true;
    }

    return error_poly;

}

// r(α^i)와 같은 반복적인 연산에서 필요함
int evaluate_poly_alpha(
    const Polynomial& poly,
    int alpha_power,
    const vector<int>& zech_table,
    int FIELD_SIZE
) {
    int sum = -1; // α^-inf = 0

    for (int i = 0; i <= poly.degree(); ++i) {
        if (!poly.mask[i] || poly.coeffs[i] == -1) continue;

        int term = (poly.coeffs[i] + alpha_power * i) % FIELD_SIZE;

        if (sum == -1) {
            sum = term;
        } else if (sum == term) {
            sum = -1; // α^a + α^a = 0
        } else {
            int delta = (term - sum + FIELD_SIZE) % FIELD_SIZE;
            int z = zech_table[delta];
            if (z == -1) {
                cerr << "Zech undefined: α^" << sum << " + α^" << term << endl;
                exit(1);
            }
            sum = (sum + z) % FIELD_SIZE;
        }
    }

    return sum; // 결과는 α^sum 형태의 지수값, 결과가 -1이면 그냥 0 
}


Polynomial compute_syndromes(
    const Polynomial& r,
    int b,
    int t,
    const vector<int>& zech_table,
    const int FIELD_SIZE
) {
    Polynomial syndromes(2 * t - 1); // deg = 2t - 1

    for (int s = 0; s < 2 * t; ++s) {
        int alpha_eval = (b + s) % FIELD_SIZE;
        int result = evaluate_poly_alpha(r, alpha_eval, zech_table, FIELD_SIZE);

        if (result != -1) {
            syndromes.coeffs[s] = result;
            syndromes.mask[s] = true;
        }
    }

    display_polynomial(syndromes, "S");
    return syndromes;
}

pair<Polynomial, Polynomial> euclidean_algorithm(
    const Polynomial& S,
    int t,
    const vector<int>& zech_table,
    int FIELD_SIZE
) {
    // 초기 다항식들
    // r_-1 항을 나타내기가 애매하다
    // 그래서 initial i 를 0,1로 잡고 euclid algorithm 적용해줌
    Polynomial r0 = Polynomial(2 * t);   // r_0 = z^{2t}
    r0.coeffs[2 * t] = 0;                // α^0 = 1
    r0.mask[2 * t] = true;
    Polynomial t0(0);                    // t0 = 0 (zero poly)

    Polynomial r1 = S;                   // r1 = S(z)
    Polynomial t1 = Polynomial(0);       // t1 = 1
    t1.coeffs[0] = 0;
    t1.mask[0] = true;



    while (r1.degree() >= t) {
        auto [q, r2] = poly_divmod(r0, r1, zech_table, FIELD_SIZE);
        Polynomial t2 = poly_add(t0, poly_mul(q, t1, zech_table, FIELD_SIZE), zech_table, FIELD_SIZE);

        // 갱신
        r0 = r1;
        r1 = r2;
        t0 = t1;
        t1 = t2;
    }

    // Polynomial sigma = u1; // error locator poly
    Polynomial sigma = t1; // error locator poly
    Polynomial omega = r1; // error evaluator poly

    return {sigma, omega};
}

// 오류 위치 찾기: Chien Search
vector<int> chein_search(
    const Polynomial& sigma,
    const vector<int>& zech_table,
    int FIELD_SIZE
){
    vector<int> error_positions;

    // a^i (i = 0 ~ i = 2^m-2) 다 박아서, w(a^(-i))=0 되는 곳 찾아야함.
    for(int i=0; i<FIELD_SIZE; i++){
        int eval_power = (FIELD_SIZE - i) % FIELD_SIZE;
        int eval = evaluate_poly_alpha(sigma, eval_power, zech_table, FIELD_SIZE);
        // 0을 만족 -> 근임 -> error location
        if(eval==-1){
            error_positions.push_back(i);// i번째 위치에 오류가 있다.
            cout<<i<<endl;
        }
    }
    return error_positions;
}

// 오류 크기 계산: Forney's Formula
Polynomial compute_error_values(
    const Polynomial& sigma,
    const Polynomial& omega,
    const vector<int>& error_pos,
    const vector<int>& zech_table,
    int FIELD_SIZE
) {
    Polynomial error_poly(FIELD_SIZE - 1);

    // d/dx(σ(x)): formal derivative (계수 * 차수, characteristic 2 -> even 계수 사라짐)
    Polynomial sigma_deriv(sigma.degree() - 1);
    for (int i = 1; i <= sigma.degree(); i += 2) { // characteristic 2 -> 짝수차 계수는 0
        if (sigma.mask[i]) {
            sigma_deriv.coeffs[i - 1] = sigma.coeffs[i];
            sigma_deriv.mask[i - 1] = true;
        }
    }

    for (int j : error_pos) {
        int x_inv = (FIELD_SIZE - j) % FIELD_SIZE;

        int omega_val = evaluate_poly_alpha(omega, x_inv, zech_table, FIELD_SIZE);
        int sigma_deriv_val = evaluate_poly_alpha(sigma_deriv, x_inv, zech_table, FIELD_SIZE);

        if (sigma_deriv_val == -1) {
            cerr << "Error: sigma'(α^" << x_inv << ") = 0" << endl;
            exit(1);
        }

        // 오류 크기 = -ω(x⁻¹) / σ'(x⁻¹) → characteristic 2에서는 - = 자기 자신
        // int delta = (FIELD_SIZE + omega_val - sigma_deriv_val) % FIELD_SIZE;
        // int z = zech_table[delta];
        // 이거 아님...
        // if (z == -1) {
        //     cerr << "Zech undefined in Forney's: α^" << omega_val << " / α^" << sigma_deriv_val << endl;
        //     exit(1);
        // }

        int error_value = (omega_val - sigma_deriv_val + FIELD_SIZE) % FIELD_SIZE;
        error_poly.coeffs[j] = error_value;
        error_poly.mask[j] = true;
    }

    return error_poly;
}

// 오류 보정: 수신 다항식에서 오류 제거
Polynomial correct_errors(
    const Polynomial& received,
    const Polynomial& error_poly,
    const vector<int>& zech_table,
    int FIELD_SIZE
) {
    return poly_add(received, error_poly, zech_table, FIELD_SIZE);
}


#endif // 