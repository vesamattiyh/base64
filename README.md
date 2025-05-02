# BASE64 encoder, decoder

This library provides simple functions to encode binary data into Base64 format and decode Base64-encoded data back into binary. It is useful for encoding binary streams for transmission over text-based protocols or storage in text files.

Overview
The library includes two primary functions:

unsigned char *base64_encode(const unsigned char *src, size_t len);
Description:
Encodes len bytes from the input buffer src into a null-terminated Base64 string.

Returns:
A pointer to a dynamically allocated string containing the Base64-encoded output.
The caller is responsible for freeing this memory using free().

unsigned char *base64_decode(const unsigned char *src, size_t len);
Description:
Decodes len bytes from a Base64-encoded string src into its original binary form.

Returns:
A pointer to a dynamically allocated buffer containing the decoded binary data.
The caller is responsible for freeing this memory using free().

Notes
Both functions return buffers that are dynamically allocated using malloc. It is the caller's responsibility to free them after use.

The input to base64_decode() must be valid Base64. If the input is malformed or contains invalid characters, the behavior is undefined.
