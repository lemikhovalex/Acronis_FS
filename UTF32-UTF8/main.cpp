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

    cout << "utf32_vector---init letter \nnew_utf32_vector" << endl;
    for (int i = 0; i < utf32_vector.size(); ++i)
    {
        cout << bitset<32>(utf32_vector[i]) << "---"<< init_string[i]<< "\n" << bitset<32>(new_utf32_vector[i]) << endl;
        printf("\n");
    }

    if (utf32_vector != new_utf32_vector)
    {
        cout << "INIT_UTF32_!=_OUT_UTF32 !+" << endl;
        return -1;
    }
    else
    {
        cout << endl << "FINE!" << endl;
    }


    cout << "utf8_vector---init letter \nutf32_vector" << endl;
    int l = 0;
    int f = 0;
    for (int i = 0; i < utf8_vector.size(); ++i)
    {
        if ((utf8_vector[i] & 128u) && (utf8_vector[i] & 64u))
        {
            f = 1;
            cout << bitset<8>(utf8_vector[i]);
        }
        else if ((utf8_vector[i] & 128u) && !(utf8_vector[i] & 64u))
        {
            cout << " " << bitset<8>(utf8_vector[i]);
        }
        else if (!(utf8_vector[i] & 128u))
        {
            if (f ==1)
            {
                cout << "---" << init_string[l] << endl << utf32_vector[l-1] << endl;
            }
            cout << bitset<8>(utf8_vector[i]) << "---" << init_string[l] << endl << bitset<32>(utf32_vector[l]) << endl;
            l ++;
        }
    }
    return 0;
}
