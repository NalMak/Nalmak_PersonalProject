#pragma once
#include "Nalmak_Include.h"

#include "PxPhysicsAPI.h"
#include "NalmakPxEventCallBack.h"
#include "MeshRenderer.h"

class RigidBody;
class Collider;
class Mesh;
class CharacterController;

using namespace physx;

class PhysicsManager
{
	DECLARE_SINGLETON(PhysicsManager)
public:
	PhysicsManager();
	~PhysicsManager();
public:
	void Initialize();
	void Release();
	void Update();
private:
	void CreatePhysicsEngine();
	void CreateEventCallBack();
	void CreateScene();
	void CreatePVD();
	void CreateController();

private:
	PxPhysics*				m_physics = nullptr;
	PxDefaultAllocator		m_allocator;
	PxDefaultErrorCallback	m_errorCallback;
	PxFoundation*			m_foundation = nullptr;
	PxPvdTransport*			m_port = nullptr;
	PxDefaultCpuDispatcher*	m_dispatcher = nullptr;
	PxPvd*					m_PVD = nullptr;
	PxScene*				m_scene = nullptr;
	PxCooking*				m_cooking = nullptr;
	PxControllerManager*	m_controllerManager = nullptr;

	NalmakPxEventCallBack*  m_eventCallback;

	vector<unsigned long long>  m_collisionLayer;
public:
	void ActiveCollisionLayer(_OBJECT_LAYER _layer1, _OBJECT_LAYER _layer2);
private:
	void AdjustCollisionLayer(PxShape * _shape, Collider * collider);
	void SetUpFiltering(PxShape* _shape, PxU32 _filterGroup, PxU32 _filterMask);
public:
	void AddActorToScene(PxRigidDynamic* _rigid);
	void RemoveActorFromScene(PxRigidDynamic* _rigid);
	const PxRenderBuffer& GetDebugRenderBuffer();
public:
	PxRigidDynamic* CreateRigidDynamic(RigidBody* _rigid);
	PxRigidStatic* CreateRigidStatic(Collider* _col);
	void CreateConvexMeshCollider(Collider * _col, RigidBody * _rigid, Mesh* _mesh, bool _directInsertion, unsigned int _gaussLimit);
	void CreateStaticMeshCollider(Collider * _col, bool _directInsertion, DWORD _vertexCount, Vector3* _vertexPositionData, DWORD _figureCount, INDEX32* _figureData);
public:
	void CreateSphereCollider(Collider* _col,RigidBody* _rigid, float _radius);
	void CreateBoxCollider(Collider* _col, RigidBody* _rigid, float _width, float _height, float _depth);
	void CreateCapsuleCollider(Collider* _col, RigidBody* _rigid, float _radius, float _height);
	PxCapsuleController* CreateCharacterController(CharacterController* _controller);
private:
	void AttachShapeToRigidBody(RigidBody* _rigid, Collider* shape);
	void InitializeShapeByColliderInfo(PxShape* _shape, Collider* collider);

public:
	GameObject* Raycast(Vector3* _hitPoint, const Vector3& _startLayPos, const Vector3& _endLayPos, vector<MeshRenderer*> _renderList);
	GameObject* RaycastCamToMouse(Vector3 * _hitPoint, const vector<MeshRenderer*>& _renderList);

};

