#pragma once
#include <cstdint>
typedef unsigned char byte;

class Rectangle {
	public:
		Rectangle(int height,int width,int x,int y,byte red,byte 			green,byte blue){
			h = height;
			w = width;
			this->x = x;
			this->y = y;
			r = red;
			g = green;
			b = blue;
		};
		byte r,g,b;
		int h,w;
		int x,y;
};
