#include "sk108_modes.hpp"

#include "hid_crypt.hpp"

#include "sk108_globals.hpp"
#include "sk108_types.hpp"

namespace Board::SK108::Modes {

	enum MODES {
		EQ = 1,
		Breath = 3,
		Gradient = 4,
		Ripple = 5,
		//Stream = 5,
		Star = 6,
		Roll = 7,
		Wind = 9,
		Normal = 9,
	};

	using namespace Board::SK108::Globals;
	using namespace Board::SK108::Types;

	void rollMode(hid_device *handle, uint16_t speed) {
		uint8_t buf[_buf_sz] = {};
		buf[0] = _report_id;
		buf[1] = 8;
		buf[2] = 5;
		buf[3] = MODES::Roll; /*NavigationViewModel.Instance.mixButtom.mode*/
		buf[4] = speed;
		buf[5] = speed >> 8;
		HID::Crypt::xorSend(buf, _buf_sz);
		hid_write(handle, buf, _buf_sz);
	}

	void starMode(hid_device *handle, uint16_t speed, uint16_t stars) {
		uint8_t buf[_buf_sz] = {};
		buf[0] = _report_id;
		buf[1] = 8;
		buf[2] = 5;
		buf[3] = MODES::Star; // NavigationViewModel.Instance.mixButtom.mode
		buf[4] = speed;
		buf[5] = speed >> 8;
		buf[6] = stars; // I don't think star_count is relevant
		buf[7] = stars >> 8;
		HID::Crypt::xorSend(buf, _buf_sz);
		hid_write(handle, buf, _buf_sz);
	}

	void windMode(hid_device *handle, uint16_t speed) {
		uint8_t buf[_buf_sz] = {};
		buf[0] = _report_id;
		buf[1] = 8;
		buf[2] = 5;
		buf[3] = MODES::Wind;
		buf[4] = speed;
		buf[5] = speed >> 8;
		HID::Crypt::xorSend(buf, _buf_sz);
		hid_write(handle, buf, _buf_sz);
	}

	void rippleMode(hid_device *handle, uint16_t speed) {
		uint8_t buf[_buf_sz] = {};
		buf[0] = _report_id;
		buf[1] = 8;
		buf[2] = 5;
		buf[3] = MODES::Ripple;
		buf[4] = speed;
		buf[5] = speed >> 8;
		HID::Crypt::xorSend(buf, _buf_sz);
		hid_write(handle, buf, _buf_sz);
	}

	void breathMode(hid_device *handle, const MBBreath &breath) {
		uint8_t buf[_buf_sz] = {};
		buf[0] = _report_id;
		buf[1] = 8;
		buf[2] = 5;
		buf[3] = Modes::Breath;
		buf[4] = breath.speed;
		buf[5] = breath.speed >> 8;
		buf[6] = breath.byte_0;
		buf[7] = breath.rgb.r;
		buf[8] = breath.rgb.g;
		buf[9] = breath.rgb.b;
		HID::Crypt::xorSend(buf, _buf_sz);
		hid_write(handle, buf, _buf_sz);
	}

	void eqMode(hid_device *handle, const Types::MBEQ &eq) {
		uint8_t buf[_buf_sz] = {};
		buf[0] = _report_id;
		/*buf[1] = 8;
		buf[2] = 5;
		buf[3] = Modes::EQ;
		buf[4] = eq.stream_speed;
		buf[5] = eq.stream_speed >> 8;
		buf[6] = eq.wave_speed;
		buf[7] = eq.wave_speed >> 8;
		buf[8] = eq.wave_mode;
		buf[9] = eq.button_mode;
		buf[10] = eq.range;
		buf[11] = eq.master_gain;
		buf[12] = eq.gain1;
		buf[13] = eq.gain2;
		buf[14] = eq.gain3;
		buf[15] = eq.gain4;
		buf[16] = eq.gain5;*/
		/*
		buf[0] = 8;
		buf[1] = 5;
		buf[2] = 1;
		buf[7] = 1;
		buf[8] = 1;
		buf[3] = 10986;
		buf[4] = 10986 >> 8;
		buf[5] = 1800;
		buf[6] = 1800 >> 8;
		buf[9] = 18;
		buf[10] = 0;
		buf[11] = 20;
		buf[12] = 20;
		buf[13] = 20;
		buf[14] = 20;
		buf[15] = 20;
		*/
		HID::Crypt::xorSend(buf, _buf_sz);
		hid_write(handle, buf, _buf_sz);
	}

}