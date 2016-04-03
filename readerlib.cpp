//
// Created by Spa on 2/20/2016.
//

// basic file operations
#include <iostream>
#include <fstream>
#include <iconv.h>
#include <vector>
#include <string.h>
#include <chrono>
#include "readerlib.h"

using namespace std;
#define c_time int64_t
#define FILEID_SIZE 256
#define MAX_SYLLABLE_TEXTSIZE 1024
#define NOW() std::chrono::high_resolution_clock::now()
typedef std::chrono::time_point<std::chrono::high_resolution_clock> hires_clock;
#define DIFF(start) std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start).count()


namespace Readerlibrary {
    typedef union _fileid_un {
        struct fileid_crack_st {
            uint16_t ui16MagicKey;
            uint16_t ui16Type;
            uint16_t ui16EntrySize;
            uint16_t _filler;
            uint32_t ui32NumEntry;
            time_t tTimeStamp;
        } crack;
        char szRaw[FILEID_SIZE];
    } FILEID;

    typedef struct DATA_RECORD {
        struct header {
            uint32_t id;
            uint16_t lang:2;
            uint16_t length:10;
            uint16_t tailSpace:1;
            uint16_t isUnused:1;
            uint16_t numeric:1;
            uint16_t _filler:1;
            uint32_t mapFilePos;
        } header;
        c_time timestamp;
        char szText[MAX_SYLLABLE_TEXTSIZE];
    } DATA_RECORD;

    string convert(ifstream *file, DATA_RECORD &record, iconv_t charset) {

        char text[1024];
        char oneChar = '\0';

        for (int i = 0; i < sizeof(text); i++) {
            file->read(&oneChar, 1);
            text[i] = oneChar;
            record.szText[i] = oneChar;

            if (text[i] == 0) {
                break;
            }
        }

        size_t inLeft = 1023;
        size_t outLeft = 1023;
        char *input = &text[0];
        char *output = &record.szText[0];
        iconv(charset, &input, &inLeft, &output, &outLeft);

        return text;
    }

    int Reader::read(char *file) {

        FILEID header;
        DATA_RECORD record;
        ifstream myfile;
        ofstream output;
        iconv_t charset = iconv_open("UTF8", "CP874");
        time_t bit;
        int amount;
        int found = 0;
        int foundyet = 0;
        int notfound = 0;
        hires_clock timer;
        std::vector<DATA_RECORD> records;


        std::string delimiter = "Text: ";
        std::vector<string> keyword;
        string line;
        size_t pos = 0;
        timer = NOW();
        output.open("output.txt");
        ifstream textfile ("text1000.txt");
        if (textfile.is_open())
        {
            while ( getline (textfile,line) )
            {
                line.erase(0, pos = line.find(delimiter)+ delimiter.length());
                    keyword.push_back(line);
                    //cout << keyword[keyword.size()-1] << '\n';
            }
            textfile.close();
        }

        else cout << "Unable to open file";



        myfile.open(file, ios::binary);
        myfile.read(reinterpret_cast<char *>(&header), sizeof(header));
        cout << "FILE POINTER now = " << myfile.tellg() << endl;
        bit = header.crack.tTimeStamp;
        while (true) {

            myfile.read(reinterpret_cast<char *>(&record.header), sizeof(record.header));
            if(myfile.eof())break;
            if (bit == 0)
                myfile.read(reinterpret_cast<char *>(&record.timestamp), sizeof(record.timestamp) - 4);
            else
                myfile.read(reinterpret_cast<char *>(&record.timestamp), sizeof(record.timestamp) + 4);

            convert(&myfile, record, charset);
            records.push_back(record);

            amount++;

            //cout << "ID : " << record.header.id << " TEXT : " << record.szText << endl;
        }


        for(int i = 0; i < keyword.size(); i++) {
            foundyet = 0;
            for (int j = 0; j < records.size(); j++) {
                if (strcmp(keyword[i].c_str(), records[j].szText) == 0) {
                    foundyet = 1;
                }
            }
            if (foundyet == 1){
                cout << "keyword: " << keyword[i].c_str() << " found" << endl;
                output << "keyword: " << keyword[i].c_str() << " found" << endl;
                found++;
            }
            else{
                cout << "keyword: " << keyword[i].c_str() << " not found" << endl;
                output << "keyword: " << keyword[i].c_str() << " not found" << endl;
            }
        }

        cout << found << " words found" << endl;
        //cout << notfound << endl;

        //cout << "LAST WORD   : "<< records[records.size()-1].header.id   << records[records.size()-1].szText << endl;

        cout << "Number of words in this text: " << keyword.size() << endl;
        cout << "running takes " << DIFF(timer)/1000000 << " seconds" << endl;


        return 0;
    }
}