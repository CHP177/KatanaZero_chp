#include "stdafx.h"
#include "Path.h"

bool Path::ExistFile(const string& path)
{
	//파일 존재여부 반환
	return ExistFile(String::ToWString(path));
}

bool Path::ExistFile(const wstring& path)
{
	//파일 존재여부 반환
	DWORD fileValue = GetFileAttributes(path.c_str());
	return fileValue < 0xFFFFFFFF;
}

bool Path::ExistDirectory(const string& path)
{
	//경로 존재여부 반환
	return ExistDirectory(String::ToWString(path));
}

bool Path::ExistDirectory(const wstring& path)
{
	//경로 존재여부 반환
	DWORD attribute = GetFileAttributes(path.c_str());
	return attribute != INVALID_FILE_ATTRIBUTES && (attribute & FILE_ATTRIBUTE_DIRECTORY);
}

string Path::Combine(const vector<string>& paths)
{
	//경로 배열을 하나로 합치기
	string temp = "";
	for (const string path : paths)
		temp += path;

	return temp;
}

wstring Path::Combine(const vector<wstring>& paths)
{
	//경로 배열을 하나로 합치기
	wstring temp = L"";
	for (const wstring path : paths)
		temp += path;

	return temp;
}

string Path::GetDirectoryName(string path)
{
	//파일명을 제외한 경로 반환
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	//파일명을 제외한 경로 반환
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

string Path::GetExtension(string path)
{
	//확장자 반환
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1);
}

wstring Path::GetExtension(wstring path)
{
	//확장자 반환
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1);
}

string Path::GetFileName(string path)
{
	//확장자 포함 파일명 반환
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1);
}

wstring Path::GetFileName(wstring path)
{
	//확장자 포함한 파일명 반환
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1);
}

string Path::GetFileNameWithoutExtension(const string& path)
{
	//확장자 제외한 파일명 반환
	string fileName = GetFileName(path);
	size_t index = fileName.find_last_of('.');

	return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(const wstring& path)
{
	//확장자 제외한 파일명 반환
	wstring fileName = GetFileName(path);
	size_t index = fileName.find_last_of('.');

	return fileName.substr(0, index);
}

const WCHAR* Path::ImageFilter = L"Image (*.png; *.bmp; *.jpg;)\0*.png;*.bmp;*.jpg";
const WCHAR* Path::ShaderFilter = L"HLSL File (*.hlsl;)\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text File (*.txt;)\0*.txt";
const WCHAR* Path::SoundFilter = L"Sound File (*.mp3;*.wav;*.flac;)\0*.mp3;*.wav;*.flac;";
const WCHAR* Path::MapFilter = L"Map File (*.map)\0*.map";

void Path::OpenFileDialog(const wstring& file, const WCHAR* filter, const wstring& folder, function<void(wstring)>& func, const HWND& hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrTitle = L"불러오기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != nullptr)
		{
#pragma warning(disable : 6054)
			wstring loadName = name;
			String::Replace(loadName, L"\\", L"/");
			func(loadName);
#pragma warning(default : 6054)
		}
	}
}

void Path::SaveFileDialog(const wstring& file, const WCHAR* filter, const wstring& folder, function<void(wstring)>& func, const HWND& hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrTitle = L"저장하기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;
	if (filter == TextFilter) //필터에 따라 기본 확장자를 지정해줄 수 있음(ex. text파일(*.txt) 등)
		ofn.lpstrDefExt = L".txt";
	else if (filter == ShaderFilter)
		ofn.lpstrDefExt = L".hlsl";
	else if (filter == MapFilter)
		ofn.lpstrDefExt = L".tile";

	if (GetSaveFileName(&ofn) == TRUE)
	{
		if (func != nullptr)
		{
#pragma warning(disable : 6054)
			wstring saveName = name;
			String::Replace(saveName, L"\\", L"/");
			func(saveName);
#pragma warning(default : 6054)
		}
	}
}

void Path::GetFiles(vector<string>& files, const string& path, const string& filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = String::ToWString(path);
	wstring wFilter = String::ToWString(filter);

	GetFiles(wFiles, wPath, wFilter, bFindSubFolder);
	for (const auto& str : wFiles)
		files.push_back(String::ToString(str));
}

void Path::GetFiles(vector<wstring>& files, const wstring& path, const wstring& filter, bool bFindSubFolder)
{
	wstring file = path + filter;

	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(file.c_str(), &findData);
	if (handle != INVALID_HANDLE_VALUE) //
	{
		do
		{
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					wstring folder = path + wstring(findData.cFileName) + L"/";
					GetFiles(files, folder, filter, bFindSubFolder);
				}
			}
			else
			{
				wstring fileName = path + wstring(findData.cFileName);
				files.push_back(fileName);
			}
		} while (FindNextFile(handle, &findData));
	}
}

void Path::CreateFolder(const string& path)
{
	CreateFolder(String::ToWString(path));
}

void Path::CreateFolder(const wstring& path)
{
	if (!ExistDirectory(path))
		CreateDirectory(path.c_str(), nullptr);
}

void Path::CreateFolders(const string& path)
{
	CreateFolders(String::ToWString(path));
}

void Path::CreateFolders(wstring path)
{
	String::Replace(path, L"\\", L"/");

	vector<wstring> folders;
	String::SplitString(folders, path, L"/");

	wstring temp = L"";
	for (wstring folder : folders)
	{
		temp += folder + L"/";
		CreateFolder(temp);
	}
}
