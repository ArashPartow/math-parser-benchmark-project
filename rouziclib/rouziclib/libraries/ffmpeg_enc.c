#ifdef RL_FFMPEG

ff_videnc_t ff_video_enc_init_file(const char *path, xyi_t dim, double fps, int codec_id, int bit_depth, int crf)	// codec can be AV_CODEC_ID_H265
{
	int ret;
	AVOutputFormat *fmt;
	AVCodec *codec;
	AVDictionary *fmt_opts=NULL;
	ff_videnc_t d={0};
	char str[32];

	// Alloc context
	d.fmt_ctx = avformat_alloc_context();
	if (d.fmt_ctx==NULL)
	{
		fprintf_rl(stderr, "avformat_alloc_context() failed in ff_video_enc_init_file()\n");
		return d;
	}

	// Init encoding format
	fmt = av_guess_format(NULL, path, NULL);
	if (fmt==NULL)
	{
		fprintf_rl(stderr, "Could not guess output format from file extension in ff_video_enc_init_file(), using MPEG4\n");
		fmt = av_guess_format("mpeg4", NULL, NULL);
	}

	// Set format header infos
	d.fmt_ctx->oformat = fmt;
	snprintf(d.fmt_ctx->filename, sizeof(d.fmt_ctx->filename), "%s", path);

	// Set format's private options to be passed to avformat_write_header()
	ret = av_dict_set(&fmt_opts, "movflags", "faststart", 0);
	codec = avcodec_find_encoder(codec_id);
	//if (codec_id==AV_CODEC_ID_H264)
	//	codec = avcodec_find_encoder_by_name("h264_nvenc");
	if (codec==NULL)
	{
		fprintf_rl(stderr, "avcodec_find_encoder() failed in ff_video_enc_init_file()\n");
		return d;
	}

	// Create stream
	d.st = avformat_new_stream(d.fmt_ctx, codec);
	if (d.st==NULL)
	{
		fprintf_rl(stderr, "avformat_new_stream() failed in ff_video_enc_init_file()\n");
		return d;
	}

	if (fabs(fps - 23.976) < 0.01 || fabs(fps - 29.97) < 0.01 || fabs(fps - 59.94) < 0.01 || fabs(fps - 119.88) < 0.01)
		d.st->time_base = (AVRational) {1001, nearbyint(fps*1001.)};
	else
		d.st->time_base = (AVRational) {1, nearbyint(fps)};

	// Set codec parameters
	d.codec_ctx = d.st->codec;
	d.codec_ctx->sample_fmt = codec->sample_fmts ?  codec->sample_fmts[0] : AV_SAMPLE_FMT_S16;
	d.codec_ctx->width = dim.x;
	d.codec_ctx->height = dim.y;
	d.codec_ctx->time_base = d.st->time_base;
	switch (bit_depth)
	{
		case 10:
			d.codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P10LE;
			break;

		case 12:
			d.codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P12LE;
			break;

		default:
			d.codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
	}
	d.codec_ctx->gop_size = 60;

	// Encoder-specific options
	sprintf(str, "%d", crf);
	ret = av_opt_set(d.codec_ctx->priv_data, "crf", str, 0);
	ret = av_opt_set(d.codec_ctx->priv_data, "profile", bit_depth==10 ? "main10" : "main", 0);
	ret = av_opt_set(d.codec_ctx->priv_data, "preset", codec_id==AV_CODEC_ID_H265 ? "ultrafast" : "medium", 0);

	if (codec_id == AV_CODEC_ID_VP9)
	{
		d.codec_ctx->bit_rate = 0;
		av_opt_set(d.codec_ctx->priv_data, "deadline", "realtime", 0);
		av_opt_set(d.codec_ctx->priv_data, "cpu-used", "8", 0);
	}

	// Copy the stream params to the muxer
	ret = avcodec_parameters_from_context(d.st->codecpar, d.codec_ctx);

	// Open the codec
	ret = avcodec_open2(d.codec_ctx, codec, NULL);
	if (ret < 0)
	{
		ffmpeg_retval(ret);
		fprintf_rl(stderr, "avcodec_open2() failed in ff_video_enc_init_file()\n");
		return d;
	}

	//av_dump_format(d.fmt_ctx, 0, path, 1);	// debug info

	// Open file for writing
	ret = avio_open(&d.fmt_ctx->pb, path, AVIO_FLAG_WRITE);
	if (ret < 0)
	{
		ffmpeg_retval(ret);
		fprintf_rl(stderr, "avio_open() failed in ff_video_enc_init_file()\n");
		return d;
	}

	ret = avformat_write_header(d.fmt_ctx, &fmt_opts);

	// Create reusable frame
	d.frame = av_frame_alloc();
	av_frame_make_writable(d.frame);
	d.frame->format = d.codec_ctx->pix_fmt;
	d.frame->width  = d.codec_ctx->width;
	d.frame->height = d.codec_ctx->height;
	ret = av_image_alloc(d.frame->data, d.frame->linesize, d.codec_ctx->width, d.codec_ctx->height, d.codec_ctx->pix_fmt, 4);

	d.s16_buf = calloc(mul_x_by_y_xyi(dim) * 3, sizeof(uint16_t));

	return d;
}

void ff_convert_to_frame(void *buf, int buf_fmt, int bpp, AVFrame *frame)	// AV_PIX_FMT_0BGR32 for srgb_t
{
	static struct SwsContext *sws_ctx=NULL;

	if (frame==NULL)
	{
		fprintf_rl(stderr, "frame is NULL in ff_convert_to_frame()\n");
		return ;
	}

	int in_linesize[3] = { bpp * frame->width, bpp * frame->width >> 1, bpp * frame->width >> 1 };

	fprintf_rl(stderr, "TODO: implement conversion to YUV for ff_convert_to_frame()\n");
	/*sws_ctx = sws_getCachedContext( sws_ctx,
				 frame->width,
				 frame->height,
				 buf_fmt,
				 frame->width,
				 frame->height,
				 frame->format,
				 SWS_BILINEAR,
				 NULL,
				 NULL,
				 NULL );

	sws_scale(sws_ctx, (uint8_t **) &buf, in_linesize, 0, frame->height, frame->data, frame->linesize);*/
}

int ff_frgb_to_frame(ff_videnc_t *d, raster_t *r)
{
	xyi_t ip;
	int in_index, bpc, bit_depth;
	float y[4], u, v, int_ratio;

	if (r->f==NULL || (r->dim.x & 1) || (r->dim.y & 1) || d->frame->data==NULL)
		return 0;

	bpc = ff_pix_fmt_byte_count(d->codec_ctx->pix_fmt);
	bit_depth = ff_pix_fmt_bit_depth(d->codec_ctx->pix_fmt);
	int_ratio = 1 << (bit_depth-8);

	if (bpc==1)	// 8-bit YUV420P
	{
		uint8_t *line_y0, *line_y1, *line_u, *line_v;

		for (ip.y=0; ip.y < r->dim.y; ip.y+=2)
		{
			line_y0 = &d->frame->data[0][ip.y * d->frame->linesize[0]];
			line_y1 = &d->frame->data[0][(ip.y+1) * d->frame->linesize[0]];
			line_u = &d->frame->data[1][(ip.y>>1) * d->frame->linesize[1]];
			line_v = &d->frame->data[2][(ip.y>>1) * d->frame->linesize[2]];

			for (ip.x=0; ip.x < r->dim.x; ip.x+=2)
			{
				in_index = ip.y*r->dim.x + ip.x;
				frgb_2x2_to_yuv420(&r->f[in_index], &r->f[in_index+r->dim.x], y, &u, &v);

				line_y0[ip.x  ] = y[0] * int_ratio + 0.5f;
				line_y0[ip.x+1] = y[1] * int_ratio + 0.5f;
				line_y1[ip.x  ] = y[2] * int_ratio + 0.5f;
				line_y1[ip.x+1] = y[3] * int_ratio + 0.5f;
				line_u[ip.x>>1] = u * int_ratio + 0.5f;
				line_v[ip.x>>1] = v * int_ratio + 0.5f;


			}
		}
	}
	else if (bpc==2)	// 9 to 16-bit YUV420P
	{
		uint16_t *line_y0, *line_y1, *line_u, *line_v;

		for (ip.y=0; ip.y < r->dim.y; ip.y+=2)
		{
			line_y0 = (uint16_t *) &d->frame->data[0][ip.y * d->frame->linesize[0]];
			line_y1 = (uint16_t *) &d->frame->data[0][(ip.y+1) * d->frame->linesize[0]];
			line_u = (uint16_t *) &d->frame->data[1][(ip.y>>1) * d->frame->linesize[1]];
			line_v = (uint16_t *) &d->frame->data[2][(ip.y>>1) * d->frame->linesize[2]];

			for (ip.x=0; ip.x < r->dim.x; ip.x+=2)
			{
				in_index = ip.y*r->dim.x + ip.x;
				frgb_2x2_to_yuv420(&r->f[in_index], &r->f[in_index+r->dim.x], y, &u, &v);

				line_y0[ip.x  ] = y[0] * int_ratio + 0.5f;
				line_y0[ip.x+1] = y[1] * int_ratio + 0.5f;
				line_y1[ip.x  ] = y[2] * int_ratio + 0.5f;
				line_y1[ip.x+1] = y[3] * int_ratio + 0.5f;
				line_u[ip.x>>1] = u * int_ratio + 0.5f;
				line_v[ip.x>>1] = v * int_ratio + 0.5f;
			}
		}
	}

	return 1;
}

int ff_yuv_to_frame(ff_videnc_t *d, raster_t *r)
{
	int in_index, bpc, bit_depth;
	int iy, ip;
	uint8_t *plane[3];

	if (r->buf==NULL || (r->dim.x & 1) || (r->dim.y & 1) || d->frame->data==NULL)
		return 0;

	bpc = ff_pix_fmt_byte_count(d->codec_ctx->pix_fmt);
	bit_depth = ff_pix_fmt_bit_depth(d->codec_ctx->pix_fmt);

	if (ff_buf_fmt_to_pix_fmt(r->buf_fmt) == d->codec_ctx->pix_fmt)		// if the YUV formats are the same
	{
		plane[0] = r->buf;
		plane[1] = &plane[0][bpc * mul_x_by_y_xyi(r->dim)];
		plane[2] = &plane[1][bpc * mul_x_by_y_xyi(r->dim)/4];

		ip = 0;
		for (iy=0; iy < r->dim.y; iy++)
			memcpy(&d->frame->data[ip][iy*d->frame->linesize[ip]], &plane[ip][iy*r->dim.x * bpc], bpc * r->dim.x);

		for (ip=1; ip < 3; ip++)
			for (iy=0; iy < r->dim.y>>1; iy++)
				memcpy(&d->frame->data[ip][iy*d->frame->linesize[ip]], &plane[ip][iy*(r->dim.x>>1) * bpc], bpc * r->dim.x>>1);
	}
	else
		return 0;	// TODO convert between different YUV bit depths

	return 1;
}

int ff_video_enc_write_raster(ff_videnc_t *d, raster_t *r)
{
	int done=0;

	if (d->frame->data==NULL)
		return -1;

	if (ff_frgb_to_frame(d, r))		// try my own RGB to YUV conversion first
		done = 1;

	else if (ff_yuv_to_frame(d, r))		// try my own YUV copy
		done = 1;

	else if (r->buf)			// if r is YUV but ff_yuv_to_frame() didn't do it
		ff_convert_to_frame(r->buf, ff_buf_fmt_to_pix_fmt(r->buf_fmt), ff_pix_fmt_byte_count(ff_buf_fmt_to_pix_fmt(r->buf_fmt)), d->frame);

	else					// if r isn't YUV nor FRGB
	{
		convert_image_to_srgb16(r, d->s16_buf, get_raster_mode(*r), 3);		// convert r to 16-bit sRGB
		ff_convert_to_frame(d->s16_buf, AV_PIX_FMT_RGB48LE, 6, d->frame);	// convert 16-bit sRGB to YUV frame
	}

	return ff_video_enc_write_frame(d, d->frame);
}

int ff_video_enc_write_frame(ff_videnc_t *d, AVFrame *frame)
{
	int ret;
	AVPacket pkt={0};

	// Set frame pts, monotonically increasing, starting from 0
	if (frame)
		frame->pts = d->pts;	// Presentation timestamp in time_base units (time when frame should be shown to user)

	d->pts += d->st->time_base.num;

	// Submit frame for encoding
	ret = avcodec_send_frame(d->codec_ctx, frame);
	if (ret < 0)
	{
		ffmpeg_retval(ret);
		fprintf_rl(stderr, "avcodec_send_frame() failed in ff_video_enc_init_file()\n");
		return -1;
	}

	av_init_packet(&pkt);

	while (ret >= 0)
	{
		// Encode frame
		ret = avcodec_receive_packet(d->codec_ctx, &pkt);
		ffmpeg_retval(ret);
		if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
		{
			ffmpeg_retval(ret);
			fprintf_rl(stderr, "avcodec_receive_packet() failed in ff_video_enc_init_file()\n");
			return -1;
		}
		else if (ret >= 0)
		{
			av_packet_rescale_ts(&pkt, d->codec_ctx->time_base, d->st->time_base);
			pkt.stream_index = d->st->index;

			// Write the compressed frame to the file
			av_interleaved_write_frame(d->fmt_ctx, &pkt);
		}
	}

	av_packet_unref(&pkt);

	return ret == AVERROR_EOF;	// 0 on success
}

void ff_video_enc_finalise_file(ff_videnc_t *d)
{
	int ret=0;

	// Write pending packets
	while (ret == 0)
	{
		ret = ff_video_enc_write_frame(d, NULL);
	}

	av_write_trailer(d->fmt_ctx);
	avcodec_close(d->st->codec);
	avio_close(d->fmt_ctx->pb);

	avformat_free_context(d->fmt_ctx);
	av_freep(&d->frame->data[0]);
	av_frame_free(&d->frame);

	free_null(&d->s16_buf);

	memset(d, 0, sizeof(ff_videnc_t));
}

#endif
