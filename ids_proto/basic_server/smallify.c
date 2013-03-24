#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE* fin = fopen(argv[1],"r");
	unsigned char image[480][640][3];
	unsigned char out[240][320][3];
	int x,y,c;

	fseek(fin, 54, SEEK_SET);
	fread(image, 640*480*3, 1, fin);
	fclose(fin);

	for(y = 0; y < 240; y+= 1)
	{
		for(x = 0; x < 320; x += 1)
		{
			for(c = 0; c < 3; c++)
			{
				out[y][x][c] = image[y*2][x*2][c];
			}
		}
	}

	FILE* fout = fopen(argv[2],"w");

	fwrite(out,sizeof out, 1, fout);
	fclose(fout);
}
