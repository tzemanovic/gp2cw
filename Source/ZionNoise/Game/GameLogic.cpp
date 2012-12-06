////////////////////////////////////////////////////
// game logic
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "GameLogic.h"
#include "..\GameObject\GameObject.h"
#include "..\Physics\Physics.h"

namespace zn
{
    GameLogic::GameLogic()
    {
        // init physics
        Physics::Get()->Init();
    }

    GameLogic::~GameLogic()
    {
        while( !m_viewList.empty() )
		    m_viewList.pop_front();
        for( GameObjectMap::iterator it = m_gameObjectMap.begin(), end = m_gameObjectMap.end(); it != end; ++it )
            it->second->Destroy();
        m_gameObjectMap.clear();
    }

    void GameLogic::AddView( shared_ptr< IView > pView )
    {
        uint32 viewId = static_cast<int>( m_viewList.size() );
        m_viewList.push_back( pView );
    }

    void GameLogic::Update( const float deltaMs )
    {
        Physics::Get()->Update( deltaMs );
        Physics::Get()->SyncVisibleScene();

        // update views
        for( ViewList::iterator i = m_viewList.begin(), end = m_viewList.end();
            i != end; ++i )
        {
            ( *i )->VUpdate( deltaMs );
        }
        // update game actors
        for ( GameObjectMap::const_iterator i = m_gameObjectMap.begin(); i != m_gameObjectMap.end(); ++i )
        {
            i->second->Update( deltaMs );
        }
    }

    shared_ptr< GameObject > GameLogic::GetGameObject( GameObjectId id )
    {
        GameObjectMap::iterator gameObject = m_gameObjectMap.find( id );
        if ( gameObject != m_gameObjectMap.end() )
            return gameObject->second;
        return shared_ptr< GameObject >();
    }

    void GameLogic::AddGameObject( shared_ptr< GameObject > pGameObject )
    {
        if( pGameObject->Init() )
            m_gameObjectMap.insert( make_pair( pGameObject->GetId(), pGameObject ) );
    }
}