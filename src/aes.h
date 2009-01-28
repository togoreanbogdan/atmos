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

/*! \brief AES encryption function.

	This function encrypts <EM>v</EM> with <EM>k</EM> and returns the
	encrypted data in <EM>v</EM>.

	\param v Array of two long values containing the data block.
	\param k Array of four long values containing the key.
*/
void aes_enc( iu8 *v, iu8 *k); //, iu32 v_len );

/*! \brief AES decryption function.

	This function decrypts <EM>v</EM> with <EM>k</EM> and returns the
	decrypted data in <EM>v</EM>.

	\param v Array of two long values containing the data block.
	\param k Array of four long values containing the key.
*/
void aes_dec( iu8 *v, iu8 *k); //, iu32 v_len );

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

