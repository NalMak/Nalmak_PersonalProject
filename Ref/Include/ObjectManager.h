#pragma once

#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include "GameObject.h"
#include "Nalmak_Include.h"

// 오브젝트 담당 (삭제, 업데이트 )
// 오브젝트 리스트는 클라이언트에서 받은 태그만큼 존재하며, 모든 오브젝트의
// 업데이트를 담당한다. 
// 생성 및 삭제를 요청받으면, 매 업데이트 처음부분에서 처리를 한다
// -> 중간에서  GameObject를 INSTANTIATE로 생성요청을 해도 m_newGameObjectList에 담기고
//    다음 프레임 처음부분에  m_gameObjectLists에 복사가 일어난다

BEGIN(Nalmak)
class ObjectManager
{
	DECLARE_SINGLETON(ObjectManager)
private:
	ObjectManager();
	~ObjectManager();
private:
	list<GameObject*> m_newGameObjectList;
	vector<list<GameObject*>> m_gameObjectLists;
	vector<GameObject*> m_willBeDeadObjectList;
	vector<Component*> m_willBeDeadComponents;
	USHORT m_objectLayerCount = 1;
public:
	void Initialize(_OBJECT_TAG _ObjectTag,_OBJECT_LAYER _objectLayer);
	void Update();
	void LateUpdate();
	void PreRender();
	void PostRender();
	void Release();
	void ReleaseScene();
	void DeleteInstance();
	void AddTo_DeleteComponentsCollector(Component* _com);

	void DeleteList(_OBJECT_TAG _tag);
	void AddObject(GameObject* _obj);
	void ChangeTag(_OBJECT_TAG _tag, GameObject* _obj);
public:
	const list<GameObject*>& GetObjectList(_OBJECT_TAG _tag);
	GameObject* Find(const wstring& _name);
	GameObject* Find(_OBJECT_TAG _tag, const wstring& _name);
	GameObject* FindFirstObjectbyTag(_OBJECT_TAG _tag);
	GameObject* PickObjectByMouse(Vector3* _hitPoint);
	USHORT GetObjectLayerCount();
public:
	void MergeObjectList();

};
END
#endif

