#pragma once
#include "CommonInclude.h"
#include "wiGraphicsDevice.h"

#include <string>
#include <vector>

namespace wiHelper
{
	template <class T>
	inline void hash_combine(std::size_t& seed, const T& v)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	// Simple binary reader utility
	struct DataBlob
	{
		char* DATA;
		size_t dataSize;
		size_t dataPos;

		DataBlob(const std::string& fileName = "");
		~DataBlob();

		template<typename T>
		void read(T& data)
		{
			assert(DATA != nullptr);
			assert(dataPos - (size_t)DATA < dataSize);
			memcpy(&data, reinterpret_cast<void*>(dataPos), sizeof(T));
			dataPos += sizeof(T);
		}
	};

	std::string toUpper(const std::string& s);

	bool readByteData(const std::string& fileName, std::vector<uint8_t>& data);

	void messageBox(const std::string& msg, const std::string& caption = "Warning!");

	void screenshot(const std::string& name = "");

	bool saveTextureToFile(wiGraphics::Texture2D& texture, const std::string& fileName);

	bool saveTextureToFile(const std::vector<uint8_t>& textureData, const wiGraphics::TextureDesc& desc, const std::string& fileName);

	std::string getCurrentDateTimeAsString();

	std::string GetApplicationDirectory();

	std::string GetOriginalWorkingDirectory();

	std::string GetWorkingDirectory();

	bool SetWorkingDirectory(const std::string& path);

	void GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory);

	void SplitPath(const std::string& fullPath, std::string& dir, std::string& fileName);

	std::string GetFileNameFromPath(const std::string& fullPath);

	std::string GetDirectoryFromPath(const std::string& fullPath);

	std::string GetExtensionFromFileName(const std::string& filename);

	void RemoveExtensionFromFileName(std::string& filename);

	bool FileExists(const std::string& fileName);

	void StringConvert(const std::string from, std::wstring& to);

	void StringConvert(const std::wstring from, std::string& to);

	// Puts the current thread to sleeping state for a given time (OS can overtake)
	void Sleep(float milliseconds);

	// Spins for the given time and does nothing (OS can not overtake)
	void Spin(float milliseconds);
};
