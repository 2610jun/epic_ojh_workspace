#include <iostream>
#include "polar.h"
#include <random>
#include <cstdarg>
#include <iomanip>

using namespace std;

// function declaration

// console output package
// 근데 얘가 원래는 정의가 안되어있나 
string format(const char* fmt, ...);

//  for EbN0 (x axis)
vector<double> linspace(double start, double ed, int num);

// decoder 
void run_SC();
void run_CA_SCL();
//void run_CONV();
//void run_PAC();

int main(){
    cout<<"<Demo start>"<<endl;
    run_SC();
    //run_CA_SCL();
    //run_CONV(); 
    //run_PAC();
}

void run_SC(){
    /**
     * Change demo parameters here
     * nL, M, K ...
     */
    int nL = 1; //number of decoders
    // 아직 N, M을 구분할 단계는 아닌거같다. 그냥 N,K를 파라미터로 갖도록 하면 될듯
    //int M = 4000; //code word length

    //int N = 1024;
    //int K = 512;
    int N = 256;
    int K = 128;
    //int N = 16;
    //int K = 8;
    double R = (double)K/N;
    int num_List = 1;

    
    //double rate = 1/2;

    // crc generator. Not necessary now
    vector<bool> crc_g = {1};
    int crc_len = crc_g.size()-1;

    // 컴파일러가 자꾸 귀찮게하길래 함
    (void)nL;
    (void)crc_len;


    // information length excluding CRC
    int K_pad = K + crc_len;

    // instantiate a POLAR object
    POLAR polar = POLAR(N,K, crc_len, "Polar 5G standard");
    //POLAR polar = POLAR(N,K, crc_len, "Huawei Approx");

    // predeclared functions for random process
    /**
     * C++ 표준 라이브러리임. <random>
     * 
     * default_random_engine: 랜덤한 정수 출력
     * bernoulli_distribution: 1,0을 p=0.5 확률로 생성한다
     * normal_distribution<double> norm_dist(0.1): 평균과 표준편차를 가지는 가우시안 확률분포.
     */
    default_random_engine random_engine;
    bernoulli_distribution  bern_dist;
    //normal_distribution<double> norm_dist(0, 1);

    // Running parameters
    /**
    * Es: 하나의 심볼을 전송하는데 필요한 에너지
    * Eb: 하나의 비트를 전송하는데 필요한 에너지
    * N0: Noise power density
    * Es=k*Eb
    * k=심볼당 비트수. (BPSK->1, QPSK->2, 16-QAM->4)
    * BER을 비교할때는 대부분 EbN0 사용
    * Modulation symbol과 관련된 경우에는 EsN0를 사용한다
    * 
    * 이번 데모에서는 EbN0 사용하면 될거같음. 그리고, 어차피 BPSK 사용할거라 두개 같은 값임
    * Polar code의 경우 BPSK가 보편적인 modulation 방법이다.
    */

    // vector<double> EbN0_dB = linspace(0,4,9); // 7 point in 2dB~5dB
    // //vector<double> EbN0_dB = linspace(0,3,7); // 7 point in 2dB~5dB
    // vector<double> EbN0;
    // vector<double> sigma;
    // //vector<double> N0;
    // for (auto e : EbN0_dB){
    //     double x = pow(10.0, e/10);
    //     EbN0.push_back(x);
    //     //cout<<x<<endl;
    //     sigma.push_back(sqrt(1/(2*R*x)));
    //     //cout<<sqrt(1/(2*R*x))<<endl;
    // }

    // parameters about simulation 
    double linspace_begin = 0;
    double linspace_end = 3;
    double linspace_num_point = 7;
    double linspace_interval = (linspace_end-linspace_begin)/(linspace_num_point-1);
    //vector<double> EbN0_dB = linspace(0,4,9); // 7 point in 2dB~5dB
    vector<double> EbN0_dB = linspace(linspace_begin,linspace_end,linspace_num_point); // 7 point in 0dB~3dB
    int n_max_blks = 100000;
    int target_frame_err = 10; // for 1024, 512
    string decoder_name = "SC";

    vector<double> EbN0;
    vector<double> sigma;
    //vector<double> N0;
    for (auto e : EbN0_dB){
        double x = pow(10.0, e/10);
        EbN0.push_back(x);
        //cout<<x<<endl;
        sigma.push_back(sqrt(1/(2*R*x)));
        //cout<<sqrt(1/(2*R*x))<<endl;
    }

    //for(auto e : sigma){
    //    cout<<e<<endl;
    //}
    vector<double> ber(EbN0.size(), 0), bler(EbN0.size(), 0);
    vector<int> n_bit_errs(EbN0.size(), 0), n_blk_errs(EbN0.size(), 0);


    // 헤더 출력
    cout << "==================================================\n";
    cout << "Eb/N0             : " 
                                    << linspace_begin << "[dB] ~ " 
                                    << linspace_end << "[dB], " 
                                    << linspace_interval << "[dB]\n";

    cout << "Target Frame Error: " << target_frame_err<<"\n";
    cout << "Max num frame     : " << n_max_blks<<"\n";
    cout << "N                 : " << N << "\n";
    cout << "K                 : " << K << "\n";
    cout << "CRC               : " << crc_len << "\n";
    cout << "Decoder           : " << decoder_name << "\n";
    cout << "L                 : " << num_List <<"\n";
    cout << "==================================================\n\n";

    cout << "|| Eb/N0 ||     BER     ||     BLER    || n_bit_errs || n_blk_errs || elapsed time ||" << endl;
    cout << "=====================================================================================" << endl;



    // Loop for each EbN0 (SNR)
    for(size_t i = 0; i<EbN0.size(); i++){
        // print progress
        string str = format("\nNow running EbN0: %.2f dB [%d of %d]", EbN0_dB[i], i+1, EbN0.size()); // format for console display.  str은 콘솔 출력 위한 버퍼로 계속 사용할것.
        //cout<<str<<endl;
        int print_len = 0; // 추후에 출력할때 지우고 다시 쓰는 동작을 구현하기 위해 필요하다

        int n_blks_done = 0;
        clock_t ts = clock();

        /**
         * n_blks_done: 
         * n_blk_errs: 
         * 
         */

         // Loop for each iteration

         // test code
        //bool flag = 0;
        //while(flag==0){
        //    flag=1;
        while((n_blks_done<n_max_blks)&&(n_blk_errs[i])<100){
            // generate random bit stream
            vector<bool> msg;
            msg.reserve(K_pad); 
            for (int j = 0; j < K_pad; j++)
                msg.push_back(bern_dist(random_engine));
            // test code
            //for(auto e : msg){
            //    cout<<e<<" ";
            //}
            //cout<<endl;
            // generate CRC and attach it to the message
            /*
                SC 먼저 마무리하고 추가하기
                vector<bool> crc = POLAR::crc_gen(&msg, crc_g); // cyclic redundant check bit를 계산해준다. 자세한 구현은 polar.cpp
                vector<bool> crc_msg = msg; crc_msg.reserve(K);
                crc_msg.insert(crc_msg.end(), crc.begin(), crc.end()); // 뒤에 이어붙일때 씀.

            */

            // polar encoding
            vector<bool> enc = polar.encoder(&msg);
            //vector<bool> encoded = polar.encoder(&crc_msg);
            
            // rate matching (Puncturing)
            vector<bool> rm_enc = enc;
            // Punctucing 구현한부분. Puncturing 구현한다음 나중에 추가하자
            /*
                vector<bool> rm_enc = poalr.rate_matching(&enc);
            */

            // BPSK+ AWGN
            normal_distribution<double> norm_dist(0, sigma[i]);
            vector<double> r; r.reserve(N);
            for (auto e : rm_enc)
                r.push_back(1 - 2.0 * e + norm_dist(random_engine));
            
            // Compute soft bits as LLR(Log Likelihood Ratio)
            //vector <double> llr; llr.reserve(M);
            vector <double> llr; llr.reserve(N);
            for (auto e : r){
                llr.push_back(2.0 * e / (sigma[i]*sigma[i])); // 여기는 한번 더 체크해보자 
            }

            // Rate recovery (Puncturing)
            // Not yet
            //vector<double> rr_llr = polar.rate_recovery(&llr); 나중에 puncturing 공부하게되면 적용해보자.
            vector<double> rr_llr = llr; 
            
            // SC decoder
            vector<bool> msg_cap = polar.sc_decoder(&rr_llr);

            // SCL decoder 
            //vector<bool> msg_cap = polar.scl_decoder(&rr_llr);

            // count errors
            int n_errs = 0;
            for(int j=0; j<K_pad; j++){
                if(msg[j]!=msg_cap[j]){
                    n_errs++;
                }
            }

            // n_blk_errs는 하나라도 error가 생겼다면 카운트해준다
            if (n_errs){
                n_bit_errs[i] += n_errs;
                n_blk_errs[i]++;
            }

            n_blks_done += 1;

            ber[i] = n_bit_errs[i] * 1.0 / (K_pad * n_blks_done);
            bler[i] = n_blk_errs[i] * 1.0 / n_blks_done;

            // 실시간 진행상태 출력
            if (n_blks_done % 2 == 0) {
                //double elapsed_time = (clock() - ts) / (double)CLOCKS_PER_SEC;
                str = format("|| %.1f  || %12.5e || %12.5e || %10d || %10d || %7.1f s  ||",
                             EbN0_dB[i], ber[i], bler[i], n_bit_errs[i], n_blk_errs[i], (clock()-ts)/(double)CLOCKS_PER_SEC);
                cout << string(print_len, '\b');
                cout << str << flush;
                print_len = str.length();
            }
         }
         // print progress when one SNR is finished
        str = format("|| %.1f  || %12.5e || %12.5e || %10d || %10d || %7.1f s  ||",
            EbN0_dB[i], ber[i], bler[i], n_bit_errs[i], n_blk_errs[i], (clock()-ts)/(double)CLOCKS_PER_SEC);
        cout << string(print_len, '\b') << str << flush << endl;

    }

    // 파일 경로 및 이름 지정
    string folder = "C:\\Users\\epic\\OneDrive - postech.ac.kr\\2025\\Epic\\ECC\\polar\\dataset\\SC\\";
    string filename = decoder_name + " (" + to_string(N) + ", " + to_string(K) + ").txt";
    string filepath = folder + filename;

    ofstream fout(filepath);
    if (!fout.is_open()) {
        cerr << "Failed to open the file: " << filepath << endl;
    }

    // 헤더 출력
    fout << "==================================================\n";
    fout << "Eb/N0             : " 
                                    << linspace_begin << "[dB] ~ " 
                                    << linspace_end << "[dB], " 
                                    << linspace_interval << "[dB]\n";

    fout << "Target Frame Error: " << target_frame_err<<"\n";
    fout << "Max num frame     : " << n_max_blks<<"\n";
    fout << "N                 : " << N << "\n";
    fout << "K                 : " << K << "\n";
    fout << "CRC               : " << crc_len << "\n";
    fout << "Decoder           : " << decoder_name << "\n";
    fout << "L                 : " << num_List <<"\n";
    fout << "==================================================\n\n";

    // BER 출력
    fout << "BER: \n";
    fout << fixed << setprecision(8);
    for (double b : ber)
        fout << b << "\n";
    fout << "\n";

    // FER 출력
    fout << "FER: \n";
    for (double f : bler)
        fout << f << "\n";

    fout.close();
    cout << "File is uploaded!: " << filepath << endl;

}
void run_CA_SCL(){
    uint32_t num_List = 8; // 4,8 .. 적어도 4는 해줘야 성능이 나오는듯
    // uint32_t N = 1024;
    // uint32_t K = 512;

    int N = 256;
    int K = 128;
    
    // crc polynomial
    vector<bool> crc_g = crc_polynomial("16"); // crc_generator 뭐쓸지는 여기서 바꾸기
    // crc_generator 다항식 종류에 따른 성능지표 비교도 해보면 좋을듯
    int crc_len = crc_g.size()-1; // 왜냐하면, crc_g로 나누는 나머지가 crc 값이기에 crc_g의 승수보다 1 작아야한다.

    int K_pad = K + crc_len; // crc + info
    double R = (double)K/N;




    // instantiate a POLAR object
    POLAR polar = POLAR(N,K, crc_len,"Polar 5G standard");

    // test code
    // vector<double> a = {10.1, 200.2, 1.7}; // 결과가 2, 0, 1 나와야함
    // vector<size_t> result = polar.sort_indexes(a);
    // display_vec(result);
    

    // 여기부터는 SC랑 동일함. 그 대신, CRC 부분만 조금 유의하면 될듯..

    // 랜덤한 info bit들 생성하기
    default_random_engine random_engine;
    bernoulli_distribution  bern_dist;

    // parameters about simulation 
    double linspace_begin = 0;
    double linspace_end = 3;
    double linspace_num_point = 7;
    double linspace_interval = (linspace_end-linspace_begin)/(linspace_num_point-1);
    //vector<double> EbN0_dB = linspace(0,4,9); // 7 point in 2dB~5dB
    vector<double> EbN0_dB = linspace(linspace_begin,linspace_end,linspace_num_point); // 7 point in 0dB~3dB
    int n_max_blks = 100000; // 
    int target_frame_err = 10; // for 1024, 512
    string decoder_name = "CA-SCL";

    vector<double> EbN0;
    vector<double> sigma;
    //vector<double> N0;
    for (auto e : EbN0_dB){
        double x = pow(10.0, e/10);
        EbN0.push_back(x);
        //cout<<x<<endl;
        sigma.push_back(sqrt(1/(2*R*x)));
        //cout<<sqrt(1/(2*R*x))<<endl;
    }
    
    vector<double> ber(EbN0.size(), 0), bler(EbN0.size(), 0);
    vector<int> n_bit_errs(EbN0.size(), 0), n_blk_errs(EbN0.size(), 0);





    // 헤더 출력
    cout << "==================================================\n";
    cout << "Eb/N0             : " 
                                    << linspace_begin << "[dB] ~ " 
                                    << linspace_end << "[dB], " 
                                    << linspace_interval << "[dB]\n";

    cout << "Target Frame Error: " << target_frame_err<<"\n";
    cout << "Max num frame     : " << n_max_blks<<"\n";
    cout << "N                 : " << N << "\n";
    cout << "K                 : " << K << "\n";
    cout << "CRC               : " << crc_len << "\n";
    cout << "Decoder           : " << decoder_name << "\n";
    cout << "L                 : " << num_List <<"\n";
    cout << "==================================================\n\n";

    cout << "|| Eb/N0 ||     BER     ||     BLER    || n_bit_errs || n_blk_errs || elapsed time ||" << endl;
    cout << "=====================================================================================" << endl;


    // Loop for each EbN0 (SNR)
    for(size_t i = 0; i<EbN0.size(); i++){
        // print progress
        string str = format("\nNow running EbN0: %.2f dB [%d of %d]", EbN0_dB[i], i+1, EbN0.size()); // format for console display.  str은 콘솔 출력 위한 버퍼로 계속 사용할것.
        //cout<<str<<endl;

        int print_len = 0; // 추후에 출력할때 지우고 다시 쓰는 동작을 구현하기 위해 필요하다

        int n_blks_done = 0;
        clock_t ts = clock();
        // 1. max_block까지 돌아가거나 block error가 target (현재는 100) 도달할때까지 돌리기
        // 이거는 좀 바꾸면 좋긴할듯...
        //  100에서 10으로
        while((n_blks_done<n_max_blks)&&(n_blk_errs[i])<target_frame_err){
            //cout << "n_blks_done: " << n_blks_done << ", n_blk_errs[i]: " << n_blk_errs[i] << endl;
            // generate random bit stream
            vector<bool> msg;
            msg.reserve(K);
            for (int j = 0; j < K; j++)
                msg.push_back(bern_dist(random_engine));

            // generate CRC and attach it to the message
            // crc 씌워준다
            vector<bool> crc = POLAR::crc_gen(&msg, crc_g); // crc 계산
            vector<bool> crc_msg = msg; crc_msg.reserve(K_pad); // 메모리 미리 확보 (size K_pad)
            crc_msg.insert(crc_msg.end(), crc.begin(), crc.end()); // msg 뒤에 crc 붙여준다

            // polar encoding
            vector<bool> enc = polar.encoder(&crc_msg);
            
            // rate matching (Puncturing).. Not yet
            vector<bool> rm_enc = enc;
            // Punctucing 구현한부분. Puncturing 구현한다음 나중에 추가하자
            /*
                vector<bool> rm_enc = poalr.rate_matching(&enc);
            */

            // BPSK+ AWGN
            normal_distribution<double> norm_dist(0, sigma[i]);
            vector<double> r; r.reserve(N);
            for (auto e : rm_enc)
                r.push_back(1 - 2.0 * e + norm_dist(random_engine));
            
            // Compute soft bits as LLR(Log Likelihood Ratio)
            vector <double> llr; llr.reserve(N);
            for (auto e : r){
                llr.push_back(2.0 * e / (sigma[i]*sigma[i])); // 여기는 한번 더 체크해보자 
            }

            // Rate recovery (Puncturing)
            // Not yet
            //vector<double> rr_llr = polar.rate_recovery(&llr); 나중에 puncturing 공부하게되면 적용해보자.
            vector<double> rr_llr = llr; 
            
            // SCL decoder
            // cout<<"OK?"<<endl;
            // option 1. 아직 최적화 안된 decoder
            //vector<bool> msg_cap = polar.scl_decoder(&rr_llr, crc_g, num_List);
            // option 2. 최적화 진행되었음. 
            vector<bool> msg_cap = polar.scl_decoder_opt(rr_llr, crc_g, num_List);
            // vector<bool> msg_cap = polar.scs_decoder(&rr_llr, crc_g, num_List);
            //display_vec(msg_cap);
            
            // cout<<"OK?"<<endl;

            // SCL decoder 
            //vector<bool> msg_cap = polar.scl_decoder(&rr_llr);

            // count errors
            int n_errs = 0;
            for(int j=0; j<K; j++){
                if(msg[j]!=msg_cap[j]){
                    n_errs++;
                }
            }

            // n_blk_errs는 하나라도 error가 생겼다면 카운트해준다
            if (n_errs){
                n_bit_errs[i] += n_errs;
                n_blk_errs[i]++;
                // cout<<n_errs<<endl;
            }

            n_blks_done += 1;

            ber[i] = n_bit_errs[i] * 1.0 / (K * n_blks_done);
            bler[i] = n_blk_errs[i] * 1.0 / n_blks_done;

            // print progress for every 10 blocks
            // flush 사용하여 실시간 업데이트
            //if(n_blks_done % 10 == 0){
            //    str = format("Elapsed time: %.1f seconds, # tx blocks: %d, # error blocks:%d, BER: %.10f, BLER: %.10f", (clock()-ts)/(double)CLOCKS_PER_SEC, n_blks_done, n_blk_errs[i], ber[i], bler[i]);
            //    cout<<string(print_len, '\b'); //print_len 길이만큼 백스페이스 문자 출력하여 이전에 출력된 문자열 지우기
            //    cout<<str<<flush; //새로운 진행상태 출력. flush는 버퍼를 즉시 비워서 출력이 실시간으로 반영되도록 보장해준다.
            //    print_len = str.length();// 현재 출력된 문자열의 길이를 print_len에 저장하여, 다음 출력 시 이전 문자열을 정확히 덮어쓰도록 보장해준다.
            //}



            // 실시간 진행상태 출력
            if (n_blks_done % 2 == 0) {
                //double elapsed_time = (clock() - ts) / (double)CLOCKS_PER_SEC;
                str = format("|| %.1f  || %12.5e || %12.5e || %10d || %10d || %7.1f s  ||",
                             EbN0_dB[i], ber[i], bler[i], n_bit_errs[i], n_blk_errs[i], (clock()-ts)/(double)CLOCKS_PER_SEC);
                cout << string(print_len, '\b');
                cout << str << flush;
                print_len = str.length();
            }
            

        }
        str = format("|| %.1f  || %12.5e || %12.5e || %10d || %10d || %7.1f s  ||",
            EbN0_dB[i], ber[i], bler[i], n_bit_errs[i], n_blk_errs[i], (clock()-ts)/(double)CLOCKS_PER_SEC);
        cout << string(print_len, '\b') << str << flush << endl;

    }


    // 파일 경로 및 이름 지정
    string folder = "C:\\Users\\epic\\OneDrive - postech.ac.kr\\2025\\Epic\\ECC\\polar\\dataset\\CA_SCL\\";
    string filename = decoder_name + " (" + to_string(N) + ", " + to_string(K) + ", "+ to_string(num_List) + ", " + to_string(crc_len) + ").txt";
    string filepath = folder + filename;

    ofstream fout(filepath);
    if (!fout.is_open()) {
        cerr << "Failed to open the file: " << filepath << endl;
    }

    // 헤더 출력
    fout << "==================================================\n";
    fout << "Eb/N0             : " 
                                    << linspace_begin << "[dB] ~ " 
                                    << linspace_end << "[dB], " 
                                    << linspace_interval << "[dB]\n";

    fout << "Target Frame Error: " << target_frame_err<<"\n";
    fout << "Max num frame     : " << n_max_blks<<"\n";
    fout << "N                 : " << N << "\n";
    fout << "K                 : " << K << "\n";
    fout << "CRC               : " << crc_len << "\n";
    fout << "Decoder           : " << decoder_name << "\n";
    fout << "L                 : " << num_List <<"\n";
    fout << "==================================================\n\n";

    // BER 출력
    fout << "BER: \n";
    fout << fixed << setprecision(8);
    for (double b : ber)
        fout << b << "\n";
    fout << "\n";

    // FER 출력
    fout << "FER: \n";
    for (double f : bler)
        fout << f << "\n";

    fout.close();
    cout << "File is uploaded!: " << filepath << endl;

}


string format(const char* fmt, ...) {
    int size = 512;
    // Chatgpt 추천 수정코드
    //char* buffer = 0;
    //buffer = new char[size];
    char* buffer = new char[size];
    va_list vl;
    va_start(vl, fmt);
    int nsize = vsnprintf(buffer, size, fmt, vl);
    va_end(vl); // 
    if (size <= nsize) { //fail delete buffer and try again
        delete[] buffer;
        buffer = 0;
        buffer = new char[nsize + 1]; //+1 for /0
        nsize = vsnprintf(buffer, size, fmt, vl);
    }
    string ret(buffer);
    //va_end(vl);
    delete[] buffer;
    return ret;
}

vector<double> linspace(double start, double ed, int num) {
    // catch rarely, throw often
    if (num < 2) {
        // 쳇지피티가 고치라고 한다
        // throw new exception();
        throw exception();
    }
    int partitions = num - 1;
    vector<double> pts;
    // length of each segment
    double length = (ed - start) / partitions;
    // first, not to change
    pts.push_back(start);
    for (int i = 1; i < num - 1; i++) {
        pts.push_back(start + i * length);
    }
    // last, not to change
    pts.push_back(ed);
    return pts;
}


