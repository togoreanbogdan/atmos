/*! @file
	\brief NEWDES-SK declarations.

	$Id: newdes-sk.h,v 1.1 2003/03/30 12:42:21 m Exp $
*/

#ifndef ATMOS_NEWDESSK_H
#define ATMOS_NEWDESSK_H

#include <types.h>

#define NEWDESSK_KEY_LEN	15	//!< NEWDES-SK key size (bytes).
#define NEWDESSK_BLOCK_LEN	8	//!< NEWDES-SK block length (bytes).

#define NEWDESSK_TEST_VAL 0x33, 0x22, 0x11, 0x00, 0xdd, 0xcc, 0xbb, 0xaa
#define NEWDESSK_TEST_KEY 0x00, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x99, 0x88, 0x77, 0x66
#define NEWDESSK_TEST_CHK 0x5a, 0xc9, 0xed, 0x97, 0xae, 0x85, 0x5d, 0xbe

/*!	\brief NEWDES-SK encryption function.

	This function encrypts <EM>v</EM> with <EM>k</EM> and returns the
	encrypted data in <EM>v</EM>.

	\param v Array of eight iu8 values containing the data block.
	\param k Array of 15 iu8 values containing the key.
*/
void newdessk_enc( iu8* v, iu8* k );

/*!	\brief NEWDES-SK decryption function.

	This function decrypts <EM>v</EM> with <EM>k</EM> and returns the
	decrypted data in <EM>v</EM>.

	\param v Array of eight iu8 values containing the data block.
	\param k Array of 15 iu8 values containing the key.
*/
void newdessk_dec( iu8* v, iu8* k );

#endif

