/*! @file
	\brief Skipjack declarations.

	Documentation for Skipjack is available at
	http://csrc.nist.gov/encryption/skipjack/skipjack-kea.htm.

	$Id: skipjack.h,v 1.1 2003/03/30 12:42:21 m Exp $
*/

#ifndef ATMOS_SKIPJACK_H
#define ATMOS_SKIPJACK_H

#include <types.h>

#define SKIPJACK_KEY_LEN	10	//!< SKIPJACK key size (bytes).
#define SKIPJACK_BLOCK_LEN	8	//!< SKIPJACK block length (bytes).

#define SKIPJACK_TEST_VAL 0x33, 0x22, 0x11, 0x00, 0xdd, 0xcc, 0xbb, 0xaa
#define SKIPJACK_TEST_KEY 0x00, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11
#define SKIPJACK_TEST_CHK 0x25, 0x87, 0xca, 0xe2, 0x7a, 0x12, 0xd3, 0x00

/*! \brief Skipjack encryption function.

	This function encrypts <EM>v</EM> with <EM>k</EM> and returns the
	encrypted data in <EM>v</EM>.

	\param v Array of eight iu8 values containing the data block.
	\param k Array of ten iu8 values containing the key.
*/
void skipjack_enc( iu8* v, iu8* k );

/*! \brief Skipjack decryption function.

	This function decrypts <EM>v</EM> with <EM>k</EM> and returns the
	decrypted data in <EM>v</EM>.

	\param v Array of eight iu8 values containing the data block.
	\param k Array of ten iu8 values containing the key.
*/
void skipjack_dec( iu8* v, iu8* k );

#endif /* ATMOS_SKIPJACK_H */

