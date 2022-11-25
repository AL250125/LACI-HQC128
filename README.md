# LACI HQC 128 Implementation 

Implementation of HQC128 for embedded systms with optimisation for ARMv7. We do not claim any side channel security. However, you can build a constant time version of our implementation by changing options in CMakeConfig.cmake file. We embedded the proposed countermeasure from https://tches.iacr.org/index.php/TCHES/article/view/9700 to provide a constant time sampling.

## How to build

CMakeConfig.cmake file show all current options for the build. You can build as follow:
```
cd 
cmake .
make
```

## Build for ARMv7
ARMv7 building is not supported in cmake framework. You should import files in your own project to build for ARMv7. We have wrapped in Laci the HAL provided by STM for STM32U5 and STM32F4. You can easly add another HAL by changing the laci_random.c file

## Benchmark on STM32U5

### Memory footprint
In our implementation we only use a static memory to perform computation of HQC framework for KeyGen, Encrypt and Decrypt. Details of memeory mapping is provided by laci_hqc_memory.c files. The static memory is computed during compilation. For HQC128, we use less than 20KB of RAM. 

### Time efficiency on STM32U5
We performed time benchmark on STM32U5 which provide a TRNG and hardware AES. We have performed 10,000 computation of KeyGen, Encrypt and Decrypt to provide accuarate benchmark. We test following configuration:
* LACI C : our full C implmentation of HQC128
* LACI ASM : our implementation of HQC128 with ARMv7 assembly optimisations
* LACI ASM + AES HW : our optimized implementation using the hardware AES
* LACI C/ASM/ASM + AES HW + CM : like previous configurations but with constant time sampling

The benchmark was done on a STM32U5 at 160MHz. The following tables show results in cycles:

* PQCLEAN :

| Operations | Mean | Min | Max |
|------------|------|-----|-----|
|KeyGen | 3,894,297   | 3,856,090  | 4,110,819 |
|Encrypt | 7,344,342  | 7,267,863  | 7,695,645 |
|Decrypt | 10,566,698  | 10,452,126  | 11,006,455 |

* LACI C :

| Operations | Mean | Min | Max |
|------------|------|-----|-----|
|KeyGen | 3,089,474   | 3,051,934  | 3,304,384 |
|Encrypt | 5,144,123  | 5,067,398  | 5,494,782 |
|Decrypt | 7,320,812  | 7,206,494  | 7,886,879 |

* LACI ASM :

| Operations | Mean | Min | Max |
|------------|------|-----|-----|
|KeyGen | 2,295,537   | 2,257,719  | 2,510,140 |
|Encrypt | 3,345,424  | 3,268,634  | 3,695,929 |
|Decrypt | 4,389,920  | 4,276,572  | 4,835,333 |

* LACI ASM + AES HW :

| Operations | Mean | Min | Max |
|------------|------|-----|-----|
|KeyGen | 695,687   | 693,696  | 707,722 |
|Encrypt | 1,520,344  | 1,516,356  | 1,539,352 |
|Decrypt | 2,292,747  | 2,286,645  | 2,322,823 |

* LACI C + CM :

| Operations | Mean | Min | Max |
|------------|------|-----|-----|
|KeyGen | 5,123,644   | 5,123,542  | 5,123,996 |
|Encrypt | 8,141,438  | 8,141,299  | 8,141,579 |
|Decrypt | 12,344,223  | 12,344,056  | 12,344,365 |

* LACI ASM + CM :

| Operations | Mean | Min | Max |
|------------|------|-----|-----|
|KeyGen | 4,338,036   | 4,337,940  | 4,338,157 |
|Encrypt | 6,345,748  | 6,345,614  | 6,345,903 |
|Decrypt | 9,423,087  | 9,422,920  | 9,423,240 |

* LACI ASM + CM + AES HW :

| Operations | Mean | Min | Max |
|------------|------|-----|-----|
|KeyGen | 1,124,006   | 1,123,931  | 1,124,170 |
|Encrypt | 2,150,868  | 2,150,759  | 2,151,028 |
|Decrypt | 3,335,256  | 3,335,124  | 3,335,418 |

