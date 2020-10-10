#ifndef KISS_UNESCAPER_H
#define KISS_UNESCAPER_H

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
     * Unescape a file
     * @param  fp  a file to be unescaped
     * @return pointer to unescaped data & size of unescaped data [byte]
     */
    std::pair<unsigned char *, unsigned> unescape(FILE *fp);

    /**
     * Unescape some packets
     * @param  packet  packet data to be unescaped
     * @param  size  size of packet data [byte]
     * @return pointer to unescaped data & size of unescaped data [byte]
     */
    std::pair<unsigned char *, unsigned> unescape(unsigned char *packet, unsigned size);

private:
    /**
     * Get size of the input file
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
     *  - C0    -> skip
     *  - DB DC -> C0
     *  - DB DD -> DB
     * @param  raw_buf  data to be unescaped
     * @param  size  size of data [byte]
     * @return pointer to unescaped data & size of unescaped data [byte]
     */
    std::pair<unsigned char *, unsigned> _unescape(unsigned char *raw_buf, unsigned size);

    //! pointers to unescaped data
    std::vector<unsigned char *> _buf_vec;
};

#endif // KISS_UNESCAPER_H