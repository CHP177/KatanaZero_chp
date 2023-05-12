#include "CBuffers.hlsl"

struct VertexInput
{
    float4 position : POSITION0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
};

 //Vertex Shader
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
        
    return output;
}

//Pixel Shader
float4 PS(PixelInput input) : SV_Target
{
    if (_color.a == 0.0f)
        discard;

    return _color;
}