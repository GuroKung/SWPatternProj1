// Compile this file:
// 		g++ -o SearchApp SearchApp.cpp RecordReader.o -liconv
// Run this file:
//		./SearchApp SyllableDB-V1.txt TextInput1000Words.txt

#include "RecordReader.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <unordered_map>
#include <string>

int main(int argc, char *argv[]) {
	if(argc < 3){
		printf("Usage: %s syllableName.txt textInputName.txt\n",argv[0]);
		return 0;
	}
	// Read SyllableDB
	RecordReader::openFile(argv[1]);
	RecordReader::readAllRecords();
	std::unordered_map<std::string, std::string> SyllableDB = RecordReader::getMap();
	int totalRecords = RecordReader::getNumberOfReadRecord();
	RecordReader::closeFile();
	// Read 1000 Inputs
	RecordReader::openFile(argv[2]);
	RecordReader::readAllRecords();
	std::vector<RECORD*> inputs = RecordReader::getReadRecords();
	int numInput = RecordReader::getNumberOfReadRecord();
	RecordReader::closeFile();

	FILE* toWrite = fopen("result.txt", "w");
	fprintf(toWrite, "Search inputs from %s\nBy using datas from %s\n\n", argv[2], argv[1]);
	clock_t start_time = clock();
	for(int i=0; i<numInput;i++) {
		RECORD* input = inputs.at(i);
		fprintf(toWrite, "Input ID: %s, Text: %s\nResult: ", input->id, input->data);
		clock_t begin_time = clock();
		if( SyllableDB[input->data].length() > 0 ) {
			fprintf(toWrite, "Found at SyllableDB ID %s", SyllableDB[input->data].c_str());
		}
		else {
			fprintf(toWrite, "Not Found");
		}

		float duration = float( clock () - begin_time );
		fprintf(toWrite, ", Searched Time: %.0fns\n==========\n", duration);
	}
	float totalTime = float( clock () - start_time );
	fprintf(toWrite, "\nSearched %d inputs, Total Searched Time: %.0fns", numInput, totalTime);
	printf("Total Searched Time: %.0fns\n", totalTime);
	return 0;
}