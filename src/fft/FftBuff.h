// write a C struct containing array of doulbes 4096-length
#include "MuviConfig.h"
#include <complex>
// template for complex numbers

typedef struct{
    std::complex<double> amplitude_1;
    std::complex<double> amplitude_2;
    double frequency;
} fft_unit_t;

typedef struct{
    fft_unit_t fft_val[AUDIO_BUFFER_SIZE];
    int samples;
} fft_buff_t;