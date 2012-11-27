#pragma once
////////////////////////////////////////////////////
// contact listener
////////////////////////////////////////////////////

namespace zn
{
    class ContactListener : public hkpContactListener
    {
    public:
        ContactListener();
        ~ContactListener();
    };
}