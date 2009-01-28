/************************************************

The Tiny Encryption Algorithm (TEA) by David Wheeler and Roger Needham
of the Cambridge Computer Laboratory

Placed in the Public Domain by David Wheeler and Roger Needham.

**** ANSI C VERSION ****

Notes:

TEA is a Feistel cipher with XOR and and addition as the non-linear
mixing functions.

Takes 64 bits of data (1 block) in v[0] and v[1] (32b + 32b).
Takes 128 bits of key in k[0] - k[3].
Returns 64 bits of data in v[0] and v[1].

TEA can be operated in any of the modes of DES. Cipher Block Chaining is,
for example, simple to implement.

n is the number of iterations. 32 is ample, 16 is sufficient, as few
as eight may be OK.  The algorithm achieves good dispersion after six
iterations. The iteration count can be made variable if required.

Note this is optimised for 32-bit CPUs with fast shift capabilities. It
can very easily be ported to assembly language on most CPUs.

delta is chosen to be the real part of (the golden ratio Sqrt(5/4) -
1/2 ~ 0.618034 multiplied by 2^32).

************************************************/

/*! @file
	\brief TEA functions.

	$Id: tea.c,v 1.6 2003/04/02 23:57:54 m Exp $
*/

#include <config.h>
#include <tea.h>
#include <tools.h>
#ifdef DEBUG
#include <stdio.h>
#endif

#define hton_ul(x,y)

// Tea is algorithm with ID 0 in our list
#if CONF_WITH_CRYPT_ALGO==0

void tea_enc( iu32 *v, iu32 *k )
{
	iu32 y, z;
	iu32 sum=0;
	iu8 n=ROUNDS;

	hton_ul(k,4);
	hton_ul(v,2);

#ifdef DEBUG
	printf( "tea_enc( %.8lX %.8lX, %.8lX %.8lX %.8lX %.8lX )\n", v[0], v[1],
		k[0], k[1], k[2], k[3] );
#endif

	y=v[0]; z=v[1];

	while(n-->0) {
		sum += DELTA;
		y += ((z<<4)+k[0]) ^ (z+sum) ^ ((z>>5)+k[1]);
		z += ((y<<4)+k[2]) ^ (y+sum) ^ ((y>>5)+k[3]);
	}

	v[0]=y; v[1]=z;

#ifdef DEBUG
	printf( "= %.8lX %.8lX\n", v[0], v[1] );
#endif

	hton_ul(k,4);
	hton_ul(v,2);
}

void tea_dec( iu32 *v, iu32 *k )
{
	iu32 y, z;
	iu32 sum=DELTA*ROUNDS;
	iu8 n=ROUNDS;

	hton_ul(k,4);
	hton_ul(v,2);

#ifdef DEBUG
	printf( "tea_dec( %.8lX %.8lX, %.8lX %.8lX %.8lX %.8lX )", v[0], v[1],
		k[0], k[1], k[2], k[3] );
#endif

	y=v[0]; z=v[1];

	while(n-->0) {
		z -= ((y<<4)+k[2]) ^ (y+sum) ^ ((y>>5)+k[3]);
		y -= ((z<<4)+k[0]) ^ (z+sum) ^ ((z>>5)+k[1]);
		sum -= DELTA;
	}

	v[0]=y; v[1]=z;

#ifdef DEBUG
	printf( "= %.8lX %.8lX\n", v[0], v[1] );
#endif

	hton_ul(k,4);
	hton_ul(v,2);
}

#ifdef TEST
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
	iu32 inp[2]	= { 0x11111111, 0x22222222 };
	iu32 key[4]	= { 0x11111111, 0x22222222, 0x33333333, 0x44444444 };
	iu32 enc[2], dec[2];
	//iu32 chk[8]	= { 0x25, 0x87, 0xca, 0xe2, 0x7a, 0x12, 0xd3, 0x00 };
	long i;
	clock_t elapsed;

	memcpy( enc, inp, 64 );
	tea_enc( enc, key );
	//printf((memcmp(enc, chk, 8) == 0) ? "encryption OK!\n" : "encryption failure!\n");
	memcpy( dec, enc, 64 );
	tea_dec( dec, key );
	printf((memcmp(dec, inp, 64) == 0) ? "decryption OK!\n" : "decryption failure!\n");

#ifdef BENCHMARK
	elapsed = -clock();
	for (i = 0; i < 1000000L; i++) {
		tea_enc( enc, key );
	}
	elapsed += clock();
	printf ("elapsed time: %.1f s.\n", (float)elapsed/CLOCKS_PER_SEC);
#endif
	return 0;
}
#endif /* TEST */

#endif /* CONF_WITH_CRYPT_ALGO==0 */

