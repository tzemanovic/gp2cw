
function initGame()

	game=LuaScriptManager.GetGame()
	audio=AudioManager.Get()
	audio:Init()
	
	--human view
	humanView=ViewHumanFirstPerson()
	game:AddView(humanView)
	humanView:SetCameraOffset(Vec3(0.0,2.0,-7.0))
	humanView:SetAmbientLightColor(Color( 0.2, 0.1, 0.3, 0.5 ))
	humanView:SetDiffuseLightColor(Color( 1.0, 0.95, 0.8, 0.9 ))
	humanView:SetSpecularLightColor(Color( 1.0, 1.0, 1.0, 0.6 ))
	humanView:SetLightDirection(Vec3( -1.0, -0.5, 0.1 ))
	
	-- sky
	skySphere=GameObject(1)
	skySphereMesh=SkySphereComponent("Assets\\Textures\\SkySphere\\SkyCloudy.dds")
	skySphere:AddComponent(skySphere,skySphereMesh)
	game:AddGameObject(skySphere)
	
	-- terrain
	terrain=GameObject(2)
	terrainTrans=TransformComponent()
	terrainTrans:SetPosition(Vec3(0.0,-0.5,0.0))
	terrain:AddComponent(terrain,terrainTrans)
	terrainMesh=MeshComponent()
	terrainMesh:CreateCubeGeometry(Vec3(500.0, 0.01, 500.0))
	terrain:AddComponent(terrain,terrainMesh)
	terrainBody=RigidBodyComponent(true,1.0)
	terrain:AddComponent(terrain,terrainBody)
	terrainBoxCollider=BoxColliderComponent(Vec3(500.0, 0.01, 500.0))
	terrain:AddComponent(terrain,terrainBoxCollider)
	game:AddGameObject(terrain)
	terrainMeshMaterial=terrainMesh:GetMeshMaterial()
	terrainMeshMaterial:LoadDiffuseTexture("Assets\\Textures\\Ground\\ground6_color.jpg")
	terrainMeshMaterial:LoadSpecularTexture("Assets\\Textures\\Ground\\ground6_spec.jpg")
	terrainMeshMaterial:LoadBumpTexture("Assets\\Textures\\Ground\\ground6_normal.jpg")
	--terrainMeshMaterial:LoadParallaxTexture("Assets\\Textures\\Ground\\ground6_height.jpg")
	terrainMeshMaterial:SetTextureRepeat(Vec2(250.0, 250.0))
	
	-- new armored recond game object
	--[[
	armoredRecon=GameObject(3)
	armoredReconTrans=TransformComponent()
	armoredReconTrans:SetPosition(Vec3(0.0,2.5,10.0))
	armoredReconTrans:SetScale(Vec3(1.0,1.0,1.0))
	armoredReconTrans:SetRotation(Vec3(0.0,180.0,20.0))
	armoredRecon:AddComponent(armoredRecon,armoredReconTrans)
	armoredReconMesh=MeshComponent()
	armoredReconMesh:LoadGeometryFromFile("Assets\\Models\\Vehicles\\armoredrecon.fbx", 1.0)
	armoredRecon:AddComponent(armoredRecon,armoredReconMesh)
	armoredReconBody=RigidBodyComponent(false,1.0)
	armoredRecon:AddComponent(armoredRecon,armoredReconBody)
	armoredReconMeshCollider=MeshColliderComponent()
	armoredRecon:AddComponent(armoredRecon,armoredReconMeshCollider)
	game:AddGameObject(armoredRecon)
	armoredReconMeshMaterial=armoredReconMesh:GetMeshMaterial()
	armoredReconMeshMaterial:LoadDiffuseTexture("Assets\\Textures\\Vehicles\\armoredrecon_diff.png")
	armoredReconMeshMaterial:LoadSpecularTexture("Assets\\Textures\\Vehicles\\armoredrecon_spec.png")
	armoredReconMeshMaterial:LoadBumpTexture("Assets\\Textures\\Vehicles\\armoredrecon_N.png")
	--armoredReconMeshMaterial:LoadParallaxTexture("Assets\\Textures\\Vehicles\\armoredrecon_Height.png")
	--]]
	
	-- new knight game object
	knight1=GameObject(4)
	charInfo=CharacterControllerInfo()
	knight1Trans=TransformComponent()
	knight1Trans:SetPosition(Vec3(0.0,1.5,-5.0))
	knight1Trans:SetScale(Vec3(1.0,1.0,1.0))
	knight1Trans:SetRotation(Vec3(0.0,0.0,0.0))
	knight1:AddComponent(knight1,knight1Trans)
	knight1Mesh=MeshComponent()
	knight1Mesh:LoadGeometryFromFile("Assets\\Models\\Characters\\Knight\\knight.fbx", 0.009)
	knight1:AddComponent(knight1,knight1Mesh)
	knight1Body=FirstPersonCharacterComponent(charInfo)
	knight1:AddComponent(knight1,knight1Body)
	knight1StepSound=AudioComponent()
	knight1StepSound:SetFilename("Assets\\Audio\\Sounds\\Knight\\earthSteps.ogg")
	knight1:AddComponent(knight1,knight1StepSound)
	game:AddGameObject(knight1)
	knight1MeshMaterial=knight1Mesh:GetMeshMaterial()
	knight1MeshMaterial:LoadDiffuseTexture("Assets\\Textures\\Characters\\Knight\\T_Black_Knight_D.jpg")
	knight1MeshMaterial:LoadBumpTexture("Assets\\Textures\\Characters\\Knight\\T_Black_Knight_N.jpg")
	
	humanView:SetOwner(4)
	humanView:SetControlledObject(knight1Body)
	
	
	holzbank1=GameObject(5)
	holzbank1Trans=TransformComponent()
	holzbank1Trans:SetPosition(Vec3(5.0,-0.1,0.0))
	holzbank1Trans:SetScale(Vec3(1.0,1.0,1.0))
	holzbank1Trans:SetRotation(Vec3(270.0,0.0,0.0))
	holzbank1:AddComponent(holzbank1,holzbank1Trans)
	holzbank1Mesh=MeshComponent()
	holzbank1Mesh:LoadGeometryFromFile("Assets\\Models\\Constructs\\holzbank.fbx", 0.04)
	holzbank1:AddComponent(holzbank1,holzbank1Mesh)
	holzbank1Body=RigidBodyComponent(false,1.0)
	holzbank1:AddComponent(holzbank1,holzbank1Body)
	holzbank1MeshCollider=MeshColliderComponent()
	holzbank1:AddComponent(holzbank1,holzbank1MeshCollider)
	game:AddGameObject(holzbank1)
	holzbank1MeshMaterial=holzbank1Mesh:GetMeshMaterial()
	holzbank1MeshMaterial:LoadDiffuseTexture("Assets\\Textures\\Constructs\\holzbank.bmp")
	holzbank1MeshMaterial:LoadSpecularTexture("Assets\\Textures\\Constructs\\holzbankS.bmp")
	holzbank1MeshMaterial:LoadBumpTexture("Assets\\Textures\\Constructs\\holzbankN.bmp")
	
	
	soldierStatus1=GameObject(6)
	soldierStatus1Trans=TransformComponent()
	soldierStatus1Trans:SetPosition(Vec3(10.0,5.8,0.0))
	soldierStatus1Trans:SetRotation(Vec3(270.0,0.0,0.0))
	soldierStatus1:AddComponent(soldierStatus1,soldierStatus1Trans)
	soldierStatus1Mesh=MeshComponent()
	soldierStatus1Mesh:LoadGeometryFromFile("Assets\\Models\\Constructs\\soldierStatus.fbx", 0.02)
	soldierStatus1:AddComponent(soldierStatus1,soldierStatus1Mesh)
	soldierStatus1Body=RigidBodyComponent(true,1.0)
	soldierStatus1:AddComponent(soldierStatus1,soldierStatus1Body)
	soldierStatus1MeshCollider=MeshColliderComponent()
	soldierStatus1:AddComponent(soldierStatus1,soldierStatus1MeshCollider)
	game:AddGameObject(soldierStatus1)
	soldierStatus1MeshMaterial=soldierStatus1Mesh:GetMeshMaterial()
	soldierStatus1MeshMaterial:LoadDiffuseTexture("Assets\\Textures\\Constructs\\soldierStatus.bmp")
	soldierStatus1MeshMaterial:LoadSpecularTexture("Assets\\Textures\\Constructs\\soldierStatusS.bmp")
	soldierStatus1MeshMaterial:LoadBumpTexture("Assets\\Textures\\Constructs\\soldierStatusN.bmp")
	
	
	underStand1=GameObject(7)
	underStand1Trans=TransformComponent()
	underStand1Trans:SetPosition(Vec3(-5.0,-0.3,0.0))
	underStand1Trans:SetRotation(Vec3(270.0,0.0,0.0))
	underStand1:AddComponent(underStand1,underStand1Trans)
	underStand1Mesh=MeshComponent()
	underStand1Mesh:LoadGeometryFromFile("Assets\\Models\\Constructs\\underStand.fbx", 0.03)
	underStand1:AddComponent(underStand1,underStand1Mesh)
	underStand1Body=RigidBodyComponent(true,1.0)
	underStand1:AddComponent(underStand1,underStand1Body)
	underStand1MeshCollider=MeshColliderComponent()
	underStand1:AddComponent(underStand1,underStand1MeshCollider)
	game:AddGameObject(underStand1)
	underStand1MeshMaterial=underStand1Mesh:GetMeshMaterial()
	underStand1MeshMaterial:LoadDiffuseTexture("Assets\\Textures\\Constructs\\underStand.bmp")
	underStand1MeshMaterial:LoadSpecularTexture("Assets\\Textures\\Constructs\\underStandS.bmp")
	underStand1MeshMaterial:LoadBumpTexture("Assets\\Textures\\Constructs\\underStandN.bmp")
	
	
	woodboard1=GameObject(8)
	woodboard1Trans=TransformComponent()
	woodboard1Trans:SetPosition(Vec3(0.0,-0.3,0.0))
	woodboard1Trans:SetRotation(Vec3(270.0,0.0,0.0))
	woodboard1:AddComponent(woodboard1,woodboard1Trans)
	woodboard1Mesh=MeshComponent()
	woodboard1Mesh:LoadGeometryFromFile("Assets\\Models\\Constructs\\woodboard.fbx", 0.03)
	woodboard1:AddComponent(woodboard1,woodboard1Mesh)
	woodboard1Body=RigidBodyComponent(false,1.0)
	woodboard1:AddComponent(woodboard1,woodboard1Body)
	woodboard1MeshCollider=MeshColliderComponent()
	woodboard1:AddComponent(woodboard1,woodboard1MeshCollider)
	game:AddGameObject(woodboard1)
	woodboard1MeshMaterial=woodboard1Mesh:GetMeshMaterial()
	woodboard1MeshMaterial:LoadDiffuseTexture("Assets\\Textures\\Constructs\\woodboard.bmp")
	woodboard1MeshMaterial:LoadSpecularTexture("Assets\\Textures\\Constructs\\woodboardS.bmp")
	woodboard1MeshMaterial:LoadBumpTexture("Assets\\Textures\\Constructs\\underStandN.bmp")
	
	
	bgmusic1=audio:LoadSound("Assets\\Audio\\Music\\music_misty_room.ogg", true, true, false)
	audio:PlaySound(bgmusic1,-1)

end