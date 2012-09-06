#include "pch.h"
#include "AppResource.h"

using namespace concurrency;
using namespace Windows::Data::Json;
using namespace Platform;

task<Platform::String^> AppResource::ReadTextFile(const wchar_t* path)
{
	auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;
	auto pathString = ref new String(path);

	task<Windows::Storage::StorageFile^> getFileTask(folder->GetFileAsync(pathString));
	auto t2 = getFileTask.then([&](Windows::Storage::StorageFile^ file) {
		return Windows::Storage::FileIO::ReadTextAsync(file);
	}).then([&](String^ value) {
		return value;
	});

	return t2;
}