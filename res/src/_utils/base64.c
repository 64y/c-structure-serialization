#include <stdlib.h>
#include <string.h>

#include "_utils/base64.h"


void base64_encode_bytes_into_base64_code(byte *bytes, byte *base64_code);
void base64_encode_bytes_into_base64_code_padding(byte *bytes, size_t bytes_size_padding, byte *base64_code);

void base64_decode_bytes_from_base64_code(byte *bytes, byte *base64_code);
void base64_decode_bytes_from_base64_code_padding(byte *bytes, byte *base64_code, size_t base64_code_padding);


char * base64_encode(Data *data) {
	size_t bytes_size_padding = data->bytes_size%3;
	size_t bytes_size = data->bytes_size-bytes_size_padding;
	size_t data_base64_code_length = data->bytes_size/3*4 + (bytes_size_padding ? 4 : 0);
	char *data_base64_code = (char *)calloc(data_base64_code_length+1, sizeof(char));
	byte *pointer_bytes = data->bytes;
	char *pointer_base64_code = data_base64_code;
	for (size_t bytes_i=0; bytes_i<bytes_size; bytes_i+=3, pointer_bytes+=3, pointer_base64_code+=4) {
		base64_encode_bytes_into_base64_code(pointer_bytes, (byte *)pointer_base64_code);
	}
	base64_encode_bytes_into_base64_code_padding(pointer_bytes, bytes_size_padding, (byte *)pointer_base64_code);
	return data_base64_code;
}

Data * base64_decode(char *data_base64_code) {
	size_t data_base64_code_length = strlen(data_base64_code), data_base64_code_size = data_base64_code_length-4;
	size_t data_base64_code_size_padding = (data_base64_code[data_base64_code_length-2]=='=')+(data_base64_code[data_base64_code_length-1]=='=');
	size_t data_bytes_size = data_base64_code_length/4*3-data_base64_code_size_padding;
	Data *data = Data_create_by_size(data_bytes_size);
	char *pointer_base64_code = data_base64_code;
	byte *pointer_bytes = data->bytes;
	for (size_t base64_code_i=0; base64_code_i<data_base64_code_size; base64_code_i+=4, pointer_base64_code+=4, pointer_bytes+=3) {
		base64_decode_bytes_from_base64_code(pointer_bytes, (byte *)pointer_base64_code);
	}
	base64_decode_bytes_from_base64_code_padding(pointer_bytes, (byte *)pointer_base64_code, 4-data_base64_code_size_padding);
	return data;
}


char * base64_encode_string(char *string) {
	return base64_encode(&((Data) {strlen(string), (byte *)string}));
}


char * base64_decode_string(char *string_base64_code) {
	Data *data = base64_decode(string_base64_code);
	char *string = (char *)calloc(data->bytes_size+1, sizeof(char));
	memcpy(string, data->bytes, data->bytes_size);
	Data_free(data);
	return string;
}


const char BASE64_ABC[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
	'='
};

const unsigned char BASE64_ABC_INVERSE[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xFF, 0xFF, 0xFF, 0x3F,
	0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
	0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

void base64_encode_bytes_into_base64_code(byte *bytes, byte *base64_code) {
	base64_code[0] = BASE64_ABC[bytes[0]>>2];
	base64_code[1] = BASE64_ABC[(0x30 & (bytes[0]<<4)) | (0x0F & (bytes[1]>>4))];
	base64_code[2] = BASE64_ABC[(0x3C & (bytes[1]<<2)) | (0x03 & (bytes[2]>>6))];
	base64_code[3] = BASE64_ABC[(0x3F & bytes[2])];
}

void base64_encode_bytes_into_base64_code_padding(byte *bytes, size_t bytes_size_padding, byte *base64_code) {
	if (bytes_size_padding==0) {
		return;
	} else if (bytes_size_padding==1) {
		base64_code[0] = BASE64_ABC[bytes[0]>>2];
		base64_code[1] = BASE64_ABC[0x30 & (bytes[0]<<4)];
		base64_code[2] = BASE64_ABC[64];
		base64_code[3] = BASE64_ABC[64];
	} else if (bytes_size_padding==2) {
		base64_code[0] = BASE64_ABC[bytes[0]>>2];
		base64_code[1] = BASE64_ABC[(0x30 & (bytes[0]<<4)) | (0x0F & (bytes[1]>>4))];
		base64_code[2] = BASE64_ABC[0x3C & (bytes[1]<<2)];
		base64_code[3] = BASE64_ABC[64];
	} else if (bytes_size_padding==3) {
		base64_encode_bytes_into_base64_code(bytes, base64_code);
	}
}

void base64_decode_bytes_from_base64_code(byte *bytes, byte *base64_code) {
	bytes[0] = (BASE64_ABC_INVERSE[base64_code[0]]<<2) | (BASE64_ABC_INVERSE[base64_code[1]]>>4);
	bytes[1] = (BASE64_ABC_INVERSE[base64_code[1]]<<4) | (BASE64_ABC_INVERSE[base64_code[2]]>>2);
	bytes[2] = (BASE64_ABC_INVERSE[base64_code[2]]<<6) | (BASE64_ABC_INVERSE[base64_code[3]]);
}

void base64_decode_bytes_from_base64_code_padding(byte *bytes, byte *base64_code, size_t base64_code_padding) {
	if (base64_code_padding==0 || base64_code_padding==1) {
		return;
	} else if (base64_code_padding==2) {
		bytes[0] = (BASE64_ABC_INVERSE[base64_code[0]]<<2) | (BASE64_ABC_INVERSE[base64_code[1]]>>4);
	} else if (base64_code_padding==3) {
		bytes[0] = (BASE64_ABC_INVERSE[base64_code[0]]<<2) | (BASE64_ABC_INVERSE[base64_code[1]]>>4);
		bytes[1] = (BASE64_ABC_INVERSE[base64_code[1]]<<4) | (BASE64_ABC_INVERSE[base64_code[2]]>>2);
	} else if (base64_code_padding==4) {
		base64_decode_bytes_from_base64_code(bytes, base64_code);
	}
}
