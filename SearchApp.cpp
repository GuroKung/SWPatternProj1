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

int main(int argc, char *argv[]) {
	if(argc < 3){
		printf("Usage: %s syllableName.txt textInputName.txt\n",argv[0]);
		return 0;
	}
	// Read SyllableDB
	RecordReader::openFile(argv[1]);
	RecordReader::readAllRecords();
	std::vector<RECORD*> SyllableDB = RecordReader::getReadRecords();
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
		int isFound = 0;
		clock_t begin_time = clock();
		for(int j=0; j<totalRecords;j++) {
			RECORD* record = SyllableDB.at(j);
			if(strcmp(input->data, record->data) == 0) {
				fprintf(toWrite, "Found at SyllableDB ID %s", record->id);
				isFound = 1;
				break;
			}
		}
		float duration = float( clock () - begin_time );
		if(isFound == 0) {
			fprintf(toWrite, "Not Found");
		}
		fprintf(toWrite, ", Searched Time: %.0fms\n==========\n", duration);
	}
	float totalTime = float( clock () - start_time );
	fprintf(toWrite, "\nSearched %d inputs, Total Searched Time: %.0fns", numInput, totalTime);
	printf("Total Searched Time: %.0fns\n", totalTime);
	return 0;
}