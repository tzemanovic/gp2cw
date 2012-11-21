#pragma once
////////////////////////////////////////////////////
// screen element interface
////////////////////////////////////////////////////

namespace zn
{
    class IScreenElement
    {
    public:
        IScreenElement() : m_zOrder( 0 ), m_isVisible( true ) {}
	    virtual ~IScreenElement() {}

        virtual void VRender( const float deltaMs ) = 0;
        virtual void VUpdate( const float deltaMs ) = 0;

	    virtual bool const operator<( IScreenElement const &other ) { return GetZOrder() < other.GetZOrder(); }
        
        uint32 GetZOrder() const { return m_zOrder; }
        void SetZOrder( uint32 const zOrder ) { m_zOrder = zOrder; }
        bool IsVisible() const { return m_isVisible; }
        void SetVisible( const bool visible ) { m_isVisible = visible; }

    protected:
        uint32 m_zOrder;
        bool m_isVisible;
    };
}