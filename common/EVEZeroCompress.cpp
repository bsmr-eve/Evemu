/*  EVEmu: EVE Online Server Emulator

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY except by those people which sell it, which
  are required to give you total support for your newly bought product;
  without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
	
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "EVEZeroCompress.h"

#ifdef ZC_TEST
	#include <stdio.h>
	#define _log(x, str, ...) \
		printf(str "\n", ##__VA_ARGS__)
#else
	#include "logsys.h"
#endif

// ZeroCompress OpCode
struct ZCOpCode {
	// first part
	uint8 f_len : 3;
	bool f_isZero : 1;

	// second part
	uint8 s_len : 3;
	bool s_isZero : 1;
};

void UnpackZeroCompressed(const byte *in_buf, uint32 in_length, std::vector<byte> &buffer) {
	buffer.clear();
	if(in_buf == NULL || in_length == 0)
		return;
	
	_log(NET__ZEROINFL, "Zero-inflating buffer of length %d",
		in_length
	);
	
	ZCOpCode opcode;
	const byte *end = in_buf + in_length;

	while(in_buf < end) {
		opcode = *(ZCOpCode *)(in_buf++);

		if(opcode.f_isZero) {
			byte count = opcode.f_len+1;
			_log(NET__ZEROINFL, "    Opcode 0x%x (first part) yields %d zero bytes at %d", opcode, count, buffer.size());
			for(; count > 0; count--) {
				buffer.push_back(0);
			}
		} else {
			byte count = 8-opcode.f_len;
			_log(NET__ZEROINFL, "    Opcode 0x%x (first part) yields %d data bytes at %d", opcode, count, buffer.size());
			//caution: if we are at the end of the buffer, its possible to be processing a '0' opcode, which should mean "8 bytes", but really means "end"
			for(; count > 0 && in_buf < end; count--) {
				buffer.push_back(*in_buf++);
			}
		}

		if(opcode.s_isZero) {
			byte count = opcode.s_len+1;
			_log(NET__ZEROINFL, "    Opcode 0x%x (second part) yields %d zero bytes at %d", opcode, count, buffer.size());
			for(; count > 0; count--) {
				buffer.push_back(0);
			}
		} else {
			byte count = 8-opcode.s_len;
			_log(NET__ZEROINFL, "    Opcode 0x%x (second part) yields %d data bytes at %d", opcode, count, buffer.size());
			//caution: if we are at the end of the buffer, its possible to be processing a '0' opcode, which should mean "8 bytes", but really means "end"
			for(; count > 0 && in_buf < end; count--) {
				buffer.push_back(*in_buf++);
			}
		}
	}

	_log(NET__ZEROINFL, "  Zero-inflating buffer yields %d inflated bytes (ratio %.02f)",
		buffer.size(), double(in_length) / double(buffer.size())
	);
}

void PackZeroCompressed(const byte *in_buf, uint32 in_length, std::vector<byte> &out_buf) {
	out_buf.clear();
	if(in_buf == NULL || in_length == 0)
		return;

	_log(NET__ZEROCOMP, "Zero-compressing buffer of length %d",
		in_length
	);

	const byte *end = in_buf + in_length;

	while(in_buf < end) {
		// we need to have enough room without moving (otherwise
		// it would invalidate our pointer obtained below); size
		// is 1 byte of opcode + at most 2x 8 bytes
		out_buf.reserve(out_buf.size() + 1 + 16);

		// insert opcode
		out_buf.push_back(0);	// insert opcode placeholder
		ZCOpCode *opcode = (ZCOpCode *)&out_buf.back();	// obtain pointer to it

		// encode first part
		if(*in_buf == 0x00) {
			//we are starting with zero, hunting for non-zero
			opcode->f_isZero = true;
			opcode->f_len = 0;

			in_buf++;
			for(; in_buf < end && *in_buf == 0x00 && opcode->f_len < 7; opcode->f_len++)
				in_buf++;
		} else {
			//we are starting with data, hunting for zero
			opcode->f_isZero = false;
			opcode->f_len = 7;

			out_buf.push_back(*in_buf++);
			for(; in_buf < end && *in_buf != 0x00 && opcode->f_len > 0; opcode->f_len--)
				out_buf.push_back(*in_buf++);
		}

		if(in_buf >= end)
			break;

		// encode second part
		if(*in_buf == 0x00) {
			//we are starting with zero, hunting for non-zero
			opcode->s_isZero = true;
			opcode->s_len = 0;

			in_buf++;
			for(; in_buf < end && *in_buf == 0x00 && opcode->s_len < 7; opcode->s_len++)
				in_buf++;
		} else {
			//we are starting with data, hunting for zero
			opcode->s_isZero = false;
			opcode->s_len = 7;

			out_buf.push_back(*in_buf++);
			for(; in_buf < end && *in_buf != 0x00 && opcode->s_len > 0; opcode->s_len--)
				out_buf.push_back(*in_buf++);
		}
	}

	_log(NET__ZEROCOMP,
		"  Zero-compressing buffer resulted in %d bytes (ratio %.02f)",
		out_buf.size(), double(out_buf.size()) / double(in_length)
	);
}

















