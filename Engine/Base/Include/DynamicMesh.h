#pragma once
#include "Mesh.h"
#include "Nalmak_Frame.h"
#include "Nalmak_MeshContainer.h"


//D3DXTRACK_DESC
//Flags
//미사용.
//Weight
//중량감의 값.믹서가 이 트랙을 다른 트랙과 블렌드 하는 차수는, 중량감에 의해 정해진다.
//Speed
//속도의 값.트랙의 간격을 스케일링하기 위한 승수와 유사하다.
//AnimTime
//로컬 애니메이션 타임.
//Enable
//트랙의 유효 / 무효.이 트랙을 믹서로 유효하게 하려면, TRUE 를 설정한다.무효로 하려면, FALSE 를 설정한다.


//https://icoder.tistory.com/entry/%EC%A7%91%EC%A4%91%EB%B6%84%EC%84%9D-DirectX-Sample-MutiAnimation 멀티애니메이션 예제
class NALMAK_DLL DynamicMesh :
	public Mesh
{
private:
	// Mesh을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
public:
	virtual void Draw(UINT subset = 0) override;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;
private:
	class DynamicMeshHierarchy* m_hierarchy;
	LPD3DXFRAME m_root;
	class AnimationController* m_animController;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;
private:
	void TraverseBone(Nalmak_Frame* _frame);
public:
	void SetAnimation(UINT _index);
	void UpdateBoneMatrix();
	void UpdateAnimationController();
private:
	void UpdateBoneMatrix(Nalmak_Frame* _bone, const Matrix& _parent);
};

