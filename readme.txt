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

Sources including:
	Library:
		FileReader (FileReader.cpp, FileReader.h)
		RecordReader (RecordReader.cpp, RecordReader.h)
	Application:
		FileReaderApp.cpp
		SearchApp.cpp
	.dat files:
		SyllableDB-V1.dat
		SyllableDB-V2.dat
		SyllableDB-V3.dat
	TextInput file:
		TextInput1000Words.txt
