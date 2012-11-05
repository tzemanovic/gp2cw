////////////////////////////////////////////////////
// game logic
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "GameLogic.h"

namespace zn
{
    GameLogic::GameLogic()
    {

    }

    GameLogic::~GameLogic()
    {

    }

    void GameLogic::AddView( shared_ptr< IView > pView, GameObjectId gameObjectId )
    {
        uint32 viewId = static_cast<int>( m_viewList.size() );
        m_viewList.push_back( pView );
        pView->Attach( viewId, gameObjectId );
    }
}