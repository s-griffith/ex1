//
//Created by Lior and Sarah on April 25, 2022.
//
#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>

/**
* Ascii Art Tool
*
* Reads and writes pictures in the form of Ascii Art.
*
* The following functions are available:
*   asciiArtRead              -Reads a given file and compresses it using RLE.
*   asciiArtPrint             -Writes a picture shown in RLEList form into a file.
*   asciiArtPrintEncoded      -Writes a compressed picture into a file.
*/


/**
* asciiArtRead: Reads a given file and compresses it using RLE
*
* @param in_stream - The file containing the desired picture.
* @return
*   A list of the type RLEList containing all the values in the picture.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
* asciiArtPrint: Prints a picture shown in RLEList form into a file
*
* @param list - The list of the type RLEList containing the values in the picture.
* @param out_stream - The file to be written in.
* @return
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as a list.
*   RLE_LIST_OUT_OF_MEMORY if malloc fails.
*   RLE_LIST_SUCCESS if the file has been written into successfully.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
* asciiArtPrintEncoded: Writes the compressed picture into a file.
*
* @param list - The list of the type RLEList containing the values in the picture.
* @param out_stream - The file to be written in
* @return
*   RLE_LIST_NULL_ARGUMENT if one of the given parameters is NULL.
*   RLE_LIST_SUCCESS if writing the compressed picture into the file succeeds.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //HW1_ASCIIARTTOOL_H
