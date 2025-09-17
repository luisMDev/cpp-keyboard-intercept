#pragma once
#include "dxsdk/Include/d3dx9math.h"

namespace {


const std::string shaderCodeD10 = "\
Texture2D SpriteTex;\
SamplerState samLinear{\
    Filter = MIN_MAG_MIP_LINEAR;\
};\
struct VertexIn {\
    float3 PosNdc : POSITION;\
    float2 Tex : TEXCOORD;\
    float4 Color : COLOR;\
};\
struct VertexOut {\
    float4 PosNdc : SV_POSITION;\
    float2 Tex : TEXCOORD;\
    float4 Color : COLOR;\
};\
VertexOut VShader(VertexIn vin) {\
    VertexOut vout;\
    vout.PosNdc = float4(vin.PosNdc, 1.0f);\
    vout.Tex = vin.Tex;\
    vout.Color = vin.Color;\
    return vout;\
};\
float4 PShader(VertexOut pin) : SV_Target{\
    float4 rgba = pin.Color*SpriteTex.Sample(samLinear, pin.Tex);\
    return float4(rgba.b, rgba.g, rgba.r, rgba.a);\
};\
float4 PShaderG(VertexOut pin) : SV_Target{\
    float4 rgba = pin.Color*SpriteTex.Sample(samLinear, pin.Tex);\
    float4 c = float4(rgba.b, rgba.g, rgba.r, rgba.a);\
    c.xyz = pow(abs(c.xyz), 2.2f);\
    return c;\
};\
";


const std::string shaderCode = "\
Texture2D SpriteTex;\
SamplerState samLinear{\
    Filter = MIN_MAG_MIP_LINEAR;\
};\
struct VertexIn {\
    float3 PosNdc : POSITION;\
    float2 Tex : TEXCOORD;\
    float4 Color : COLOR;\
};\
struct VertexOut {\
    float4 PosNdc : SV_POSITION;\
    float2 Tex : TEXCOORD;\
    float4 Color : COLOR;\
};\
VertexOut VShader(VertexIn vin) {\
    VertexOut vout;\
    vout.PosNdc = float4(vin.PosNdc, 1.0f);\
    vout.Tex = vin.Tex;\
    vout.Color = vin.Color;\
    return vout;\
};\
float4 PShader(VertexOut pin) : SV_Target{\
    return pin.Color*SpriteTex.Sample(samLinear, pin.Tex);\
};\
float4 PShaderG(VertexOut pin) : SV_Target{\
    float4 c = pin.Color*SpriteTex.Sample(samLinear, pin.Tex);\
    c.xyz = pow(abs(c.xyz), 2.2f);\
    return c;\
};\
";

}


struct  SpriteVertex
{
    D3DXVECTOR3 position;
    D3DXVECTOR2 tex;
    D3DXCOLOR color;
};

inline D3DXVECTOR3 PointToNdc(int x, int y, float z, float targetWidth, float targetHeight)
{
    float X = 2.0f * (float)x / targetWidth - 1.0f;
    float Y = 1.0f - 2.0f * (float)y / targetHeight;
    float Z = z;

    return D3DXVECTOR3(X, Y, Z);
}
