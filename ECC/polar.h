#ifndef POLAR_H
#define POLAR_H

// headers
#include<vector>
#include<math.h>
#include<assert.h>
#include<string>
#include<algorithm>
#include<numeric>

#include <cstdint> // uint32_t...
#include <tuple>
#include <cmath>
#include <stack>

#include <iostream>
#include <random>
#include <cstdarg>
#include <fstream>


using namespace std;

extern vector<int> reliability_sequence; // 변수의 선언 (정의 X)

// structure definition
// struct SCL_Path{
//     // 1. LLR
//     vector<vector<double>> alpha;
//     // 2. hard_decision
//     vector<vector<bool>> beta;
//     // 3. u_cap
//     vector<bool> u_cap;
//     // 4. PM
//     double PM;

//     // 시작부터 그냥 vector의 크기를 지정해준다
//     // codelength와 node의 개수를 input으로 넣어준다
//     SCL_Path(int total_nodes, int N){
//         alpha.assign(total_nodes, vector<double>(N, 0.0));
//         beta.assign(total_nodes, vector<bool>(N, false));
//         u_cap.assign(N, false);
//         PM = 0.0;
//     }

//     SCL_Path(int total_nodes, int N, vector<double>& llr){
//         alpha.assign(total_nodes, vector<double>(N, 0.0));
//         beta.assign(total_nodes, vector<bool>(N, false));
//         u_cap.assign(N, false);
//         PM = 0.0;
//         // llr 값을 바탕으로 path의 alpha값 초기화해주기
//         for (int i = 0; i<N; i++){
//             alpha[0][i] = llr[i];
//         }
//     }
//};

// structure definition
struct SCL_Path{
    // 1. LLR
    vector<vector<double>> alpha;
    // 2. hard_decision
    vector<vector<bool>> beta;
    // 3. u_cap
    vector<bool> u_cap;
    // 4. PM
    double PM;

    // 시작부터 그냥 vector의 크기를 지정해준다
    // codelength와 node의 개수를 input으로 넣어준다
    SCL_Path(int total_nodes, int N, const vector<int>& node_sizes){
        alpha.resize(total_nodes);
        beta.resize(total_nodes);
        
        for(int i=0; i <total_nodes; i++){
            int node_size = node_sizes[i];
            alpha[i].assign(node_size, 0.0);
            beta[i].assign(node_size, false);
        }
        u_cap.assign(N, false);
        PM =0.0;
    }
    // 흠냐 이거 쓰려나
    SCL_Path(int total_nodes, int N, vector<double>& llr, const vector<int>& node_sizes){
        //cout<<"Hello boy";
        alpha.resize(total_nodes);
        beta.resize(total_nodes);
        
        for(int i=0; i <total_nodes; i++){
            int node_size = node_sizes[i];
            alpha[i].assign(node_size, 0.0);
            beta[i].assign(node_size, false);
        }
        u_cap.assign(N, false);
        PM =0.0;
        // llr 값을 바탕으로 path의 alpha값 초기화해주기
        for (int i = 0; i<N; i++){
            alpha[0][i] = llr[i];
        }
        //cout<<"Hello boy";
    }
};

// class definition
class POLAR{
private:
    // private member variables
    int N;          // codeword length
    int M;          // mother codeword length. Much stronger
    int K;          // information length
    int crc_len;    // crc length
    int K_pad;      // information length + crc length 
    int F;          // N - K_pad

    // Indices vector of each information
    vector<int> idx_F;		// frozen bit positions (including puncture postions)
    vector<int> idx_P;		// puncture pattern
    vector<int> idx_I;		// information bit positions
    vector<int> idx_Q;		// reliability sequence

    vector<int> node_sizes;


public: // public member functions

    // Constructor
    // Should add Arikan channel construction
    // 파라미터 조정 필요할듯. 애초에, 
    POLAR(int code_len, 
          int info_len,
          int crc_len,
          const string channel_construction_method = "Arikan",
          const double design_para = 0);
        
    // encoder
    vector<bool> encoder(vector<bool>* msg);
    // SC decoder
    vector<bool> sc_decoder(vector<double>* llr);
    // SCL decoder
    vector<bool> scl_decoder(vector<double>* llr, vector<bool> crc_g, int nL);
    
    // SCL decoder optimized
    vector<bool> scl_decoder_opt(vector<double>& llr, const vector<bool>& crc_polynomial ,int nL);

    // rate matching
    vector<bool> rate_matching(vector<bool>* in);
    // rate recovery
    vector<double> rate_recovery(vector<double>* in); 
    
    // Static member functions that can be used outside the class object
    // Huawei approximation
    static vector<int> rate_profiling_huawei_approx(int N);
    template<typename T>
    static vector<size_t> sort_indexes(const vector<T>& v);
    // Arikan (given reliability sequence)
    static vector<int> rate_profiling_polar_5G_Standard(int N);
    
    // crc related
    static vector<bool> crc_gen(vector<bool>* msg, vector<bool> crc_g);
    static bool crc_check_sum(vector<bool>* msg, vector<bool> crc_g);
    static void crc_division(vector<bool>* pad_msg, vector<bool> gen);
    

private: // private member functions for encoding and decoding
    // encoding
    vector<bool> polar_encode_recur(vector<bool> u);
    vector<bool> polar_encode_no_recur(vector<bool> u);
    // decoding
    // SC decode
    vector<bool> sc_node_operations_recur(vector<double>* alpha,
                                            const vector<bool>& F,
                                            vector<bool>* u_cap);

    //SC decode
    
    vector<bool> sc_node_operations_no_recur(vector<double>* alpha,
                                                    vector<bool> F,
                                                    vector<bool>* u_cap);
    
    // SCL decode
    void scl_node_operations(
        int N,
        const vector<bool>& F_Map,
        vector<vector<vector<double>>>& LLR,                   
        vector<vector<vector<bool>>>& hard_decision,         
        vector<double>& PM,
        vector<vector<bool>>& u_cap_List               
    );


    // scl_node_operartions 다시 구현
    void scl_node_operations_opt(
        int N,  
        const vector<bool>& F_Map,  
        vector<SCL_Path*>& paths,
        int max_nL);

    // core function of SCL: sort and prune sc decoders
    template<typename T>
    inline void sort_and_prune(vector<vector<T>>* V, vector<uint8_t> P);

};

vector<bool> crc_polynomial(const string crc_type);

template<typename T>
void display_vec(vector<T> vec){
    for(auto e : vec){
        cout<<e<<" ";;
    }
    cout<<endl;
}

#endif // !POLAR_H