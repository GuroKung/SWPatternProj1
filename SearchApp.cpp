// Compile this file:
// 		g++ -o SearchApp SearchApp.cpp RecordReader.o -liconv
// Run this file:
//		./SearchApp SyllableDB-V1.txt TextInput1000Words.txt

#include "RecordReader.h"
#include <time.h>
#include <vector>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[]) {
	if(argc < 3){
		printf("Usage: %s syllableName.txt textInputName.txt\n",argv[0]);
		return 0;
	}
	// Read SyllableDB
	RecordReader::openFile(argv[1]);
	RecordReader::readAllRecords();
	unordered_map<string, string> SyllableDB = RecordReader::getMap();
	int totalRecords = RecordReader::getNumberOfReadRecord();
	RecordReader::closeFile();
	
	// Read 1000 Inputs
	RecordReader::openFile(argv[2]);
	RecordReader::readAllRecords();
	vector<RECORD*> inputs = RecordReader::getReadRecords();
	int numInput = RecordReader::getNumberOfReadRecord();
	RecordReader::closeFile();

	FILE* output = fopen("result.txt", "w");
	fprintf(output, "Search inputs from %s\nBy using datas from %s\n\n", argv[2], argv[1]);
	clock_t start_time = clock();
	int notFound = 0;
	for(int i=0; i<numInput; i++) {
		RECORD* input = inputs.at(i);
		fprintf(output, "Input ID: %s, Text: %s\nResult: ", input->id, input->data);
		clock_t begin_time = clock();
		string value = SyllableDB[input->data];
		if( value.length() > 0 ) {
			fprintf(output, "Found at SyllableDB ID %s", value.c_str());
		}
		else {
			fprintf(output, "Not Found");
			notFound++;
		}

		float duration = float( clock () - begin_time );
		fprintf(output, ", Searched Time: %.2fus\n==========\n", duration);
	}
	float totalTime = float( clock () - start_time );
	fprintf(output, "\nSearched %d inputs, Not Found: %d\nTotal Searched Time: %.2fus", numInput, notFound, totalTime);
	printf("Searched %d inputs, Not Found: %d\nTotal Searched Time: %.2fus\n", numInput, notFound, totalTime);
	return 0;
}