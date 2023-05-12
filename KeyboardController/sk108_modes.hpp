#pragma once

#include <cstdint>

#include "hidapi/hidapi.h"

#include "sk108_types.hpp"

namespace Board::SK108::Modes {

	void rollMode(hid_device *handle, uint16_t speed);

	void starMode(hid_device *handle, uint16_t speed, uint16_t stars);

	void windMode(hid_device *handle, uint16_t speed);

	void rippleMode(hid_device *handle, uint16_t speed);

	void breathMode(hid_device *handle, const Types::MBBreath &breath);

	// not yet working
	void eqMode(hid_device *handle, const Types::MBEQ &eq);

}