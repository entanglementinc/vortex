#if hashlen == 160
#define w (80)
#define r (640)
#define p (653)
#define s (1120)
#endif

#if hashlen == 224
#define w (112)
#define r (896)
#define p (907)
#define s (1568)
#endif

#if hashlen == 256
#define w (128)
#define r (1024)
#define p (1061)
#define s (1792)
#endif

#if hashlen == 384
#define w (184)
#define r (1472)
#define p (1483)
#define s (2392)
#endif

#if hashlen == 512
#define w (248)
#define r (1984)
#define p (1987)
#define s (3224)
#endif

#define n (w*(1<<(s/w)))
