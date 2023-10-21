// static unsigned random_seed = 552001;

// #define RANDOM_MAX ((1u << 31u) - 1u)
// unsigned lcg_parkmiller(unsigned *state)
// {
//     const unsigned N = 0x7fffffff;
//     const unsigned G = 48271u;

//     /*  
//         Indirectly compute state*G%N.

//         Let:
//           div = state/(N/G)
//           rem = state%(N/G)

//         Then:
//           rem + div*(N/G) == state
//           rem*G + div*(N/G)*G == state*G

//         Now:
//           div*(N/G)*G == div*(N - N%G) === -div*(N%G)  (mod N)

//         Therefore:
//           rem*G - div*(N%G) === state*G  (mod N)

//         Add N if necessary so that the result is between 1 and N-1.
//     */
//     unsigned div = *state / (N / G);  /* max : 2,147,483,646 / 44,488 = 48,271 */
//     unsigned rem = *state % (N / G);  /* max : 2,147,483,646 % 44,488 = 44,487 */

//     unsigned a = rem * G;        /* max : 44,487 * 48,271 = 2,147,431,977 */
//     unsigned b = div * (N % G);  /* max : 48,271 * 3,399 = 164,073,129 */

//     return *state = (a > b) ? (a - b) : (a + (N - b));
// }

// unsigned prand(void) {
//     return lcg_parkmiller(&random_seed);
// }


//-----------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

/* The following code is added by Mugil() and Mahesh(MXA220203)
** MT Pseudo Random Generotor Algorithm
** srand(int) -> To seed the generator with initial value
** rand() -> Generate the random number and returns it. 
*/

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

#define RAND_MAX 0x7fffffff

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializing the array with a NONZERO seed */
void
srand(unsigned long seed)
{
    /* setting initial seeds to mt[N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    mt[0]= seed & 0xffffffff;
    for (mti=1; mti<N; mti++)
        mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
}

long /* for integer generation */
rand()
{
    unsigned long y;
    static unsigned long mag01[2]={0x0, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if sgenrand() has not been called, */
            srand(4357); /* a default initial seed is used   */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }
  
    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);

    // Strip off uppermost bit because we want a long,
    // not an unsigned long
    return y & RAND_MAX;
}

// Assumes 0 <= max <= RAND_MAX
// Returns in the half-open interval [0, max]
long random_at_most(long max) {
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = rand();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}
/* End of code added */

//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//

// #define PHI 0x9e3779b9

// static unsigned int Q[4096], c = 362436;

// void srand(unsigned int x)
// {
//   int i;

//   Q[0] = x;
//   Q[1] = x + PHI;
//   Q[2] = x + PHI + PHI;

//   for (i = 3; i < 4096; i++)
//     Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
// }

// unsigned int rand(void)
// {
//   if(sizeof(unsigned long long) != 8){
//     return 0;
//   }
//   unsigned long long t, a = 18782LL;
//   static unsigned int i = 4095;
//   unsigned int x, r = 0xfffffffe;
//   i = (i + 1) & 4095;
//   t = a * Q[i] + c;
//   c = (t >> 32);
//   x = t + c;
//   if (x < c) {
//     x++;
//     c++;
//   }
//   return (Q[i] = r - x);
// }
