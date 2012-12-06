#pragma once
////////////////////////////////////////////////////
// human first person view
////////////////////////////////////////////////////

namespace zn
{
    class ViewHumanFirstPerson : public ViewHuman
    {
    public:
        ViewHumanFirstPerson();
        virtual ~ViewHumanFirstPerson();

        void VInit();
        void VUpdate( const float deltaMs );
        const bool VProcessMessage( const Message& message );
        void VSetOwner( GameObjectId id );

        void SetControlledObject( shared_ptr< FirstPersonCharacterComponent > pFirstPersonComp );
        
    private:
        shared_ptr< SceneNode > m_pHumanChar;
        bool m_isFreeCameraController;
        FirstPersonController* m_pFirstPersonController;
    };
};