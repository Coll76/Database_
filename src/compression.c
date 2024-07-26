#include "compression.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WINDOW_SIZE 1024
#define MAX_LOOKAHEAD_SIZE 16

typedef struct {
    unsigned short offset;
    unsigned char length;
    unsigned char nextChar;
} LZ77Token;

// Compress data using LZ77 algorithm
size_t compressLZ77(const unsigned char* input, size_t inputSize, unsigned char* output, size_t outputSize) {
    if (inputSize == 0 || outputSize < 1) return 0;

    size_t inputPos = 0;
    size_t outputPos = 0;
    unsigned char window[MAX_WINDOW_SIZE];
    size_t windowSize = 0;

    while (inputPos < inputSize && outputPos < outputSize) {
        size_t matchLength = 0;
        size_t matchOffset = 0;
        size_t searchPos = (inputPos > MAX_WINDOW_SIZE) ? inputPos - MAX_WINDOW_SIZE : 0;

        // Search for the longest match
        for (size_t i = searchPos; i < inputPos; ++i) {
            size_t length = 0;
            while (inputPos + length < inputSize && length < MAX_LOOKAHEAD_SIZE &&
                   input[i + length] == input[inputPos + length]) {
                length++;
            }
            if (length > matchLength) {
                matchLength = length;
                matchOffset = inputPos - i;
            }
        }

        // Write the token to the output
        if (matchLength > 1) {
            if (outputPos + 3 > outputSize) return 0; // Not enough space in output buffer

            LZ77Token token;
            token.offset = (unsigned short)matchOffset;
            token.length = (unsigned char)(matchLength - 1);
            token.nextChar = input[inputPos + matchLength];
            memcpy(output + outputPos, &token, sizeof(token));
            outputPos += sizeof(token);
            inputPos += matchLength + 1;
        } else {
            if (outputPos + 1 > outputSize) return 0; // Not enough space in output buffer

            output[outputPos++] = input[inputPos++];
        }
    }

    return outputPos;
}

// Decompress data using LZ77 algorithm
size_t decompressLZ77(const unsigned char* input, size_t inputSize, unsigned char* output, size_t outputSize) {
    if (inputSize == 0 || outputSize < 1) return 0;

    size_t inputPos = 0;
    size_t outputPos = 0;

    while (inputPos < inputSize && outputPos < outputSize) {
        if (inputSize - inputPos < sizeof(LZ77Token)) {
            output[outputPos++] = input[inputPos++];
        } else {
            LZ77Token token;
            memcpy(&token, input + inputPos, sizeof(token));
            inputPos += sizeof(token);

            if (outputPos + token.length + 1 > outputSize) return 0; // Not enough space in output buffer

            size_t start = outputPos - token.offset;
            for (size_t i = 0; i <= token.length; ++i) {
                output[outputPos++] = output[start + i];
            }
            output[outputPos++] = token.nextChar;
        }
    }

    return outputPos;
}
