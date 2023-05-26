#pragma once
#include "MuviConfig.h"
#include <complex>


typedef struct{
    std::complex<double> amplitude_1[CHUNK_SIZE];
    std::complex<double> amplitude_2[CHUNK_SIZE];
    double frequency;
    double max_amplitude;
} fft_buff_t;