#include "pch.h"


HRESULT dxutils_create_bitmap(ID2D1DeviceContext* ctx,
							  int w, 
							  int h, 
							  ID2D1Bitmap1** bmp)
{
	D2D1_BITMAP_PROPERTIES1 p = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET,
		D2D1::PixelFormat(DXGI_FORMAT_A8_UNORM,
						  D2D1_ALPHA_MODE_PREMULTIPLIED));
	D2D1_SIZE_U sz = D2D1::SizeU(
		(UINT32)w,
		(UINT32)h);

	return ctx->CreateBitmap(
			sz,
			nullptr,
			0,
			&p,
			bmp
		);
}

