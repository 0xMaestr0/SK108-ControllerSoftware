#pragma once

#include <cstdint>

#include "hidapi/hidapi.h"

namespace HID::Util {

	hid_device* openByPath(const char *path);

	hid_device* getDevice(uint16_t vid, uint16_t pid, const char *component);

}