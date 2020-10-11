<h1 align="center">
  kiss-unescaper
</h1>

<p align="center">
  <a href="https://github.com/wowry/kiss-unescaper/actions?query=workflow%3ACodeQL">
    <img src="https://img.shields.io/github/workflow/status/wowry/kiss-unescaper/CodeQL/main?style=flat-square" alt="Current CodeQL build status." />
  </a>
</p>

<p align="center">
  Unescaper C++ library for KISS special characters
</p>

## Description
kiss-unescaper replaces special characters in [KISS protocol](http://www.ax25.net/kiss.aspx) with the original data.

### Unescape special characters (Hex)
<table>
  <tr>
    <td>C0</td><td>→</td><td>(delete)</td>
  </tr>
  <tr>
    <td>DB DC</td><td>→</td><td>C0</td>
  </tr>
  <tr>
    <td>DB DD</td><td>→</td><td>DB</td>
  </tr>
</table>

### Example
- before<br>
`F8 F9 C0 C0 00 01 DB DC 10 11 DB DD 13 14 C0 C0 FA FB`

- after<br>
`F8 F9 00 01 C0 10 11 DB 13 14 FA FB`

## Usage
All you have to do is call `unescape` method.

This method accepts input of a binary file or an array of some packets,\
then writes unescaped data to ```buf```, and returns the size of ```buf``` as a result.

- ### `unsigned unescape(unsigned char **buf, FILE *fp)`
  Unescape a binary file.
   
  #### Parameters
  - ###### `buf`
    address of pointer to unescaped data\
    (unescaped data is written here)

  - ###### `fp`
    a binary file to be unescaped
   
  #### Return
  size of unescaped data [byte]

- ### `unsigned unescape(unsigned char **buf, unsigned char *packets, unsigned size)`
  Unescape an array of some packets.
   
  #### Parameters
  - ###### `buf`
    address of pointer to unescaped data\
    (unescaped data is written here)
  
  - ###### `packets`
    an array to be unescaped
  
  - ###### `size`
    size of the packets [byte]
   
  #### Return
  size of unescaped data [byte]

### Example
```C++
#include "../KissUnescaper.h"

using namespace std;

int main()
{
    KissUnescaper unescaper;

    /**
     * Unescape a binary file
     */
    FILE *fp = fopen("test.log", "rb"); // raw file (mode must be "rb")

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
```

## License
[MIT License](https://github.com/wowry/kiss-unescaper/blob/main/LICENSE)

## Author
[wowry](https://github.com/wowry)