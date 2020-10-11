#ifndef KISS_UNESCAPER_H
#define KISS_UNESCAPER_H

#include <iostream>
#include <vector>

class KissUnescaper
{
public:
    /**
     * destructor
     * Delete all pointers to unescaped data
     */
    ~KissUnescaper();

    /**
     * Unescape a binary file
     * @param  buf  address of pointer to unescaped data (unescaped data is written here)
     * @param  fp  a binary file to be unescaped
     * @return size of unescaped data [byte]
     */
    unsigned unescape(unsigned char **buf, FILE *fp);

    /**
     * Unescape an array of some packets
     * @param  buf  address of pointer to unescaped data (unescaped data is written here)
     * @param  packets  an array to be unescaped
     * @param  size  size of the packets [byte]
     * @return size of unescaped data [byte]
     */
    unsigned unescape(unsigned char **buf, unsigned char *packets, unsigned size);

private:
    /**
     * Get size of a input file
     * @param  fp  a file to be unescaped
     * @return size of the file [byte]
     */
    unsigned getFileSize(FILE *fp);

    /**
     * Allocate memory for an unsigned char buffer
     * @param  size  size of a buffer to be allocated [byte]
     * @return pointer to the buffer
     */
    unsigned char *allocate(unsigned size);

    /**
     * Unescape data
     *  - C0    -> (delete)
     *  - DB DC -> C0
     *  - DB DD -> DB
     * @param  raw_buf  data to be unescaped
     * @param  size  size of raw_buf [byte]
     * @return pointer to unescaped data & size of unescaped data [byte]
     */
    std::pair<unsigned char *, unsigned> _unescape(unsigned char *raw_buf, unsigned size);

    //! pointers to unescaped data
    std::vector<unsigned char *> _buf_vec;
};

#endif // KISS_UNESCAPER_H