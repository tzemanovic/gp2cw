#pragma once
////////////////////////////////////////////////////
// first person character component
////////////////////////////////////////////////////

#include "RigidBodyComponent.h"
#include "..\..\..\UserInterface\CharacterControllerInfo.h"

namespace zn
{
    class FirstPersonCharacterComponent : public RigidBodyComponent
    {
    public:
        FirstPersonCharacterComponent( const CharacterControllerInfo& cInfo );
        ~FirstPersonCharacterComponent();

        bool VInit();
        void VUpdate( const float deltaMs );
        void Rotate( const fVec3& axis, const float angleRad );

        const CharacterControllerInfo& GetCharInfo() { return m_charInfo; }
        float GetForwardBack() { return m_forwardBack; }
        void SetForwardBack( const float forwardBack ) { m_forwardBack = forwardBack; }
        float GetLeftRight() { return m_leftRight; }
        void SetLeftRight( const float leftRight ) { m_leftRight = leftRight; }
        void SetJump( const bool jump ) { m_jump = jump; }
        
    protected:
        hkpCharacterRigidBody* m_pCharacterRigidBody;
        hkpCharacterContext* m_pCharacterContext;
        hkpCharacterStateManager* m_pStateManager;
        hkpFirstPersonCharacter* m_pFirstPersonCharacter;
        CharacterControllerInfo m_charInfo;
        float m_currentTime;
        float m_forwardBack;
        float m_leftRight;
        bool m_jump;
    };
}