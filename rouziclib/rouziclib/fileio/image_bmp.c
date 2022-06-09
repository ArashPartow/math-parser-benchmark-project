void save_raster_bmp(char *path, raster_t im)
{
	FILE *f;
	int32_t	i, iy, ix;			// various iterators
	int32_t	filesize, imagesize;
	uint8_t	zerobytes, val, zero=0;
	srgb_t pv;

	f = fopen_utf8(path, "wb");
	if (f==NULL)
	{
		fprintf_rl(stderr, "Couldn't open \"%s\" for writing in save_raster_bmp()\n", path);
		return ;
	}

	zerobytes = (4 - ((im.dim.x*3) & 3)) & 3;		// computation of zero bytes which pads lines so they're 4 byte-aligned

	//********Tags********

	filesize = 56 + ((im.dim.x*3)+zerobytes) * im.dim.y;
	imagesize = 2 + ((im.dim.x*3)+zerobytes) * im.dim.y;

	fwrite_LE16(f, 19778);
	fwrite_LE32(f, filesize);
	fwrite_LE32(f, 0);
	fwrite_LE32(f, 54);
	fwrite_LE32(f, 40);
	fwrite_LE32(f, im.dim.x);
	fwrite_LE32(f, im.dim.y);
	fwrite_LE16(f, 1);
	fwrite_LE32(f, 24);
	fwrite_LE16(f, 0);
	fwrite_LE32(f, imagesize);
	fwrite_LE32(f, 2834);
	fwrite_LE32(f, 2834);
	fwrite_LE32(f, 0);
	fwrite_LE32(f, 0);
	//--------Tags--------

	for (iy=im.dim.y-1; iy >= 0; iy--)		// backwards writing
	{
		for (ix=0; ix < im.dim.x; ix++)
		{
			pv = get_raster_pixel_in_srgb(im, iy*im.dim.x + ix);

			fwrite(&pv.r, 1, 1, f);
			fwrite(&pv.g, 1, 1, f);
			fwrite(&pv.b, 1, 1, f);
		}

		for (i=0; i < zerobytes; i++)
			fwrite(&zero, 1, 1, f);	// write padding bytes
	}

	fwrite_LE16(f, 0);

	fclose(f);
}
