Member:
	Jiratchaya Intaragumhaeng 5610546702
	Chonnipa Kittisiriprasert 5610546222
	Natchanon Charoensuk 5610546257
	Nichamon Han-Idhikul 5610545684
	Piyapat Tulakoop 5610545731
	Vasupol Chatmethakul 5610546788

FileReader:
	g++ -c FileReader.cpp -o FileReader.o
	./FileReaderApp SyllableDB-V1.dat

SearchEngine:
	g++ -c farmhash.cc -o farmhash.o
	g++ -c RecordReader.cpp -o RecordReader.o farmhash.o
	g++ -o FileReaderApp FileReaderApp.cpp FileReader.o -liconv
	g++ -o SearchApp SearchApp.cpp RecordReader.o farmhash.o
	./SearchApp SyllableDB-V1.txt TextInput1000Words.txt

Results:
	After running SearchApp with
		./SearchApp SyllableDB-V1.txt TextInput1000Words.txt
	the result will be written into result.txt and will not show in the console.
	The console shows only other information and time.

Sources including:
	Library:
		FileReader (FileReader.cpp, FileReader.h)
		   description: reads data from .dat into .txt
		RecordReader (RecordReader.cpp, RecordReader.h)
		   description: reads data from .txt into vector and map for building a list out of the data
	Application:
		FileReaderApp.cpp
		SearchApp.cpp
		   description: search by using inputFile from SyllableDB
	.dat files:
		SyllableDB-V1.dat
		SyllableDB-V2.dat
		SyllableDB-V3.dat
	TextInput file:
		TextInput1000Words.txt
