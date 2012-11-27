////////////////////////////////////////////////////
// game physics
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Physics.h"
#include "ContactListener.h"
#include "..\GameObject\Component\Physics\RigidBodyComponent.h"
#include "..\Game\GameLogic.h"
#include "..\GameObject\GameObject.h"
#include "..\GameObject\Component\TransformComponent.h"

// Keycode
#include <Common/Base/keycode.cxx>

// Productfeatures
// We're using only physics - we undef products even if the keycode is present so
// that we don't get the usual initialization for these products.
#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR

// Also we're not using any serialization/versioning so we don't need any of these.
#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
//#define HK_EXCLUDE_FEATURE_RegisterReflectedClasses
#define HK_EXCLUDE_FEATURE_MemoryTracker

// This include generates an initialization function based on the products
// and the excluded features.
#include <Common/Base/Config/hkProductFeatures.cxx>

//Error function
static void HK_CALL errorReport( const char* msg, void* userContext )
{
	OutputDebugStringA( msg );
}

namespace zn
{
    const float PHYSICS_UPDATE_TIME( 1000.f / 60.f );

    Physics::Physics() : m_pWorld( NULL ), m_pVisualDebugger( NULL ), m_pPhysicsContext( NULL ), 
        m_pContactListener( NULL ), m_useVisualDebugger( false ), m_currentTime( 0.f )
    {

    }

    Physics::~Physics()
    {
        ZN_SAFE_DELETE( m_pContactListener );
        Destroy();
    }

    void Physics::Init()
    {
        // Need to have memory allocated for the solver. Allocate 1mb for it.
	    hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, 
		    hkMemorySystem::FrameInfo( 1024*1024 ) );
	    //Init base physics system
	    hkBaseSystem::init( memoryRouter, errorReport );
	    //Setup physics world
	    hkpWorldCinfo info;
	    //gravity
	    info.m_gravity.set( 0, -9.8f, 0 );
	    //broad phase world 
	    info.setBroadPhaseWorldSize( 1500.0f );
	    //Physics world creation
	    m_pWorld = new hkpWorld( info );
	    // Register all collision agents
	    // It's important to register collision agents before adding any entities to the world.
	    hkpAgentRegisterUtil::registerAllAgents( m_pWorld->getCollisionDispatcher() );

	    if ( m_useVisualDebugger ){
		    // Register all the physics viewers
		    hkpPhysicsContext::registerAllPhysicsProcesses(); 

		    // Set up a physics context containing the world for the use in the visual debugger
		    m_pPhysicsContext = new hkpPhysicsContext;
		    m_pPhysicsContext->addWorld( m_pWorld ); 
	
		    hkArray<hkProcessContext*> contexts;
		    contexts.pushBack( m_pPhysicsContext );
		    m_pVisualDebugger = new hkVisualDebugger( contexts );
		    m_pVisualDebugger->serve();
	    }

        m_pWorld->addContactListener( m_pContactListener );
    }

    void Physics::Destroy()
    {
        if( m_useVisualDebugger)
		    m_pVisualDebugger->removeReference();

        m_pWorld->removeReference();

        if( m_useVisualDebugger )
		    m_pPhysicsContext->removeReference();

        // exit the base system and memory
        hkBaseSystem::quit();
	    hkMemoryInitUtil::quit();
    }
        
    void Physics::Update( float deltaMs )
    {
        m_currentTime += deltaMs;
        if( m_currentTime >= PHYSICS_UPDATE_TIME )
        {
            m_pWorld->stepDeltaTime( PHYSICS_UPDATE_TIME / 1000.f );
		    //Update visual debugger
		    if( m_useVisualDebugger )
			    m_pVisualDebugger->step();
            m_currentTime = 0.f;
        }
    }

    void Physics::SyncVisibleScene()
    {
        // update the transfrom components with rigid bodies
        for( RigidBodyMap::const_iterator it = m_rigidBodies.begin(); it != m_rigidBodies.end(); ++it )
	    { 
            RigidBodyComponent* pRigidBodyComponent = it->second;
            if( !pRigidBodyComponent->IsFixed() )
            {
		        const GameObjectId id = it->first;
                shared_ptr< GameObject > pGameObject = g_pGame->GetGameLogic()->GetGameObject( id );
                if( pGameObject && pRigidBodyComponent )
                {
                    shared_ptr< TransformComponent > pTransformComponent = MakeStrongPtr( pGameObject->GetComponent< TransformComponent >( GameObjectComponent::Transform ) );
                    if( pTransformComponent )
                    {
                        if( pTransformComponent->GetPosition() != pRigidBodyComponent->GetPosition() )
                        {
                            pTransformComponent->SetPosition( pRigidBodyComponent->GetPosition() );
                        }
                        if( pTransformComponent->GetRotation() != pRigidBodyComponent->GetRotation() )
                        {
                            pTransformComponent->SetRotation( pRigidBodyComponent->GetRotation() );
                        }
                    }
                }
            }
        }
    }

    void Physics::AddEntity( GameObjectId id, RigidBodyComponent* pRigidBodyComponent )
    {
        m_pWorld->addEntity( pRigidBodyComponent->GetRigidBody() );
        m_rigidBodies.insert( make_pair( id, pRigidBodyComponent ) );
    }
}