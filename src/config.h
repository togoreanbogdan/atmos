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
  \brief Configuration settings (build options).
*/

#ifndef SOSSE_CONFIG_H
#define SOSSE_CONFIG_H


/* Configuration defines */

/*! \brief En-/disables file system.
*/
#define CONF_WITH_FILESYSTEM    1

/*! \brief En-/disables transactions.
  Adds about 354-400 bytes to flash image size.
*/
#define CONF_WITH_TRANSACTIONS  1

/*! \brief En-/disables test commands.
  If set to 1, commands READ EEPROM and WRITE EEPROM are included.
*/
#define CONF_WITH_TESTCMDS      0

/*! \brief En-/disables DELETE.
  Automatically disabled if building without filesystem.
*/
#define CONF_WITH_DELETECMD     1

/*! \brief En-/disables CREATE.
  Automatically disabled if building without filesystem.
*/
#define CONF_WITH_CREATECMD     1

/*! \brief En-/disables PIN authentication functions.
  If set to 1, functions to set and test PIN and PUK are included. This is a
  requirement for CONF_WITH_PINCMDS.
  Adds about 950 bytes to flash image size.
*/
#define CONF_WITH_PINAUTH       1

/*! \brief En-/disables PIN commands.
  If set to 1, commands CHANGE PIN and VERIFY PIN are included.
  Adds about 240 bytes to flash image size.
*/
#define CONF_WITH_PINCMDS       1

/*! \brief En-/disables key authentication functions.

  If set to 1, functions impelementing calculations with challenges are
  included. This is a requirement for CONF_WITH_KEY_CMDS.
*/
#define CONF_WITH_KEYAUTH       1

/*! \brief En-/disables key related commands.
  If set to 1, commands EXTERNAL KEYENTIFICATION, GET CHALLENGE,
  INTERNAL KEYENTIFICATION and VERIFY KEY are included.
*/
#define CONF_WITH_KEYCMDS       1

/*! \brief En-/disables support for the external (I2C) EEPROM.
 *  Atmel chips have internal EEPROM integrated onto the card, usually
 *  512 Bytes. This option enables use of the external EEPROM chip, the
 *  one specified as 24C64 (8 KB), 24C128, 256, 512, 1024 (128 KB)...
*/
#define CONF_WITH_I2CEEPROM     1

/*! \brief En-/disables support for decryption.
  If set to 1, support for decryption side of the cryptographic algorithms
  are included.
*/
#define CONF_WITH_DECRYPT       1

/*! \brief En-/disables support for logging.
  If set to 1, support for logging is included.
*/
#define CONF_WITH_LOGGING       1

/*! \brief En-/disables return code manager.
  If set to 1, the return code manager is included.
  Adds about 188 bytes to flash image size.
*/
#define CONF_WITH_RETCODEMGR    1

/*! \brief En-/disables funny commands.
  If set to 1, funny commands are included. Use only with 8535.
*/
#define CONF_WITH_FUNNY         0

/*! \brief En-/disables true random generator. <B>Highly experimental!</B>
  If set to 1, a true random number generator is included. This is
  currently only for test purposes and highly experimental!
*/
#define CONF_WITH_TRNG          0

/*! \brief Set crypto algorithm
  - 0: TEA
  - 1: Skipjack
  - 2: NEWDES-SK
*/
//#define CONF_WITH_CRYPT_ALGO    0 /* TEA */
#define CONF_WITH_CRYPT_ALGO    1 /* Skipjack */
//#define CONF_WITH_CRYPT_ALGO    2 /* NEWDES-SK */
//#define CONF_WITH_CRYPT_ALGO    3 /* AES */


/* Verify dependencies */

/* CONF_WITH_PINAUTH is required for CONF_WITH_PINCMDS */
#if (CONF_WITH_PINCMDS==1) && (CONF_WITH_PINAUTH!=1)
#warning CONF_WITH_PINCMDS implies CONF_WITH_PINAUTH
#undef CONF_WITH_PINAUTH
#define CONF_WITH_PINAUTH       1
#endif

/* CONF_WITH_KEYAUTH is required for CONF_WITH_KEYCMDS */
#if (CONF_WITH_KEYCMDS==1) && (CONF_WITH_KEYAUTH!=1)
#warning CONF_WITH_KEYCMDS implies CONF_WITH_KEYAUTH
#undef CONF_WITH_KEYAUTH
#define CONF_WITH_KEYAUTH       1
#endif

/* If we do not have a file system, we don't need CREATE and DELETE */
#if (CONF_WITH_FILESYSTEM!=1) && (CONF_WITH_DELETECMD==1)
#warning CONF_WITHOUT_FILESYSTEM implies CONF_WITHOUT_DELETECMD
#undef CONF_WITH_DELETECMD
#define CONF_WITH_DELETECMD     0
#endif
#if (CONF_WITH_FILESYSTEM!=1) && (CONF_WITH_CREATECMD==1)
#warning CONF_WITHOUT_FILESYSTEM implies CONF_WITHOUT_CREATECMD
#undef CONF_WITH_CREATECMD
#define CONF_WITH_CREATECMD     0
#endif


/* EEPROM addresses */

/*! \brief EEPROM address of the state of the card.
  <EM>Warning: When using interrupts on the AVR, this byte may accidently
  be changed. See errata sheets of AVR.</EM>
  This is currently unused and just skipped.
*/
#define CARD_STATE_ADDR     0x0000

//! EEPROM address of the ATR length.
//! Max. length of the ATR
//! EEPROM address of the ATR.
#define ATR_LEN_ADDR        (CARD_STATE_ADDR+1)
#define ATR_MAXLEN          28
#define ATR_ADDR            (ATR_LEN_ADDR+1)

//! EEPROM address of the serial number of the card.
//! Length of the serial number.
#define SERNUM_ADDR         (ATR_ADDR+ATR_MAXLEN)
#define SERNUM_LEN          8

//! EEPROM address of the state of the PRNG.
//! Length of the state of the PRNG. (Counter[8], State[8], Key[16])
#define RAND_STATE_ADDR     (SERNUM_ADDR+SERNUM_LEN)
#define RAND_STATE_LEN      8+8+16

//! EEPROM address of the transaction state.
//! EEPROM address of the transaction data.
//! Length of the transaction data.
#define TRANSAC_STATE_ADDR  (RAND_STATE_ADDR+RAND_STATE_LEN)
#define TRANSAC_DATA_ADDR   (TRANSAC_STATE_ADDR+1)
#define TRANSAC_DATA_LEN    19  /* Currently 2B addr, 1B len, 16B data */

//! Length of the External Authentication key.
//! Length of the Internal Authentication key.
//! Length of the PIN.
//! Length of the PUK.
#define ADM_KEY_LEN         16
#define INT_KEY_LEN         16
#define PIN_LEN             8
#define PUK_LEN             8

/* If filesystem is used, it starts right away and mandatory data is
 * created as files in the filesystem. If not, then the mandatory data
 * is just placed at memory offsets so that it can be read.
 */
#if CONF_WITH_FILESYSTEM==1
//! Dummy address to handle the ifdefs here. Filesystem starts right away.
#define DATA_END_1          (TRANSAC_DATA_ADDR+TRANSAC_DATA_LEN)

#else /* CONF_WITH_FILESYSTEM!=1 */

//! EEPROM address of the External Authentication key.
//! EEPROM address of the retry counter for the External Authentication key.
#define ADM_KEY_ADDR        (TRANSAC_DATA_ADDR+TRANSAC_DATA_LEN)
#define ADM_RETCNTR_ADDR    (ADM_KEY_ADDR+ADM_KEY_LEN)

//! EEPROM address of the Internal Authentication key.
//! EEPROM address of the retry counter for the Internal Authentication key.
#define INT_KEY_ADDR        (ADM_RETCNTR_ADDR+1)
#define INT_RETCNTR_ADDR    (INT_KEY_ADDR+INT_KEY_LEN)

//! EEPROM address of the PIN.
//! EEPROM address of the retry counter for the PIN.
//! EEPROM address of the PUK.
//! EEPROM address of the retry counter for the PUK.
//! Dummy address to handle the ifdefs here.
#define PIN_ADDR            (INT_RETCNTR_ADDR+1)
#define PIN_RETCNTR_ADDR    (PIN_ADDR+PIN_LEN)
#define PUK_ADDR            (PIN_RETCNTR_ADDR+1)
#define PUK_RETCNTR_ADDR    (PUK_ADDR+PUK_LEN)
#define DATA_END_1          (PUK_RETCNTR_ADDR+1)

#endif /* CONF_WITH_FILESYSTEM!=1 */


//! EEPROM address of pointer to the file system start.
/* Filesystem starts right after mandatory data part ends */
#define FS_START_PTR_ADDR   DATA_END_1


/*
 * Type of target chip and smart card
 *
 * AVR-based smartcards have the following elements:
 *   RAM, ROM (Flash) and internal EEPROM on the processor chip itself.
 *   External EEPROM on additional chip (24LC64, 24LC128, 256, 512, 1024).
 *   (External EEPROM is currently completely unused).
 *
 * The following data needs to be defined for each chip:
 *
 *  ENDIAN_LITTLE    If architecture is little endian
 *  INT_EEPROM_SIZE  Internal EEPROM size in bytes (0x200=512B, 0x80=128B...)
 *  RAM_SIZE         RAM size in bytes (0x200 = 512 B, 0x400 = 1 KB...)
 *  CHIP             Chip ID, voluntarily assigned by us and returned as
 *                     part of card's ATR signature. Scheme is as follows:
 *                       00: AT90S2323, AT90S2343 (2343 not supported)
 *                       01: AT90S8515, AT90S8535
 *                       02: ATmega161
 *                       03: ATmega163
 *                       10: 16F84 (not supported)
 *                       11: 16F876 (not supported)
 *                       FF: unspec. (running on 386 emulator)
 *  EXT_EEPROM_SIZE  External EEPROM size in Kbytes. Unused, but returned as
 *                     part of card's ATR signature. The defines here are 
 *                     commented because this information is not part of
 *                     the chip (can vary between smartcards even though
 *                     the processor chip may be the same), so it is set as 
 *                     its own option in the Makefile. Scheme is as follows:
 *                       00: none
 *                       01: 16 KB
 *                       02: 32 KB
 *                       03: 64 KB
 *                       04: 128 KB
 *                       05: 256 KB
 *                       06: 512 KB
 *                       07: 1024 KB
 *                       08: 2048 KB
 *                       FF: unspec.
 *  ARCH             Architecture type. Needed for assembler code and returned
 *                     as part of card's ATR signature. (Note that this setting
 *                     is unrelated and different to Makefile's ARCH=).
 *
 */

#if defined(__AVR_AT90S8515__)
#define ENDIAN_LITTLE
#define INT_EEPROM_SIZE    0x200
#define RAM_SIZE           0x200
#define CHIP               0x01
//#define EXT_EEPROM_SIZE    0x02
#define ARCH               avr2

#elif defined(__AVR_AT90S8535__)
#define ENDIAN_LITTLE
#define INT_EEPROM_SIZE    0x200
#define RAM_SIZE           0x200
#define CHIP               0x01
//#define EXT_EEPROM_SIZE    0x03
#define ARCH               avr2

#elif defined(__AVR_AT90S2323__)
#define ENDIAN_LITTLE
#define INT_EEPROM_SIZE    0x80
#define RAM_SIZE           0x80
#define CHIP               0x00
//#define EXT_EEPROM_SIZE    0x03
#define ARCH               avr2

#elif defined(__AVR_ATmega161__)
#define ENDIAN_LITTLE
#define INT_EEPROM_SIZE    0x200
#define RAM_SIZE           0x400
#define CHIP               0x02
//#define EXT_EEPROM_SIZE    0x03
#define ARCH               avr5

#elif defined(__AVR_ATmega163__)
#define ENDIAN_LITTLE
#define INT_EEPROM_SIZE    0x200
#define RAM_SIZE           0x400
#define CHIP               0x03
//#define EXT_EEPROM_SIZE    0x03
#define ARCH               avr5

#elif defined(__i386__)
#define ENDIAN_LITTLE
#define INT_EEPROM_SIZE    0x200
#define RAM_SIZE           0x200
#define CHIP               0xFF
//#define EXT_EEPROM_SIZE    0xFF

#else
#error Unknown destination platform. Use proper ARCH type in Makefile.
#endif


/* Just for pretty printing */
#define ESIZ EXT_EEPROM_SIZE


#endif /* SOSSE_CONFIG_H */

