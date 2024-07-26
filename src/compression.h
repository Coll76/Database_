#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stddef.h>

// Compress data using LZ77 algorithm
size_t compressLZ77(const unsigned char* input, size_t inputSize, unsigned char* output, size_t outputSize);

// Decompress data using LZ77 algorithm
size_t decompressLZ77(const unsigned char* input, size_t inputSize, unsigned char* output, size_t outputSize);

#endif // COMPRESSION_H

