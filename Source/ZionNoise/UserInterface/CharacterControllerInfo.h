#pragma once
////////////////////////////////////////////////////
// character controller info
////////////////////////////////////////////////////

namespace zn
{
    struct CharacterControllerInfo
    {
	    CharacterControllerInfo()
		    : maxRunSpeed( 5.0f ),
            maxBackwardSpeed( 1.f ),
            maxStraffeSpeed( 2.5f ),
		    airSpeed( 1.0f ),
		    jumpHeight( 3.0f ),
		    mass( 100.0f ),
		    maxPushForce( 50.0f ),
		    capsuleHeight( 1.2f ),
		    capsuleRadius( 0.3f ),
		    eyeHeight( 1.1f ),
		    gravityStrength( 2.0f )
	    {}

	    float maxRunSpeed;
        float maxBackwardSpeed;
        float maxStraffeSpeed;
	    float airSpeed;
	    float jumpHeight;
	    float mass;
	    float maxPushForce;
	    float capsuleHeight;
	    float capsuleRadius;
	    float eyeHeight;
	    float gravityStrength;
    };
}