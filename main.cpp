//
// Created by Spa on 2/20/2016.
//
#include <iostream>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <iconv.h>
#include "readerlib.h"

using namespace std;

int main(int argc, char *argv[])
    {
        Readerlibrary::Reader read;
        read.read(argv[1]);
        return 0;
    }
