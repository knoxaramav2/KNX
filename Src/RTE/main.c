#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <poll.h>

#include "KNX_String.h"
#include "KNX_Console.h"
#define PI 3.14159265

int main(){

    //startConsoleControl();

    //terminal * term = createTerminal();

    echo_off();

    char c;

    do{
        c = getKeyPress();
    } while(c != '5');

    //destroyTerminal(term);
    //endConsoleControl();
    echo_on();

    return 0;
}