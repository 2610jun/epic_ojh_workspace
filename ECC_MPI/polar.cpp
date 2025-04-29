#include "polar.h"
#include <iostream>
// reliability sequence
vector<int> reliability_sequence ={0, 1, 2, 4, 8, 16, 32, 3, 5, 64, 9, 6, 17, 10, 18, 128, 12, 33, 65, 20, 256, 34, 24, 36, 7, 129, 66, 512, 11, 40, 68, 130, 
    19, 13, 48, 14, 72, 257, 21, 132, 35, 258, 26, 513, 80, 37, 25, 22, 136, 260, 264, 38, 514, 96, 67, 41, 144, 28, 69, 42, 
    516, 49, 74, 272, 160, 520, 288, 528, 192, 544, 70, 44, 131, 81, 50, 73, 15, 320, 133, 52, 23, 134, 384, 76, 137, 82, 56, 27, 
    97, 39, 259, 84, 138, 145, 261, 29, 43, 98, 515, 88, 140, 30, 146, 71, 262, 265, 161, 576, 45, 100, 640, 51, 148, 46, 75, 266, 273, 517, 104, 162, 
    53, 193, 152, 77, 164, 768, 268, 274, 518, 54, 83, 57, 521, 112, 135, 78, 289, 194, 85, 276, 522, 58, 168, 139, 99, 86, 60, 280, 89, 290, 529, 524, 
    196, 141, 101, 147, 176, 142, 530, 321, 31, 200, 90, 545, 292, 322, 532, 263, 149, 102, 105, 304, 296, 163, 92, 47, 267, 385, 546, 324, 208, 386, 150, 153, 
    165, 106, 55, 328, 536, 577, 548, 113, 154, 79, 269, 108, 578, 224, 166, 519, 552, 195, 270, 641, 523, 275, 580, 291, 59, 169, 560, 114, 277, 156, 87, 197, 
    116, 170, 61, 531, 525, 642, 281, 278, 526, 177, 293, 388, 91, 584, 769, 198, 172, 120, 201, 336, 62, 282, 143, 103, 178, 294, 93, 644, 202, 592, 323, 392, 
    297, 770, 107, 180, 151, 209, 284, 648, 94, 204, 298, 400, 608, 352, 325, 533, 155, 210, 305, 547, 300, 109, 184, 534, 537, 115, 167, 225, 326, 306, 772, 157, 
    656, 329, 110, 117, 212, 171, 776, 330, 226, 549, 538, 387, 308, 216, 416, 271, 279, 158, 337, 550, 672, 118, 332, 579, 540, 389, 173, 121, 553, 199, 784, 179, 
    228, 338, 312, 704, 390, 174, 554, 581, 393, 283, 122, 448, 353, 561, 203, 63, 340, 394, 527, 582, 556, 181, 295, 285, 232, 124, 205, 182, 643, 562, 286, 585, 
    299, 354, 211, 401, 185, 396, 344, 586, 645, 593, 535, 240, 206, 95, 327, 564, 800, 402, 356, 307, 301, 417, 213, 568, 832, 588, 186, 646, 404, 227, 896, 594, 
    418, 302, 649, 771, 360, 539, 111, 331, 214, 309, 188, 449, 217, 408, 609, 596, 551, 650, 229, 159, 420, 310, 541, 773, 610, 657, 333, 119, 600, 339, 218, 368, 
    652, 230, 391, 313, 450, 542, 334, 233, 555, 774, 175, 123, 658, 612, 341, 777, 220, 314, 424, 395, 673, 583, 355, 287, 183, 234, 125, 557, 660, 616, 342, 316, 
    241, 778, 563, 345, 452, 397, 403, 207, 674, 558, 785, 432, 357, 187, 236, 664, 624, 587, 780, 705, 126, 242, 565, 398, 346, 456, 358, 405, 303, 569, 244, 595, 
    189, 566, 676, 361, 706, 589, 215, 786, 647, 348, 419, 406, 464, 680, 801, 362, 590, 409, 570, 788, 597, 572, 219, 311, 708, 598, 601, 651, 421, 792, 802, 611, 
    602, 410, 231, 688, 653, 248, 369, 190, 364, 654, 659, 335, 480, 315, 221, 370, 613, 422, 425, 451, 614, 543, 235, 412, 343, 372, 775, 317, 222, 426, 453, 237, 
    559, 833, 804, 712, 834, 661, 808, 779, 617, 604, 433, 720, 816, 836, 347, 897, 243, 662, 454, 318, 675, 618, 898, 781, 376, 428, 665, 736, 567, 840, 625, 238, 
    359, 457, 399, 787 ,591, 678, 434, 677, 349, 245, 458, 666, 620, 363, 127, 191, 782, 407, 436, 626, 571, 465, 681, 246, 707, 350, 599, 668, 790, 460, 249, 682, 
    573, 411, 803, 789, 709, 365, 440, 628, 689, 374, 423, 466, 793, 250, 371, 481, 574, 413, 603, 366, 468, 655, 900, 805, 615, 684, 710, 429, 794, 252, 373, 605, 
    848, 690, 713, 632, 482, 806, 427, 904, 414, 223, 663, 692, 835, 619, 472, 455, 796, 809, 714, 721, 837, 716, 864, 810, 606, 912, 722, 696, 377, 435, 817, 319, 
    621, 812, 484, 430, 838, 667, 488, 239, 378, 459, 622, 627, 437, 380, 818, 461, 496, 669, 679, 724, 841, 629, 351, 467, 438, 737, 251, 462, 442, 441, 469, 247, 
    683, 842, 738, 899, 670, 783, 849, 820, 728, 928, 791, 367, 901, 630, 685, 844, 633, 711, 253, 691, 824, 902, 686, 740, 850, 375, 444, 470, 483, 415, 485, 905, 
    795, 473, 634, 744, 852, 960, 865, 693, 797, 906, 715, 807, 474, 636, 694, 254, 717, 575, 913, 798, 811, 379, 697, 431, 607, 489, 866, 723, 486, 908, 718, 813, 
    476, 856, 839, 725, 698, 914, 752, 868, 819, 814, 439, 929, 490, 623, 671, 739, 916, 463, 843, 381, 497, 930, 821, 726, 961, 872, 492, 631, 729, 700, 443, 741, 
    845, 920, 382, 822, 851, 730, 498, 880, 742, 445, 471, 635, 932, 687, 903, 825, 500, 846, 745, 826, 732, 446, 962, 936, 475, 853, 867, 637, 907, 487, 695, 746, 
    828, 753, 854, 857, 504, 799, 255, 964, 909, 719, 477, 915, 638, 748, 944, 869, 491, 699, 754, 858, 478, 968, 383, 910, 815, 976, 870, 917, 727, 493, 873, 701, 
    931, 756, 860, 499, 731, 823, 922, 874, 918, 502, 933, 743, 760, 881, 494, 702, 921, 501, 876, 847, 992, 447, 733, 827, 934, 882, 937, 963, 747, 505, 855, 924, 
    734, 829, 965, 938, 884, 506, 749, 945, 966, 755, 859, 940, 830, 911, 871, 639, 888, 479, 946, 750, 969, 508, 861, 757, 970, 919, 875, 862, 758, 948, 977, 923, 
    972, 761, 877, 952, 495, 703, 935, 978, 883, 762, 503, 925, 878, 735, 993, 885, 939, 994, 980, 926, 764, 941, 967, 886, 831, 947, 507, 889, 984, 751, 942, 996, 
    971, 890, 509, 949, 973, 1000, 892, 950, 863, 759, 1008, 510, 979, 953, 763, 974, 954, 879, 981, 982, 927, 995, 765, 956, 887, 985, 997, 986, 943, 891, 998, 766, 
    511, 988, 1001, 951, 1002, 893, 975, 894, 1009, 955, 1004, 1010, 957, 983, 958, 987, 1012, 999, 1016, 767, 989, 1003, 990, 1005, 959, 1011, 1013, 895, 1006, 1014, 1017, 1018, 
    991, 1020, 1007, 1015, 1019, 1021, 1022 ,1023};
// public member functions
// parameterized constructor




void print_buffer_sizes(
    const vector<vector<vector<double>>>& LLR,
    const vector<vector<vector<bool>>>& hard_decision,
    const vector<vector<bool>>& u_cap,
    const vector<double>& PM
) {
    cout << "LLR size: ["
         << LLR.size() << "]["
         << (LLR.empty() ? 0 : LLR[0].size()) << "]["
         << (LLR.empty() || LLR[0].empty() ? 0 : LLR[0][0].size()) << "]" << endl;

    cout << "hard_decision size: ["
         << hard_decision.size() << "]["
         << (hard_decision.empty() ? 0 : hard_decision[0].size()) << "]["
         << (hard_decision.empty() || hard_decision[0].empty() ? 0 : hard_decision[0][0].size()) << "]" << endl;

    cout << "u_cap size: ["
         << u_cap.size() << "]["
         << (u_cap.empty() ? 0 : u_cap[0].size()) << "]" << endl;

    cout << "PM size: ["
         << PM.size() << "]" << endl;
}


// f function`
void f(const vector<double> &llr_parents, vector<double> &llr_leftchild){
    int half = llr_parents.size()/2;
    for(int i =0; i<half; i++){
        // 1. tanh
        //double temp = 2.0 * atanh(tanh(alpha_left / 2.0) * tanh(alpha_right / 2.0));  // f-function
        //result[i] = 2.0 * atanh(tanh(left[i] / 2.0) * tanh(right[i] / 2.0));  // f-function

        // 2. min-sum
        int sign = (1 - 2 * ((llr_parents[i]) * (llr_parents[i+half]) < 0));
        llr_leftchild[i] = (std::min(abs(llr_parents[i]), abs(llr_parents[i+half])) * sign);

        // test code
        // cout<<"-------------------------------------"<<endl;
        // cout<<"alpha_left: "<< llr_parents[i]<<"  alpha_right: "<< llr_parents[i+half]<<endl;
        // cout<<"|alpha_left|: "<< abs(llr_parents[i])<<"  |alpha_right|: "<< abs(llr_parents[i+half])<<endl;
        // cout<<"sign: "<<sign<<endl;
        // cout<<"f_result: "<<llr_leftchild[i]<<endl;
        // cout<<"-------------------------------------"<<endl;

    }
}

// g function
void g(const vector<double> &llr_parents, const vector<bool> &hard_decision_left, vector<double> &llr_rightchild){
    int half = hard_decision_left.size();
    for(int i=0; i<half; i++){
        double right = llr_parents[i+half];
        double left = llr_parents[i];
        llr_rightchild[i] = (hard_decision_left[i]==0)? right + left : right - left;
        // cout<<"-------------------------------------"<<endl;
        // cout<<"right: "<< llr_parents[i+half]<<"  left: "<< llr_parents[i]<<endl;
        // cout<<"hard decision of the left child: " << hard_decision_left[i] << endl;
        // cout<< "right + left: "<< right + left<< endl;
        // cout<< "right - left: "<< right - left<< endl;
        // cout<< "llr_rightchild: "<< llr_rightchild[i] <<endl;
        // cout<<"-------------------------------------"<<endl;
    }
}

void hard_decision(const vector<bool>& hard_decision_left, const vector<bool>& hard_decision_right, vector<bool> &hard_decision_parents){
    int half = hard_decision_left.size();
    for(int i = 0; i<half; i++){
        bool temp = hard_decision_left[i] ^ hard_decision_right[i];
        hard_decision_parents[i] = temp;
        hard_decision_parents[i+half] = hard_decision_right[i];
        // cout<<"-------------------------------------"<<endl;
        // cout<<"hard decision left: "<< hard_decision_left[i] <<"  hard decision right: "<< hard_decision_right[i]<<endl;
        // cout<< "l ^ r: "<< (hard_decision_left[i] ^ hard_decision_right[i]) << endl;
        // cout<< "temp: "<< temp<<endl;
        // cout<<"hard decision left(l^r): "<< hard_decision_parents[i]<<endl;
        // cout<<"hard decision right(r): "<< hard_decision_parents[i+half]<<endl;
        // cout<<"-------------------------------------"<<endl;
    }

}

POLAR::POLAR(int code_len, int info_len, int crc_len, const string channel_construction_method, const double design_para){
    //---------------------------------------------------------------------------------
    // polar construction
    // Input:
    //		info_length: information bits length
    //		code_length: coded bit length
    // 		construct_method: "Huawei approx", "Arikan", "BP", "GA""
    // 		design_para: N/A for"Huawei approx"; erasure probability for "BP"; design SNR in dB for "GA"
    // 
    //---------------------------------------------------------------------------------
    //M = code_len; // codeword length(=M) 

    (void) design_para;
    N = code_len;
    M = code_len;       // 아직까지는.. 사실 M을 뭐 쓸일이 아직 없다
    K = info_len;       // information length(=k)
    // crc_len = crc_len;
    K_pad = K + crc_len;  // effective info length including crc bits
    F = N - K_pad;


    // Obtain channel's reliability
    // m_Q: 크기 M의 reliability sequence indices sequence가 필요하다.
    if(channel_construction_method.compare("Huawei Approx")==0){
        idx_Q = rate_profiling_huawei_approx(N);
    }
    else if (channel_construction_method.compare("Polar 5G standard")==0){
        // reliability sequence에서 M 크기만큼 추출해오면 될거같음
        idx_Q = rate_profiling_polar_5G_Standard(N);
    }

    // puncture pattern.. 이건 나중에 고려해주자
    // puncture pattern
    //idx_P.reserve(idx_N - idx_M);
    //m_P = vector<int>(idx_Q.begin(), idx_Q.begin() + (idx_N - idx_M));
    //sort(idx_P.begin(), idx_P.end()); 

    // frozen bits positions
    idx_F.reserve(F);
    idx_F = vector<int>(idx_Q.begin(), idx_Q.begin()+F);
    sort(idx_F.begin(), idx_F.end());

    // information bit positions
    idx_I.reserve(K_pad); // 메모리 확보
    idx_I = vector<int>(idx_Q.end()-K_pad, idx_Q.end()); // m_Q에서 K 길이만큼 뒤에서 추출
    sort(idx_I.begin(), idx_I.end()); // m_I를 오름차순으로 정렬

    // vector<int> node_sizes; 
    int total_nodes = 2*N-1;
    node_sizes.resize(total_nodes);
    for(int i = N-1; i < total_nodes; i++){
        node_sizes[i]=1;

    }
    for(int i = N-2; i>=0; i--){
        int left = 2*i +1;
        node_sizes[i]= 2*node_sizes[left];
    }

    
}
  
// encoder
vector<bool> POLAR::encoder(vector<bool>* msg){
    //assert (msg->size()==m_K);
    // m_Q와 m_I 이용해서 information bit 채워준다.
    vector<bool> u(N, 0);
    
    for(int i = 0; i< K_pad; i++){
        u[idx_I[i]]=(*msg)[i];
        //test code cout<<m_I[i]<<endl;
    }
    // no-recursion
    //return polar_encode_no_recur(u);
    return polar_encode_no_recur(u);
    //return polar_encode_recur(u);

}
// SC decoder
vector<bool> POLAR::sc_decoder(vector<double>* llr){

    // Frozen bit map을 구성해야함
    vector<bool>F_map(N, 0);
    for(auto e:idx_F){
        F_map[e]=1;
    }

    // decoding algorithm 적용
    // llr 계산값을 넣어주자
    // 
    vector<bool> u_cap; //최종적으로 디코딩된 애가 u_cap으로 모이게됨.
    //sc_node_operations_recur(llr, F_map, &u_cap);
    sc_node_operations_no_recur(llr, F_map, &u_cap);

    // extract the message bits
    vector<bool> msg_cap; msg_cap.reserve(K_pad);
    for (auto e : idx_I){
        msg_cap.push_back(u_cap[e]);
    }
    //for(auto e: msg_cap){
    //    cout<<e;
    //}
    //cout<<endl;
    return msg_cap;
}
// SCL decoder


// optimize
vector<bool> POLAR::scl_decoder_opt(vector<double>& llr, const vector<bool>& crc_polynomial, int nL){
    // 1. 필요한 constant 값들 지정해준다.
    /**
     * A: Length of the codeword except crc bits
     * N: Code
     * Frozen Map
     * total nodes of the decoding tree
     */
    // 잘 보이도록 한곳에 모아두기
    // int len_g = crc_polynomial.size()-1;
    //int N = llr.size();
    // 진짜 실화냐...
    // int A = m_K - len_g;
    //int K_pad = + len_g;
    //int K = m_K;
    int total_nodes = 2*N - 1;

    vector<bool> F_Map(N, 0);
    // idx_F: Frozen bit의 인덱스들 오름차순으로 저장해둠. 
    for(auto e:idx_F){
        F_Map[e] = 1;
        // cout<<e<<endl;
    }

    /**
     * 2. 그리고, SCL_Path 구조체를 선언하여, Candidate SC decoder들을 관리해야한다.
     * 
     * 여기서 비효율이 제일 많이 생긴 것 같다. 
     * 일단 분기 과정에서 복사는 SCL_Path 구조체의 shallow copy를 사용해준다.
     * 불필요한 메모리 복사 및 초기화 과정을 없애준다.
     */
    SCL_Path* path0 = new SCL_Path(total_nodes, N, llr, node_sizes);
    vector<SCL_Path*> paths = {path0};

    // cout<<"OK?"<<endl;
    //////////////////////
    /**
     * 3. scl_node_operation 함수를 호출하여 scl의 nodal operation을 수행해준다.
     */
    // cout<<N<<M<<K<<K_pad<<F<<endl;
    // cout<<F_Map.size()<<endl;
    scl_node_operations_opt(N, F_Map, paths, nL);

    // cout<<"OK?"<<endl;

    /**
     * 4. SCL 결과 나온 애를 바탕으로 final decision을 도출한다
     */
        // cout<<"Finish scl node operations"<<endl;
    // best decoding result 찾기
    vector<bool> msg_cap(K); vector<bool> temp_cap(K_pad);

    vector<double> PM;
    for(int i = 0; i< nL; i++){
        PM.push_back(paths[i]->PM);
        // cout<<paths[i]->PM<<endl;// test code
        // cout<<i<<"th PM "<<PM[i]<<endl;
    }
    vector<size_t> idx_pm = sort_indexes(PM);
    // test code
    // 이 과정 사실 필요없음
    // for(int i=0; i<nL; i++){
    //     cout<<idx_pm[i]<<endl;
    // }
    int final_idx = idx_pm[0];

    //일단 u_cap_list에서 msg_candi_list 값들을 추출해줌
    for(int i = 0; i< nL; i++){
        for(int j = 0; j< K_pad; j++){
            //cout<<m_I[j]<<endl;
            temp_cap[j] = paths[idx_pm[i]]->u_cap[idx_I[j]];
            // cout<<paths[idx_pm[i]]->u_cap[m_I[j]]<<endl;
        }
        // crc test 진행
        if(crc_check_sum(&temp_cap, crc_polynomial)){
            final_idx = idx_pm[i];
            //cout<<"Final idx: "<<final_idx<<endl;
            //cout<<"OK!"<<endl;
            break;
        }
    }
    // 각각 msg 값에 대한 crc test를 수행한다.
    // PM값 가장 낮은 놈을 최종 msg_cap으로 출력한다.
    for(int i = 0; i<K; i++){
        //cout<<"i: "<<i<<endl;
        //cout<<m_I[i]<<endl;
        msg_cap[i] = paths[final_idx]->u_cap[idx_I[i]];
    }
    
    return msg_cap;

}

// rate matching
vector<bool> POLAR::rate_matching(vector<bool>* in){
    (void) in;
    return {};
}
// rate recovery
vector<double> POLAR::rate_recovery(vector<double>* in){
    (void) in;
    return {};
}

// Static member functions that can be used outside the class object
// Huawei approximation
vector<int> POLAR::rate_profiling_huawei_approx(int N){
    vector<double> W(N, 0);
    vector<int> seq(N, 0);

    for (int j = 0; j < N; j++) {
        int tmp = j;

        for (int k = 0; k < N; k++)
        {
            double bit_val = tmp % 2;
            W[j] += bit_val * pow(2, (k * 0.25));
            tmp = tmp / 2;
            if (tmp == 0)
                break;
        }
    }
    vector<size_t> sorted_indices = sort_indexes(W);
    for (int i = 0; i < N; i++) {
        seq[i] = sorted_indices[i];
    }

    return seq;
}

// static function to sort the indices in ascending order.
// 원소들을 정렬했을때의 인덱스 순서를 반환하는 역할을 한다
template<typename T>
vector<size_t> POLAR::sort_indexes(const vector<T>& v){
    // initialize original index locations
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0); // idx[i]=i

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values
    // 오름차순
    stable_sort(idx.begin(), idx.end(),
                [&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

    return idx;
}

// Arikan (given reliability sequence)
vector<int> POLAR:: rate_profiling_polar_5G_Standard(int N){
    assert(N<=1024); // 왜냐하면 reliability sequence가 1024까지밖에 정의가 안되어있다.
    vector<int> result;
    result.reserve(N);
    for(size_t i=0; i< reliability_sequence.size(); i++){
        if(reliability_sequence[i]<N){
            result.push_back(reliability_sequence[i]);
        }
    }
    return result;
}

// encoding
// 1. Recursion (Top-down)
// top-down
vector<bool> POLAR::polar_encode_recur(vector<bool> u){
    //---------------------------------------------------------------------------------
    // This function encodes u into x. x = u * F_N
    // where N = 2 ^ n bits,  F_N = F kroncker N, F = [1 0; 1 1];
    // Dr. J Mao 2021 Sep
    //---------------------------------------------------------------------------------

    uint32_t N = u.size();
    if (N == 1)
        return u;
    else {
        // butterfly operation
        vector<bool> u1_xor_u2; u1_xor_u2.reserve(N / 2);
        for (uint32_t i = 0; i < N / 2; i++)
            u1_xor_u2.push_back(u[i] xor u[i + N / 2]);

        // recursive encoding for left half
        vector<bool> x; x.reserve(N);
        x = polar_encode_recur(u1_xor_u2);

        // for right half
        vector<bool> x2 = polar_encode_recur(vector<bool>(u.end() - N / 2, u.end()));
        x.insert(x.end(), x2.begin(), x2.end());

        return x;
    }   
}

// 2. Non-recursion (Bottom-up)
vector<bool> POLAR::polar_encode_no_recur(vector<bool> u) {
    uint32_t N = u.size();
    vector<bool> x = u; // 초기화, 결과를 저장할 벡터
    
    // 단계적으로 F_N 적용 (비트-리버설 없이 처리)
    /** 단계적으로 F_N 연산을 적용한다.
     * step: 연산의 단계. 1->2->4->8 ...
     * 
     */
    for (uint32_t step = 1; step < N; step *= 2) {
        // stride of each step   
        for (uint32_t i = 0; i < N; i += 2 * step) { 

            for (uint32_t j = 0; j < step; ++j) {
                // Butterfly operation
                x[i + j] = x[i + j] ^ x[i + j + step];
            }
        } 
    }
    
    return x;
}
// decoding
// SC decode
/**
 * alpha: 신뢰도 값 (LLR, Log-Likelihood Ratio)
 * beta: 복호화된 Hard decision bits를 저장하는 벡터임. 각 노드에서 디코딩된 비트들의 집합을 의미한다.
 *       최종적으로 디코딩된 코드워드 (정보 비트 + Frozen Bit 포함)를 반환한다. 
 * F: Frozen bit 정보. 1이면 Frozen bit이고 0이면 Information bit이다.
 * u_cap: 디코딩된 정보 비트를 저장한다
 */


vector<bool> POLAR::sc_node_operations_recur(vector<double>* alpha, const vector<bool>& F, vector<bool>* u_cap)
{
    int N = alpha->size();
    vector<bool> beta; beta.reserve(N); // hard decisions for corresponding soft bits

    //std::cout << "alpha = [";
    //for (auto e : alpha)
    //	std::cout << e << " ";
    //std::cout<<"]"<< std::endl;

    if (N == 1) { // leaf nodes
        if (F[0] == 1) {
            beta.push_back(0); // frozen bits always zero
        }
        else {
            beta.push_back(((*alpha)[0] < 0) ? 1 : 0); // threshold detection
        }

        u_cap->push_back(beta[0]); // save decoded bits
    }
    else { // non-leaf nodes
        vector<double> a(vector<double>(alpha->begin(), alpha->begin() + N / 2));
        vector<double> b(vector<double>(alpha->end() - N / 2, alpha->end()));

        // calculate llr for its left child
        vector<double> alpha_left(N / 2);
        for (int i = 0; i < N / 2; i++) {
            alpha_left[i] = 2.0 * atanhf(tanhf(a[i] / 2.0) * tanhf(b[i] / 2.0)); // slower
            //int sign = (1 - 2 * (a[i] * b[i] < 0));
            //alpha_left[i] = (std::min(abs(a[i]), abs(b[i])) * sign); // much faster with ignorable loss
        }

        // recursive decoding, pass llr message to its left child and expect for corresping hard decision
        vector<bool> F_left(vector<bool>(F.begin(), F.begin() + N / 2));
        vector<bool> beta_left = sc_node_operations_recur(&alpha_left, F_left, u_cap);

        // calculate llr for its right child
        vector<double> alpha_right(N / 2);
        for (int i = 0; i < N / 2; i++) {
            alpha_right[i] = (beta_left[i] == 0) ? b[i] + a[i] : b[i] - a[i];
        }

        // recursive decoding, pass llr message to its right child and expect for corresping hard decision
        vector<bool> F_right(vector<bool>(F.end() - N / 2, F.end()));
        vector<bool> beta_right = sc_node_operations_recur(&alpha_right, F_right, u_cap);

        // combine hard decision from its both children and return to its parent

        for (int i = 0; i < N / 2; i++) {
            beta.push_back(beta_left[i] xor beta_right[i]);
        }
        beta.insert(beta.end(), beta_right.begin(), beta_right.end());
    }
    //std::cout << "beta = [";
    //for (auto e : beta)
    //	std::cout << e << " ";
    //std::cout << "]" << std::endl;
    return beta;
}




// Node structure를 구성해서 tree를 구성해야 한다.
// 최종적으로 u_cap에 estimated bit가 저장이된다.
struct Node{
    int height; // 최대 n(=logN). leaf node는 0의 height를 가지게된다.
    int num_element; // 2^h의 element를 가지게된다. leaf node는 1개의 element, head node는 2^n의
    int idx;  
    Node* parent;
    Node* left_child;
    Node* right_child;
    vector<double> alpha;
    vector<bool> beta;

    // Parameterized constructor
    Node(int height,int idx, Node* parent)
    : height(height), num_element(pow(2,height)), idx(idx), parent(parent), left_child(nullptr), right_child(nullptr), alpha(num_element, 0.0), beta(num_element, 0){}
};

// SC 디코딩 비재귀 DFS 방식


void display(Node* current){
    cout<<"Height: "<<current->height<<" "<<"Num: "<<current->idx<<endl;// 
    cout<<"Alpha: ";
    for(auto e: current->alpha){
        cout<<e<<" ";
    }
    cout<<endl;
    cout<<"Beta: ";
    for(auto e: current->beta){
        cout<<e<<" ";
    }  
    cout<<endl;

    if(current->height==0){
        cout<<"Hard decision: "<<current->beta[0]<<endl;
    }
}

vector<bool> POLAR::sc_node_operations_no_recur(vector<double>* alpha, vector<bool> F, vector<bool>* u_cap) {
    //int N = alpha->size();
    vector<bool> beta(N, 0);  // 초기화된 beta 벡터

    // 1. 트리의 루트 노드 생성
    Node* root = new Node(log2(N), 0, nullptr);
    root->alpha = *alpha; // LLR 값 초기화

    //cout<<e<<" ";
    //cout<<root->alpha.size() <<" ";

    // 2. DFS 탐색을 위한 스택 (비재귀)
    stack<Node*> sc_stk;
    sc_stk.push(root);


    // 3. DFS 탐색 시작
    while (!sc_stk.empty()) {
        Node* cur = sc_stk.top();
        sc_stk.pop();
        int half = cur->num_element / 2;
        //cout<<half<<endl;

        // 리프 노드 (height == 0) 처리
        if (cur->height == 0) {
            int bit_idx = cur->idx;  // 현재 리프 노드가 위치한 인덱스
            // Frozen bit이면 0, 아니면 hard decision 수행
            double temp = (F[bit_idx] == 1) ? 0 : ((cur->alpha[0] < 0) ? 1 : 0);
            cur->beta[0]=temp;
            u_cap->push_back(temp);
            //display(cur); // test code
            //sc_stk.push(cur->parent);
            continue;
        }

        // 1. al
        // 아직 자식 노드가 없는 경우 (처음 방문): left child로 옮겨감
        if (cur->left_child == nullptr && cur->right_child == nullptr) {
            cur->left_child = new Node(cur->height - 1, cur->idx * 2, cur);

            // Left Child LLR 계산
            for (int i = 0; i < half; i++) {
                //double temp = 2.0 * atanh(tanh(cur->alpha[i] / 2.0) * tanh(cur->alpha[i + half] / 2.0));  // f-function
                //cur->left_child->alpha[i] = temp;
                
                int sign = (1 - 2 * ((cur->alpha[i]) * (cur->alpha[i + half]) < 0));
                double temp = (std::min(abs(cur->alpha[i]), abs(cur->alpha[i + half])) * sign); // much faster with ignorable loss
                cur->left_child->alpha[i] = temp;
               
            }

            // 스택에 추가 (DFS 순서: left -> parent)
            sc_stk.push(cur);
            //sc_stk.push(cur->right_child);
            sc_stk.push(cur->left_child);
            //display(cur); // test code
        }
        // 2. bl값 토대로 ar 값 계산해주기
        // 이미 방문한 경우 (beta 계산)
        else if (cur->left_child!=nullptr && cur->right_child==nullptr){
            cur->right_child = new Node(cur->height - 1, cur->idx * 2 + 1, cur); // right child 선언해준다
            Node* left = cur->left_child;
            Node* right = cur->right_child;

            // alpha값을 계산한다. ar
            for (int i = 0; i < half; i++) {
                right->alpha[i] = (left->beta[i] == 0) ? cur->alpha[i + half] + cur->alpha[i] : cur->alpha[i + half] - cur->alpha[i];
            }
            
            // 그 다음 cur와 cur->right를 stack에 넣어준다.
            sc_stk.push(cur);
            //sc_stk.push(cur->right_child);
            sc_stk.push(cur->right_child);
            //cout<<"height: "<<cur->height<<" "<<"num: "<<cur->idx<<endl;// test code
            //display(cur); // test code
        }
        // 3. bl, br 값이 모두 계산되었을때 처리
        else if(cur->left_child!=nullptr && cur->right_child!=nullptr){
            // 부모 노드의 beta 값 갱신
            //cout<<"Hey...."<<endl;// test code
            Node* left = cur->left_child;
            Node* right = cur->right_child;
            for (int i = 0; i < half; i++) {
                cur->beta[i] = left->beta[i] xor right->beta[i];
                cur->beta[i+half] = right->beta[i];
            }

            //display(cur); // test code///

            // if(cur->parent!=nullptr){
            //      sc_stk.push(cur->parent);
            // }
            // sc_stk.push(cur->parent);
            
        }
    }
    //for(auto e: *u_cap){
    //    cout<<e<<" ";
    //}
    //cout<<endl;
    //cout<<(*u_cap).size()<<" ";
    return root->beta;
}

// DFS 순회는 stack이랑 cur_height & cur_id로 관리하자

// List 구조체를 선언해야할듯

// 최종적으로 u_cap에 estimated bit가 저장이된다.
enum NodeStage{
    FirstVisit, 
    AfterLeftDone,
    AfterRightDone
};

struct Node_SCL{
    int node_id;    // left = 2*i + 1, right = 2*i + 2
    int depth;
    int node_size;
    NodeStage stage;
    
};

void node_display(Node_SCL e){
    cout<<"node stage: "<<e.stage<<endl;
}




// scl_node_operartions 다시 구현
void POLAR::scl_node_operations_opt(int N, const vector<bool>& F_Map, vector<SCL_Path*>& paths, int max_nL){
    /**
     * 1. DFS를 진행할 Stack을 만들기. 
     * 2. Leaf node: frozen bits, information bit에 따른 분기 처리
     * 3. Non-leaf node: SC decoder를 할때랑 별반 다르지 않음
     */
    // 0. 필요한 변수들 선언하기
    int cur_num_list = 1;
    //int num_node = 2*N-1; // non-leaf: N-1, Leaf: N개

    // 1. Tree traversal을 위한 Stack 구성하기
    stack<Node_SCL> dfs_stack; // Tree traversal을 수행할 Stack
    dfs_stack.push({0, 0, N, FirstVisit});
    while(!dfs_stack.empty()){
        Node_SCL cur_node = dfs_stack.top(); dfs_stack.pop();
        int cur_id = cur_node.node_id;
        int cur_size = cur_node.node_size;
        
        // cout << "[DFS] cur_id: " << cur_id
        // << ", cur_size: " << cur_size
        // << ", stage: " << cur_node.stage
        // << ", stack_size: " << dfs_stack.size()
        // << ", cur_num_list: " << cur_num_list << endl;

        // 1. Leaf nodeb
        if(cur_size == 1){
            //cout<<"Here is the leaf node."<<endl;
            int leaf_id = cur_id - (N-1);
            // frozen bit
            if(F_Map[leaf_id]==1){
                for(int l=0; l<cur_num_list; l++){
                    SCL_Path& cur_list = (*(paths[l]));
                    double alpha = cur_list.alpha[cur_id][0];
                    cur_list.beta[cur_id][0] = 0;
                    cur_list.u_cap[leaf_id] = 0;
                    // 핵심. PM 업데이트 해야함
                    double temp = (alpha<0)? abs(alpha) : 0.0; // 얘를 좀 더 하드웨어 친화적인 코드로 바꿔야한다
                    cur_list.PM+= temp;

                    // cout<<"Frozen"<<endl; // test code
                }
            }
            // information bit
            // 여기가 진짜 슈퍼 핵심임
            // Information bit에서 List의 분기가 진행되어야한다.
            else{
                vector<SCL_Path*> new_paths;
                vector<double> new_PMs;
                // 일단 분기를 시작한다
                for(int l=0; l<cur_num_list; l++){
                    SCL_Path* orig = paths[l];
                    double alpha = orig->alpha[cur_id][0];

                    // Case 0
                    SCL_Path* path0 = new SCL_Path(*orig);
                    path0->beta[cur_id][0]=0;
                    path0->u_cap[leaf_id] = 0;
                    path0->PM += (alpha<0)? abs(alpha) : 0.0;

                    new_paths.push_back(path0);
                    new_PMs.push_back(path0->PM);

                    // Case 1 
                    SCL_Path* path1 = new SCL_Path(*orig);
                    path1->beta[cur_id][0]= 1;
                    path1->u_cap[leaf_id] = 1;
                    path1->PM += (alpha>0)? abs(alpha) : 0.0;
                    // cout<<"PM: "<<path1->PM<<endl; // test code

                    new_paths.push_back(path1);
                    new_PMs.push_back(path1->PM);
                    // cout<<"Non-Leaf"<<endl; // test code
                }

                // 기존의 path들 메모리 해제
                for(int l = 0; l<cur_num_list; l++){
                    delete paths[l];
                }
                paths.clear();
                // 정렬된 인덱스 얻기 (PM 오름차순)
                vector<size_t> sorted_idx = sort_indexes(new_PMs);

                // 새로운 path 리스트 구성
                vector<SCL_Path*> pruned_paths;
                int new_num_list = min((int)new_paths.size(), max_nL);
                // cout<<"New num list: "<< new_num_list<<endl;
                for(int i =0; i<new_num_list; i++){
                    pruned_paths.push_back(new_paths[sorted_idx[i]]);
                }

                // 나머지는 해제
                for(int i = new_num_list; i<(int)new_paths.size(); i++){
                    delete new_paths[sorted_idx[i]];
                }
                // 갱신
                paths = pruned_paths;
                cur_num_list = new_num_list;
                // cout<<"5"<<endl; // test code

            }
        }
        // 2. Non-Leaf node
        else{
            int half = cur_size/2;
            // 1. FirstVisit: f function
            if(cur_node.stage == FirstVisit){
                for(int l=0; l< cur_num_list; l++){
                    SCL_Path& cur_list = *(paths[l]);
                    f(cur_list.alpha[cur_id], cur_list.alpha[2*cur_id+1]);
                }
                dfs_stack.push({cur_id, cur_node.depth, cur_node.node_size, AfterLeftDone}); // 자기 자신을 push한다.
                dfs_stack.push({2*cur_id+1, cur_node.depth+1, half, FirstVisit}); // 그리고나서 왼쪽 자식을 push한다.

            }
            // 2. AfterLeftDone: g function
            else if(cur_node.stage == AfterLeftDone){
                for(int l=0; l< cur_num_list; l++){
                    SCL_Path& cur_list = *(paths[l]);
                    g(cur_list.alpha[cur_id], cur_list.beta[2*cur_id+1], cur_list.alpha[2*cur_id+2]);
                }
                dfs_stack.push({cur_id, cur_node.depth, cur_node.node_size, AfterRightDone}); // 자기 자신을 push한다.
                dfs_stack.push({2*cur_id+2, cur_node.depth+1, half, FirstVisit}); // 그리고나서 오른쪽 자식을 push한다.
            }
            // 3. AfterRightDone: Hard decision for parent node, Butterfly operation
            else if(cur_node.stage == AfterRightDone){
                for(int l=0; l< cur_num_list; l++){
                    SCL_Path& cur_list = *(paths[l]);
                    hard_decision(cur_list.beta[cur_id*2+1], cur_list.beta[cur_id*2+2],cur_list.beta[cur_id]);
                }
            }


        }

    }

}


// core function of SCL: sort and prune sc decoders
template<typename T>
void POLAR::sort_and_prune(vector<vector<T>>* V, vector<uint8_t> P){
    // Should select beta, u_cap, and llr based on selected_bit
    // P의 idx 값에 해당하는 V를 추출해서 가져와야한다.
    // P는 이미 PM에 의해서 정렬된 인덱스임. 그 idx에 해당하는 애들만 가져오면 된다.
    vector<vector<T>> temp;
    for(auto idx : P){
        temp.push_back((*V)[idx]);
    }

    // 그 다음에 temp (pruning 완료)를 기존의 V와 바꿔줘야한다.
    V->swap(temp);
}


// crc related
vector<bool> POLAR::crc_gen(vector<bool>* msg, vector<bool> crc_g){
    /**
     * input: msg, crc generator polynomial
     * output: crc bit(= crc_g.len() - 1)
     */
    // 1. msg padding 진행
    size_t crc_len = crc_g.size()-1;
    vector<bool> pad_msg(msg->begin(), msg->end()); // 일단 복사해오기
    for(size_t i = 0; i< crc_len; i++){
        pad_msg.push_back(0);
    }
    // 2. pad_msg와 crc_g 가지고 division 수행
    crc_division(&pad_msg, crc_g);
    // 3. pad_msg의 결과를 crc 비트로 지정 (push_back)
    vector<bool> crc_result(pad_msg.end()-crc_len, pad_msg.end());

    return crc_result;
}

// 이거는 msg crc가 0인지 아닌지 확인하는 애인듯
// crc test를 통과하면 true, 아니면 false 출력하자
bool POLAR::crc_check_sum(vector<bool>* msg, vector<bool> crc_g){
    // crc bit 제외한 원래 message bit의 크기
    uint32_t crc_len = crc_g.size()-1;
    uint32_t n = msg->size() - crc_len;   

    // division을 수행한다
    crc_division(msg, crc_g);

    // division 결과 나온 crc bit에 대해서, crc bit에 0이 포함되어있는지 확인한다.
    for(size_t i = 0; i< crc_len; i++){
        if((*msg)[n+i]==1){
            return false; // 0
        }
    }
    return true; // 1
}


void POLAR::crc_division(vector<bool>* pad_msg, vector<bool> gen){
    // 일단 이미 packing은 완료함.
    
    // 나누기 연산은 packing되기 전 횟수만큼 하면 된다.
    unsigned crc_len = gen.size()-1;
    unsigned n = pad_msg->size() - gen.size() + 1;
    // bool temp = false;

    // 나누기는 bitwise xor operation 수행하면 된다
    for(unsigned i = 0; i<n; i++){
        // 나누는게 가능한 경우
        // bitwise xor 연산 수행
        if((*pad_msg)[i]==1){
            for(unsigned j=0; j<crc_len+1; j++){
                if((*pad_msg)[i+j]==gen[j]){
                    (*pad_msg)[i+j]=0;
                }
                else{
                    (*pad_msg)[i+j]=1;
                }
            }
        }
    }
}

vector<bool> crc_polynomial(const string crc_type){
    if (!crc_type.compare("24A"))
        return { 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1 };
    else if (!crc_type.compare("24B"))
        return{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1 };
    else if (!crc_type.compare("24C"))
        return{ 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1 };
    else if (!crc_type.compare("16"))
        return{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    else if (!crc_type.compare("11"))
        return{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    else if (!crc_type.compare("6"))
        return{ 1, 1, 0, 0, 0, 0, 1 };
    else if (!crc_type.compare("3"))
        return{ 1, 0, 1, 1 };
    else if (!crc_type.compare("1"))
        return{ 1 };
    else
        return {1};
}