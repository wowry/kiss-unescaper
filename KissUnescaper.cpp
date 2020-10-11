#include <iostream>
#include <tuple>
#include "KissUnescaper.h"

using namespace std;

KissUnescaper::~KissUnescaper()
{
    for (int i = 0; i < _buf_vec.size(); i++)
    {
        delete[] _buf_vec[i];
    }
}

unsigned KissUnescaper::unescape(unsigned char **buf, FILE *fp)
{
    const unsigned size = getFileSize(fp);

    unsigned char *raw_buf = allocate(size);

    fread(raw_buf, sizeof(unsigned char), size, fp);
    
    unsigned buf_size;

    tie(*buf, buf_size) = _unescape(raw_buf, size);

    delete[] raw_buf;

    return buf_size;
}

unsigned KissUnescaper::unescape(unsigned char **buf, unsigned char *packets, unsigned size)
{
    unsigned buf_size;

    tie(*buf, buf_size) = _unescape(packets, size);

    return buf_size;
}

unsigned KissUnescaper::getFileSize(FILE *fp)
{
    fseek(fp, 0, SEEK_END);

    const unsigned size = ftell(fp);

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
        if (raw_buf[i] == 0xC0) // delete "C0"
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

    return {buf, buf_size};
}
