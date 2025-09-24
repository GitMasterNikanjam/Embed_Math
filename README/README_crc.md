# CRC Library

## Overview
This library provides a collection of **CRC (Cyclic Redundancy Check)** and checksum algorithms that are widely used in embedded systems, networking, and communication protocols.  
It is **portable** (no hardware/board dependencies) and written in C/C++ with only `<stdint.h>` required.

Available implementations include:
- **CRC4**
- **CRC8** (several variants: generic, DVB-S2, DVB, Maxim/Dallas, SAE J1850, RDS02UF)
- **CRC16** (XMODEM, IBM, CCITT, CCITT reversed, CCITT GDL90, Modbus, Fletcher-16)
- **CRC24** (polynomial 0x1864CFB)
- **CRC32** (standard polynomial, small-table variant)
- **CRC64** (polynomial 0x42F0E1EBA9EA3693)
- **Hashing**: FNV-1a 64-bit hash
- **Utility checks**: byte sum (8/16-bit) and parity

---

## What is CRC?

**CRC (Cyclic Redundancy Check)** is an error-detecting code used to identify accidental changes to raw data.  

- Data is treated as a binary number.
- A fixed **polynomial** (e.g., `0x1021` for CRC16-CCITT) is used to divide the data stream.
- The **remainder** of this division is the CRC "checksum."
- This checksum is appended to transmitted data.
- The receiver recomputes the CRC and verifies it matches — if not, errors are detected.

CRC is widely used in:
- **Networking** (Ethernet, CAN, USB, XMODEM, Modbus).
- **Storage** (hard drives, flash memory).
- **Embedded systems** (sensors, communication protocols).

Unlike a simple sum, CRCs can detect **bursts of bit errors** with high probability.

---

## API Reference

All functions are declared in [`crc.h`](crc.h) and implemented in [`crc.cpp`](crc.cpp).

Examples:
- `uint16_t crc16_ccitt(const uint8_t *buf, uint32_t len, uint16_t crc);`
- `uint32_t crc_crc32(uint32_t crc, const uint8_t *buf, uint32_t size);`
- `uint8_t crc8_maxim(const uint8_t *data, uint16_t length);`

---

## Usage

### Example 1: CRC16-CCITT
```cpp
#include "crc.h"
#include <iostream>

int main() {
    const uint8_t msg[] = { 'H', 'e', 'l', 'l', 'o' };
    uint16_t crc = crc16_ccitt(msg, sizeof(msg), 0xFFFF);
    std::cout << "CRC16-CCITT: 0x" << std::hex << crc << std::endl;
}
```

### Example 2: CRC32

```cpp
#include "crc.h"
#include <iostream>

int main() {
    const uint8_t data[] = { 1, 2, 3, 4, 5 };
    uint32_t crc = crc_crc32(0xFFFFFFFF, data, sizeof(data));
    std::cout << "CRC32: 0x" << std::hex << crc << std::endl;
}
```

### Example 3: FNV-1a Hash

```cpp
#include "crc.h"
#include <iostream>

int main() {
    const uint8_t data[] = "OpenAI";
    uint64_t hash = FNV_1_OFFSET_BASIS_64;
    hash_fnv_1a(sizeof(data)-1, data, &hash);
    std::cout << "FNV-1a Hash: 0x" << std::hex << hash << std::endl;
}
```

---

## Build

Compile into a static library:

```bash
g++ -std=c++11 -Wall -Wextra -O2 -c crc.cpp -o crc.o
ar rcs libcrc.a crc.o
```

Use in your project:

```bash
g++ main.cpp crc.o -o main
```

---

## Notes

* CRC initial values differ between protocols (e.g., `0xFFFF` for CCITT).
* Some algorithms require a final **XOR-out** step.
* Always verify against the protocol specification.

---

## License

This library is distributed under the **GPLv3** license.

```

---

✅ This `README.md`:
- Explains **what CRC is**.
- Lists all **algorithms provided**.
- Gives **ready-to-run examples**.
- Shows **build instructions**.
- Clarifies licensing.


