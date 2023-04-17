#include <iostream>
#include <complex>
#include <cmath>
#include <FftBuff.h>
#include <FftCalc.h>

namespace Muvi {
    using namespace std::complex_literals;
    FftCalc::FftCalc(void){
        ;
    }

void fft_rec(std::complex<double> *x, int N) {
    // Check if it is splitted enough
    if (N <= 1) {
        return;
    }

    // Split even and odd
    std::complex<double> odd[N/2];
    std::complex<double> even[N/2];
    for (int i = 0; i < N / 2; i++) {
        even[i] = x[i*2];
        odd[i] = x[i*2+1];
    }

    // Split on tasks
    fft_rec(even, N/2);
    fft_rec(odd, N/2);


    // Calculate DFT
    for (int k = 0; k < N / 2; k++) {
        std::complex<double> t = exp(std::complex<double>(0, -2 * M_PI * k / N)) * odd[k];
        x[k] = even[k] + t;
        x[N / 2 + k] = even[k] - t;
    }
}

void fft(float *x_in, 
    std::complex<double> *x_out,
    int N) {

    // Make copy of array and apply window
    for (int i = 0; i < N; i++) {
        x_out[i] = std::complex<double>(x_in[i], 0);
        x_out[i] *= 1; // Window
    }

    // Start recursion
    fft_rec(x_out, N);
}

    void FftCalc::calcFFT(audiobuff_t *input, fft_buff_t *output){
        std::complex<double> *output_complex;
        int N = CHUNK_SIZE;

        output_complex = new std::complex<double> [N]();
        if (output_complex == nullptr) {
            return;
        }

        fft(input->first_channel, output_complex, N);

        for(int i = 0; i < N; i++) {
            output->amplitude_1[i] = output_complex[i];
        }

        return;
    }

    void FftCalc::calcDFT(audiobuff_t *input, fft_buff_t *output){
        int N = CHUNK_SIZE;
        for (int k = 0; k < CHUNK_SIZE; k++) {
            output->amplitude_1[k] = 0i;
            for(int n = 0; n < CHUNK_SIZE; n++) {
                output->amplitude_1[k] = 
                    (real(output->amplitude_1[k]) + input->first_channel[n] * cos(2 * M_PI * k * n / N)) 
                    +
                    (imag(output->amplitude_1[k]) - input->first_channel[n] * sin(2 *  M_PI * k * n / N))*1i;
            }
        }
        return;
    }
}