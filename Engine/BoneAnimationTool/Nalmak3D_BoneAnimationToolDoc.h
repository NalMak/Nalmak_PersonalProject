
// Nalmak3D_BoneAnimationToolDoc.h : CNalmak3D_BoneAnimationToolDoc Ŭ������ �������̽�
//


#pragma once


class CNalmak3D_BoneAnimationToolDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CNalmak3D_BoneAnimationToolDoc();
	DECLARE_DYNCREATE(CNalmak3D_BoneAnimationToolDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CNalmak3D_BoneAnimationToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
