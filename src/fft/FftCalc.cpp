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

    void FftCalc::calc(audiobuff_t *input, fft_buff_t *output){
        int len_data = input->samples;
        int N = pow(2, ceil(log2(len_data)));
        /*
        write C++ equivalent of python code:    

        if N % 2 > 0:
            raise ValueError("size of x must be a power of 2")
        elif N <= 32:  # this cutoff should be optimized
            return DFT_slow(x)
        else:
            X_even = FFT(x[::2])
            X_odd = FFT(x[1::2])
            factor = np.exp(-2j * np.pi * np.arange(N) / N)
            return np.concatenate([X_even + factor[:N / 2] * X_odd,
                                X_even + factor[N / 2:] * X_odd])
        */
        if(N % 2 > 0){
            ;
        }
        return;
    };

    void FftCalc::slowFFT(audiobuff_t *input, fft_buff_t *output){
        output->samples = input->samples;
        int N = input->samples;
        for (int k = 0; k < input->samples; k++) {
            output->fft_val[k].amplitude_1 = 0i;
            for(int n = 0; n < input->samples; n++) {
                output->fft_val[k].amplitude_1 = 
                    (real(output->fft_val[k].amplitude_1) + input->first_channel[n] * cos(2 * M_PI * k * n / N)) 
                    +
                    (imag(output->fft_val[k].amplitude_1) - input->first_channel[n] * sin(2 *  M_PI * k * n / N))*1i;
            }
        }
        return;
    }
}