#pragma once

#include <cstdint>

#include "type_rgb.hpp"

namespace Board::SK108::Types {

	struct MBBreath {
		uint8_t byte_0; // idk what this is
		::Types::RGB rgb;
		uint16_t speed;
	};

	enum EQWaveModes: uint8_t {
		horizontal = 1,
		vertical = 2,
	};

	struct MBEQ {
		EQWaveModes wave_mode;
		uint8_t button_mode;
		uint16_t stream_speed;
		uint16_t wave_speed; // between 1800 and 200 in their panel
		int8_t range; // aka 'range', between 0 and 20?
		int8_t master_gain; // between -20 and 0?
		int8_t gain1; // the rest seem to be between -20 and 20
		int8_t gain2;
		int8_t gain3;
		int8_t gain4;
		int8_t gain5;
	};

}