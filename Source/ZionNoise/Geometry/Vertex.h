#pragma once
////////////////////////////////////////////////////
// vertex
////////////////////////////////////////////////////

#include "Color.h"

namespace zn
{
    struct Vertex
    {
        fVec3 position;
        Color color;
        fVec2 texCoord;
        fVec3 normal;
        fVec3 tangent;
    };

#   ifdef ZN_PLATFORM_WIN32
        static const D3D11_INPUT_ELEMENT_DESC D3D11_LAYOUT[] =
        {
            {
                "POSITION", // semantic name
	            0, // semantic index
	            DXGI_FORMAT_R32G32B32_FLOAT, // format
	            0, // input slot
	            0, // aligned byte offset
	            D3D11_INPUT_PER_VERTEX_DATA, // input slot class
	            0 // instance data step rate
            },

            {
                "COLOR", // semantic name
	            0, // semantic index
	            DXGI_FORMAT_R32G32B32A32_FLOAT, // format
	            0, // input slot
	            12, // aligned byte offset
	            D3D11_INPUT_PER_VERTEX_DATA, // input slot class
	            0 // instance data step rate
            },

            {
                "TEXCOORD", // semantic name
	            0, // semantic index
	            DXGI_FORMAT_R32G32_FLOAT, // format
	            0, // input slot
	            28, // aligned byte offset
	            D3D11_INPUT_PER_VERTEX_DATA, // input slot class
	            0 // instance data step rate
            },

            {
                "NORMAL", // semantic name
	            0, // semantic index
	            DXGI_FORMAT_R32G32B32_FLOAT, // format
	            0, // input slot
	            36, // aligned byte offset
	            D3D11_INPUT_PER_VERTEX_DATA, // input slot class
	            0 // instance data step rate
            },

            {
                "TANGENT", // semantic name
	            0, // semantic index
	            DXGI_FORMAT_R32G32B32_FLOAT, // format
	            0, // input slot
	            48, // aligned byte offset
	            D3D11_INPUT_PER_VERTEX_DATA, // input slot class
	            0 // instance data step rate
            },
        };
#   endif
}