/*! @file
	\brief AES declarations.

	Documentation for AES is available at
	XXX-fill in.

	$Id: aes.h,v 1.5 2002/12/22 15:42:55 m Exp $
*/

#ifndef ATMOS_AES_H
#define ATMOS_AES_H

#include <types.h>

#define AES_KEY_LEN   16  //!< AES key size.
#define AES_BLOCK_LEN 16  //!< AES block length.

#define AES_TEST_VAL 0x33, 0x22, 0x11, 0x00, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22
#define AES_TEST_KEY 0x00, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
#define AES_TEST_CHK 0x99, 0x3E, 0xB3, 0x30, 0x14, 0x5E, 0xC6, 0x59, 0x2F, 0x57, 0x26, 0xC6, 0xCC, 0xF8, 0x70, 0xF0

/*! \brief AES encryption function.

	This function encrypts <EM>v</EM> with <EM>k</EM> and returns the
	encrypted data in <EM>v</EM>.

	\param v Array of two long values containing the data block.
	\param k Array of four long values containing the key.
*/
void aes_enc( iu8 *v, iu8 *k, iu32 v_len );

/*! \brief AES decryption function.

	This function decrypts <EM>v</EM> with <EM>k</EM> and returns the
	decrypted data in <EM>v</EM>.

	\param v Array of two long values containing the data block.
	\param k Array of four long values containing the key.
*/
void aes_dec( iu8 *v, iu8 *k, iu32 v_len );

void addRoundKeyAndSubstituteBytes(iu8 *, iu8 *);
void shiftRows(iu8 *);
void mixColumns(iu8 *);
void keyExpansion(iu8 *, iu8 *);
void inverseSubstituteBytesAndAddRoundKey(iu8 *, iu8 *);
void inverseShiftRows(iu8 *);
void inverseMixColumns(iu8 *);
void inverseKeyExpansion(iu8 *, iu8 *);
void calculateLastRoundKey(iu8 *, iu8 *, iu8 *);
void swap(iu8 *, iu8 *);
iu8 xtime(iu8);

#endif /* ATMOS_AES_H */

