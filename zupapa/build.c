#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int loadrom(unsigned char *dst, int gap, char *name) // flags & 1 = skip byte
{
	int length = 0;
	FILE *fa = fopen(name, "rb");
	if (fa == NULL)
	{
		printf ("Unable to open %s!\n", name);
		return 1;
	}
	fseek (fa, 0, SEEK_END);
	length = ftell (fa);
	rewind (fa);

	unsigned char *tmp = (unsigned char *)malloc(length);
	if (tmp == NULL) {
		printf ("Unable to allocate %d bytes of memory!\n", length);
		return 1;
	}

	fread (tmp, length, 1, fa);
	fclose (fa);

	int i;
	for (i = 0; i < length; i++)
	{
		dst[i * gap] = tmp[i];
	}

	free (tmp);

	return 0;
}

static const unsigned char type0_t03[256] = {
	0xfb, 0x86, 0x9d, 0xf1, 0xbf, 0x80, 0xd5, 0x43, 0xab, 0xb3, 0x9f, 0x6a, 0x33, 0xd9, 0xdb, 0xb6,
	0x66, 0x08, 0x69, 0x88, 0xcc, 0xb7, 0xde, 0x49, 0x97, 0x64, 0x1f, 0xa6, 0xc0, 0x2f, 0x52, 0x42,
	0x44, 0x5a, 0xf2, 0x28, 0x98, 0x87, 0x96, 0x8a, 0x83, 0x0b, 0x03, 0x61, 0x71, 0x99, 0x6b, 0xb5,
	0x1a, 0x8e, 0xfe, 0x04, 0xe1, 0xf7, 0x7d, 0xdd, 0xed, 0xca, 0x37, 0xfc, 0xef, 0x39, 0x72, 0xda,
	0xb8, 0xbe, 0xee, 0x7f, 0xe5, 0x31, 0x78, 0xf3, 0x91, 0x9a, 0xd2, 0x11, 0x19, 0xb9, 0x09, 0x4c,
	0xfd, 0x6d, 0x2a, 0x4d, 0x65, 0xa1, 0x89, 0xc7, 0x75, 0x50, 0x21, 0xfa, 0x16, 0x00, 0xe9, 0x12,
	0x74, 0x2b, 0x1e, 0x4f, 0x14, 0x01, 0x70, 0x3a, 0x4e, 0x3f, 0xf5, 0xf4, 0x1d, 0x3d, 0x15, 0x27,
	0xa7, 0xff, 0x45, 0xe0, 0x6e, 0xf9, 0x54, 0xc8, 0x48, 0xad, 0xa5, 0x0a, 0xf6, 0x2d, 0x2c, 0xe2,
	0x68, 0x67, 0xd6, 0x85, 0xb4, 0xc3, 0x34, 0xbc, 0x62, 0xd3, 0x5f, 0x84, 0x06, 0x5b, 0x0d, 0x95,
	0xea, 0x5e, 0x9e, 0xd4, 0xeb, 0x90, 0x7a, 0x05, 0x81, 0x57, 0xe8, 0x60, 0x2e, 0x20, 0x25, 0x7c,
	0x46, 0x0c, 0x93, 0xcb, 0xbd, 0x17, 0x7e, 0xec, 0x79, 0xb2, 0xc2, 0x22, 0x41, 0xb1, 0x10, 0xac,
	0xa8, 0xbb, 0x9b, 0x82, 0x4b, 0x9c, 0x8b, 0x07, 0x47, 0x35, 0x24, 0x56, 0x8d, 0xaf, 0xe6, 0x26,
	0x40, 0x38, 0xc4, 0x5d, 0x1b, 0xc5, 0xd1, 0x0f, 0x6c, 0x7b, 0xb0, 0xe3, 0xa3, 0x23, 0x6f, 0x58,
	0xc1, 0xba, 0xcf, 0xd7, 0xa2, 0xe7, 0xd0, 0x63, 0x5c, 0xf8, 0x73, 0xa0, 0x13, 0xdc, 0x29, 0xcd,
	0xc9, 0x76, 0xae, 0x8f, 0xe4, 0x59, 0x30, 0xaa, 0x94, 0x1c, 0x3c, 0x0e, 0x55, 0x92, 0x77, 0x32,
	0xc6, 0xce, 0x18, 0x36, 0xdf, 0xa9, 0x8c, 0xd8, 0xa4, 0xf0, 0x3b, 0x51, 0x4a, 0x02, 0x3e, 0x53,
};

static const unsigned char type0_t12[256] = {
	0x1f, 0xac, 0x4d, 0xcd, 0xca, 0x70, 0x02, 0x6b, 0x18, 0x40, 0x62, 0xb2, 0x3f, 0x9b, 0x5b, 0xef,
	0x69, 0x68, 0x71, 0x3b, 0xcb, 0xd4, 0x30, 0xbc, 0x47, 0x72, 0x74, 0x5e, 0x84, 0x4c, 0x1b, 0xdb,
	0x6a, 0x35, 0x1d, 0xf5, 0xa1, 0xb3, 0x87, 0x5d, 0x57, 0x28, 0x2f, 0xc4, 0xfd, 0x24, 0x26, 0x36,
	0xad, 0xbe, 0x61, 0x63, 0x73, 0xaa, 0x82, 0xee, 0x29, 0xd0, 0xdf, 0x8c, 0x15, 0xb5, 0x96, 0xf3,
	0xdd, 0x7e, 0x3a, 0x37, 0x58, 0x7f, 0x0c, 0xfc, 0x0b, 0x07, 0xe8, 0xf7, 0xf4, 0x14, 0xb8, 0x81,
	0xb6, 0xd7, 0x1e, 0xc8, 0x85, 0xe6, 0x9d, 0x33, 0x60, 0xc5, 0x95, 0xd5, 0x55, 0x00, 0xa3, 0xb7,
	0x7d, 0x50, 0x0d, 0xd2, 0xc1, 0x12, 0xe5, 0xed, 0xd8, 0xa4, 0x9c, 0x8f, 0x2a, 0x4f, 0xa8, 0x01,
	0x52, 0x83, 0x65, 0xea, 0x9a, 0x6c, 0x44, 0x4a, 0xe2, 0xa5, 0x2b, 0x46, 0xe1, 0x34, 0x25, 0xf8,
	0xc3, 0xda, 0xc7, 0x6e, 0x48, 0x38, 0x7c, 0x78, 0x06, 0x53, 0x64, 0x16, 0x98, 0x3c, 0x91, 0x42,
	0x39, 0xcc, 0xb0, 0xf1, 0xeb, 0x13, 0xbb, 0x05, 0x32, 0x86, 0x0e, 0xa2, 0x0a, 0x9e, 0xfa, 0x66,
	0x54, 0x8e, 0xd3, 0xe7, 0x19, 0x20, 0x77, 0xec, 0xff, 0xbd, 0x6d, 0x43, 0x23, 0x03, 0xab, 0x75,
	0x3d, 0xcf, 0xd1, 0xde, 0x92, 0x31, 0xa7, 0x45, 0x4b, 0xc2, 0x97, 0xf9, 0x7a, 0x88, 0xd9, 0x1c,
	0xe9, 0xe4, 0x10, 0xc9, 0x22, 0x2d, 0x90, 0x76, 0x17, 0x79, 0x04, 0x51, 0x1a, 0x5a, 0x5f, 0x2c,
	0x21, 0x6f, 0x3e, 0xe0, 0xf0, 0xbf, 0xd6, 0x94, 0x0f, 0x80, 0x11, 0xa0, 0x5c, 0xa9, 0x49, 0x2e,
	0xce, 0xaf, 0xa6, 0x9f, 0x7b, 0x99, 0xb9, 0xb4, 0xe3, 0xfb, 0xf6, 0x27, 0xf2, 0x93, 0xfe, 0x08,
	0x67, 0xae, 0x09, 0x89, 0xdc, 0x4e, 0xc6, 0xc0, 0x8a, 0xb1, 0x59, 0x8b, 0x41, 0x56, 0x8d, 0xba,
};

static const unsigned char type1_t03[256] = {
	0xa9, 0x17, 0xaf, 0x0d, 0x34, 0x6e, 0x53, 0xb6, 0x7f, 0x58, 0xe9, 0x14, 0x5f, 0x55, 0xdb, 0xd4,
	0x42, 0x80, 0x99, 0x59, 0xa8, 0x3a, 0x57, 0x5d, 0xd5, 0x6f, 0x4c, 0x68, 0x35, 0x46, 0xa6, 0xe7,
	0x7b, 0x71, 0xe0, 0x93, 0xa2, 0x1f, 0x64, 0x21, 0xe3, 0xb1, 0x98, 0x26, 0xab, 0xad, 0xee, 0xe5,
	0xbb, 0xd9, 0x1e, 0x2e, 0x95, 0x36, 0xef, 0x23, 0x79, 0x45, 0x04, 0xed, 0x13, 0x1d, 0xf4, 0x85,
	0x96, 0xec, 0xc2, 0x32, 0xaa, 0x7c, 0x15, 0xd8, 0xda, 0x92, 0x90, 0x9d, 0xb7, 0x56, 0x6a, 0x66,
	0x41, 0xfc, 0x00, 0xf6, 0x50, 0x24, 0xcf, 0xfb, 0x11, 0xfe, 0x82, 0x48, 0x9b, 0x27, 0x1b, 0x67,
	0x4e, 0x84, 0x69, 0x97, 0x6d, 0x8c, 0xd2, 0xba, 0x74, 0xf9, 0x8f, 0xa5, 0x54, 0x5c, 0xcd, 0x73,
	0x07, 0xd1, 0x01, 0x09, 0xf1, 0x19, 0x3b, 0x5e, 0x87, 0x30, 0x76, 0xcc, 0xc0, 0x5a, 0xa7, 0x49,
	0x22, 0xfa, 0x16, 0x02, 0xdf, 0xa4, 0xff, 0xb3, 0x75, 0x33, 0xbd, 0x88, 0x2f, 0xcb, 0x2a, 0x44,
	0xb8, 0xbf, 0x1c, 0x0f, 0x81, 0x10, 0x43, 0xb4, 0xc8, 0x7e, 0x9a, 0x25, 0xea, 0x83, 0x4b, 0x38,
	0x7a, 0xd7, 0x3d, 0x1a, 0x4f, 0x62, 0x51, 0xc9, 0x47, 0x0e, 0xce, 0x3f, 0xc7, 0x4d, 0x2c, 0xa1,
	0x86, 0xb9, 0xc5, 0xca, 0xdd, 0x6b, 0x70, 0x6c, 0x91, 0x9c, 0xbe, 0x0a, 0x9f, 0xf5, 0x94, 0xbc,
	0x18, 0x2b, 0x60, 0x20, 0x29, 0xf7, 0xf2, 0x28, 0xc4, 0xa0, 0x0b, 0x65, 0xde, 0x8d, 0x78, 0x12,
	0x3e, 0xd0, 0x77, 0x08, 0x8b, 0xae, 0x05, 0x31, 0x3c, 0xd6, 0xa3, 0x89, 0x06, 0xdc, 0x52, 0x72,
	0xb0, 0xb5, 0x37, 0xd3, 0xc3, 0x8a, 0xc6, 0xf0, 0xc1, 0x61, 0xfd, 0x4a, 0x5b, 0x7d, 0x9e, 0xf3,
	0x63, 0x40, 0x2d, 0xe8, 0xb2, 0xe6, 0x39, 0x03, 0xeb, 0x8e, 0xe1, 0x0c, 0xe4, 0xe2, 0xf8, 0xac,
};

static const unsigned char type1_t12[256] = {
	0xea, 0xe6, 0x5e, 0xa7, 0x8e, 0xac, 0x34, 0x03, 0x30, 0x97, 0x52, 0x53, 0x76, 0xf2, 0x62, 0x0b,
	0x0a, 0xfc, 0x94, 0xb8, 0x67, 0x36, 0x11, 0xbc, 0xae, 0xca, 0xfa, 0x15, 0x04, 0x2b, 0x17, 0xc4,
	0x3e, 0x5b, 0x59, 0x01, 0x57, 0xe2, 0xba, 0xb7, 0xd1, 0x3f, 0xf0, 0x6a, 0x9c, 0x2a, 0xcb, 0xa9,
	0xe3, 0x2c, 0xc0, 0x0f, 0x46, 0x91, 0x8a, 0xd0, 0x98, 0xc5, 0xa6, 0x1b, 0x96, 0x29, 0x12, 0x09,
	0x63, 0xed, 0xe0, 0xa2, 0x86, 0x77, 0xbe, 0xe5, 0x65, 0xdb, 0xbd, 0x50, 0xb3, 0x9d, 0x1a, 0x4e,
	0x79, 0x0c, 0x00, 0x43, 0xdf, 0x3d, 0x54, 0x33, 0x8f, 0x89, 0xa8, 0x7b, 0xf9, 0xd5, 0x27, 0x82,
	0xbb, 0xc2, 0x8c, 0x47, 0x88, 0x6b, 0xb4, 0xc3, 0xf8, 0xaa, 0x06, 0x1e, 0x83, 0x7d, 0x05, 0x78,
	0x85, 0xf6, 0x6e, 0x2e, 0xec, 0x5a, 0x31, 0x45, 0x38, 0x14, 0x16, 0x8b, 0x02, 0xe4, 0x4f, 0xb0,
	0xbf, 0xab, 0xa4, 0x9e, 0x48, 0x60, 0x19, 0x35, 0x08, 0xde, 0xdd, 0x66, 0x90, 0x51, 0xcc, 0xa3,
	0xaf, 0x70, 0x9b, 0x75, 0x95, 0x49, 0x6c, 0x64, 0x72, 0x7e, 0x44, 0xa0, 0x73, 0x25, 0x68, 0x55,
	0x1f, 0x40, 0x7a, 0x74, 0x0e, 0x8d, 0xdc, 0x1c, 0x71, 0xc8, 0xcf, 0xd7, 0xe8, 0xce, 0xeb, 0x32,
	0x3a, 0xee, 0x07, 0x61, 0x4d, 0xfe, 0x5c, 0x7c, 0x56, 0x2f, 0x2d, 0x5f, 0x6f, 0x9f, 0x81, 0x22,
	0x58, 0x4b, 0xad, 0xda, 0xb9, 0x10, 0x18, 0x23, 0xe1, 0xf3, 0x6d, 0xe7, 0xe9, 0x28, 0xd6, 0xd8,
	0xf4, 0x4c, 0x39, 0x21, 0xb2, 0x84, 0xc1, 0x24, 0x26, 0xf1, 0x93, 0x37, 0xc6, 0x4a, 0xcd, 0x20,
	0xc9, 0xd9, 0xc7, 0xb1, 0xff, 0x99, 0xd4, 0x5d, 0xb5, 0xa1, 0x87, 0x0d, 0x69, 0x92, 0x13, 0x80,
	0xd2, 0xd3, 0xfd, 0x1d, 0xf5, 0x3b, 0xa5, 0x7f, 0xef, 0x9a, 0xb6, 0x42, 0xfb, 0x3c, 0xf7, 0x41,
};

static const unsigned char address_8_15_xor1[256] = {
	0x00, 0xb1, 0x1e, 0xc5, 0x3d, 0x40, 0x45, 0x5e, 0xf2, 0xf8, 0x04, 0x63, 0x36, 0x87, 0x88, 0xbf,
	0xab, 0xcc, 0x78, 0x08, 0xdd, 0x20, 0xd4, 0x35, 0x09, 0x8e, 0x44, 0xae, 0x33, 0xa9, 0x9e, 0xcd,
	0xb3, 0xe5, 0xad, 0x41, 0xda, 0xbe, 0xf4, 0x16, 0x57, 0x2e, 0x53, 0x67, 0xaf, 0xdb, 0x8a, 0xd8,
	0x34, 0x17, 0x3c, 0x01, 0x55, 0x73, 0xcf, 0xe3, 0xe8, 0xc7, 0x0d, 0xe9, 0xa3, 0x13, 0x0c, 0xf6,
	0x90, 0x4e, 0xfb, 0x97, 0x6d, 0x5f, 0xa8, 0x71, 0x11, 0xfc, 0xd1, 0x95, 0x81, 0xba, 0x8c, 0x1b,
	0x39, 0xfe, 0xa2, 0x15, 0xa6, 0x52, 0x4d, 0x5b, 0x59, 0xa5, 0xe0, 0x96, 0xd9, 0x8f, 0x7b, 0xed,
	0x29, 0xd3, 0x1f, 0x0e, 0xec, 0x23, 0x0f, 0xb8, 0x6c, 0x6f, 0x7d, 0x18, 0x46, 0xd6, 0xe4, 0xb5,
	0x9a, 0x79, 0x02, 0xf5, 0x03, 0xc0, 0x60, 0x66, 0x5c, 0x2f, 0x76, 0x85, 0x9d, 0x54, 0x1a, 0x6a,
	0x28, 0xce, 0x7f, 0x7c, 0x91, 0x99, 0x4c, 0x83, 0x3e, 0xb4, 0x1d, 0x05, 0xc1, 0xc3, 0xd7, 0x47,
	0xde, 0xbc, 0x62, 0x6e, 0x86, 0x14, 0x80, 0x77, 0xeb, 0xf3, 0x07, 0x31, 0x56, 0xd2, 0xc2, 0xc6,
	0x6b, 0xdc, 0xfd, 0x22, 0x92, 0xf0, 0x06, 0x51, 0x2d, 0x38, 0xe6, 0xa0, 0x25, 0xdf, 0xd5, 0x2c,
	0x1c, 0x94, 0x12, 0x9c, 0xb0, 0x9b, 0xc4, 0x0b, 0xc8, 0xd0, 0xf7, 0x30, 0xcb, 0x27, 0xfa, 0x7a,
	0x10, 0x61, 0xaa, 0xa4, 0x70, 0xb7, 0x2a, 0x5a, 0xc9, 0xf1, 0x0a, 0x49, 0x65, 0xee, 0x69, 0x4b,
	0x3a, 0x8d, 0x32, 0x5d, 0x68, 0xb9, 0x9f, 0x75, 0x19, 0x3f, 0xac, 0x37, 0x4f, 0xe7, 0x93, 0x89,
	0x7e, 0x4a, 0x3b, 0xea, 0x74, 0x72, 0x43, 0xbd, 0x24, 0xef, 0xb6, 0xff, 0x64, 0x58, 0x84, 0x8b,
	0xa7, 0xbb, 0xb2, 0xe1, 0x26, 0x2b, 0x50, 0xca, 0x21, 0xf9, 0x98, 0xa1, 0xe2, 0x42, 0x82, 0x48,
};

static const unsigned char address_8_15_xor2[256] = {
	0x9b, 0x9d, 0xc1, 0x3d, 0xa9, 0xb8, 0xf4, 0x6f, 0xf6, 0x25, 0xc7, 0x47, 0xd5, 0x97, 0xdf, 0x6b,
	0xeb, 0x90, 0xa4, 0xb2, 0x5d, 0xf5, 0x66, 0xb0, 0xb9, 0x8b, 0x93, 0x64, 0xec, 0x7b, 0x65, 0x8c,
	0xf1, 0x43, 0x42, 0x6e, 0x45, 0x9f, 0xb3, 0x35, 0x06, 0x71, 0x96, 0xdb, 0xa0, 0xfb, 0x0b, 0x3a,
	0x1f, 0xf8, 0x8e, 0x69, 0xcd, 0x26, 0xab, 0x86, 0xa2, 0x0c, 0xbd, 0x63, 0xa5, 0x7a, 0xe7, 0x6a,
	0x5f, 0x18, 0x9e, 0xbf, 0xad, 0x55, 0xb1, 0x1c, 0x5c, 0x03, 0x30, 0xc6, 0x37, 0x20, 0xe3, 0xc9,
	0x52, 0xe8, 0xee, 0x4f, 0x01, 0x70, 0xc4, 0x77, 0x29, 0x2a, 0xba, 0x53, 0x12, 0x04, 0x7d, 0xaf,
	0x33, 0x8f, 0xa8, 0x4d, 0xaa, 0x5b, 0xb4, 0x0f, 0x92, 0xbb, 0xed, 0xe1, 0x2f, 0x50, 0x6c, 0xd2,
	0x2c, 0x95, 0xd9, 0xf9, 0x98, 0xc3, 0x76, 0x4c, 0xf2, 0xe4, 0xe5, 0x2b, 0xef, 0x9c, 0x49, 0xb6,
	0x31, 0x3b, 0xbc, 0xa1, 0xca, 0xde, 0x62, 0x74, 0xea, 0x81, 0x00, 0xdd, 0xa6, 0x46, 0x88, 0x3f,
	0x39, 0xd6, 0x23, 0x54, 0x24, 0x4a, 0xd8, 0xdc, 0xd7, 0xd1, 0xcc, 0xbe, 0x57, 0x7c, 0xda, 0x44,
	0x61, 0xce, 0xd3, 0xd4, 0xe9, 0x28, 0x80, 0xe0, 0x56, 0x8a, 0x09, 0x05, 0x9a, 0x89, 0x1b, 0xf7,
	0xf3, 0x99, 0x6d, 0x5e, 0x48, 0x91, 0xc0, 0xd0, 0xc5, 0x79, 0x78, 0x41, 0x59, 0x21, 0x2e, 0xff,
	0xc2, 0x4b, 0x38, 0x83, 0x32, 0xe6, 0xe2, 0x7f, 0x1e, 0x17, 0x58, 0x1d, 0x1a, 0xfa, 0x85, 0x82,
	0x94, 0xc8, 0x72, 0x7e, 0xb7, 0xac, 0x0e, 0xfc, 0xfd, 0x16, 0x27, 0x75, 0x8d, 0xcb, 0x08, 0xfe,
	0x0a, 0x02, 0x0d, 0x36, 0x11, 0x22, 0x84, 0x40, 0x34, 0x3e, 0x2d, 0x68, 0x5a, 0xa7, 0x67, 0xae,
	0x87, 0x07, 0x10, 0x60, 0x14, 0x73, 0x3c, 0x51, 0x19, 0xa3, 0xb5, 0xcf, 0x13, 0xf0, 0x15, 0x4e,
};

static const unsigned char address_16_23_xor1[256] = {
	0x00, 0x5f, 0x03, 0x52, 0xce, 0xe3, 0x7d, 0x8f, 0x6b, 0xf8, 0x20, 0xde, 0x7b, 0x7e, 0x39, 0xbe,
	0xf5, 0x94, 0x18, 0x78, 0x80, 0xc9, 0x7f, 0x7a, 0x3e, 0x63, 0xf2, 0xe0, 0x4e, 0xf7, 0x87, 0x27,
	0x69, 0x6c, 0xa4, 0x1d, 0x85, 0x5b, 0xe6, 0x44, 0x25, 0x0c, 0x98, 0xc7, 0x01, 0x02, 0xa3, 0x26,
	0x09, 0x38, 0xdb, 0xc3, 0x1e, 0xcf, 0x23, 0x45, 0x68, 0x76, 0xd6, 0x22, 0x5d, 0x5a, 0xae, 0x16,
	0x9f, 0xa2, 0xb5, 0xcd, 0x81, 0xea, 0x5e, 0xb8, 0xb9, 0x9d, 0x9c, 0x1a, 0x0f, 0xff, 0xe1, 0xe7,
	0x74, 0xaa, 0xd4, 0xaf, 0xfc, 0xc6, 0x33, 0x29, 0x5c, 0xab, 0x95, 0xf0, 0x19, 0x47, 0x59, 0x67,
	0xf3, 0x96, 0x60, 0x1f, 0x62, 0x92, 0xbd, 0x89, 0xee, 0x28, 0x13, 0x06, 0xfe, 0xfa, 0x32, 0x6d,
	0x57, 0x3c, 0x54, 0x50, 0x2c, 0x58, 0x49, 0xfb, 0x17, 0xcc, 0xef, 0xb2, 0xb4, 0xf9, 0x07, 0x70,
	0xc5, 0xa9, 0xdf, 0xd5, 0x3b, 0x86, 0x2b, 0x0d, 0x6e, 0x4d, 0x0a, 0x90, 0x43, 0x31, 0xc1, 0xf6,
	0x88, 0x0b, 0xda, 0x53, 0x14, 0xdc, 0x75, 0x8e, 0xb0, 0xeb, 0x99, 0x46, 0xa1, 0x15, 0x71, 0xc8,
	0xe9, 0x3f, 0x4a, 0xd9, 0x73, 0xe5, 0x7c, 0x30, 0x77, 0xd3, 0xb3, 0x4b, 0x37, 0x72, 0xc2, 0x04,
	0x97, 0x08, 0x36, 0xb1, 0x3a, 0x61, 0xec, 0xe2, 0x1c, 0x9a, 0x8b, 0xd1, 0x1b, 0x2e, 0x9e, 0x8a,
	0xd8, 0x41, 0xe4, 0xc4, 0x40, 0x2f, 0xad, 0xc0, 0xb6, 0x84, 0x51, 0x66, 0xbb, 0x12, 0xe8, 0xdd,
	0xcb, 0xbc, 0x6f, 0xd0, 0x11, 0x83, 0x56, 0x4c, 0xca, 0xbf, 0x05, 0x10, 0xd7, 0xba, 0xfd, 0xed,
	0x8c, 0x0e, 0x4f, 0x3d, 0x35, 0x91, 0xb7, 0xac, 0x34, 0x64, 0x2a, 0xf1, 0x79, 0x6a, 0x9b, 0x2d,
	0x65, 0xf4, 0x42, 0xa0, 0x8d, 0xa7, 0x48, 0x55, 0x21, 0x93, 0x24, 0xd2, 0xa6, 0xa5, 0xa8, 0x82,
};

static const unsigned char address_16_23_xor2[256] = {
	0x29, 0x97, 0x1a, 0x2c, 0x0b, 0x94, 0x3e, 0x75, 0x01, 0x0d, 0x1b, 0xe1, 0x4d, 0x38, 0x39, 0x8f,
	0xe7, 0xd0, 0x60, 0x90, 0xb2, 0x0f, 0xbb, 0x70, 0x1f, 0xe6, 0x5b, 0x87, 0xb4, 0x43, 0xfd, 0xf5,
	0xf6, 0xf9, 0xad, 0xc0, 0x98, 0x17, 0x9f, 0x91, 0x15, 0x51, 0x55, 0x64, 0x6c, 0x18, 0x61, 0x0e,
	0xd9, 0x93, 0xab, 0xd6, 0x24, 0x2f, 0x6a, 0x3a, 0x22, 0xb1, 0x4f, 0xaa, 0x23, 0x48, 0xed, 0xb9,
	0x88, 0x8b, 0xa3, 0x6b, 0x26, 0x4c, 0xe8, 0x2d, 0x1c, 0x99, 0xbd, 0x5c, 0x58, 0x08, 0x50, 0xf2,
	0x2a, 0x62, 0xc1, 0x72, 0x66, 0x04, 0x10, 0x37, 0x6e, 0xfc, 0x44, 0xa9, 0xdf, 0xd4, 0x20, 0xdd,
	0xee, 0x41, 0xdb, 0x73, 0xde, 0x54, 0xec, 0xc9, 0xf3, 0x4b, 0x2e, 0xae, 0x5a, 0x4a, 0x5e, 0x47,
	0x07, 0x2b, 0x76, 0xa4, 0xe3, 0x28, 0xfe, 0xb0, 0xf0, 0x02, 0x06, 0xd1, 0xaf, 0x42, 0xc2, 0xa5,
	0xe0, 0x67, 0xbf, 0x16, 0x8e, 0x35, 0xce, 0x8a, 0xe5, 0x3d, 0x7b, 0x96, 0xd7, 0x79, 0x52, 0x1e,
	0xa1, 0xfb, 0x9b, 0xbe, 0x21, 0x9c, 0xe9, 0x56, 0x14, 0x7f, 0xa0, 0xe4, 0xc3, 0xc4, 0x46, 0xea,
	0xf7, 0xd2, 0x1d, 0x31, 0x0a, 0x5f, 0xeb, 0xa2, 0x68, 0x8d, 0xb5, 0xc5, 0x74, 0x0c, 0xdc, 0x82,
	0x80, 0x09, 0x19, 0x95, 0x71, 0x9a, 0x11, 0x57, 0x77, 0x4e, 0xc6, 0xff, 0x12, 0x03, 0xa7, 0xc7,
	0xf4, 0xc8, 0xb6, 0x7a, 0x59, 0x36, 0x3c, 0x53, 0xe2, 0x69, 0x8c, 0x25, 0x05, 0x45, 0x63, 0xf8,
	0x34, 0x89, 0x33, 0x3f, 0x85, 0x27, 0xbc, 0x65, 0xfa, 0xa8, 0x6d, 0x84, 0x5d, 0xba, 0x40, 0x32,
	0x30, 0xef, 0x83, 0x13, 0xa6, 0x78, 0xcc, 0x81, 0x9e, 0xda, 0xca, 0xd3, 0x7e, 0x9d, 0x6f, 0xcd,
	0xb7, 0xb3, 0xd8, 0xcf, 0x3b, 0x00, 0x92, 0xb8, 0x86, 0xac, 0x49, 0x7c, 0xf1, 0xd5, 0xcb, 0x7d,
};

static const unsigned char address_0_7_xor[256] = {
	0x74, 0xad, 0x5d, 0x1d, 0x9e, 0xc3, 0xfa, 0x4e, 0xf7, 0xdb, 0xca, 0xa2, 0x64, 0x36, 0x56, 0x0c,
	0x4f, 0xcf, 0x43, 0x66, 0x1e, 0x91, 0xe3, 0xa5, 0x58, 0xc2, 0xc1, 0xd4, 0xb9, 0xdd, 0x76, 0x16,
	0xce, 0x61, 0x75, 0x01, 0x2b, 0x22, 0x38, 0x55, 0x50, 0xef, 0x6c, 0x99, 0x05, 0xe9, 0xe8, 0xe0,
	0x2d, 0xa4, 0x4b, 0x4a, 0x42, 0xae, 0xba, 0x8c, 0x6f, 0x93, 0x14, 0xbd, 0x71, 0x21, 0xb0, 0x02,
	0x15, 0xc4, 0xe6, 0x60, 0xd7, 0x44, 0xfd, 0x85, 0x7e, 0x78, 0x8f, 0x00, 0x81, 0xf1, 0xa7, 0x3b,
	0xa0, 0x10, 0xf4, 0x9f, 0x39, 0x88, 0x35, 0x62, 0xcb, 0x19, 0x31, 0x11, 0x51, 0xfb, 0x2a, 0x20,
	0x45, 0xd3, 0x7d, 0x92, 0x1b, 0xf2, 0x09, 0x0d, 0x97, 0xa9, 0xb5, 0x3c, 0xee, 0x5c, 0xaf, 0x7b,
	0xd2, 0x3a, 0x49, 0x8e, 0xb6, 0xcd, 0xd9, 0xde, 0x8a, 0x29, 0x6e, 0xd8, 0x0b, 0xe1, 0x69, 0x87,
	0x1a, 0x96, 0x18, 0xcc, 0xdf, 0xe7, 0xc5, 0xc7, 0xf8, 0x52, 0xc9, 0xf0, 0xb7, 0xe5, 0x33, 0xda,
	0x67, 0x9d, 0xa3, 0x03, 0x0e, 0x72, 0x26, 0x79, 0xe2, 0xb8, 0xfc, 0xaa, 0xfe, 0xb4, 0x86, 0xc8,
	0xd1, 0xbc, 0x12, 0x08, 0x77, 0xeb, 0x40, 0x8d, 0x04, 0x25, 0x4d, 0x5a, 0x6a, 0x7a, 0x2e, 0x41,
	0x65, 0x1c, 0x13, 0x94, 0xb2, 0x63, 0x28, 0x59, 0x5e, 0x9a, 0x30, 0x07, 0xc6, 0xbf, 0x17, 0xf5,
	0x0f, 0x89, 0xf3, 0x1f, 0xea, 0x6d, 0xb3, 0xc0, 0x70, 0x47, 0xf9, 0x53, 0xf6, 0xd6, 0x54, 0xed,
	0x6b, 0x4c, 0xe4, 0x8b, 0x83, 0x24, 0x90, 0xb1, 0x7c, 0xbb, 0x73, 0xab, 0xd5, 0x2f, 0x5f, 0xec,
	0x9c, 0x2c, 0xa8, 0x34, 0x46, 0x37, 0x27, 0xa1, 0x0a, 0x06, 0x80, 0x68, 0x82, 0x32, 0x84, 0xff,
	0x48, 0xac, 0x7f, 0x3f, 0x95, 0xdc, 0x98, 0x9b, 0xbe, 0x23, 0x57, 0x3e, 0x5b, 0xd0, 0x3d, 0xa6,
};

static void decrypt(unsigned char *r0, unsigned char *r1,
					unsigned char c0,  unsigned char c1,
					const unsigned char *table0hi,
					const unsigned char *table0lo,
					const unsigned char *table1,
					int base,
					int invert)
{
	unsigned char tmp, xor0, xor1;

	tmp = table1[(base & 0xff) ^ address_0_7_xor[(base >> 8) & 0xff]];
	xor0 = (table0hi[(base >> 8) & 0xff] & 0xfe) | (tmp & 0x01);
	xor1 = (tmp & 0xfe) | (table0lo[(base >> 8) & 0xff] & 0x01);

	if (invert)
	{
		*r0 = c1 ^ xor0;
		*r1 = c0 ^ xor1;
	}
	else
	{
		*r0 = c0 ^ xor0;
		*r1 = c1 ^ xor1;
	}
}

static void gfx_decrypt(unsigned char* rom, unsigned int rom_size, int extra_xor)
{
	int rpos;
	unsigned char * buf = (unsigned char *)malloc(rom_size);

	for (rpos = 0; rpos < rom_size/4; rpos++)
	{
		decrypt(&buf[4*rpos+0], &buf[4*rpos+3], rom[4*rpos+0], rom[4*rpos+3], type0_t03, type0_t12, type1_t03, rpos, (rpos>>8) & 1);
		decrypt(&buf[4*rpos+1], &buf[4*rpos+2], rom[4*rpos+1], rom[4*rpos+2], type0_t12, type0_t03, type1_t12, rpos, ((rpos>>16) ^ address_16_23_xor2[(rpos>>8) & 0xff]) & 1);
	}

	for (rpos = 0; rpos < rom_size/4; rpos++)
	{
		int baser = rpos;

		baser ^= extra_xor;
		baser ^= address_8_15_xor1[(baser >> 16) & 0xff] << 8;
		baser ^= address_8_15_xor2[baser & 0xff] << 8;
		baser ^= address_16_23_xor1[baser & 0xff] << 16;
		baser ^= address_16_23_xor2[(baser >> 8) & 0xff] << 16;
		baser ^= address_0_7_xor[(baser >> 8) & 0xff];
		baser &= (rom_size/4)-1;

		rom[4*rpos+0] = buf[4*baser+0];
		rom[4*rpos+1] = buf[4*baser+1];
		rom[4*rpos+2] = buf[4*baser+2];
		rom[4*rpos+3] = buf[4*baser+3];
	}
}

static int build_sprites()
{
	int i;
	unsigned char *gfx = (unsigned char*)malloc(0x1000000);

	loadrom(gfx + 0, 2, "070-c1.c1");
	loadrom(gfx + 1, 2, "070-c2.c2");

	gfx_decrypt(gfx, 0x1000000, 0xbd);

	// extract fix
	{
		unsigned char *src = gfx + 0x1000000 - 0x20000;
		unsigned char *dst = (unsigned char*)malloc(0x20000);

		for (i = 0; i < 0x20000; i++)
		{
			dst[i] = src[(i & ~0x1f) + ((i & 7) << 2) + ((~i & 8) >> 2) + ((i & 0x10) >> 4)];
		}
		
		FILE *s1 = fopen("FIX.FIX", "wb");
		fwrite (dst, 0x20000, 1, s1);
		fclose (s1);

		free (dst);
	}

	{
		unsigned char tmp[4];

		for (i = 0; i < 0x400000; i+=4)
		{
			tmp[0] = gfx[i+2];
			tmp[1] = gfx[i+0];
			tmp[2] = gfx[i+3];
			tmp[3] = gfx[i+1];
			memcpy (gfx + i, tmp, 4);
		}

		FILE *cx;

		cx = fopen("SPR.SPR", "wb");
		fwrite (gfx + 0x000000, 0x400000, 1, cx);
		fclose (cx);
	}

	free (gfx);

	return 0;
}

static void build_prog()
{
#define HSWAP(x)	(((x) << 16) | ((x) >> 16))

	int i;
	unsigned char *tmp = (unsigned char*)malloc(0x100000);
	memset (tmp,0xff,0x100000);
	
	unsigned short *rom16 = (unsigned short*)tmp;
	unsigned int *rom32 = (unsigned int*)tmp;
	
	loadrom(tmp, 1, "070-p1.p1");
	
	rom16[0x80290/2] = 0x4e71; // aes patch
	// irq swap
	
	rom32[0x00000/4] = HSWAP(0x10f300);
	rom32[0x00004/4] = HSWAP(0xc00402);
	rom32[0x00008/4] = HSWAP(0xc00408);
	rom32[0x0000c/4] = HSWAP(0xc0040e);
	rom32[0x00010/4] = HSWAP(0xc00414);
	rom32[0x00014/4] = HSWAP(0xc00426);
	rom32[0x00018/4] = HSWAP(0xc00426);
	rom32[0x0001c/4] = HSWAP(0xc00426);
	rom32[0x0001e/4] = HSWAP(0xc00426);
	rom32[0x00020/4] = HSWAP(0xc0041a);
	rom32[0x00024/4] = HSWAP(0xc00420);
	rom32[0x00028/4] = HSWAP(0xc00426);
	rom32[0x0002c/4] = HSWAP(0xc00426);
	rom32[0x00030/4] = HSWAP(0xc00426);
	rom32[0x00034/4] = HSWAP(0xc00426);
	rom32[0x00038/4] = HSWAP(0xc00426);
	rom32[0x0003c/4] = HSWAP(0xc0042c);
	rom32[0x00040/4] = HSWAP(0xc00522);
	rom32[0x00044/4] = HSWAP(0xc00528);
	rom32[0x00048/4] = HSWAP(0xc0052e);
	rom32[0x0004c/4] = HSWAP(0xc00534);
	rom32[0x00050/4] = HSWAP(0xc0053a);
	rom32[0x00054/4] = HSWAP(0xc004f2);
	rom32[0x00058/4] = HSWAP(0xc004ec);
	rom32[0x0005c/4] = HSWAP(0xc004e6);
	rom32[0x00060/4] = HSWAP(0xc004e0);

	unsigned int t = rom32[0x00064/4];
	rom32[0x00064/4] = rom32[0x00068/4];
	rom32[0x00068/4] = t;
	rom32[0x0006c/4] = t;

	rom32[0x00070/4] = HSWAP(0xc00426);
	rom32[0x00072/4] = HSWAP(0xc00426);
	rom32[0x00078/4] = HSWAP(0xc00426);
	rom32[0x0007c/4] = HSWAP(0xc00426);

	tmp[0x106] = 0;
	rom16[0x13a/2] = 0xffff;

	for (i = 0; i < 0x90000/2; i++)
	{
		rom16[i] = (rom16[i] << 8) | (rom16[i] >> 8);
	}
	
	FILE *fa = fopen("PRG.PRG", "wb");
	fwrite (tmp, 0x90000, 1, fa);
	fclose (fa);

	free (tmp);	
}

int main()
{
	build_prog();
	build_sprites();
}
