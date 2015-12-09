#include "NodeCore.h"

#define WINVER 0x500
#include <Windows.h>

systemState sysState;

systemState::systemState()
{
	//base loop has default access to user inputs
	I_hndle = GLOBAL_INPUT;
	def_hndle = GLOBAL_INPUT;

	//set default option flags
	prntErrors = false;
	prntWarnings = false;
}

bool systemState::requestInput(nodeBase*nb)
{
	if (nb == nullptr)
		return false;
	if (I_hndle != nullptr)
		return false;
	I_hndle = nb;
	return true;
}

bool systemState::releaseInput(nodeBase*nb)
{
	if (I_hndle == nb)//including null for forced operations
		I_hndle = def_hndle;
	else
		return false;
	return true;
}

bool systemState::assignDefault(nodeBase*nb)
{
	if (nb == nullptr)
		return false;
	def_hndle = nb;
	return true;
}


void nodeBase::interrupt()
{
	if (sysState.I_hndle != this)
		return;

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