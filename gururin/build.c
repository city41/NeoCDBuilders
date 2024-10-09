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

	return length;
}

static int build_s1()
{
	int i;
	unsigned char *tmp = (unsigned char*)malloc(0x20000);
	
	loadrom(tmp, 1, "067-s1.S1");

	FILE *fa = fopen("FIX.FIX", "wb");
	fwrite (tmp, 0x20000, 1, fa);
	fclose (fa);

	free (tmp);
	
	return 0;
}

static int build_v1()
{
	int i;
	unsigned char *tmp = (unsigned char*)malloc(0x80000);
	
	loadrom(tmp, 1, "067-v1.v1");

	FILE *fa = fopen("PCM.PCM", "wb");
	fwrite (tmp, 0x80000, 1, fa);
	fclose (fa);

	free (tmp);
	
	return 0;
}

static int build_m1()
{
	int i;
	unsigned char *tmp = (unsigned char*)malloc(0x20000);
	
	loadrom(tmp, 1, "067-m1.m1");

	FILE *fa = fopen("Z80.Z80", "wb");
	fwrite (tmp, 0xb000, 1, fa);
	fclose (fa);

	free (tmp);
	
	return 0;
}

static int build_sprites()
{
	int i;
	unsigned char *gfx = (unsigned char*)malloc(0x400000);

	loadrom(gfx + 0, 2, "067-c1.c1");
	loadrom(gfx + 1, 2, "067-c2.c2");

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

		cx = fopen("SPR1.SPR", "wb");
		fwrite (gfx + 0x080000, 0x034000, 1, cx);
		fclose (cx);

		cx = fopen("SPR2.SPR", "wb");
		fwrite (gfx + 0x100000, 0x04a000, 1, cx);
		fclose (cx);

		cx = fopen("SPR3.SPR", "wb");
		fwrite (gfx + 0x180000, 0x080000, 1, cx);
		fclose (cx);

		cx = fopen("SPR4.SPR", "wb");
		fwrite (gfx + 0x200000, 0x068000, 1, cx);
		fclose (cx);

		cx = fopen("SPR5.SPR", "wb");
		fwrite (gfx + 0x280000, 0x06e000, 1, cx);
		fclose (cx);

		cx = fopen("SPR6.SPR", "wb");
		fwrite (gfx + 0x300000, 0x05c000, 1, cx);
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
	
	loadrom(tmp, 1, "067-p1.p1");
	
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

	for (i = 0; i < 0x100000/2; i++)
	{
		rom16[i] = (rom16[i] << 8) | (rom16[i] >> 8);
	}
	
	FILE *fa = fopen("PRG.PRG", "wb");
	fwrite (tmp, 0x40000, 1, fa);
	fclose (fa);

	free (tmp);	
}

int main()
{
	build_prog();
	build_sprites();
	build_m1();
	build_v1();
	build_s1();
}
