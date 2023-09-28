#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define u8 uint8_t
#define u32 uint32_t
#define i32 int32_t
#define usize size_t

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
void verify(bool cond, char* msg) {
    if (cond == false) {
        fprintf(stderr, "%s\n", msg);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    verify(argc == 2, "Usage: imgcat <filename>");
    HANDLE hwnd = GetConsoleWindow();
    HDC ctxt = GetDC(hwnd);
    i32 width, height, number_of_bits;
    i32 desired_channels = 4;
    u8* data = stbi_load(argv[1], &width, &height, &number_of_bits, desired_channels);
    verify(data, "Failed to load image");
    int i =0;
    int j = 0;
    for(int y = 0; y < height; y++, i++) {
		for(int x = 0; x < width*desired_channels; x+=desired_channels, j++) {
            COLORREF pixel = RGB(data[x+y*width*4], data[x+y*width*4+1], data[x+y*width*4+2]);
            SetPixel(ctxt, j, i, pixel);
		}
        j = 0;
	}
    getchar();
    return 0;
}