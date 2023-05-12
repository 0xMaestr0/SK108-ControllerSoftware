#pragma once

#include <cstdint>

#include "type_rgb.hpp"

#include "sk108_types.hpp"

namespace Board::SK108 {

	namespace {

		// all rgb settings seem to be communicated form this
#pragma push(pack, 1)
		struct Config {
			uint8_t dev_mode;
			uint8_t keyMemNum;
			uint8_t brightness; // seems to be between 26 (10%) and 255 (100%)
			uint8_t light_mode; // there seems to be only 3
			uint8_t circle_bright;
			uint8_t circle_sync;
			uint8_t multiplex_cfg;
			uint8_t key_delay; // between 1 and 8? in ms
			uint16_t meArgbSpeed;
			uint16_t meSpreadSpeed;
			uint8_t breath_speed; // seems to be between 20 and 5, with faster being a lower number
			uint8_t gradient_speed; // seems to be between 20 and 4, with faster being a lower number
			uint8_t sync_active_mode;
		} g_config;
#pragma pop

		struct MBLight {
			uint16_t speed1;
			uint16_t speed2;
		};

		struct MBNormal {
			uint8_t byte_0;
			::Types::RGB rgb;
		};

		struct KeySettings {
			uint8_t mode;
			uint8_t nullA;
			Types::MBEQ eq;
			MBNormal normal;
			Types::MBBreath breath;
			MBLight gradient;
			MBLight stream;
			MBLight star;
			uint16_t roll_speed; // lower value = faster
			uint16_t ripple_speed;
			uint16_t wind_speed;
		} key_settings;

		enum MULTIPLEX_MASKS: uint8_t {
			backlight = 0b0000001,
			custom = 0b0000010,
			enter = 0b0000100,
			under = 0b0001000,
			wireless_sleep = 0b00100000,
		};

		enum INIT_CMD: uint8_t {
			KEY_M1_CRC_INIT = 193,
			KEY_M2_CRC_INIT,
			ME_CRC_INIT = 197,
			INIT_START = 0,
			DEV_INFO = 240,
			DEV_INIT = 1,
			LAYER_KEY_INIT = 12,
			KEY_M1_INIT = 2,
			KEY_M1_SEQ_INIT,
			KEY_M2_INIT,
			KEY_M2_SEQ_INIT,
			MB_INIT,
			MT_INIT,
			ME_INIT,
			ME_SEQ_INIT = 10,
			MC_INIT = 9,
			MA_INIT = 11,
			INDICATOR_INIT = 13,
			INIT_END = 254,
			DRIVER_SLAVE_TEST = 238,
		};

	}

	void start();

}