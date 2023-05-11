#pragma once

#include <cstdint>

namespace HID::Crypt {

	void xorSend(uint8_t *dat, size_t len);

	void xorRcv(uint8_t *dat, size_t len);

}