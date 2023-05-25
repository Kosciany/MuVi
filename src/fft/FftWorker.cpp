#include "FftWorker.h"
#include "FftBuff.h"
#include "FftCalc.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#include "Logger.h"

#define DEBUG 1

#ifdef DEBUG
    #define FLOAT_DEBUG_FILE_PRECISION 8
#endif // DEBUG


namespace Muvi {

    void FftWorker::Run() {
//         using namespace std::chrono_literals;
//         FftCalc fftcalc = FftCalc();
//         fft_buff_t buff;
// #ifdef DEBUG
//         bool dumped = false;
// #endif // DEBUG
//         while(IsRunning()) {
//             audiobuff_t value;
//             while(Consume(value)) {
//                 MUVI_FFT_TRACE("Samples read");

//                 fftcalc.calcFFT(&value, &buff);
//                 Produce(buff);
// #ifdef DEBUG
//                 if(!dumped){
//                     // Debug purpose only, may be removed forever after verifying
//                     std::ofstream myfile;
//                     dumped = true;
//                     myfile.open("samples.dat", std::ios::out);
//                     for(int j=0; j<CHUNK_SIZE; j++ ){
//                         myfile << std::setprecision(FLOAT_DEBUG_FILE_PRECISION) << value.first_channel[j] << "\n";
//                     }
//                     myfile.close();

//                     myfile.open("fft.dat", std::ios::out);
//                     for(int j=0; j<CHUNK_SIZE; j++){
//                         myfile << std::setprecision(FLOAT_DEBUG_FILE_PRECISION) << real(buff.amplitude_1[j]) << '|'
//                                << std::setprecision(FLOAT_DEBUG_FILE_PRECISION) << imag(buff.amplitude_1[j]) << "\n";
//                     }
//                     myfile.close();
//                 }
// #endif // DEBUG
//             }
//             waitForProduct();
//         }
    }
} // Muvi
