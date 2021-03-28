#include "DepthStencil.h"
#include <fstream>


DepthStencil::DepthStencil()
{
}

DepthStencil::DepthStencil(UINT _width, UINT _height, D3DFORMAT _format)
{
	ThrowIfFailed(D3DXCreateTexture(m_device, _width, _height, 1, D3DUSAGE_DEPTHSTENCIL, _format, D3DPOOL_DEFAULT, &m_texture));
	//ThrowIfFailed(m_device->CreateRenderTarget(_width, _height, _format, 0, 0, TRUE, &m_captureSurface, NULL));

	ThrowIfFailed(m_texture->GetSurfaceLevel(0, &m_captureSurface));
}


DepthStencil::~DepthStencil()
{
	Release();
}

void DepthStencil::Initialize(wstring _fp)
{
	string path;
	path.assign(_fp.begin(), _fp.end());

	ifstream file(path.c_str());

	string buffer;
	size_t length = 0;

	UINT width = 0;
	UINT height = 0;
	DEPTH_STENCIL_FORMAT format = DEPTH_STENCIL_FORMAT::DEPTH_STENCIL_FORMAT_D24S8;

	while (true)
	{
		getline(file, buffer);
		if ('#' == buffer[0] || "" == buffer)
			continue;

		// 항목 확인
		size_t firstWordEnd;
		for (firstWordEnd = 0; firstWordEnd < buffer.size(); ++firstWordEnd)
		{
			if (' ' == buffer[firstWordEnd])
				break;
		}

		string memberName = buffer.substr(0, firstWordEnd);

		// 다음 " 찾기
		while ('\"' != buffer[firstWordEnd])
		{
			++firstWordEnd;
		}
		++firstWordEnd;

		// 1. width
		if (strcmp(memberName.c_str(), "width") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			width = (UINT)atoi(handleName.c_str());
		}
		// 2. height
		if (strcmp(memberName.c_str(), "height") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			height = (UINT)atoi(handleName.c_str());
		}
	


#pragma endregion
		// 3. renderQueue
		if (strcmp(memberName.c_str(), "format") == 0)
		{
			// render queue value
			size_t valueEnd;
			for (valueEnd = firstWordEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string str = buffer.substr(firstWordEnd, valueEnd - firstWordEnd);

			int value = atoi(str.c_str());
			format = (DEPTH_STENCIL_FORMAT)value;

			break;
		}
	}

	// D3DPOOL_DEFAULT 만 지원 , D3DPOOL_MANAGED 사용불가
	D3DFORMAT d3dformat = D3DFMT_D24S8;
	//switch (format)
	//{
	//case TEXTURE_FORMAT_D24S8:
	//	d3dformat = D3DFORMAT::D3DFMT_D24S8;
	//	break;
	//default:
	//	break;
	//}

	ThrowIfFailed(D3DXCreateTexture(m_device, width, height, 1, D3DUSAGE_DEPTHSTENCIL, d3dformat, D3DPOOL_DEFAULT, &m_texture));
	ThrowIfFailed(m_texture->GetSurfaceLevel(0, &m_captureSurface));
}

void DepthStencil::Release()
{
	SAFE_RELEASE(m_originSurface);
	SAFE_RELEASE(m_captureSurface);
	SAFE_RELEASE(m_texture);
}

void DepthStencil::StartRecord()
{
	ThrowIfFailed(m_device->GetDepthStencilSurface(&m_originSurface));
	ThrowIfFailed(m_device->SetDepthStencilSurface(m_captureSurface));
}

void DepthStencil::EndRecord()
{
	ThrowIfFailed(m_device->SetDepthStencilSurface(m_originSurface));
}

void DepthStencil::Clear()
{
	StartRecord();
	
	m_device->Clear(0, nullptr, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, 1, 0);

	EndRecord();
}
