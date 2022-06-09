void win_reorder_screenshot_pixels(raster_t r)
{
	xyi_t ip;
	int i, invy;
	srgb_t p;

	// Swap channels
	for (i=0; i < mul_x_by_y_xyi(r.dim); i++)
	{
		p = r.srgb[i];

		r.srgb[i].r = p.b;
		r.srgb[i].b = p.r;
	}

	// Flip image upside down
	for (ip.y=0; ip.y < r.dim.y>>1; ip.y++)
	{
		invy = r.dim.y - 1 - ip.y;

		for (ip.x=0; ip.x < r.dim.x; ip.x++)
		{
			p = r.srgb[ip.y*r.dim.x + ip.x];
			r.srgb[ip.y*r.dim.x + ip.x] = r.srgb[invy*r.dim.x + ip.x];
			r.srgb[invy*r.dim.x + ip.x] = p;
		}
	}
}

#ifdef _WIN32
#ifdef RL_GDI32
#include <wingdi.h>
#include <WinUser.h>
#endif
#endif

raster_t take_desktop_screenshot()
{
	raster_t r={0};

#ifdef _WIN32
#ifdef RL_GDI32
	// Capture the primary display
	int nScreenWidth = GetSystemMetrics(0 /*SM_CXSCREEN*/);
	int nScreenHeight = GetSystemMetrics(1 /*SM_CYSCREEN*/);
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetDC(hDesktopWnd);
	HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, nScreenWidth, nScreenHeight);
	SelectObject(hCaptureDC, hCaptureBitmap);
	BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hDesktopDC, 0, 0, (DWORD)0x00CC0020 /*SRCCOPY*/ | (DWORD)0x40000000 /*CAPTUREBLT*/);	// this does the capture

	// Convert the bitmap to a raster
	r = make_raster(NULL, xyi(nScreenWidth, nScreenHeight), XYI0, IMAGE_USE_SRGB);

	BITMAPINFO bmi = {0};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = nScreenWidth;
	bmi.bmiHeader.biHeight = nScreenHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	GetDIBits(hCaptureDC, hCaptureBitmap, 0, nScreenHeight, r.srgb, &bmi, DIB_RGB_COLORS);

	win_reorder_screenshot_pixels(r);

	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);
	DeleteObject(hCaptureBitmap);
#endif
#endif

	return r;
}
