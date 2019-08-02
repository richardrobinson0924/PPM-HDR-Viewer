//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <winsdkver.h>
#define _WIN32_WINNT 0x0601
#include <sdkddkver.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "opencv_world410d.lib")
#pragma comment(lib, "dxguid.lib")

// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif

#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <PostProcess.h>
#include <SimpleMath.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/directx.hpp>

#include "Utils.h"

#include <comdef.h>
#include <dxgidebug.h>

#include <stdio.h>
#include <vector>

#define NUMBER_OF_WINDOWS 1
//#define FULLSCREEN

// convenience typealiases

template <typename T>
using matrix = std::vector<std::vector<T>>;

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

namespace DX
{
	// Helper class for COM exceptions
	class com_exception : public std::exception
	{
	public:
		com_exception(HRESULT hr) : result(hr) {}

		virtual const char* what() const override
		{
			static char s_str[64] = {};
			sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
			return s_str;
		}

	private:
		HRESULT result;
	};

	// Helper utility converts D3D API failures into exceptions.
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			auto msg = _com_error(hr);
			LPCTSTR errMsg = msg.ErrorMessage();

			throw com_exception(hr);
		}
	}
}