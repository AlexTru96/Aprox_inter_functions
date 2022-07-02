Even though the FISR is not used anymore because modern hardware is able to beat the benchmark of the algorithm more than 20 years ago, it is important to appreciate the genius to take advantage of the available hardware, for this case in its time was able to make the game QUAKE one of the fastest for its epoch.

In this report we consider the 64 bit version of this algorithm, changing the magic number to 0x5fe6eb50c7b537a9 

Summary:
- No repetition:
invsqrt():   0.0143us  FISR():   0.0080us
avgerr:  0.0215643
- 1 repetition:
invsqrt():   0.0117us   FISR():  0.0066us  
avgerr  0.000822579
- 2 repetition:
invsqrt():  0.0164us  FISR():   0.0125us  
avgerr  1.70339e-06


With only 2 newton raphson repetitions the algorithm can obtain a precision of 10e-6, even though it is faster than the current square root algorithm for the C library, we are not taking into account that this modern algorithm obtains a 10e-12 precision in that amount of time.
