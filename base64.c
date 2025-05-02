/*
 * Base64 Encoding/Decoding Library
 *
 * Provides functions to encode binary data into Base64 and decode Base64 back to binary.
 *
 * Functions:
 *
 * unsigned char *base64_encode(const unsigned char *src, size_t len);
 *   - Encodes 'len' bytes from 'src' into a null-terminated Base64 string.
 *   - Returns a malloc'd string that must be freed by the caller.
 *
 * unsigned char *base64_decode(const unsigned char *src, size_t len);
 *   - Decodes 'len' bytes from Base64-encoded 'src' into binary data.
 *   - Returns a malloc'd buffer containing the decoded bytes.
 *
 * Notes:
 * - Caller is responsible for freeing the returned buffers.
 * - Input to base64_decode() must be valid Base64; behavior is undefined otherwise.
 */

#include "base64.h"

static const char *BASE64_LUT = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int get_index(char c)
{
    return((int)(strchr(BASE64_LUT, c) - BASE64_LUT));
}

unsigned char *base64_encode(const unsigned char *src, size_t len)
{
    unsigned char *pos, *out;
    const unsigned char *end, *in;

    out = (unsigned char*)calloc(len*4/3 + 1, sizeof(char));

    if(out == NULL){
        free(out);
        return NULL;
    }

    pos = out;
    in = src;
    end = src + len;

    while(end - in >= 3){
        *pos++ = BASE64_LUT[(in[0] >> 2)];
        *pos++ = BASE64_LUT[(in[0] & 0x3) << 4 | (in[1] >> 4)];
        *pos++ = BASE64_LUT[(in[1] & 0xF) << 2 | in[2] >> 6];
        *pos++ = BASE64_LUT[(in[2] & 0x3F)];
        in+=3;
    }

    if(end - in){ // Go through remaining chars one by one
        *pos++ = BASE64_LUT[(in[0] >> 2)];
        *pos++ = BASE64_LUT[(in[0] & 0x3) << 4 | ((in+1<end) ? in[1] >> 4 : 0)];
        (in<end) ? in++ : in;
        *pos++ = (end-in) ? BASE64_LUT[(in[0] & 0xF) << 2 | ((in+1<end) ? in[1] >> 6 : 0)] : '=';
        (in<end) ? in++ : in;
        *pos++ =  (end-in) ? BASE64_LUT[(in[0] & 0x3F)] : '='; // In case of out of chars we use the padding sign '='.
    }

    *pos = '\0';
    return out;
}

unsigned char *base64_decode(const unsigned char *src, size_t len)
{
    unsigned char *pos, *out;
    const unsigned char *end, *in;

    out = (unsigned char*)calloc(len*3/4 + 1, sizeof(char));

    if(out == NULL){
        free(out);
        return NULL;
    }

    pos = out;
    in = src;
    end = src + len;

    while(end - in >= 4){
        *pos++ = (get_index(in[0]) << 2) | (get_index(in[1]) >> 4);          // Shitf 2 bits and take 2 most significant bits
        *pos++ = (get_index(in[1]) & 0xF) << 4 | ((in[2] != '=') ? get_index(in[2]) >> 2 : 0);    // Shitf 4 bits and take 2 most significant bits

        if(in[2] == '='){
            break;
        }

        *pos++ = (get_index(in[2]) & 0x3) << 6 | ((in[3] != '=') ? get_index(in[3]) : 0);         // Shitf 2 bits and take rest bits
        in+=4;
    }

    *pos = '\0';
    return out;
}
