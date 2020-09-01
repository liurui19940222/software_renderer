#include "input.h"

unsigned char key[256];

void input_init() {
	memset(key, 0, sizeof(key));
}

void input_setKeyDown(unsigned char keyCode) {
	key[keyCode] = 1;
}

void input_setKeyUp(unsigned char keyCode) {
	key[keyCode] = 0;
}

BOOL input_isKeyPressed(unsigned char keyCode) {
	return key[keyCode];
}