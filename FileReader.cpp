// Compile this library:
// 		g++ -c FileReader.cpp -o FileReader.o
// Use this library:
//		#include "FileReader.h"

#include "FileReader.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

#define RECORD_TYPE_64 0
#define RECORD_TYPE_32 1

typedef struct DATA_RECORD {
	struct header{
		uint32_t id;
		uint16_t lang:2;
		uint16_t length:10;
		uint16_t tailSpace:1;
		uint16_t isUnused:1;
		uint16_t numeric:1;
		uint16_t _filler:1;
		uint32_t mapFilePos;
	} header;
	int64_t timestamp;
	char data[1024];
} DATA_RECORD;

FILE* file;
FILE* toWrite;
DATA_RECORD* record;
int recordsCount;
int recordType; // For check type
iconv_t charset; // For encoding data

void checkRecordType() {
	fseek(file, 12, SEEK_SET);
	if(fgetc(file) != 0) {
		recordType = RECORD_TYPE_32;
	}
}
void initReader() {
	record = (DATA_RECORD*) malloc(sizeof(DATA_RECORD));
	recordsCount = 0;
	recordType = RECORD_TYPE_64;
	charset = iconv_open("UTF8", "CP874");
	checkRecordType();
	fseek(file, 256-13, SEEK_CUR); // Skip header
}

void readRecordTimeStamp() {
	if(recordType == RECORD_TYPE_64) {
		fread(&record->timestamp, sizeof(int64_t), 1, file);
		fseek(file, 4, SEEK_CUR);
	}
	else if(recordType == RECORD_TYPE_32) {
		fread(&record->timestamp, sizeof(int32_t), 1, file);
	}
}

void readRecordData() {
	char temp[1023];
	for(int i = 0; i < sizeof(temp); i++) {
		temp[i] = fgetc(file);
		if(temp[i] == 0) {
			break;
		}
	}
	size_t inputSize = 1023;
	size_t outputSize = 1023;
	char *input = &temp[0];
	char *output = &record->data[0];
	iconv(charset, &input, &inputSize, &output, &outputSize);
	record->data[1023] = 0;
}

char* getToWriteName(char* str, char* buffer) {
	char* p;
	char orig[] = ".dat";
	char rep[] = ".txt";
	if(!(p = strstr(str, orig))) {
		return str;
	}
	strncpy(buffer, str, p-str);
	buffer[p-str] = '\0';
	sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));
	return buffer;
}

void FileReader::openFile(char* path) {
	file = fopen(path, "rb");
	char buffer[4096];
	toWrite = fopen(getToWriteName(path, buffer), "w");
	initReader();
}
void FileReader::closeFile() {
	fprintf(toWrite, " ");
	fclose(file);
	fclose(toWrite);
	printf("Read %d records\n", recordsCount);
}
bool FileReader::readRecord() {
	if(!fread(&record->header, sizeof(record->header), 1, file)) {
		return false;
	}
	readRecordTimeStamp();
	readRecordData();
	fprintf(toWrite, "ID: %u, Text: %s\n", record->header.id, record->data );
	recordsCount++;
	return true;
}
int FileReader::readAllRecords() {
	int count = 0;
	while(readRecord()) {
		 count++;
	}
	return count;
}
int FileReader::getNumberOfReadRecord() {
	return recordsCount;
}
int FileReader::getRecordType() {
	return recordType;
}