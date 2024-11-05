#version 330 core
layout(location = 0) out vec4 FragColor;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;
void main(){
    //FragColor = texture(u_Texture,v_TexCoord);
    FragColor = texture(u_Texture,v_TexCoord * 10.0) * vec4(1.0,0.8,0.8,1.0); 
}