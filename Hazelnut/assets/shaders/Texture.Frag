#version 450 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out int color2;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;
uniform float u_TilingFactor;
uniform vec4 u_Color;
in vec4 v_Color;
in float v_TexIndex;
in float v_TilingFactor;
in flat int v_EntityID;
uniform sampler2D u_Textures[32];
void main(){
    //FragColor = texture(u_Texture,v_TexCoord);
    //FragColor = v_Color;
    FragColor = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color; 
    color2 = v_EntityID;
}