<h1 align="center">
  kiss-unescaper
</h1>

<p align="center">
  Unescape tool for KISS special characters
</p>

## Description
kiss-unescaper replaces special characters in KISS protocol with the original data.

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
```
{
    KissUnescaper unescaper;
    
    /**
     * Unescape a binary file
     */
    FILE *fp = fopen("test.log", "rb"); // raw file (mode must be "rb")

    unsigned char *data;
    unsigned data_size;

    data_size = unescaper.unescape(&data, fp);

    /**
     * Unescape an array of some packets
     */
    unsigned char packets[] = {0xC0, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xC0}; // raw packets

    unsigned char *data2;
    unsigned data_size2;

    data_size2 = unescaper.unescape(&data2, packets, sizeof(packets));
}
```

## License
[MIT License](https://github.com/wowry/kiss-unescaper/blob/main/LICENSE)

## Author
[wowry](https://github.com/wowry)