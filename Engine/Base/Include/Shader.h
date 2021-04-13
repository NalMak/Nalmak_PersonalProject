#pragma once

#ifndef __SHADER_H__
#define __SHADER_H__

#include "IResource.h"

class RenderTarget;

BEGIN(Nalmak)
class NALMAK_DLL Shader :
	public IResource
{
	friend class ResourceManager;
public:
	explicit Shader();
	~Shader();
private:
	virtual void Initialize(wstring _fp) override;

	virtual void Release() override;
public:
	void SetBool(const string& _parameter, bool _value);
	void SetInt(const string& _parameter, int _value);
	void SetFloat(const string& _parameter, float _value);
	void SetMatrix(const string& _parameter, const Matrix& _value);
	void SetMatrixArray(const string& _parameter, Matrix* _matrix, UINT _count);
	void SetTexture(const string& _parameter, IDirect3DBaseTexture9* _value);
	void SetVector(const string& _parameter, const Vector4& _vec);
	void SetVector(const string& _parameter, const Vector2& _vec);
	void SetValue(const string& _parameter, void* value, UINT _size);
public:
	HRESULT CheckShaderInitialize();
	wstring GetName() { return m_name; }
	void CommitChanges();
	void BeginPass();
	void EndPass();
public:
	VERTEX_INPUT_LAYOUT GetInputLayout() { return m_vertexInputLayout; }
private:
	LPD3DXEFFECT m_effect = nullptr;
	IDirect3DVertexDeclaration9* m_decl = nullptr;
	UINT m_inputLayoutSize;
	VERTEX_INPUT_LAYOUT m_vertexInputLayout;
private:
	
public:
	IDirect3DVertexDeclaration9* GetDeclartion()const { assert("Is not define Vertex Declaration. Please Set Vertex Declaration at Resource Manager Load Shader! " && m_decl); return m_decl; }
	unsigned int GetInputLayoutSize()const { return m_inputLayoutSize; }
private:
	RenderTarget* m_renderTarget[4];
public:
	RenderTarget* GetRenderTarget(int i) { return m_renderTarget[i]; }
	void AddRenderTarget(int _index,const wstring& _rtName);
public:
	void SetInputLayout(D3DVERTEXELEMENT9* _decl, UINT _inputLayoutSize);

	
};
END
#endif // !__SHADER_H__
