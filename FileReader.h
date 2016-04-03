// FileReader.h

class FileReader {
	public:
		static void openFile(char* path);
		static void closeFile();
		// Read record and return true if can read the record, otherwise return false
		static bool readRecord();
		// Read all records left and return the number of records read
		static int readAllRecords();
		// Return the number of all records read
		static int getNumberOfReadRecord();
		// Return 0 if timestamp is 64 bits, 1 if timestamp is 32bits
		static int getRecordType();
};