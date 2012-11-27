#pragma once
////////////////////////////////////////////////////
// transform component
////////////////////////////////////////////////////

#include "IGameObjectComponent.h"

namespace zn
{
    class TransformComponent : public IGameObjectComponent
    {
    public:
        TransformComponent();

        void VUpdate( const float deltaMs );

        const Mat4x4 GetTransform() const { return m_transform; }
        const fVec3& GetPosition() const { return m_pos; }
        void SetPosition( const fVec3& pos ) { m_transform.SetPosition( pos ); m_pos = pos; m_changeTransform = true; }
        const Quaternion& GetRotation() const { return m_rot; }
        void SetRotation( const Quaternion& rot ) { m_rot = rot; m_changeTransform = true; }
        const fVec3& GetScale() const { return m_scale; }
        void SetScale( const fVec3& scale ) { m_scale = scale; m_changeTransform = true; }
        
    private:
        Mat4x4 m_transform, m_matPos, m_matScale, m_matRot;
        fVec3 m_pos, m_scale;
        Quaternion m_rot;
        bool m_changeTransform;
    };
}