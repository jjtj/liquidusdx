#pragma once

class AppResource
{
public:
	static concurrency::task<Platform::String^> ReadTextFile(const wchar_t* path);
};