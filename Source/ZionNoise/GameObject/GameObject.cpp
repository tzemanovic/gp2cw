////////////////////////////////////////////////////
// game object
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "GameObject.h"

namespace zn
{
    GameObject::GameObject( GameObjectId id ) : m_id( id )
    {

    }

    GameObject::~GameObject()
    {

    }

    void GameObject::Destroy()
    {
        m_components.clear();
    }

    void GameObject::AddComponent( shared_ptr< GameObject > pGameObject, shared_ptr< IGameObjectComponent > pComponent )
    {
        m_components.insert( pair< GameObjectComponentType, shared_ptr< IGameObjectComponent > >( pComponent->GetType(), pComponent ) );
        pComponent->SetGameObject( pGameObject );
    }

    void GameObject::SAddComponent( shared_ptr< GameObject > pGameObject, shared_ptr< IGameObjectComponent > pComponent )
    {
        pGameObject->AddComponent( pGameObject, pComponent );
        //m_components.insert( pair< GameObjectComponentType, shared_ptr< IGameObjectComponent > >( pComponent->GetType(), pComponent ) );
        //pComponent->SetGameObject( pGameObject );
    }
    
    bool GameObject::Init()
    {
        bool result = true;
        for( GameObjectComponentsMap::iterator it = m_components.begin(), end = m_components.end(); it != end; ++it )
        {
            if( !it->second->VInit() )
            {
                result = false;
                break;
            }
        }
        return result;
    }
}