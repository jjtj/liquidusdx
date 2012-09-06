#pragma once

using namespace Microsoft::WRL;

HRESULT dxutils_create_bitmap(ID2D1DeviceContext* ctx,
                              int w, 
                              int h, 
                              ID2D1Bitmap1** bmp);