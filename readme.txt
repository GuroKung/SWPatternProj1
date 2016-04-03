Author: Natchanon Charoensuk 5610546257

Description: Library of decoding .dat and reading datas in .txt to terminal
1) Decoding .dat by using FileReader library
2) Reading datas in .txt by RecordReader library
3) Records automatically print after read by RecordReader library
4) Can get the number of read records by using RecordReader library
5) Can search input from SyllableDB

Complies:
	g++ -c FileReader.cpp -o FileReader.o
	g++ -c farmhash.cc -o farmhash.o
	g++ -c RecordReader.cpp -o RecordReader.o farmhash.o
	g++ -o FileReaderApp FileReaderApp.cpp FileReader.o -liconv
	g++ -o SearchApp SearchApp.cpp RecordReader.o farmhash.o
Run:
	./FileReaderApp SyllableDB-V1.dat
	./SearchApp SyllableDB-V1.txt TextInput1000Words.txt

How to complies library?
	For FileReader:
		g++ -c FileReader.cpp -o FileReader.o
	For RecordReader:
		g++ -c RecordReader.cpp -o RecordReader.o

How to test the library?
1) Make sure to complies both of including library (FileReader and RecordReader)
2) Complies the test application (file_reader.cpp and record_reader.cpp) respectively
	g++ -o FileReaderApp FileReaderApp.cpp FileReader.o -liconv
	g++ -o SearchApp SearchApp.cpp RecordReader.o
3) Run the test application, start with FileReaderApp.cpp first
	./FileReaderApp filename.dat
	ex.
		./FileReaderApp SyllableDB-V1.dat
4) After 3) ‘filename.txt’ will be created, then run SearchApp.cpp
	./SearchApp syllableName.txt textInputName.txt
	ex.
		./SearchApp SyllableDB-V1.txt TextInput1000Words.txt
5) The result will be shown in the terminal
6) After 5) it will create ‘result.txt’ for the running time of searching
* You can read the API of each library in .h files


Sources including:
	Library:
		FileReader (FileReader.cpp, FileReader.h)
		RecordReader (RecordReader.cpp, RecordReader.h)
	Test Application:
		file_reader.cpp
		record_reader.cpp
	.dat files:
		SyllableDB-V1.dat
		SyllableDB-V2.dat
		SyllableDB-V3.dat
	TextInput file:
		TextInput1000Words.txt