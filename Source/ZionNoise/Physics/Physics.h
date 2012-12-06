#pragma once
////////////////////////////////////////////////////
// game physics
////////////////////////////////////////////////////

// Error function, this will get called if there is an error with Havok
static void HK_CALL errorReport( const char* msg, void* userContext );

#include "..\Utilities\INoCopy.h"

namespace zn
{
    class ContactListener;
    class RigidBodyComponent;

    typedef map< GameObjectId, RigidBodyComponent* > RigidBodyMap;

    class Physics : private INoCopy
    {
    public:
        ~Physics();

        static Physics* Get()
        {
            static Physics instance;
            return &instance;
        }

        void Init();
        void Update( float deltaMs );
        void SyncVisibleScene();
        void AddEntity( GameObjectId id, RigidBodyComponent* pRigidBodyComponent );

        hkpWorld* GetWorld() { return m_pWorld; }
        ContactListener* GetContactListener() { return m_pContactListener; }

    private:
        Physics();
        void Destroy();
        
        hkpWorld* m_pWorld;
        hkpWorldCinfo m_worldInfo;
	    hkVisualDebugger* m_pVisualDebugger;
	    hkpPhysicsContext* m_pPhysicsContext;
        ContactListener* m_pContactListener;
	    bool m_useVisualDebugger;
        RigidBodyMap m_rigidBodies;
        float m_currentTime;
    };

    extern const float PHYSICS_UPDATE_TIME;
}