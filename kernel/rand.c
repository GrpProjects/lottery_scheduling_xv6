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


/* A C-program for MT19937: Real number version  (1998/4/6)    */
/*   genrand() generates one pseudorandom real number (double) */
/* which is uniformly distributed on [0,1]-interval, for each  */
/* call. sgenrand(seed) set initial values to the working area */
/* of 624 words. Before genrand(), sgenrand(seed) must be      */
/* called once. (seed is any 32-bit integer except for 0).     */
/* Integer generator is obtained by modifying two lines.       */
/*   Coded by Takuji Nishimura, considering the suggestions by */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997.           */

/* This library is free software; you can redistribute it and/or   */
/* modify it under the terms of the GNU Library General Public     */
/* License as published by the Free Software Foundation; either    */
/* version 2 of the License, or (at your option) any later         */
/* version.                                                        */
/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            */
/* See the GNU Library General Public License for more details.    */
/* You should have received a copy of the GNU Library General      */
/* Public License along with this library; if not, write to the    */
/* Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   */ 
/* 02111-1307  USA                                                 */

/* Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.       */
/* When you use this, send an email to: matumoto@math.keio.ac.jp   */
/* with an appropriate reference to your work.                     */

/* REFERENCE                                                       */
/* M. Matsumoto and T. Nishimura,                                  */
/* "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform  */
/* Pseudo-Random Number Generator",                                */
/* ACM Transactions on Modeling and Computer Simulation,           */
/* Vol. 8, No. 1, January 1998, pp 3--30.                          */


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

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializing the array with a NONZERO seed */
void
srand(seed)
    unsigned long seed;	
{
    /* setting initial seeds to mt[N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    mt[0]= seed & 0xffffffff;
    for (mti=1; mti<N; mti++)
        mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
}


unsigned long
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

    return y;
}


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