# %%
import numpy as np

# %%
with open("data.dat", "r") as file:
    floats = file.readlines()
# %%

# %%
floats_array = [float(item) for item in floats]
# %%
result = np.fft.fft(floats_array)

# %%
# dump result to txt file
with open("result.txt", "w+") as file:
    for item in result:
        file.write(str(item) + '\n')
# %%
import numpy as np
import matplotlib.pyplot as plt

# rate, aud_data = scipy.io.wavfile.read(file)
rate = 44000
ii = np.arange(0, 9218368)
t = ii / rate
aud_data = floats_array
#np.zeros(len(t))
#for w in [1000, 5000, 10000, 15000]:
#    aud_data += np.cos(2 * np.pi * w * t)

# From here down, everything else can be the same
len_data = len(aud_data)

channel_1 = np.zeros(2**(int(np.ceil(np.log2(len_data)))))
channel_1[0:len_data] = aud_data

fourier = np.fft.fft(channel_1)
w = np.linspace(0, 44000, len(fourier))

# First half is the real component, second half is imaginary
fourier_to_plot = fourier[1:len(fourier)//2]
w = w[1:len(fourier)//2]

plt.figure(1)

plt.plot(w, fourier_to_plot)
plt.xlabel('frequency')
plt.ylabel('amplitude')
plt.show()
# %%
