#define LOG_LENGTH 11
#define ERROR_WEIGHT 32

#define REDUC 2
#define ERROR_SIZE 232
// rounded down from 232.766
// log_2(binomial(2^11,32)) = 233.986
// log_2(binomial(2^9,32)) + 2 * 32 = 232.91
// security loss is 1.98553
// final security is 86.6478
