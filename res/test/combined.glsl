#glsl{
    #version 450
    #extension GL_ARB_separate_shader_objects : enable
}

#glsl layout(binding = 0) uniform FrameData {
#hlsl struct FrameData{
    mat4 worldMatrix;
#glsl } frameData;
#hlsl }; ConstantBuffer<FrameData> frameData : register(b0, space5);

void foo(){
    mat4 matrix = frameData.worldMatrix;
}