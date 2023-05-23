#include "CBuffers.hlsl"

struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
};

//Vertex Shader
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
    
    output.uv = input.uv;
    
    return output;
}

//Extract Color from UV
Texture2D srcTex : register(t0);
SamplerState samp : register(s0);

//Pixel Shader
float4 PS(PixelInput input) : SV_Target
{
    //Input Color Sampling
    float4 color = srcTex.Sample(samp, input.uv);

    if (input.uv.x > 0 || input.uv.y > 0)
        return color;
    else
        return float4(0, 0, 0, 1);
}