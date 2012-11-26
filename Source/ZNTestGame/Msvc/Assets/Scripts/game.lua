
function initGame()

	game=LuaScriptManager.GetGame()
	
	-- new armored recond game object
	armoredRecon=GameObject(1)
	armoredReconTrans=TransformComponent()
	armoredReconTrans:SetPosition(fVec3(0.0,0.0,30.0))
	armoredRecon:AddComponent(armoredRecon,armoredReconTrans)
	armoredReconMesh=MeshComponent()
	armoredReconMesh:LoadGeometryFromFile("Assets\\Models\\Vehicles\\armoredrecon.fbx")
	armoredRecon:AddComponent(armoredRecon,armoredReconMesh)
	game:AddGameObject(armoredRecon)
	armoredReconMeshMaterial=armoredReconMesh:GetMeshMaterial()
	armoredReconMeshMaterial:VLoadDiffuseTexture("Assets\\Textures\\Vehicles\\armoredrecon_diff.png")
	armoredReconMeshMaterial:VLoadSpecularTexture("Assets\\Textures\\Vehicles\\armoredrecon_spec.png")
	armoredReconMeshMaterial:VLoadBumpTexture("Assets\\Textures\\Vehicles\\armoredrecon_N.png")
	armoredReconMeshMaterial:VLoadParallaxTexture("Assets\\Textures\\Vehicles\\armoredrecon_Height.png")
	
	skySphere=GameObject(2)
	skySphereMesh=SkySphereComponent("Assets\\Textures\\SkySphere\\SkyCloudy.dds")
	skySphere:AddComponent(skySphere,skySphereMesh)
	game:AddGameObject(skySphere)

end