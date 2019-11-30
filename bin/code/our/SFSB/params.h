#if hashlen == 160
#define s (384)
#define w (24)
#define c (240)
#define p (389)
#endif

#if hashlen == 224
#define s (544)
#define w (34)
#define c (336)
#define p (547)
#endif

#if hashlen == 384
#define s (928)
#define w (58)
#define c (576)
#define p (941)
#endif

#define n (w*(1<<(s/w)))
