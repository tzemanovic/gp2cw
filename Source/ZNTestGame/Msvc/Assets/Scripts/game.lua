
function initGame()

	game=LuaScriptManager.GetGame()
	
	-- sky
	skySphere=GameObject(1)
	skySphereMesh=SkySphereComponent("Assets\\Textures\\SkySphere\\SkyCloudy.dds")
	skySphere:AddComponent(skySphere,skySphereMesh)
	game:AddGameObject(skySphere)
	
	-- terrain
	terrain=GameObject(2)
	terrainTrans=TransformComponent()
	terrainTrans:SetPosition(fVec3(0.0,-0.5,0.0))
	terrain:AddComponent(terrain,terrainTrans)
	terrainMesh=MeshComponent()
	terrainMesh:CreateCubeGeometry(fVec3(1000.0, 0.001, 1000.0))
	terrain:AddComponent(terrain,terrainMesh)
	terrainBody=RigidBodyComponent(true,1.0)
	terrain:AddComponent(terrain,terrainBody)
	terrainBoxCollider=BoxColliderComponent(fVec3(1000.0, 0.001, 1000.0))
	terrain:AddComponent(terrain,terrainBoxCollider)
	game:AddGameObject(terrain)
	terrainMeshMaterial=terrainMesh:GetMeshMaterial()
	terrainMeshMaterial:VLoadDiffuseTexture("Assets\\Textures\\face.png")
	
	-- new armored recond game object
	armoredRecon=GameObject(3)
	armoredReconTrans=TransformComponent()
	armoredReconTrans:SetPosition(fVec3(0.0,2.5,30.0))
	armoredRecon:AddComponent(armoredRecon,armoredReconTrans)
	armoredReconMesh=MeshComponent()
	--armoredReconMesh:LoadGeometryFromFile("Assets\\Models\\Vehicles\\armoredrecon.fbx")
	armoredReconMesh:CreateCubeGeometry(fVec3(1.0, 0.3, 2.8))
	armoredRecon:AddComponent(armoredRecon,armoredReconMesh)
	armoredReconBody=RigidBodyComponent(false,1.0)
	armoredRecon:AddComponent(armoredRecon,armoredReconBody)
	armoredReconBoxCollider=BoxColliderComponent(fVec3(1.0, 0.3, 2.8))
	armoredRecon:AddComponent(armoredRecon,armoredReconBoxCollider)
	game:AddGameObject(armoredRecon)
	armoredReconMeshMaterial=armoredReconMesh:GetMeshMaterial()
	armoredReconMeshMaterial:VLoadDiffuseTexture("Assets\\Textures\\Vehicles\\armoredrecon_diff.png")
	--armoredReconMeshMaterial:VLoadSpecularTexture("Assets\\Textures\\Vehicles\\armoredrecon_spec.png")
	--armoredReconMeshMaterial:VLoadBumpTexture("Assets\\Textures\\Vehicles\\armoredrecon_N.png")
	--armoredReconMeshMaterial:VLoadParallaxTexture("Assets\\Textures\\Vehicles\\armoredrecon_Height.png")
	

end