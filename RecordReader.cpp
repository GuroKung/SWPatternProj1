// Compile this library:
// 		g++ -c RecordReader.cpp -o RecordReader.o
// Use this library:
//		#include "RecordReader.h"

#include "RecordReader.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

FILE* file;
RECORD* record;
int recordsCount;
std::vector<RECORD*> records;
/////////////////// MAP //////////////////
std::unordered_map<std::string, std::string> mymap;

void initReader() {
	recordsCount = 0;
	records.clear();
}

void RecordReader::openFile(char* path) {
	file = fopen(path, "r");
	initReader();
}
void RecordReader::closeFile() {
	fclose(file);
	printf("Read %d records\n", recordsCount);
}
bool RecordReader::readRecord() {
	if(feof(file)) {
		return false;
	}
	// "ID: "
	char firstChar = fgetc(file);
	if(firstChar == ' ' || firstChar == 0) {
		return false;
	}
	for(int i = 0; i<3;i++) {
		fgetc(file);
	}
	record = (RECORD*) malloc(sizeof(RECORD));
	// Read id
	for(int i = 0; i < sizeof(record->id); i++) {
		record->id[i] = fgetc(file);
		if(record->id[i] == ',') {
			record->id[i] = 0;
			break;
		}
	}
	// " Text: "
	for(int i = 0; i<7;i++) {
		fgetc(file);
	}
	// Read data
	for(int i = 0; i < sizeof(record->data); i++) {
		record->data[i] = fgetc(file);
		if(record->data[i] == '\n') {
			record->data[i] = 0;
			break;
		}
	}
	record->data[1023] = 0;
	////////////////////////// MAP /////////////////
	mymap[record->data] = record->id; 
	////////////////////////////////////////////////
	printf("ID: %s, Text: %s\n", record->id, record->data);
	printf("=========================\n");
	recordsCount++;
	records.push_back(record);
	return true;
}
int RecordReader::readAllRecords() {
	int count = 0;
	while(readRecord()) {
		count++;
	}
	return count;
}
int RecordReader::getNumberOfReadRecord() {
	return recordsCount;
}
std::vector<RECORD*> RecordReader::getReadRecords() {
	return records;
}

std::unordered_map<std::string, std::string> RecordReader::getMap(){
	return mymap;
}
