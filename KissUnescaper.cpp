#include <iostream>
#include "KissUnescaper.h"

using namespace std;

KissUnescaper::~KissUnescaper()
{
    for (int i = 0; i < _buf_vec.size(); i++)
    {
        delete[] _buf_vec[i];
    }
}

pair<unsigned char *, unsigned> KissUnescaper::unescape(FILE *fp)
{
    unsigned size = getFileSize(fp);

    unsigned char *buf = allocate(size);

    fread(buf, sizeof(unsigned char), size, fp);

    return _unescape(buf, size);
}

pair<unsigned char *, unsigned> KissUnescaper::unescape(unsigned char *packet, unsigned size)
{
    return _unescape(packet, size);
}

unsigned KissUnescaper::getFileSize(FILE *fp)
{
    fseek(fp, 0, SEEK_END);

    unsigned size = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    return size;
}

unsigned char *KissUnescaper::allocate(unsigned size)
{
    unsigned char *buf = NULL;

    try
    {
        buf = new unsigned char[sizeof(unsigned char) * size];
    }
    catch (bad_alloc &e)
    {
        cerr << "Error: Failed to allocate memory" << endl;
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    return buf;
}

pair<unsigned char *, unsigned> KissUnescaper::_unescape(unsigned char *raw_buf, unsigned size)
{
    //! pointer to unescaped data
    unsigned char *buf = allocate(size);

    //! size of unescaped data [byte]
    unsigned buf_size = 0;

    _buf_vec.push_back(buf);

    for (unsigned i = 0; i < size; i++)
    {
        if (raw_buf[i] == 0xC0) // skip "C0"
        {
            continue;
        }
        else if (raw_buf[i] == 0xDB && raw_buf[i + 1] == 0xDC) // "DB DC" -> "C0"
        {
            buf[buf_size++] = 0xC0;
            i++;
        }
        else if (raw_buf[i] == 0xDB && raw_buf[i + 1] == 0xDD) // "DB DD" -> "DB"
        {
            buf[buf_size++] = 0xDB;
            i++;
        }
        else
        {
            buf[buf_size++] = raw_buf[i];
        }
    }

    delete[] raw_buf;

    return {buf, buf_size};
}
