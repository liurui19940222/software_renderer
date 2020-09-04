#include "input.h"

unsigned char key[256];
unsigned char keydown[256];
unsigned char keyup[256];

void input_init() {
	memset(key, 0, sizeof(key));
	memset(keydown, 0, sizeof(keydown));
	memset(keyup, 0, sizeof(keyup));
}

void input_setKeyDown(unsigned char keyCode) {
	key[keyCode] = 1;
	keydown[keyCode] = 1;
}

void input_setKeyUp(unsigned char keyCode) {
	key[keyCode] = 0;
	keydown[keyCode] = 0;
}

BOOL input_isKeyPressed(unsigned char keyCode) {
	return key[keyCode];
}

void input_endRecord() {
	memset(keydown, 0, sizeof(keydown));
	memset(keyup, 0, sizeof(keyup));
}

BOOL input_getKeyDown(unsigned char keyCode) {
	return keydown[keyCode];
}

BOOL input_getKeyUp(unsigned char keyCode) {
	return keyup[keyCode];
}