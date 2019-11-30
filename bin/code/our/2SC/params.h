#if keylen == 144
#define S 384
#define C 240
#endif

#if keylen == 208
#define S 544
#define C 336
#endif

#if keylen == 352
#define S 928
#define C 576
#endif

#define R (S-C)
#define S8 (S/8)
#define R8 (R/8)   // state length (in bytes)
//#define K   (R/2)   // key length (in bits)
//#define K8  (K/8)   // ley length (in bytes)
//#define IV  (R-K)   // initial value length (in bits)
//#define IV8 (IV/8)  // initial value length (in bytes)
#define W  (R/8)   // one reads one byte at a time
#define N  (256*W) // one choose each of the W columns amoungst 256

#define R8A (R8%16 ? (R8/16+1)*16 : R8) // 128 bits aligment
#define S8A (S8%16 ? (S8/16+1)*16 : S8) // 128 bits aligment
