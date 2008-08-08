
#include "config.h"
#include "crypt.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
	iu8 inp[8]	= { 0x33, 0x22, 0x11, 0x00, 0xdd, 0xcc, 0xbb, 0xaa };
	iu8 key[10]	= { 0x00, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 };
	iu8 enc[8], dec[8];
	iu8 chk[8]	= { 0x25, 0x87, 0xca, 0xe2, 0x7a, 0x12, 0xd3, 0x00 };
	//iu8 tab[10][256];
	long i;
	clock_t elapsed;

	memcpy( enc, inp, 8 );
	crypt_enc( enc, key );
	printf((memcmp(enc, chk, 8) == 0) ? "encryption OK!\n" : "encryption failure!\n");
	memcpy( dec, enc, 8 );
	crypt_dec( dec, key );
	printf((memcmp(dec, inp, 8) == 0) ? "decryption OK!\n" : "decryption failure!\n");

	elapsed = -clock();
	for (i = 0; i < 1000000L; i++) {
		crypt_enc( enc, key );
	}
	elapsed += clock();
	printf ("elapsed time: %.1f s.\n", (float)elapsed/CLOCKS_PER_SEC);
	return 0;
}

