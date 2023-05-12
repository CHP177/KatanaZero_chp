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

    if (color.r == 1.0f && color.g == 0.0f && color.b == 1.0f)
        discard;

    //border line
    float border = 1.0f / 128.0f;

    if (_bOutline && (input.uv.x < border || input.uv.x > 1.0f - border || input.uv.y < border || input.uv.y > 1.0f - border))
        color = float4(1, 0.2f, 0.2f, 1);

    return color;
}