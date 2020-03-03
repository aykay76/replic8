#pragma once

namespace r8 {

class Colour
{
public:
	union ColourValue {
		unsigned long c;
		struct rgba {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};
	};

	ColourValue m_col;
};

}