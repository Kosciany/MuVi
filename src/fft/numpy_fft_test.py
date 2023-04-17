# %%
import numpy as np


def extract_value(line):
    real, imag = line.split('|')
    return complex(float(real), float(imag))


# %%

with open("samples.dat", "r") as file:
    raw_samples = file.readlines()
# %%
with open("fft.dat", "r") as file:
    raw_fft_cpp = file.readlines()
# %%
fft_cpp = np.array(list(map(extract_value, raw_fft_cpp)))
# %%
samples_array = [float(item) for item in raw_samples]
# %%
fft_np = np.fft.fft(samples_array)
# %%
if (np.allclose(fft_np, fft_cpp, rtol=1.e-3, atol=1.e-6)):
    print("FFT works correctly")
else:
    print("FFT does not work correctly")

# %%
