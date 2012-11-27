////////////////////////////////////////////////////
// transform component
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "TransformComponent.h"

namespace zn
{
    TransformComponent::TransformComponent() : IGameObjectComponent( GameObjectComponent::Transform ),
        m_changeTransform( false )
    {
        Mat4x4::Identity( &m_transform );
        Mat4x4::Identity( &m_matScale );
        Mat4x4::Identity( &m_matPos );
        Mat4x4::Identity( &m_matRot );
        m_scale = fVec3( 1.f, 1.f, 1.f );
        Quaternion::Identity( &m_rot );
    }

    void TransformComponent::VUpdate( const float deltaMs )
    {
        if( m_changeTransform )
        {
            Geometry::MatrixRotationQuaternion( &m_matRot, &m_rot );
            Geometry::MatrixTranslation( &m_matPos, m_pos );
            Geometry::MatrixScaling( &m_matScale, m_scale );
            Geometry::MatrixMultiply( &m_transform, &m_matRot, &m_matScale );
            Geometry::MatrixMultiply( &m_transform, &m_transform, &m_matPos );
        }
    }
}