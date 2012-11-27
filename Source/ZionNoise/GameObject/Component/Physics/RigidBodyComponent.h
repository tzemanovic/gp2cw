#pragma once
////////////////////////////////////////////////////
// rigid body component
////////////////////////////////////////////////////

#include "..\IGameObjectComponent.h"

namespace zn
{
    class RigidBodyComponent : public IGameObjectComponent
    {
    public:
        RigidBodyComponent( bool isFixed = false, float mass = 1.0f );
        ~RigidBodyComponent();

        bool VInit();
        //void VUpdate( float deltaMs );
        fVec3 GetPosition();
        Quaternion GetRotation();

        hkpRigidBody* GetRigidBody() const { return m_pRigidBody; }
        const bool IsFixed() const { return m_isFixed; }
    protected:
        hkpRigidBody* m_pRigidBody;
	    float m_mass;
	    bool m_isFixed;
    };
}