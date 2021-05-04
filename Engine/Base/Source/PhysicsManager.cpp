#include "PhysicsManager.h"
#include "UserCollisionFilterFlag.h"
#include "TimeManager.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Collider.h"
#include "MeshRenderer.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "RenderManager.h"
#include "CharacterController.h"

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
	if (dTime > 0.0166666666666667f)
	{

	}
	else
	{
		m_scene->simulate(dTime);
		m_scene->fetchResults(true);
	}
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

	sceneDesc.flags |= PxSceneFlag::eENABLE_KINEMATIC_PAIRS;
	sceneDesc.flags |= PxSceneFlag::eENABLE_KINEMATIC_STATIC_PAIRS;

	m_scene = m_physics->createScene(sceneDesc);

#ifdef _DEBUG
	m_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	m_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
	//m_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_DYNAMIC, 1.0f);

	//m_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_STATIC, 1.0f);

	//m_scene->setVisualizationParameter(PxVisualizationParameter::eBODY_LIN_VELOCITY, 1.0f);
	//m_scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 2.0f);
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

PxFilterData PhysicsManager::GetFilterData(_OBJECT_LAYER _layer)
{
	PxU32 shapeLayer = (PxU32)pow(2, _layer);
	PxU32 targetFinalLayer = 0;

	int layerCount = ObjectManager::GetInstance()->GetObjectLayerCount();

	for (int i = 0; i < layerCount; ++i)
	{
		PxU32 targetLayer = (PxU32)pow(2, i);
		for (auto& resultLayer : m_collisionLayer)
		{
			if (resultLayer == shapeLayer + targetLayer)
			{
				targetFinalLayer |= targetLayer;
			}
		}
	}
	PxFilterData filterData;
	filterData.word0 = shapeLayer;
	filterData.word1 = targetFinalLayer;

	return filterData;
}

void PhysicsManager::ActiveCollisionLayer(_OBJECT_LAYER _layer1, _OBJECT_LAYER _layer2)
{
	m_collisionLayer.emplace_back((unsigned long long)pow(2, _layer1) + (UINT)pow(2, _layer2));
}

void PhysicsManager::AdjustCollisionLayer(PxShape * _shape, USHORT _layer)
{
	PxU32 shapeLayer = (PxU32)pow(2, _layer);

	PxU32 targetFinalLayer = 0;

	int layerCount = ObjectManager::GetInstance()->GetObjectLayerCount();

	for (int i = 0; i < layerCount; ++i)
	{
		PxU32 targetLayer = (PxU32)pow(2, i);
		for (auto& resultLayer : m_collisionLayer)
		{
			if (resultLayer == shapeLayer + targetLayer)
			{
				targetFinalLayer |= targetLayer;
			}
		}
	}
	SetUpFiltering(_shape, shapeLayer, targetFinalLayer);
}

void PhysicsManager::SetUpFiltering(PxShape* _shape, PxU32 _filterGroup, PxU32 _filterMask)
{
	PxFilterData filterData;
	filterData.word0 = _filterGroup;
	filterData.word1 = _filterMask;

	_shape->setSimulationFilterData(filterData);
}

void PhysicsManager::AddActorToScene(PxActor * _rigid)
{
	m_scene->addActor(*_rigid);
}

void PhysicsManager::RemoveActorFromScene(PxActor * _rigid)
{
	if(_rigid)
		m_scene->removeActor(*_rigid);
}

const PxRenderBuffer& PhysicsManager::GetDebugRenderBuffer()
{
	return m_scene->getRenderBuffer();
}

PxRigidDynamic* PhysicsManager::CreateRigidDynamic(RigidBody * _rigid)
{
	PxRigidDynamic* actor = nullptr;
	actor = _rigid->GetRigidBody();
	if (actor)
		return actor;

	auto pos = _rigid->GetTransform()->GetWorldPosition();
	auto rot = _rigid->GetTransform()->GetWorldRotation();
	PxTransform trans = PxTransform(PxVec3(pos.x, pos.y, pos.z), PxQuat(rot.x, rot.y, rot.z, rot.w));

	actor = m_physics->createRigidDynamic(trans);
	actor->userData = _rigid->GetGameObject();
	actor->setLinearDamping(_rigid->GetDamping());
	actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, _rigid->IsKinematic());
	actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !_rigid->IsGravity());
	actor->setMass(_rigid->GetMass());

	m_scene->addActor(*actor);

	_rigid->SetRigidBody(actor);

	return actor;
}

PxRigidStatic * PhysicsManager::CreateRigidStatic(Collider* _col)
{
	auto pos = _col->GetTransform()->GetWorldPosition();
	auto rot = _col->GetTransform()->GetWorldRotation();

	PxTransform trans = PxTransform(PxVec3(pos.x, pos.y, pos.z), PxQuat(rot.x, rot.y, rot.z, rot.w));
	PxRigidStatic* actor = m_physics->createRigidStatic(trans);
	actor->userData = _col->GetGameObject();

	m_scene->addActor(*actor);

	return actor;
}

void PhysicsManager::CreateConvexMeshCollider(Collider * _col, RigidBody * _rigid, Mesh * _mesh, bool _directInsertion, unsigned int _gaussLimit)
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
	PxMeshScale meshScale = PxMeshScale(PxVec3(scale.x, scale.y, scale.z), PxQuat(PxIdentity));
	PxMaterial* pMat = m_physics->createMaterial(0.5f, 0.5f, 0.5f);


	PxShape* shape = PxRigidActorExt::createExclusiveShape(*CreateRigidDynamic(_rigid), PxConvexMeshGeometry(convexMesh, meshScale), *pMat);
	assert(L"Failed to create shape!" && shape);

	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !_col->IsTrigger());
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, _col->IsTrigger());

	_col->SetShape(shape);
	AdjustCollisionLayer(shape, _col->GetGameObject()->GetLayer());

	PxRigidDynamic* actor = CreateRigidDynamic(_rigid);
	actor->userData = _col->GetGameObject();
	//pActor->attachShape(*pShape);	// 위에서 자동으로 붙여짐
	PxQueryFilterData query;
	query.flags |= PxQueryFlag::eNO_BLOCK;

	convexMesh->release();
}

void PhysicsManager::CreateStaticMeshCollider(Collider * _col, bool _directInsertion, DWORD _vertexCount, Vector3* _vertexPositionData, DWORD _figureCount, INDEX32* _figureData)
{
	PxCookingParams params = m_cooking->getParams();

	// 3.4버전
	params.midphaseDesc = PxMeshMidPhase::eBVH34;

	// for speed
	params.suppressTriangleMeshRemapTable = true;


	// 쿠킹 중 메쉬 정리 여부 결정 (조건)
	//  1. 버텍스 복사가 없어야 함
	//  2. 거대 폴리곤이 없어야 함
	bool skipMeshCleanup = false;
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
	//params.meshWeldTolerance = 10.f;

	m_cooking->setParams(params);


	PxTriangleMeshDesc meshDesc;
	meshDesc.setToDefault();
	meshDesc.points.count = _vertexCount;
	meshDesc.points.data = _vertexPositionData;
	meshDesc.points.stride = sizeof(Vector3);

	meshDesc.triangles.count = _figureCount;
	meshDesc.triangles.data = _figureData;
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

	Vector3 scale = _col->GetTransform()->scale;
	auto pos = _col->GetTransform()->GetWorldPosition();
	auto rot = _col->GetTransform()->GetWorldRotation();
	PxMeshScale meshScale = PxMeshScale(PxVec3(scale.x, scale.y, scale.z), PxQuat(PxIdentity));
	PxMaterial* pMat = m_physics->createMaterial(0.5f, 0.5f, 0.5f);
	PxTransform trans = PxTransform(PxVec3(pos.x, pos.y, pos.z), PxQuat(rot.x, rot.y, rot.z, rot.w));
	PxRigidStatic* actor = m_physics->createRigidStatic(trans);
	PxShape* shape = PxRigidActorExt::createExclusiveShape(*actor, PxTriangleMeshGeometry(triMesh, meshScale), *pMat);
	//shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE,true);
	AdjustCollisionLayer(shape, _col->GetGameObject()->GetLayer());
	_col->SetShape(shape);
	actor->attachShape(*shape);
	actor->userData = _col->GetGameObject();

	m_scene->addActor(*actor);
}

void PhysicsManager::CreateSphereCollider(Collider * _col, RigidBody * _rigid, float _radius)
{
	PxMaterial* material = m_physics->createMaterial(0.5f, 0.5f, 0.5f);
	PxShape* shape = m_physics->createShape(PxSphereGeometry(_radius), *material, true);
	InitializeShapeByColliderInfo(shape, _col);
	AttachShapeToRigidBody(_rigid, _col);
}

void PhysicsManager::CreateBoxCollider(Collider * _col, RigidBody * _rigid, float _width, float _height, float _depth)
{
	PxMaterial* material = m_physics->createMaterial(0.5f, 0.5f, 0.5f);
	PxShape* shape = m_physics->createShape(PxBoxGeometry(_width * 0.5f, _height * 0.5f, _depth * 0.5f), *material, true);
	InitializeShapeByColliderInfo(shape, _col);
	AttachShapeToRigidBody(_rigid, _col);
	

}

void PhysicsManager::CreateCapsuleCollider(Collider * _col, RigidBody * _rigid, float _radius, float _height)
{
	PxMaterial* material = m_physics->createMaterial(0.5f, 0.5f, 0.5f);
	PxShape* shape = m_physics->createShape(PxCapsuleGeometry(_radius,_height * 0.5f), *material, true);
	InitializeShapeByColliderInfo(shape, _col);
	AttachShapeToRigidBody(_rigid, _col);
}

PxCapsuleController* PhysicsManager::CreateCharacterController(CharacterController* _controller)
{
	PxCapsuleControllerDesc desc;
	desc.userData = _controller->GetGameObject();
	desc.climbingMode = _controller->m_climbingMode;
	desc.material = m_physics->createMaterial(0.5f, 0.5f, 0.5f);
	desc.height = _controller->m_height;
	desc.radius = _controller->m_radius;
	desc.contactOffset = _controller->m_skinWidth;
	desc.stepOffset = _controller->m_stepOffset;
	desc.slopeLimit =  Deg2Rad * _controller->m_slopeLimit;
	desc.upDirection = PxVec3(0.f, 1.f, 0.f);
	Vector3 pos = _controller->GetTransform()->GetWorldPosition(); 
	desc.position = PxExtendedVec3(pos.x, pos.y, pos.z);

	//PxFilterData filterData;
	//filterData.word0 = _filterGroup;
	//filterData.word1 = _filterMask;

	//_shape->setSimulationFilterData(filterData);
	
	PxController*	 controller =  m_controllerManager->createController(desc);
	controller->setUserData(_controller->GetGameObject());
	Vector3 footPos = pos + _controller->m_center;
	controller->setFootPosition(PxExtendedVec3(footPos.x, footPos.y, footPos.z));


	USHORT layer =  _controller->GetGameObject()->GetLayer();

	const PxU32 numShapes = controller->getActor()->getNbShapes();

	PxShape** ppShapes = (PxShape**)m_allocator.allocate(sizeof(PxShape*)*numShapes, 0, __FILE__, __LINE__);
	controller->getActor()->getShapes(ppShapes, numShapes);
	controller->getActor()->userData = _controller->GetGameObject();
	
	for (PxU32 i = 0; i < numShapes; i++)
	{
		PxShape* pShape = ppShapes[i];
		pShape->userData = _controller->GetGameObject();
		AdjustCollisionLayer(pShape, layer);
	}

	if (ppShapes)
	{
		m_allocator.deallocate(ppShapes);
		ppShapes = NULL;
	}

	return (PxCapsuleController*)controller;
}

void PhysicsManager::AttachShapeToRigidBody(RigidBody * _rigid, Collider* shape)
{
	if (_rigid)
	{
		PxRigidDynamic* actor = CreateRigidDynamic(_rigid);
		actor->userData = shape->GetGameObject();
		actor->attachShape(*shape->GetShape());
	}
	else
	{
		PxRigidStatic* actor = CreateRigidStatic(shape);
		actor->userData = shape->GetGameObject();
		actor->attachShape(*shape->GetShape());
	}
	
}

void PhysicsManager::InitializeShapeByColliderInfo(PxShape * _shape, Collider * _collider)
{
	auto pos = _collider->GetPosOffset();
	auto rot = _collider->GetRotOffset();
	PxTransform trans = PxTransform(PxVec3(pos.x, pos.y, pos.z), PxQuat(rot.x, rot.y, rot.z, rot.w));
	_shape->setLocalPose(trans);
	_shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !_collider->IsTrigger());
	_shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, _collider->IsTrigger());

	_collider->SetShape(_shape);
	AdjustCollisionLayer(_shape, _collider->GetGameObject()->GetLayer());
}

GameObject * PhysicsManager::Raycast(Vector3* _hitPoint,const Vector3 & _startRayPos, const Vector3 & _endRayPos, vector<MeshRenderer*> _renderList)
{
	
	vector<MeshRenderer*> raycastRenderers;
	for (auto& render : _renderList)
	{

		Vector3 center = render->GetTransform()->GetWorldPosition();

		float rayLength = sqrt(
			pow(_endRayPos.x - _startRayPos.x, 2) +
			pow(_endRayPos.y - _startRayPos.y, 2) +
			pow(_endRayPos.z - _startRayPos.z, 2)
		);

		float rayDx = (_endRayPos.x - _startRayPos.x) / rayLength;
		float rayDy = (_endRayPos.y - _startRayPos.y) / rayLength;
		float rayDz = (_endRayPos.z - _startRayPos.z) / rayLength;

		float t =
			rayDx * (center.x - _startRayPos.x) +
			rayDy * (center.y - _startRayPos.y) +
			rayDz * (center.z - _startRayPos.z);

		float Ex = t * rayDx + _startRayPos.x;
		float Ey = t * rayDy + _startRayPos.y;
		float Ez = t * rayDz + _startRayPos.z;

		float LineToSphereMinDistance = pow(Ex - center.x, 2) + pow(Ey - center.y, 2) + pow(Ez - center.z, 2);

		Vector3 scale = render->GetTransform()->scale;
		float radius = render->GetBoundingRadius();
		float maxScale = max(max(scale.x, scale.y), scale.z);
		if (LineToSphereMinDistance > radius * radius* maxScale * maxScale) //
			continue;

		raycastRenderers.emplace_back(render);

	}
	if (raycastRenderers.size() == 0)
		return nullptr;

	GameObject* pickObject = nullptr;
	Vector3 rayDirection = Nalmak_Math::Normalize(_endRayPos - _startRayPos);
	
	float minDistance = INFINITY;

	for(auto& render : raycastRenderers)
	{
		Vector3 rayStartPos = _startRayPos; 
		Vector3 dir = rayDirection;
		Matrix matInvWorld;
		
		D3DXMatrixInverse(&matInvWorld, 0, &render->GetTransform()->GetNoneScaleWorldMatrix());
		D3DXVec3TransformCoord(&rayStartPos, &_startRayPos, &matInvWorld);
		D3DXVec3TransformNormal(&dir, &dir, &matInvWorld);
		
		float u, v, dist;
		
		Mesh* mesh = render->GetMesh();
	
		Vector3 scale = render->GetTransform()->scale;
		for (unsigned long i = 0; i < mesh->GetFigureCount(); ++i)
		{
			Vector3 v0, v1, v2;
			v0 = mesh->GetVertexPositionData()[mesh->GetIndexData()[i]._0];
			v0 = { v0.x * scale.x ,v0.y * scale.y,v0.z * scale.z };
			v1 = mesh->GetVertexPositionData()[mesh->GetIndexData()[i]._1];
			v1 = { v1.x * scale.x ,v1.y * scale.y,v1.z * scale.z };
			v2 = mesh->GetVertexPositionData()[mesh->GetIndexData()[i]._2];
			v2 = { v2.x * scale.x ,v2.y * scale.y,v2.z * scale.z };

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
				if (minDistance > dist)
				{
					minDistance = dist;
					*_hitPoint = v0 + u * (v1 - v0) + v * (v2 - v0);
					D3DXVec3TransformCoord(_hitPoint, _hitPoint, &render->GetTransform()->GetNoneScaleWorldMatrix());
					pickObject = render->GetGameObject();

				}

			}
		}
	}
	return pickObject;
}

GameObject * PhysicsManager::RaycastCamToMouse(Vector3 * _hitPoint, const vector<MeshRenderer*>& _renderList)
{
	vector<MeshRenderer*> raycastRenderers;
	Camera* mainCam = RenderManager::GetInstance()->GetMainCamera();

	float rayLength = mainCam->GetFar();
	Vector3 startRayPos = mainCam->GetTransform()->GetWorldPosition();
	Vector3 endRayPos = startRayPos + mainCam->GetCamToMouseWorldDirection() *rayLength;

	for (auto& render : _renderList)
	{
		Vector3 center = render->GetTransform()->GetWorldPosition();

		float rayDx = (endRayPos.x - startRayPos.x) / rayLength;
		float rayDy = (endRayPos.y - startRayPos.y) / rayLength;
		float rayDz = (endRayPos.z - startRayPos.z) / rayLength;

		float t =
			rayDx * (center.x - startRayPos.x) +
			rayDy * (center.y - startRayPos.y) +
			rayDz * (center.z - startRayPos.z);

		float Ex = t * rayDx + startRayPos.x;
		float Ey = t * rayDy + startRayPos.y;
		float Ez = t * rayDz + startRayPos.z;

		float LineToSphereMinDistance = pow(Ex - center.x, 2) + pow(Ey - center.y, 2) + pow(Ez - center.z, 2);

		Vector3 scale = render->GetTransform()->scale;
		float maxScale = max(max(scale.x, scale.y), scale.z);
		if (LineToSphereMinDistance > render->GetBoundingRadius() *  render->GetBoundingRadius()* maxScale * maxScale) //
			continue;

		raycastRenderers.emplace_back(render);

	
	}
	if (raycastRenderers.size() == 0)
		return nullptr;

	GameObject* pickObject = nullptr;
	Vector3 rayDirection = Nalmak_Math::Normalize(endRayPos - startRayPos);

	float minDistance = INFINITY;

	for (auto& render : raycastRenderers)
	{
		Vector3 rayStartPos = startRayPos;
		Vector3 dir = rayDirection;
		Matrix matInvWorld;
		D3DXMatrixInverse(&matInvWorld, 0, &render->GetTransform()->GetNoneScaleWorldMatrix());
		D3DXVec3TransformCoord(&rayStartPos, &startRayPos, &matInvWorld);
		D3DXVec3TransformNormal(&dir, &dir, &matInvWorld);

		float u, v, dist;

		Mesh* mesh = render->GetMesh();

		Vector3 scale = render->GetTransform()->scale;

		for (unsigned long i = 0; i < mesh->GetFigureCount(); ++i)
		{
			Vector3 v0, v1, v2;
			v0 = mesh->GetVertexPositionData()[mesh->GetIndexData()[i]._0];
			v0 = { v0.x * scale.x ,v0.y * scale.y,v0.z * scale.z };
			v1 = mesh->GetVertexPositionData()[mesh->GetIndexData()[i]._1];
			v1 = { v1.x * scale.x ,v1.y * scale.y,v1.z * scale.z };
			v2 = mesh->GetVertexPositionData()[mesh->GetIndexData()[i]._2];
			v2 = { v2.x * scale.x ,v2.y * scale.y,v2.z * scale.z };

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
				if (minDistance > dist)
				{
					minDistance = dist;

					if (_hitPoint)
					{
						*_hitPoint = v0 + u * (v1 - v0) + v * (v2 - v0);
						D3DXVec3TransformCoord(_hitPoint, _hitPoint, &render->GetTransform()->GetNoneScaleWorldMatrix());
					}
				
					pickObject = render->GetGameObject();
				}

			}
		}
	}
	return pickObject;
}


