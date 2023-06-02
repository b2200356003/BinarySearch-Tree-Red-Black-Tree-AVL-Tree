//
// Created by dayte on 22.12.2022.
//

#ifndef ASSIGNMENT4_READANDPROCESS_H
#define ASSIGNMENT4_READANDPROCESS_H
using namespace std;
#include <string>
#include "Primary.h"

class ReadAndProcess {
public:
    static Primary *Action(string filename,Primary *primary,string outputFile,string outputFile2);
};


#endif //ASSIGNMENT4_READANDPROCESS_H
