#pragma once

#include <cstdint>

namespace Types {

	struct Firmware {
		uint8_t major = 0;
		uint8_t minor = 0;
		uint8_t build = 0;
		uint8_t revision = 0;
	};

}