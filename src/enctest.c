
#include "config.h"
#include "crypt.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
	iu8 inp[]	= { CRYPT_TEST_VAL };
	iu8 key[]	= { CRYPT_TEST_KEY };
	iu8 chk[]	= { CRYPT_TEST_CHK };
	iu8 enc[CRYPT_BLOCK_LEN], dec[CRYPT_BLOCK_LEN];

#ifdef BENCHMARK
	long i;
	clock_t elapsed;
#endif

	printf("Using crypt algorithm %s, block size %d, key length %d\n",
		CRYPT_ALGO, CRYPT_BLOCK_LEN, CRYPT_KEY_LEN);

	memcpy( enc, inp, CRYPT_BLOCK_LEN);
	crypt_enc( enc, key );
	printf((memcmp(enc, chk, CRYPT_BLOCK_LEN) == 0) ?
		"encryption OK!\n" : "encryption failure!\n");
	memcpy( dec, enc, CRYPT_BLOCK_LEN);
	crypt_dec( dec, key );
	printf((memcmp(dec, inp, CRYPT_BLOCK_LEN) == 0) ?
		"decryption OK!\n" : "decryption failure!\n");

#ifdef BENCHMARK
	elapsed = -clock();
	for (i = 0; i < 1000000L; i++) {
		crypt_enc( enc, key );
	}
	elapsed += clock();
	printf ("elapsed time: %.1f s.\n", (float)elapsed/CLOCKS_PER_SEC);
#endif
	return 0;
}

