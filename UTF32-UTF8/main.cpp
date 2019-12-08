#include <bitset>
#include <iconv.h>
#include <iostream>
#include "converter.hpp"
#include <stdexcept>

#define ERROR_MSG "conversion FAILED"
#define ERROR -1

using namespace std;

std::u32string init_string = U"`rщ";


int main(int argc, char const *argv[])
{
    std::vector<uint32_t> utf32_vector;
    for (int i =0; i <init_string.length(); i++)
    {
        utf32_vector.push_back(static_cast<uint32_t>(init_string[i]));
    }

    // converting to utf8
    std::vector<uint8_t> utf8_vector;
    utf8_vector = to_utf8(utf32_vector);
    // go back
    std::vector<uint32_t> new_utf32_vector;
    new_utf32_vector = from_utf8(utf8_vector);


    for (int i = 0; i < utf32_vector.size(); ++i)
    {
        cout << "Here is UTF32 letter we got:" << endl;
        cout << bitset<32>(utf32_vector[i]) << endl;
        cout << "And here is the same but shorter:" << endl << init_string[i] << endl;
        cout << "UTF32->UTF8->UTF32 is here:"<< endl << bitset<32>(new_utf32_vector[i]) << endl;
        printf("\n");
    }

    if (utf32_vector != new_utf32_vector)
    {
        cout << "INIT_UTF32_!=_OUT_UTF32 !" << endl;
        return -1;
    }
    else
    {
        cout << endl << "UTF32 there and back works FINE!\n\n\n";
    }

    int utf8_pos = 0;
    int utf8_len = 0;
    for(int i =0; i <init_string.length(); i++)
    {
        cout << "Here is UTF32 letter we got:" << endl;
        cout << bitset<32>(utf32_vector[i]) << endl;
        cout << "And here is the same but shorter:" << endl << init_string[i] << endl;
        // here starts printing utf8
        cout << "UTF32->UTF8 is here:"<< endl;
        //finding out amount of bytes in this letter
        for(utf8_len = 1; (int)(utf8_vector[utf8_pos] >> (8-utf8_len)) == 1; utf8_len++)
        {
        }
        for(int i = 0; i < utf8_len; i++)
        {
            cout << bitset<8>(utf8_vector[utf8_pos + i]) << " ";
        }
        utf8_pos += utf8_len;
        printf("\n");
    }
    return 0;
}