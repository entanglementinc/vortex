#define K   (keylen) // ley length (in bits)
#define K8  (K/8)    // ley length (in bytes)
#define R   (2*K)    // state length (in bits)
#define R8  (R/8)    // state length (in bytes)
#define IV  (R-K)    // initial value length (in bits)
#define IV8 (IV/8)   // initial value length (in bytes)
#define W   (R/8)    // one reads one byte at a time
#define N   (256*W)  // one choose each of the W columns amoungst 256

#define R8A (R8%16 ? (R8/16+1)*16 : R8) // 128 bits aligment
