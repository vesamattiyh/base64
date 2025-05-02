#ifndef __BASE64_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// unsigned char* base64_encode(char* input_text, int length);
unsigned char *base64_encode(const unsigned char *src, size_t len);
unsigned char *base64_decode(const unsigned char *src, size_t len);

#endif  // __BASE64_H__