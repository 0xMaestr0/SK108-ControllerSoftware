#include "hid_crypt.hpp"

namespace HID::Crypt {

	uint8_t _xor_send[] {
		142,
		150,
		206,
		106,
		242,
		114,
		153,
		72,
		88,
		97,
		39,
		88,
		232,
		154,
		127,
		1,
		149,
		238,
		237,
		47
	};
	uint8_t _xor_rcv[] {
		106,
		109,
		100,
		102,
		63,
		46,
		240,
		67,
		10,
		65,
		234,
		143,
		43,
		252,
		224,
		231,
		213,
		82,
		123,
		165
	};

	void xorData(uint8_t *dat, uint8_t *xor_arr, size_t len) {
		for (int i = 1; i < len; i++) {
			dat[i] ^= xor_arr[i - 1];
		}
	}

	void xorSend(uint8_t *dat, size_t len) {
		xorData(dat, _xor_send, len);
	}

	void xorRcv(uint8_t *dat, size_t len) {
		xorData(dat, _xor_rcv, len);
	}

}