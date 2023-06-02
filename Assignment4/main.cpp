#include <iostream>
#include "ReadAndProcess.h"

int main(int argc, char *argv[]) {
    Primary *primary = NULL;
    primary=ReadAndProcess::Action(argv[1],primary,argv[2],argv[3]);
}
