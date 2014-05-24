#include <stdint.h>
#include "global.h"
#include "functiongen.h"

const unsigned int DELTA_IDX_440 = (unsigned int) ((440.L/SAMPLE_FREQ * TABLE_SIZE) * (1<<FIXPOINT_ARITH));
const unsigned int DELTA_IDX_5000 = (unsigned int) ((5000.L/SAMPLE_FREQ * TABLE_SIZE) * (1<<FIXPOINT_ARITH));

const unsigned int SHIFTED_TABLE_SIZE =  TABLE_SIZE * (1<<FIXPOINT_ARITH);
	
const unsigned int a =  (unsigned int)((1.5L/3.3 *DAC_MAX_VAL)* (1<< FIXPOINT_ARITH));
const unsigned int b_small =  (unsigned int)((0.5L/DAC_MAX_V * DAC_MAX_VAL)/(1 << 15) *  (1 << FIXPOINT_ARITH));
const unsigned int b_big = (unsigned int)((1.0L/DAC_MAX_V * DAC_MAX_VAL)/(1 << 15) *  (1 << FIXPOINT_ARITH));


int sinus_table[TABLE_SIZE] = {
         0,   804,  1608,  2411,  3212,  4011,  4808,  5602,  6393,  7180,
      7962,  8740,  9512, 10279, 11039, 11793, 12540, 13279, 14010, 14733,
     15447, 16151, 16846, 17531, 18205, 18868, 19520, 20160, 20788, 21403,
     22006, 22595, 23170, 23732, 24279, 24812, 25330, 25833, 26320, 26791,
     27246, 27684, 28106, 28511, 28899, 29269, 29622, 29957, 30274, 30572,
     30853, 31114, 31357, 31581, 31786, 31972, 32138, 32286, 32413, 32522,
     32610, 32679, 32729, 32758, 32768, 32758, 32729, 32679, 32610, 32522,
     32413, 32286, 32138, 31972, 31786, 31581, 31357, 31114, 30853, 30572,
     30274, 29957, 29622, 29269, 28899, 28511, 28106, 27684, 27246, 26791,
     26320, 25833, 25330, 24812, 24279, 23732, 23170, 22595, 22006, 21403,
     20788, 20160, 19520, 18868, 18205, 17531, 16846, 16151, 15447, 14733,
     14010, 13279, 12540, 11793, 11039, 10279,  9512,  8740,  7962,  7180,
      6393,  5602,  4808,  4011,  3212,  2411,  1608,   804,     0,  -804,
     -1608, -2411, -3212, -4011, -4808, -5602, -6393, -7180, -7962, -8740,
     -9512,-10279,-11039,-11793,-12540,-13279,-14010,-14733,-15447,-16151,
    -16846,-17531,-18205,-18868,-19520,-20160,-20788,-21403,-22006,-22595,
    -23170,-23732,-24279,-24812,-25330,-25833,-26320,-26791,-27246,-27684,
    -28106,-28511,-28899,-29269,-29622,-29957,-30274,-30572,-30853,-31114,
    -31357,-31581,-31786,-31972,-32138,-32286,-32413,-32522,-32610,-32679,
    -32729,-32758,-32768,-32758,-32729,-32679,-32610,-32522,-32413,-32286,
    -32138,-31972,-31786,-31581,-31357,-31114,-30853,-30572,-30274,-29957,
    -29622,-29269,-28899,-28511,-28106,-27684,-27246,-26791,-26320,-25833,
    -25330,-24812,-24279,-23732,-23170,-22595,-22006,-21403,-20788,-20160,
    -19520,-18868,-18205,-17531,-16846,-16151,-15447,-14733,-14010,-13279,
    -12540,-11793,-11039,-10279, -9512, -8740, -7962, -7180, -6393, -5602,
     -4808, -4011, -3212, -2411, -1608,  -804
};

int triangle_table[TABLE_SIZE] = {
         0,   512,  1024,  1536,  2048,  2560,  3072,  3584,  4096,  4608,
      5120,  5632,  6144,  6656,  7168,  7680,  8192,  8704,  9216,  9728,
     10240, 10752, 11264, 11776, 12288, 12800, 13312, 13824, 14336, 14848,
     15360, 15872, 16384, 16896, 17408, 17920, 18432, 18944, 19456, 19968,
     20480, 20992, 21504, 22016, 22528, 23040, 23552, 24064, 24576, 25088,
     25600, 26112, 26624, 27136, 27648, 28160, 28672, 29184, 29696, 30208,
     30720, 31232, 31744, 32256, 32768, 32256, 31744, 31232, 30720, 30208,
     29696, 29184, 28672, 28160, 27648, 27136, 26624, 26112, 25600, 25088,
     24576, 24064, 23552, 23040, 22528, 22016, 21504, 20992, 20480, 19968,
     19456, 18944, 18432, 17920, 17408, 16896, 16384, 15872, 15360, 14848,
     14336, 13824, 13312, 12800, 12288, 11776, 11264, 10752, 10240,  9728,
      9216,  8704,  8192,  7680,  7168,  6656,  6144,  5632,  5120,  4608,
      4096,  3584,  3072,  2560,  2048,  1536,  1024,   512,     0,  -512,
     -1024, -1536, -2048, -2560, -3072, -3584, -4096, -4608, -5120, -5632,
     -6144, -6656, -7168, -7680, -8192, -8704, -9216, -9728,-10240,-10752,
    -11264,-11776,-12288,-12800,-13312,-13824,-14336,-14848,-15360,-15872,
    -16384,-16896,-17408,-17920,-18432,-18944,-19456,-19968,-20480,-20992,
    -21504,-22016,-22528,-23040,-23552,-24064,-24576,-25088,-25600,-26112,
    -26624,-27136,-27648,-28160,-28672,-29184,-29696,-30208,-30720,-31232,
    -31744,-32256,-32768,-32256,-31744,-31232,-30720,-30208,-29696,-29184,
    -28672,-28160,-27648,-27136,-26624,-26112,-25600,-25088,-24576,-24064,
    -23552,-23040,-22528,-22016,-21504,-20992,-20480,-19968,-19456,-18944,
    -18432,-17920,-17408,-16896,-16384,-15872,-15360,-14848,-14336,-13824,
    -13312,-12800,-12288,-11776,-11264,-10752,-10240, -9728, -9216, -8704,
     -8192, -7680, -7168, -6656, -6144, -5632, -5120, -4608, -4096, -3584,
     -3072, -2560, -2048, -1536, -1024,  -512
};


