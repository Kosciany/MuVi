#include "FftWorker.h"
#include "FftBuff.h"
#include "FftCalc.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

namespace Muvi {


    void FftWorker::Run() {
        using namespace std::chrono_literals;
        FftCalc fftcalc = FftCalc();
        fft_buff_t buff;
        bool i = false;
        while(IsRunning()) {
            audiobuff_t value;
            while(ProducerPop(value)) {
                std::cout << "[FFT Worker] read " << value.channels << std::fixed << std::setw(10) << std::setprecision(5) << value.first_channel[0] << std::endl;
                if(!i && value.samples) {
                    std::ofstream myfile;
                    fftcalc.slowFFT(&value, &buff);
                    myfile.open("data.dat", std::ios::out);
                    i = true;
                    for(int j=0; j<value.samples; j++ ){
                            myfile << value.first_channel[j] << "\n";
                    }
                    myfile.close();

                    myfile.open("fft.dat", std::ios::out);
                    for(int j=0; j<value.samples; j++ ){
                            myfile << real(buff.fft_val[j].amplitude_1) << " + j*" << imag(buff.fft_val[j].amplitude_1)  << "\n";
                    }
                    myfile.close();
                }
            }
            std::this_thread::sleep_for(50ms);
        }
    }
} // Muvi
