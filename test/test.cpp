#include "../KissUnescaper.h"
#include <string>

using namespace std;

FILE *openFile(string path, string mode)
{
    FILE *fp;

    if ((fp = fopen(path.c_str(), mode.c_str())) == NULL)
    {
        cerr << "Error: Failed to open the input file" << endl;
        exit(EXIT_FAILURE);
    }

    return fp;
}

int main()
{
    KissUnescaper unescaper;

    /**
     * Unescape a binary file
     */
    FILE *fp = openFile("test.log", "rb"); // raw file (mode must be "rb")

    unsigned char *data = NULL;
    unsigned data_size;

    data_size = unescaper.unescape(&data, fp);

    // print unescaped data
    for (int i = 0; i < data_size; i++)
    {
        cout << uppercase << hex << int(data[i]) << " ";
    }
    cout << endl
         << endl;

    /**
     * Unescape an array of some packets
     */
    unsigned char packets[] = {0xC0, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xC0}; // raw packets

    unsigned char *data2 = NULL;
    unsigned data_size2;

    data_size2 = unescaper.unescape(&data2, packets, sizeof(packets));

    // print unescaped data
    for (int i = 0; i < data_size2; i++)
    {
        cout << uppercase << hex << int(data2[i]) << " ";
    }
    cout << endl;

    return 0;
}