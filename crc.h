/**
 * @file crc.h
 * @brief Collection of CRC and checksum functions (portable, no HAL dependency).
 *
 * @details
 * This header provides a variety of cyclic redundancy check (CRC) and checksum
 * algorithms used in embedded systems and communication protocols. It includes:
 *   - CRC4, CRC8 (multiple polynomials), CRC16 (IBM, CCITT, Modbus, Fletcher),
 *   - CRC24, CRC32, CRC64,
 *   - FNV-1a 64-bit hashing,
 *   - simple parity and sum functions.
 *
 * All functions operate on standard integer and byte buffers.
 *
 * @note Originally from ArduPilot; stripped of HAL dependencies for portability.
 */

#pragma once

#include <stdint.h>

/**
 * @brief Compute CRC-4 across 16 bits of data.
 * @param data Pointer to 16-bit data array.
 * @return CRC-4 checksum.
 */
uint16_t crc_crc4(uint16_t *data);

/**
 * @brief Compute CRC-8 (generic default polynomial).
 * @param p Pointer to input buffer.
 * @param len Buffer length in bytes.
 * @return CRC-8 checksum.
 */
uint8_t crc_crc8(const uint8_t *p, uint8_t len);

/**
 * @brief Compute CRC-8 with arbitrary polynomial (bitwise implementation).
 * @param buf Pointer to input buffer.
 * @param buf_len Buffer length.
 * @param polynomial Generator polynomial.
 * @param initial_value Initial CRC seed (default = 0).
 * @return CRC-8 checksum.
 */
uint8_t crc8_generic(const uint8_t *buf, const uint16_t buf_len,
                     const uint8_t polynomial, uint8_t initial_value=0);

/**
 * @brief Update DVB-S2 CRC-8 with one byte.
 */
uint8_t crc8_dvb_s2(uint8_t crc, uint8_t a);

/**
 * @brief Update DVB CRC-8 with one byte.
 */
uint8_t crc8_dvb(uint8_t crc, uint8_t a, uint8_t seed);

/**
 * @brief Update DVB-S2 CRC-8 with a block.
 */
uint8_t crc8_dvb_s2_update(uint8_t crc, const void *data, uint32_t length);

/**
 * @brief Update DVB CRC-8 with a block.
 */
uint8_t crc8_dvb_update(uint8_t crc, const uint8_t* buf, const uint16_t buf_len);

/**
 * @brief Compute Maxim/Dallas one-wire CRC-8.
 */
uint8_t crc8_maxim(const uint8_t *data, uint16_t length);

/**
 * @brief Compute CRC-8-SAE J1850.
 */
uint8_t crc8_sae(const uint8_t *data, uint16_t length);

/**
 * @brief Compute CRC-8 RDS (0x1D polynomial, used in RDS02UF).
 */
uint8_t crc8_rds02uf(const uint8_t *data, uint16_t length);

/**
 * @brief Update XMODEM CRC-16 with one byte.
 */
uint16_t crc_xmodem_update(uint16_t crc, uint8_t data);

/**
 * @brief Compute XMODEM CRC-16 for a buffer.
 */
uint16_t crc_xmodem(const uint8_t *data, uint16_t len);

/**
 * @brief Compute CRC-32 (standard polynomial 0xEDB88320).
 */
uint32_t crc_crc32(uint32_t crc, const uint8_t *buf, uint32_t size);

/**
 * @brief Lightweight CRC-32 (small table).
 */
uint32_t crc32_small(uint32_t crc, const uint8_t *buf, uint32_t size);

/**
 * @brief Compute CRC-24 with polynomial 0x1864CFB.
 */
uint32_t crc_crc24(const uint8_t *bytes, uint16_t len);

/**
 * @brief Compute IBM CRC-16.
 */
uint16_t crc_crc16_ibm(uint16_t crc_accum, uint8_t *data_blk_ptr, uint16_t data_blk_size);

/**
 * @brief SPORT/FPort checksum: 16-bit sum, fold to 8 bits with carry, invert.
 */
uint8_t crc_sum8_with_carry(const uint8_t *p, uint8_t len);

/**
 * @brief Compute CCITT CRC-16.
 */
uint16_t crc16_ccitt(const uint8_t *buf, uint32_t len, uint16_t crc);

/**
 * @brief Compute reversed CCITT CRC-16.
 * @param out Final XOR output value.
 */
uint16_t crc16_ccitt_r(const uint8_t *buf, uint32_t len, uint16_t crc, uint16_t out);

/**
 * @brief GDL90 variant of CRC16-CCITT (non-standard).
 * @see https://www.faa.gov/nextgen/programs/adsb/archival/media/gdl90_public_icd_reva.pdf
 */
uint16_t crc16_ccitt_GDL90(const uint8_t *buf, uint32_t len, uint16_t crc);

/**
 * @brief Compute Modbus CRC-16.
 */
uint16_t calc_crc_modbus(const uint8_t *buf, uint16_t len);

/**
 * @brief Compute Fletcher-16 checksum.
 */
uint16_t crc_fletcher16(const uint8_t * buffer, uint32_t len);

/** @brief Offset basis constant for 64-bit FNV-1a hash. */
#define FNV_1_OFFSET_BASIS_64 14695981039346656037UL

/**
 * @brief Compute 64-bit FNV-1a hash.
 * @param len Buffer length.
 * @param buf Pointer to data.
 * @param hash Output pointer for hash result.
 */
void hash_fnv_1a(uint32_t len, const uint8_t* buf, uint64_t* hash);

/**
 * @brief Compute CRC-64-WE with polynomial 0x42F0E1EBA9EA3693.
 */
uint64_t crc_crc64(const uint32_t *data, uint16_t num_words);

/**
 * @brief Compute parity of a byte.
 * @return 1 if odd number of bits set, 0 if even.
 */
uint8_t parity(uint8_t byte);

/**
 * @brief Compute simple sum of bytes (mod 256).
 */
uint8_t crc_sum_of_bytes(const uint8_t *data, uint16_t count);

/**
 * @brief Compute simple sum of bytes (mod 0xFFFF).
 */
uint16_t crc_sum_of_bytes_16(const uint8_t *data, uint16_t count);
