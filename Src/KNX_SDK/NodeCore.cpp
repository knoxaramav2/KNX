#define WINVER 0x500
#include <Windows.h>

#include "NodeCore.h"

void nodeBase::interrupt()
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = INTERRUPT;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = 13;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
}