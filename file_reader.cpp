// Compile this file:
// 		g++ -o file_reader file_reader.cpp FileReader.o -liconv
// Run this file:
//		./file_reader SyllableDB-V1.dat

#include "FileReader.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc < 2){
		printf("Usage: %s filename.dat\n",argv[0]);
		return 0;
	}
	FileReader::openFile(argv[1]);
	FileReader::readAllRecords();
	FileReader::closeFile();

	return 0;
}