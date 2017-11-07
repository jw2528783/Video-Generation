#include <iostream>
#include <cstdint>
#include "Rectangle.cpp"
#include <fstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cstring>

#define W 720
#define H 480	
unsigned char frame[H][W][3];

class Screen{
	public:
		void clear(){memset(frame, 0, sizeof(frame));}
		void drawframe(double t,Rectangle r1,Rectangle r2,Rectangle r3);
		void drawrect(Rectangle r1,Rectangle r2,Rectangle r3);
		bool outside(int *x,int *y);
		void clamp(int x,int y);
		friend class Rectangle;
};

void Screen::drawrect(Rectangle r1,Rectangle r2,Rectangle r3){
	if (outside(&r1.x,&r1.y)) return;
	int r1x0=r1.x;
	int r1x1=r1.x+4*r1.w;
	int r1y0=r1.y;
	int r1y1=r1.y+4*r1.h;
	clamp(r1x0,r1y0);
	clamp(r1x1,r1y1);
	for(int y=r1y0;y<r1y1;++y){
		for(int x=r1x0;x<r1x1;++x){
			frame[y][5*x][0]=r1.r;
			frame[y][x][1]=r1.g;
			frame[y][x][2]=r1.b;
		}
	}
	if (outside(&r2.x,&r2.y)) return;
	int r2x0=r2.x;
	int r2x1=r2.x+r2.w;
	int r2y0=r2.y;
	int r2y1=r2.y+4*r2.h;
	clamp(r2x0,r2y0);
	clamp(r2x1,r2y1);
	for(int y=r2y0;y<r2y1;++y){
		for(int x=r2x0;x<r2x1;++x){
			frame[y][5*x][0]=r2.r;
			frame[y][x][1]=r2.g;
			frame[y][x][2]=r2.b;
		}
	}
	if (outside(&r3.x,&r3.y)) return;
	int r3x0=r3.x;
	int r3x1=r3.x+3*r2.w;
	int r3y0=r3.y;
	int r3y1=r3.y+3*r2.h;
	clamp(r3x0,r3y0);
	clamp(r3x1,r3y1);
	for(int y=r3y0;y<r3y1;++y){
		for(int x=r3x0;x<r3x1;++x){
			frame[y][x][0]=r3.r;
			frame[y][x][1]=r3.g;
			frame[y][x][2]=r3.b;
		}
	}
};

bool Screen::outside(int *x,int *y){
	return *x<0 or *x>=W or *y<0 or *y>= H;
};

void Screen::clamp(int x,int y) {
	if(x<0)x=0; else if (x>=W)x=W-1;
	if(y<0)y=0; else if (y>=H)y=H-1;
};

void Screen::drawframe(double t,Rectangle r1,Rectangle r2,Rectangle r3){
	clear();
	const double pps = 80;
	Rectangle newR1=r1;
	newR1.x=r1.x+t *pps;
	newR1.y=r1.y+t *pps;
	Rectangle newR2=r2;
	newR2.x=r2.x+t *pps;
	newR2.y=r2.y+t *pps;
	Rectangle newR3=r3;
	newR3.x=r3.x+t *pps;
	newR3.y=r3.y+t *pps;
	drawrect(newR1,newR2,newR3);
};
