#ifdef RL_DEVIL

raster_t load_image_mem_libdevil(ILubyte *raw_data, ILuint size, const int mode)
{
	ILboolean err;
	ILuint ImgId;
	int32_t bpp, format;
	raster_t im={0};

	if (raw_data==NULL || size==0)
	return make_raster_empty();

	// Initialize DevIL.
	ilInit();
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
	ilEnable(IL_ORIGIN_SET);

	ilGenImages(1, &ImgId);		// Generate the main image name to use.
	ilBindImage(ImgId);		// Bind this image name.

	if (!ilLoadL(IL_TYPE_UNKNOWN, raw_data, size))
	{
		fprintf_rl(stderr, "Could not open image from the %d byte buffer in memory\n", size);
		return make_raster_empty();
	}
 
	im.dim.x = ilGetInteger(IL_IMAGE_WIDTH);
	im.dim.y = ilGetInteger(IL_IMAGE_HEIGHT);
	bpp = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	format = ilGetInteger(IL_IMAGE_FORMAT);

	err = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);	// TODO decide of IL_FLOAT conversion depending on bpp/format

	convert_image_srgb8(&im, ilGetData(), mode);		// fills all the necessary buffers with the image data

	ilDeleteImages(1, &ImgId);

	return im;
}

#endif
