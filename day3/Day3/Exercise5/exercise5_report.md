### Approximation to the natural exponential
### Taylor.c
The code performs a simple Taylor
expansion of 7th degree.

The error is abismal in the [-10,10] range due to the polynomial approximations lead to even or odd functions , which is not the case for exp function.
- time for    t_exp():   0.0090us  avgerr  204682



If we reduce the range to [-0.5,0.5] the error got reduced to 3.e-9.
-  time for   t_exp():   0.0099us  avgerr  3.74777e-09

If we decrease the range we can barely observe any slight slowdown in the computational time .

### Pade.c
The code performs the Pade approximation of 4th degree.

The error is much better in the [-10,10] range as we now use rational functions, but the precision is not decent yet
- time for pad_exp():   0.0089us  avgerr  5.96728



If we reduce the range to [-0.5,0.5] the error got reduced to 2.e-12- 
- time for  	pad_exp():   0.0105us  avgerr  2.01835e-12

### Improving Pade.c

Taking advantage that Pade implementation works really nice in the 0 neighbourhood , we can separate the calculation in the integer and float part where the floating port will be in the range of [0,1]

This implementation can be found in exp.c in the function called fast_exp.

The error is way better in the [-10,10] 
- time for fast_exp():   0.0943us  avgerr  2.70249e-17


If we reduce the range to [-0.5,0.5] 
- time for  fast_exp():   0.0761us  avgerr  1.45155e-17

According to these results, the improvedd PAde version is the most accurate version to calculate the function exp(x), even though Taylor remains as the fastest approximation as we are only dealing with sums and multiplication operations.
