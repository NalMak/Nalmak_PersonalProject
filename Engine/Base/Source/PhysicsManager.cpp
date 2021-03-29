#include "PhysicsManager.h"
#include "UserCollisionFilterFlag.h"
#include "TimeManager.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Collider.h"
#include "MeshRenderer.h"
IMPLEMENT_SINGLETON(PhysicsManager)

PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
	Release();
}

void PhysicsManager::Initialize()
{
	CreatePhysicsEngine();
	CreateEventCallBack();
	CreateScene();
	//CreatePVD();
	CreateController();
}

void PhysicsManager::Release()
{
	Safe_release(m_controllerManager);
	Safe_release(m_scene);
	Safe_release(m_dispatcher);
	Safe_release(m_physics);
	Safe_release(m_cooking);
	Safe_release(m_PVD);
	Safe_release(m_port);
	Safe_release(m_foundation);
	SAFE_DELETE(m_eventCallback);
}

void PhysicsManager::Update()
{
	m_scene->simulate(dTime);
	m_scene->fetchResults(true);
}

void PhysicsManager::CreatePhysicsEngine()
{
	char* port = "127.0.0.1";

	m_foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, m_allocator, m_errorCallback);

	//m_PVD = PxCreatePvd(*m_foundation);
	//m_port = PxDefaultPvdSocketTransportCreate(port, 5425, 10 );
	//if (m_PVD->connect(*m_port, PxPvdInstrumentationFlag::eALL))
	//{
	//	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale(), false, m_PVD);	
	//}
	//else
	//{
	//	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale()); // Create Physics
	//}

	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale()); // Create Physics
	m_dispatcher = PxDefaultCpuDispatcherCreate(2); //?? 

	PxTolerancesScale toleranceScale;
	toleranceScale.mass = 1000;
	toleranceScale.speed = 9;
	if (!toleranceScale.isValid())
	{
		ERR_MSG(L"ToleranceScale is invalid");
	}
	PxCookingParams params(toleranceScale);
	params.meshPreprocessParams = PxMeshPreprocessingFlags(PxMeshPreprocessingFlag::eWELD_VERTICES);
	params.buildGPUData = true;

	m_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_foundation, params);
}

void PhysicsManager::CreateEventCallBack()
{
	m_eventCallback = new NalmakPxEventCallBack();
}

void PhysicsManager::CreateScene()
{
	PxSceneDesc sceneDesc(m_physics->getTolerancesScale());

	sceneDesc.gravity = PxVec3(0.f, -9.8f, 0.f);
	sceneDesc.cpuDispatcher = m_dispatcher;

	sceneDesc.simulationEventCallback = m_eventCallback;
	sceneDesc.filterShader = UserCollisionFilterFlag;

	sceneDesc.flags != PxSceneFlag::eENABLE_KINEMATIC_PAIRS;
	sceneDesc.flags != PxSceneFlag::eENABLE_KINEMATIC_STATIC_PAIRS;

	m_scene = m_physics->createScene(sceneDesc);

#ifdef _DEBUG
	m_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	m_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
	//m_scene->setVisualizationParameter(PxVisualizationParameter::eBODY_LIN_VELOCITY, 1.0f);
	m_scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 2.0f);
	//m_scene->setVisualizationParameter(PxVisualizationParameter::eCULL_BOX, 2.0f);

	//m_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_EDGES, 1.0f);

#endif
	/*m_scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 2.0f);
	m_scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 2.0f);*/


}

void PhysicsManager::CreatePVD()
{
	PxPvdSceneClient* pvdClient = m_scene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
}

void PhysicsManager::CreateController()
{
	m_controllerManager = PxCreateControllerManager(*m_scene);
}

void PhysicsManager::AddActorToScene(PxRigidDynamic * _rigid)
{
	m_scene->addActor(*_rigid);
}

void PhysicsManager::RemoveActorFromScene(PxRigidDynamic * _rigid)
{
	if(_rigid)
		m_scene->removeActor(*_rigid);
}

const PxRenderBuffer& PhysicsManager::GetDebugRenderBuffer()
{
	return m_scene->getRenderBuffer();
}

PxRigidDynamic * PhysicsManager::CreateConvexMeshCollider(Collider * _col, RigidBody * _rigid, Mesh * _mesh, bool _directInsertion, unsigned int _gaussLimit)
{
	PxCookingParams params = m_cooking->getParams();
	params.convexMeshCookingType = PxConvexMeshCookingType::eQUICKHULL;
	// PxConvexMeshCookingType::eINFLATION_INCREMENTAL_HULL //
	// PxConvexMeshCookingType::eQUICKHULL					//

	// 필요에 따라 늘리기
	params.gaussMapLimit = _gaussLimit;
	//params.gaussMapLimit = 16;
	//params.gaussMapLimit = 256;

	m_cooking->setParams(params);

	PxConvexMeshDesc convecDesc;
	convecDesc.points.count = _mesh->GetVertexCount();
	convecDesc.points.stride = sizeof(Vector3);
	convecDesc.points.data = _mesh->GetVertexPositionData();
	//convecDesc.polygons.count = _mesh->GetFigureCount();
	//convecDesc.polygons.stride = sizeof(INDEX16);
	//convecDesc.polygons.data = _mesh->GetIndices();
	//convecDesc.indices.count = _mesh->GetFigureCount() * 3;
	//convecDesc.indices.data = _mesh->GetIndices();
	//convecDesc.indices.stride = sizeof(unsigned short);
	convecDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;		// 폴리곤 없으면 사용하는듯?

															//tConvexDesc.polygons.count = numTriangles;
															//tConvexDesc.polygons.data = polygons;
															//tConvexDesc.polygons.stride = 3 * sizeof(_uint);
	PxConvexMesh* convexMesh = nullptr;

	if (_directInsertion)
	{
		convexMesh = m_cooking->createConvexMesh(convecDesc, m_physics->getPhysicsInsertionCallback());
	}
	else
	{
		PxDefaultMemoryOutputStream outputStream;
		if (!m_cooking->cookConvexMesh(convecDesc, outputStream))
			assert(L"Fail to Cook Convex Mesh!" && 0);

		PxDefaultMemoryInputData inputStream(outputStream.getData(), outputStream.getSize());
		convexMesh = m_physics->createConvexMesh(inputStream);
	}
	
	Vector3 scale = _rigid->GetTransform()->scale;
	auto pos = _rigid->GetTransform()->GetWorldPosition();
	auto rot = _rigid->GetTransform()->GetWorldRotation();
	PxMeshScale meshScale = PxMeshScale(PxVec3(scale.x, scale.y, scale.z), PxQuat(PxIdentity));
	PxMaterial* pMat = m_physics->createMaterial(0.5f, 0.5f, 0.5f);

	PxTransform trans = PxTransform(PxVec3(pos.x, pos.y, pos.z), PxQuat(rot.x, rot.y, rot.z, rot.w));
	PxRigidDynamic* actor = m_physics->createRigidDynamic(trans);
	actor->setLinearDamping(_rigid->GetDamping());
	actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, _rigid->IsKinematic());
	actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !_rigid->IsGravity());
	actor->userData = _col->GetGameObject();

	PxShape* shape = PxRigidActorExt::createExclusiveShape(*actor, PxConvexMeshGeometry(convexMesh, meshScale), *pMat);
	assert(L"Failed to create shape!" && shape);

	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !_col->IsTrigger());
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, _col->IsTrigger());

	//pActor->attachShape(*pShape);	// 위에서 자동으로 붙여짐
	PxQueryFilterData query;
	query.flags |= PxQueryFlag::eNO_BLOCK;

	m_scene->addActor(*actor);

	convexMesh->release();

	return actor;
}

PxRigidStatic * PhysicsManager::CreateStaticMeshCollider(Collider * _col, RigidBody * _rigid, Mesh * _mesh, bool _directInsertion)
{

	PxCookingParams params = m_cooking->getParams();

	// 3.4버전
	params.midphaseDesc = PxMeshMidPhase::eBVH34;

	// for speed
	params.suppressTriangleMeshRemapTable = true;


	// 쿠킹 중 메쉬 정리 여부 결정 (조건)
	//  1. 버텍스 복사가 없어야 함
	//  2. 거대 폴리곤이 없어야 함
	bool skipMeshCleanup = true;
	bool skipEdgeData = false;
	bool inserted = false; // false -> fast

	if (!skipMeshCleanup)
		params.meshPreprocessParams &= ~static_cast<PxMeshPreprocessingFlags>(PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH);
	else
		params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;

	// 모든 가장자리 액티브를 체크하지 않고 바로 활성화
	// 쿠킹은 빠르지만 충돌 검출이 느려질 수 있고, 충돌 효과가 변할 수 있음. 
	if (!skipEdgeData)
		params.meshPreprocessParams &= ~static_cast<PxMeshPreprocessingFlags>(PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE);
	else
		params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;

	params.midphaseDesc.mBVH34Desc.numTrisPerLeaf = 15;

	m_cooking->setParams(params);


	PxTriangleMeshDesc meshDesc;
	meshDesc.setToDefault();
	meshDesc.points.count = _mesh->GetVertexCount();
	meshDesc.points.data = _mesh->GetVertexPositionData();
	meshDesc.points.stride = sizeof(Vector3);

	meshDesc.triangles.count = _mesh->GetFigureCount();
	meshDesc.triangles.data = _mesh->GetIndices();
	meshDesc.triangles.stride = sizeof(INDEX32);

	assert(L"Mesh is not valid for triangleMesh" && meshDesc.isValid());

#if defined(_DEBUG)
	// 디버그에서 유효 트라이앵글 체크
	if (skipMeshCleanup)
	{
		PX_ASSERT(m_pCooking->validateTriangleMesh(meshDesc));
	}
#endif // DEBUG
	PxTriangleMesh* triMesh = nullptr;
	PxU32 meshSize = 0;

	// The cooked mesh may either be saved to a stream for later loading, or inserted directly into PxPhysics.
	if (inserted)
	{
		triMesh = m_cooking->createTriangleMesh(meshDesc, m_physics->getPhysicsInsertionCallback());
	}
	else
	{
		PxDefaultMemoryOutputStream outBuffer;
		m_cooking->cookTriangleMesh(meshDesc, outBuffer);

		PxDefaultMemoryInputData stream(outBuffer.getData(), outBuffer.getSize());
		triMesh = m_physics->createTriangleMesh(stream);

		meshSize = outBuffer.getSize();
	}

	assert(L"Fail to cook static mesh!" && triMesh);
	

	Vector3 scale = _rigid->GetTransform()->scale;
	auto pos = _rigid->GetTransform()->GetWorldPosition();
	auto rot = _rigid->GetTransform()->GetWorldRotation();
	PxMeshScale meshScale = PxMeshScale(PxVec3(scale.x, scale.y, scale.z), PxQuat(PxIdentity));
	PxMaterial* pMat = m_physics->createMaterial(0.5f, 0.5f, 0.5f);

	PxTransform trans = PxTransform(PxVec3(pos.x, pos.y, pos.z), PxQuat(rot.x, rot.y, rot.z, rot.w));

	PxRigidStatic* actor = m_physics->createRigidStatic(trans);
	PxShape* shape = PxRigidActorExt::createExclusiveShape(*actor, PxTriangleMeshGeometry(triMesh, meshScale), *pMat);
	

	actor->attachShape(*shape);
	actor->userData = _col->GetGameObject();

	m_scene->addActor(*actor);

	return actor;
}

PxRigidDynamic * PhysicsManager::CreateSphereCollider(Collider * _col, RigidBody * _rigid, float _radius)
{
	auto pos = _rigid->GetTransform()->GetWorldPosition();
	auto rot = _rigid->GetTransform()->GetWorldRotation();
	PxTransform trans = PxTransform(PxVec3(pos.x, pos.y, pos.z), PxQuat(rot.x, rot.y, rot.z, rot.w));
	PxMaterial* material = m_physics->createMaterial(0.5f, 0.5f, 0.5f);

	PxShape* shape = m_physics->createShape(PxSphereGeometry(_radius), *material, true);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !_col->IsTrigger());
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, _col->IsTrigger());

	PxRigidDynamic* actor = PxCreateDynamic(*m_physics, trans, *shape, PxReal(_rigid->GetDensity()));
	actor->userData = _col->GetGameObject();
	actor->setLinearDamping(_rigid->GetDamping());
	actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, _rigid->IsKinematic());
	actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !_rigid->IsGravity());
	
	m_scene->addActor(*actor);

	return actor;
}

PxRigidDynamic * PhysicsManager::CreateBoxCollider(Collider * _col, RigidBody * _rigid, float _width, float _height, float _depth)
{
	auto pos = _rigid->GetTransform()->GetWorldPosition();
	auto rot = _rigid->GetTransform()->GetWorldRotation();
	PxTransform trans = PxTransform(PxVec3(pos.x, pos.y, pos.z), PxQuat(rot.x, rot.y, rot.z, rot.w));
	PxMaterial* material = m_physics->createMaterial(0.5f, 0.5f, 0.5f);

	PxShape* shape = m_physics->createShape(PxBoxGeometry(_width * 0.5f, _height * 0.5f, _depth * 0.5f), *material, true);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !_col->IsTrigger());
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, _col->IsTrigger());
	PxRigidDynamic* actor = PxCreateDynamic(*m_physics, trans, *shape, PxReal(_rigid->GetDensity()));
	actor->userData = _col->GetGameObject();
	actor->setLinearDamping(_rigid->GetDamping());
	actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, _rigid->IsKinematic());
	actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !_rigid->IsGravity());
	m_scene->addActor(*actor);

	return actor;
}

GameObject * PhysicsManager::Raycast(const Vector3 & _startLayPos, const Vector3 & _endLayPos, vector<MeshRenderer*>& _renderList)
{
	
	vector<MeshRenderer*> raycastRenderers;
	for (auto& render : _renderList)
	{

		Vector3 center = render->GetTransform()->GetWorldPosition();

		float rayLength = sqrt(
			pow(_endLayPos.x - _startLayPos.x, 2) +
			pow(_endLayPos.y - _startLayPos.y, 2) +
			pow(_endLayPos.z - _startLayPos.z, 2)
		);

		float rayDx = (_endLayPos.x - _startLayPos.x) / rayLength;
		float rayDy = (_endLayPos.y - _startLayPos.y) / rayLength;
		float rayDz = (_endLayPos.z - _startLayPos.z) / rayLength;

		float t =
			rayDx * (center.x - _startLayPos.x) +
			rayDy * (center.y - _startLayPos.y) +
			rayDz * (center.z - _startLayPos.z);

		float Ex = t * rayDx + _startLayPos.x;
		float Ey = t * rayDy + _startLayPos.y;
		float Ez = t * rayDz + _startLayPos.z;

		float LineToSphereMinDistance = pow(Ex - center.x, 2) + pow(Ey - center.y, 2) + pow(Ez - center.z, 2);

		Vector3 scale = render->GetTransform()->scale;
		//float maxScale = max(max(scale.x, scale.y), scale.z);
		if (LineToSphereMinDistance > render->GetBoundingRadius() *  render->GetBoundingRadius()) //* maxScale * maxScale
			continue;

		raycastRenderers.emplace_back(render);
	}
	if (raycastRenderers.size() == 0)
		return nullptr;

	vector<pair<float, GameObject*>> pickingDistanceAndObject;
	Vector3 rayDirection = Nalmak_Math::Normalize(_endLayPos - _startLayPos);
	for(auto& render : raycastRenderers)
	{
		Vector3 rayStartPos = _startLayPos; 
		Vector3 dir = rayDirection;
		Matrix matInvWorld;
		D3DXMatrixInverse(&matInvWorld, 0, &render->GetTransform()->GetWorldMatrix());
		D3DXVec3TransformCoord(&rayStartPos, &_startLayPos, &matInvWorld);
		D3DXVec3TransformNormal(&dir, &dir, &matInvWorld);
		
		float u, v, dist;
		
		Mesh* mesh = render->GetMesh();
		for (unsigned long i = 0; i < mesh->GetFigureCount(); ++i)
		{
			Vector3 v0, v1, v2;
			v0 = mesh->GetVertexPositionData()[mesh->GetIndices()[i]._0];
			v1 = mesh->GetVertexPositionData()[mesh->GetIndices()[i]._1];
			v2 = mesh->GetVertexPositionData()[mesh->GetIndices()[i]._2];

			if (D3DXIntersectTri(
				&v0,
				&v1,
				&v2,
				&rayStartPos,
				&dir,
				&u, &v, &dist))
			{
				//// 교차점 구하는 공식
				//// V1 + U(V2-V1) + V(V3-V1)
				//*pOut = m_pVertices[_1] + u * (m_pVertices[_2] - m_pVertices[_1]) + v * (m_pVertices[_3] - m_pVertices[_1]);
				//D3DXVec3TransformCoord(pOut, pOut, pWorldMatrix);
				pickingDistanceAndObject.emplace_back(pair<float, GameObject*>(dist ,render->GetGameObject()));
				break;
			}
		}
	}
	if(pickingDistanceAndObject.size() == 0)
		return nullptr;
	
	sort(pickingDistanceAndObject.begin(), pickingDistanceAndObject.end(), [](pair<float, GameObject*> _r1, pair<float, GameObject*> _r2)
		->bool
	{
		return _r1.first < _r2.first;
	}); // Z 정렬 

	return pickingDistanceAndObject.front().second;
}



