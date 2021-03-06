/*
  Simple Operating System for Smartcard Education
  Copyright (C) 2002  Matthias Bruestle <m@mbsks.franken.de>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*! @file
  \brief Crypto declarations.

  $Id: crypt.h,v 1.1 2003/03/30 12:42:21 m Exp $
*/

#ifndef ATMOS_CRYPT_H
#define ATMOS_CRYPT_H

#include <config.h>

#include <sw.h>
#include <string.h>
#include <types.h>

//#define CRYPT_ALGO_TEA      0 //!< Algorithm ID: TEA
//#define CRYPT_ALGO_SKIPJACK   1 //!< Algorithm ID: Skipjack
//#define CRYPT_ALGO_NEWDESSK   2 //!< Algorithm ID: NEWDES-SK
//#define CRYPT_ALGO_AES    3 //!< Algorithm ID: AES

#if CONF_WITH_CRYPT_ALGO==0
#define CRYPT_ALGO "TEA"
#include <tea.h>
//! Length of key in octets.
#define CRYPT_KEY_LEN TEA_KEY_LEN
//! Length of cipher block in octets.
#define CRYPT_BLOCK_LEN TEA_BLOCK_LEN
//! Test input value, crypt key and encryption result for algorithm
//  correctness verification.
#define CRYPT_TEST_VAL TEA_TEST_VAL
#define CRYPT_TEST_KEY TEA_TEST_KEY
#define CRYPT_TEST_CHK TEA_TEST_CHK
//! Single block encryption function.
#define crypt_enc(v,k) tea_enc((iu32*)(v),(iu32*)(k))
//! Single block decryption function.
#define crypt_dec(v,k) tea_dec((iu32*)(v),(iu32*)(k))

#elif CONF_WITH_CRYPT_ALGO==1
#define CRYPT_ALGO "SKIPJACK"
#include <skipjack.h>
#define CRYPT_KEY_LEN SKIPJACK_KEY_LEN
#define CRYPT_BLOCK_LEN SKIPJACK_BLOCK_LEN
#define CRYPT_TEST_VAL SKIPJACK_TEST_VAL
#define CRYPT_TEST_KEY SKIPJACK_TEST_KEY
#define CRYPT_TEST_CHK SKIPJACK_TEST_CHK
#define crypt_enc(v,k) skipjack_enc((iu8*)(v),(iu8*)(k))
#define crypt_dec(v,k) skipjack_dec((iu8*)(v),(iu8*)(k))

#elif CONF_WITH_CRYPT_ALGO==2
#define CRYPT_ALGO "NEWDES-SK"
#include <newdes-sk.h>
#define CRYPT_KEY_LEN NEWDESSK_KEY_LEN
#define CRYPT_BLOCK_LEN NEWDESSK_BLOCK_LEN
#define CRYPT_TEST_VAL NEWDESSK_TEST_VAL
#define CRYPT_TEST_KEY NEWDESSK_TEST_KEY
#define CRYPT_TEST_CHK NEWDESSK_TEST_CHK
#define crypt_enc(v,k) newdessk_enc((iu8*)(v),(iu8*)(k))
#define crypt_dec(v,k) newdessk_dec((iu8*)(v),(iu8*)(k))

#elif CONF_WITH_CRYPT_ALGO==3
#define CRYPT_ALGO "AES"
#include <aes.h>
#define CRYPT_KEY_LEN AES_KEY_LEN
#define CRYPT_BLOCK_LEN AES_BLOCK_LEN
#define CRYPT_TEST_VAL AES_TEST_VAL
#define CRYPT_TEST_KEY AES_TEST_KEY
#define CRYPT_TEST_CHK AES_TEST_CHK
#define crypt_enc(v,k) aes_enc(v,k,1)
#define crypt_dec(v,k) aes_dec(v,k,1)

#else
#error No valid crypto algorithm selected.
#endif

#define TO_STRING(x) #x

#endif /* ATMOS_CRYPT_H */

