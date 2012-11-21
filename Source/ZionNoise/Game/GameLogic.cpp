////////////////////////////////////////////////////
// game logic
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "GameLogic.h"
#include "..\GameObject\GameObject.h"

namespace zn
{
    GameLogic::GameLogic()
    {

    }

    GameLogic::~GameLogic()
    {
        while( !m_viewList.empty() )
		    m_viewList.pop_front();
        for( GameObjectMap::iterator it = m_gameObjectMap.begin(), end = m_gameObjectMap.end(); it != end; ++it )
            it->second->Destroy();
        m_gameObjectMap.clear();
    }

    void GameLogic::AddView( shared_ptr< IView > pView, GameObjectId gameObjectId )
    {
        uint32 viewId = static_cast<int>( m_viewList.size() );
        m_viewList.push_back( pView );
        pView->Attach( viewId, gameObjectId );
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