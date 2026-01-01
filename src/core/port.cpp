#include <stdint.h>
#include "../include/port.h"  // Make sure this path is correct for your project structure

namespace uqaabOS {
    namespace include {

        // Base class for port
        Port::Port(uint16_t portNumber) {
            this->portNumber = portNumber;
        }

        Port::~Port() {}

        // 8-bit Port
        Port8Bit::Port8Bit(uint16_t portNumber) : Port(portNumber) {}

        Port8Bit::~Port8Bit() {}

        void Port8Bit::write(uint8_t data) {
            write8(portNumber, data);  // Ensure write8 is implemented elsewhere
        }

        uint8_t Port8Bit::read() {
            return read8(portNumber);  // Ensure read8 is implemented elsewhere
        }

        // 8-bit Slow Port
        Port8BitSlow::Port8BitSlow(uint16_t portNumber) : Port8Bit(portNumber) {}

        Port8BitSlow::~Port8BitSlow() {}

        void Port8BitSlow::write(uint8_t data) {
            write8Slow(portNumber, data);  // Ensure write8Slow is implemented elsewhere
        }

        // 16-bit Port
        Port16Bit::Port16Bit(uint16_t portNumber) : Port(portNumber) {}

        Port16Bit::~Port16Bit() {}

        void Port16Bit::write(uint16_t data) {
            write16(portNumber, data);  // Ensure write16 is implemented elsewhere
        }

        uint16_t Port16Bit::read() {
            return read16(portNumber);  // Ensure read16 is implemented elsewhere
        }

        // 32-bit Port
        Port32Bit::Port32Bit(uint16_t portNumber) : Port(portNumber) {}

        Port32Bit::~Port32Bit() {}

        void Port32Bit::write(uint32_t data) {
            write32(portNumber, data);  // Ensure write32 is implemented elsewhere
        }

        uint32_t Port32Bit::read() {
            return read32(portNumber);  // Ensure read32 is implemented elsewhere
        }

    }  // namespace include
}  // namespace uqaabOS
