#pragma once
////////////////////////////////////////////////////
// mesh material interface
////////////////////////////////////////////////////

namespace zn
{
    class IMeshMaterial
    {
    public:
        IMeshMaterial() {}
        virtual ~IMeshMaterial() {}
        
        virtual bool VInit() = 0;
        virtual bool VLoadEnvMapTexture( const string& filename ) = 0;
        virtual void VSetProjection( const Mat4x4& mat ) = 0;
        virtual void VSetView( const Mat4x4& mat ) = 0;
        virtual void VSetWorld( const Mat4x4& mat ) = 0;
        virtual void VSetAbientLightColor( const Color& color ) = 0;
        virtual void VSetDiffuseLightColor( const Color& color ) = 0;
        virtual void VSetSpecularLightColor( const Color& color ) = 0;
        virtual void VSetLightDirection( const fVec3& dir ) = 0;
        virtual void VSetCameraPosition( const fVec3& dir ) = 0;
        virtual void VSetTextures() = 0;
        virtual void VSetMaterials() = 0;
        virtual void VBindInputLayout() = 0;
        virtual uint32 VGetPassCount() = 0;
        virtual void VApplyPass( uint32 i ) = 0;
        
        static IMeshMaterial* CreateDefault( const string& filename );

    protected:
        string m_filename;
    };
}