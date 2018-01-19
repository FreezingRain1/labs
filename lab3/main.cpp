#include <iostream>
#include "music.h"
#include "Exception_music.h"

int main() {
    try {
     const char* input_fname="0.wav";
   const char* out_fname="1.wav";
   wav_header header;
    
   Music wav1;
   wav1.read_Header(input_fname, &header);
   wav1.print_Info(&header);
    }
    catch (wavExc &e) {
        cout << e.what();
    }
    system("pause");
}

