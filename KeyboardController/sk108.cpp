#include "sk108.hpp"

#include <thread>
#include <cstdint>
#include <qdebug.h>

#include "hidapi/hidapi.h"

#include "type_firmware.hpp"
#include "hid_util.hpp"
#include "hid_crypt.hpp"
#include "ids.hpp"

#include "sk108_modes.hpp"
#include "sk108_globals.hpp"

namespace Board::SK108 {

	using namespace SK108::Globals;

	struct RecvData {
		uint8_t mb_activated: 1;
		uint8_t light_sync_state: 1;
	};

	void sendConfig(hid_device *handle) {
		uint8_t buf[_buf_sz] = {};
		buf[0] = _report_id;
		buf[1] = 8;
		buf[2] = 2;
		buf[3] = g_config.dev_mode;
		buf[4] = g_config.keyMemNum;
		buf[5] = g_config.brightness;
		buf[6] = g_config.light_mode;
		buf[7] = g_config.circle_bright;
		buf[8] = g_config.circle_sync;
		buf[9] = g_config.multiplex_cfg;
		buf[10] = g_config.key_delay;
		buf[11] = g_config.meArgbSpeed;
		buf[12] = g_config.meArgbSpeed >> 8;
		buf[13] = g_config.meSpreadSpeed;
		buf[14] = g_config.meSpreadSpeed >> 8;
		buf[15] = g_config.breath_speed;
		buf[16] = g_config.gradient_speed;
		HID::Crypt::xorSend(buf, Globals::_buf_sz);
		hid_write(handle, buf, _buf_sz);
	}

	void sendInitCmd(hid_device *handle, enum INIT_CMD cmd) {
		uint8_t buf[_buf_sz] = {};
		buf[0] = _report_id;
		buf[1] = 8;
		buf[2] = 0;
		buf[3] = cmd;
		HID::Crypt::xorSend(buf, Globals::_buf_sz);
		hid_write(handle, buf, _buf_sz);
	}

	/*		
				 data[ writeAddr, 0] = 8;
				 data[ writeAddr, 1] = 2;
				 data[ writeAddr, 2] = this.devCfg.devMode;
				 data[ writeAddr, 3] = this.devCfg.keyMemNum;
				 data[ writeAddr, 4] = this.devCfg.bright;
				 data[ writeAddr, 5] = this.devCfg.light_mode;
				 data[ writeAddr, 6] = this.devCfg.circleBright;
				 data[ writeAddr, 7] = this.devCfg.circleSync;
				 data[ writeAddr, 8] = this.devCfg.multiPlexConfig;
				 data[ writeAddr, 9] = this.devCfg.keyDelay;
				 data[ writeAddr, 10] = (uint8_t)this.devCfg.meArgbSpeed;
				 data[ writeAddr, 11] = (uint8_t)(this.devCfg.meArgbSpeed >> 8);
				 data[ writeAddr, 12] = (uint8_t)this.devCfg.meSpreadSpeed;
				 data[ writeAddr, 13] = (uint8_t)(this.devCfg.meSpreadSpeed >> 8);
				 data[ writeAddr, 14] = this.devCfg.mtBreathSpeed;
				 data[ writeAddr, 15] = this.devCfg.mtGradientSpeed;
				UsbDevice hidDev =  fastConnList[this.conn_index].hidDev;
				hidDev.naviSendBuf.writeAddr = hidDev.naviSendBuf.writeAddr + 1;
				UsbDevice hidDev2 =  fastConnList[this.conn_index].hidDev;
				hidDev2.naviSendBuf.writeAddr = hidDev2.naviSendBuf.writeAddr % 8;
	*/

	// receivers
	void receiveROMInfo(hid_device *handle, uint8_t buf[_buf_sz - 9]) {
		// it also creates some .BIN files, 
		// and receives some data (maybe serial ID?) 
		// then uses it to create a directory where it puts the files
		::Types::Firmware firmware_ver;
		firmware_ver.major = buf[6];
		firmware_ver.minor = buf[7];
		firmware_ver.build = buf[8];
		firmware_ver.revision = buf[9];
		sendInitCmd(handle, INIT_CMD::DEV_INIT);
	}

	// leave this for later.. pretty boring
	void receiver(hid_device *handle, uint8_t buf[Globals::_buf_sz]) {
		HID::Crypt::xorRcv(buf, Globals::_buf_sz);
		uint8_t *ptr = &buf[1]; // ignore report id
		qDebug() << ptr[1];
		if (ptr[0] == 2) {
			// ...
		} else if (ptr[1] == 243) {

		} else if (ptr[1] == 244) {
			uint8_t mb_mode = ptr[17];
			uint8_t mb_activated = ptr[8] & 1;
			uint8_t light_sync = ((ptr[8] >> 6) & 1);
			int bb = 9;
		} else if (ptr[1] == 0) { // <= 197
			uint16_t num6 = (uint16_t)((int)ptr[5] + ((int)ptr[6] << 8));
			uint16_t num7 = (uint16_t)((int)ptr[3] + ((int)ptr[4] << 8));
			int num8 = (int)((num6 - 1) * 12);
			int num9 = (int)ptr[2];
			int num10 = num9;
			int bb = 9;
			if (num10 <= 197) {
				switch (num10) {
					case 0:
						sendInitCmd(handle, INIT_CMD::DEV_INFO);
						break;
					case 1:
						break;
				}
			} else if (num10 != 240) {

			} else {
				receiveROMInfo(handle, buf + 9);
			}
		}

	}

	void fast_conn(hid_device *handle) {
		uint8_t buf[Globals::_buf_sz] = {};
		buf[0] = Globals::_report_id;
		buf[1] = 1;
		HID::Crypt::xorSend(buf, Globals::_buf_sz);
		hid_write(handle, (const unsigned char*)buf, Globals::_buf_sz);
	}

	/*
	multiplex configs:
	128 - off
	129 - backlight (entire kb)
	136 - under ('util' keys)
	137 - both backlight and under
	141 - enter, backlight, under
	132 - enter
	130 - custom

	under: 4th bit (1xxx)
	enter: 3rd bit (x1xx)
	custom: 2nd bit (xx1x)
	backlight: 1st bit

	*/

	void start() {
		g_config.brightness = 255;
		g_config.dev_mode = 15;
		g_config.circle_bright = 1;
		g_config.circle_sync = 0;
		g_config.key_delay = 8;
		g_config.keyMemNum = 0;
		g_config.light_mode = 0;
		g_config.meArgbSpeed = 750;
		g_config.meSpreadSpeed = 8000;
		g_config.breath_speed = 10;
		g_config.gradient_speed = 7;
		g_config.multiplex_cfg = 128 | MULTIPLEX_MASKS::backlight;
		g_config.sync_active_mode = 0;

		int res = hid_init();
		hid_device *handle = HID::Util::getDevice(Globals::_vid, Globals::_pid, Globals::_component);
		if (handle == nullptr) {
			hid_exit();
			return;
		}
		uint8_t buf[Globals::_buf_sz];
		std::thread t([&handle, &buf]() {
			while (true) {
				// Read requested state
				int res = hid_read(handle, buf, 21);
				receiver(handle, buf);
			}
		});
		fast_conn(handle);
		// send this when we select it in the gui
		sendInitCmd(handle, INIT_CMD::INIT_START);
		/*sendInitCmd(handle, INIT_CMD::DEV_INFO);
		sendInitCmd(handle, INIT_CMD::DEV_INIT);
		sendInitCmd(handle, INIT_CMD::LAYER_KEY_INIT);
		sendInitCmd(handle, INIT_CMD::KEY_M1_CRC_INIT);
		sendInitCmd(handle, INIT_CMD::KEY_M2_CRC_INIT);
		sendInitCmd(handle, INIT_CMD::MB_INIT);
		sendInitCmd(handle, INIT_CMD::MC_INIT);
		sendInitCmd(handle, INIT_CMD::MT_INIT);
		sendInitCmd(handle, INIT_CMD::INDICATOR_INIT);
		sendInitCmd(handle, INIT_CMD::ME_CRC_INIT);
		sendInitCmd(handle, INIT_CMD::INIT_END);*/
		sendConfig(handle);
		//Modes::starMode(handle, key_settings.star.speed1, key_settings.star.speed2);
		//Modes::rollMode(handle, key_settings.roll_speed);
		//Modes::windMode(handle, key_settings.wind_speed);
		//Modes::breathMode(handle, key_settings.breath);
		//Modes::rollMode(handle, key_settings.roll_speed);
		Modes::rippleMode(handle, key_settings.ripple_speed);
		if (t.joinable()) {
			t.join();
		}
		// Close the device
		hid_close(handle);
		// Finalize the hidapi library
		res = hid_exit();
	}

}