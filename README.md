# Base64 Encoding/Decoding Library

This library provides simple functions to encode binary data into Base64 format and decode Base64-encoded data back into binary. It is useful for encoding binary streams for transmission over text-based protocols or storage in text files.

## Functions

### `unsigned char *base64_encode(const unsigned char *src, size_t len);`

- **Description**:  
  Encodes `len` bytes from the input buffer `src` into a null-terminated Base64 string.

- **Returns**:  
  A pointer to a dynamically allocated string containing the Base64-encoded output.  
  The caller is responsible for freeing this memory using `free()`.

---

### `unsigned char *base64_decode(const unsigned char *src, size_t len);`

- **Description**:  
  Decodes `len` bytes from a Base64-encoded string `src` into its original binary form.

- **Returns**:  
  A pointer to a dynamically allocated buffer containing the decoded binary data.  
  The caller is responsible for freeing this memory using `free()`.

---

## Notes

- The returned strings/buffers from both functions are allocated using `malloc`. The caller must call `free()` to release them.
- The input to `base64_decode()` must be valid Base64. If invalid characters or malformed input are provided, the behavior is undefined.

## Example Usage

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assume base64_encode and base64_decode are declared and implemented

int main() {
    const unsigned char *data = (const unsigned char *)"Hello, World!";
    size_t data_len = strlen((const char *)data);

    // Encode
    unsigned char *encoded = base64_encode(data, data_len);
    printf("Base64 Encoded: %s\n", encoded);

    // Decode
    unsigned char *decoded = base64_decode(encoded, strlen((const char *)encoded));
    printf("Decoded: %s\n", decoded);

    free(encoded);
    free(decoded);

    return 0;
}
