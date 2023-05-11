#include "hid_util.hpp"

namespace HID::Util {

	// move this to a util class later
	hid_device* openByPath(const char *path) {
		return hid_open_path(path);
	}

	hid_device* getDevice(uint16_t vid, uint16_t pid, const char *component) {
		hid_device_info *dev;
		dev = hid_enumerate(0x0, 0x0); // enumerate over all devices
		hid_device *dev_handle = nullptr;
		while (dev) {
			hid_device_info *tmp_dev = dev;
			dev = dev->next;
			if (tmp_dev->vendor_id != vid || tmp_dev->product_id != pid) {
				continue;
			}
			if (strstr(tmp_dev->path, component)) {
				dev_handle = openByPath(tmp_dev->path);
				break;
			}
		}
		return dev_handle;
	}

}