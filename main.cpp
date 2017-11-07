#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include <cstdint>
#include "Rectangle.cpp"
#include "screen.cpp"

const double fps=30; 
const int duration=3;
using namespace std;

int main(int argc, char * argv[]) {
	Screen s;	
	Rectangle r1(20,25,51,152,0xff,0x00,0x00);
	Rectangle r2(10,12,25,75,0xff,0x00,0x00);
	Rectangle r3(10,12,0,0,0x00,0xff,0x00);
	// Construct the ffmpeg command to run.
	const char *cmd = 
		"ffmpeg              "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

	// Run the ffmpeg command and get pipe to write into its standard input stream.
	FILE *pipe=popen(cmd,"w");
	if (pipe == 0) {
		cout<<"error: "<<strerror(errno)<<endl;
		return 1;
	}
	// Write video frames into the pipe.
	int numframes=duration*fps;
	for(int i=0;i<numframes;++i){
		double time=i/fps;
		s.drawframe(time,r1,r2,r3);
		fwrite(frame,3,W*H,pipe);
	}
	fflush(pipe);
	pclose(pipe);
	cout<<"\n\n\nnum_frames: "<<numframes<<endl;
	cout<<"Done.\n"<<endl;
	return 0;
}
