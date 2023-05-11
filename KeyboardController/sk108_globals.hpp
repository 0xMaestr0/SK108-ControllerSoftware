#pragma once

#include <cstdint>

namespace Board::SK108::Globals {

	static const uint8_t _report_id = 4;
	static const uint16_t _vid = 0x31D6;
	static const uint16_t _pid = 0x78;
	static const char *_component = "MI_02";
	static constexpr int _buf_sz = 21; // this is both for input and output

}