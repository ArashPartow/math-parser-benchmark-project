#ifdef RL_OPENCV

void convert_cvimage_to_raster(IplImage *frame, raster_t *image, const int mode)
{
	int32_t i, ic;
	uint8_t *ps0, *ps1;

	if (frame==NULL)		return ;
	if (frame->imageData==NULL)	return ;

	if (image->dim.x != frame->width || image->dim.y != frame->height)
	{
		image->dim.x = frame->width;
		image->dim.y = frame->height;

		free (image->srgb);
		image->srgb = calloc(image->dim.x*image->dim.y, sizeof(srgb_t));
	}

	for (i=0; i < image->dim.x*image->dim.y; i++)
	{
		ps0 = &frame->imageData[i*3];
		ps1 = &image->srgb[i];

		for (ic=0; ic<3; ic++)
			ps1[ic] = ps0[2-ic];
	}

	convert_image_srgb8(image, image->srgb, mode);		// fills all the necessary buffers with the image data
}

void convert_srgb_to_cvimage(raster_t *image, IplImage *frame)
{
	int32_t ix, iy, ic;
	uint8_t *ps0, *ps1;

	for (iy=0; iy<image->dim.y; iy++)
		for (ix=0; ix<image->dim.x; ix++)
		{
			ps0 = &image->srgb[iy*image->dim.x+ix];
			ps1 = &frame->imageData[(iy*image->dim.x+ix)*3];

			for (ic=0; ic<3; ic++)
				ps1[ic] = ps0[ic];
		}
}

int get_webcam_frame(raster_t *image, char *debug_str, const int mode)
{
	static CvCapture *capture;
	IplImage *frame;
	static int init=1;
	raster_t im_local={0};

	if (init)
	{
		init = 0;

		capture = cvCreateCameraCapture(0);
		if (capture==NULL)
			return 0;

		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 1280.);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 960.);
	}

	frame = cvQueryFrame(capture);

	if (image==NULL)
		image = &im_local;

	convert_cvimage_to_raster(frame, image, mode);

	if (debug_str)
		sprintf(debug_str, "%gx%g, %.3g FPS, %g, %g", 
				cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH), 
				cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT),
				cvGetCaptureProperty(capture, CV_CAP_PROP_FPS),
				cvGetCaptureProperty(capture, CV_CAP_PROP_GAIN),
				cvGetCaptureProperty(capture, CV_CAP_PROP_EXPOSURE),
				0);

	//cvReleaseCapture(&capture);

	return 1;
}

int get_video_frame(raster_t *image, char *path, const int mode)
{
	static CvCapture *capture;
	IplImage *frame;
	static int init=1;

	if (init)
	{
		init = 0;

		capture = cvCaptureFromFile(path);
		if (capture==NULL)
			return 0;
	}

	frame = cvQueryFrame(capture);

	convert_cvimage_to_raster(frame, image, mode);

	//cvReleaseCapture(&capture);		// TODO close it at some point

	return 1;
}

void write_video_frame(raster_t *image, char *path, double fps, int action)	// FIXME can only handle one video file at a time
{
	static CvVideoWriter *writer=NULL;
	static IplImage *frame=NULL;
return ;

	if (action==0 && path)		// initiate new file
	{
		if (writer)
		{
			cvReleaseVideoWriter(writer);
			cvReleaseImage(frame);
		}

		writer = cvCreateVideoWriter(path, CV_FOURCC('X','V','I','D'), fps, cvSize(image->dim.x, image->dim.y), 1);
		frame = cvCreateImage(cvSize(image->dim.x, image->dim.y), IPL_DEPTH_8U, 3);
	}

	if (action==2 && writer)	// close and clean up
	{
			cvReleaseImage(frame);	// FIXME crashes
			frame = NULL;

			cvReleaseVideoWriter(writer);
			writer = NULL;
	}

	if (action==1 && writer)
	{
		convert_srgb_to_cvimage(image, frame);
		cvWriteFrame(writer, frame);
	}
}

#endif
