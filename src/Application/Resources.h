#pragma once

namespace Resources {

inline const char* DEFAULT_IMGUI_INI = R"(
[Window][DockSpace Demo]
Pos=0,0
Size=1600,900
Collapsed=0

[Window][Debug##Default]
Pos=60,60
Size=400,400
Collapsed=0

[Window][FEN]
Pos=202,465
Size=988,435
Collapsed=0
DockId=0x00000003,0

[Window][Main Layout]
Size=1600,900
Collapsed=0

[Window][Main Layout/Left_93BE0DF7]
IsChild=1
Size=200,865

[Window][Main Layout/Middle_28866EA5]
IsChild=1
Size=1021,865

[Window][Settings]
Pos=0,19
Size=200,881
Collapsed=0
DockId=0x00000006,0

[Window][Setting]
Pos=8,27
Size=200,200
Collapsed=0

[Window][Left Window]
Size=347,559
Collapsed=0

[Window][Right Window]
Pos=349,541
Size=1251,359
Collapsed=0

[Window][Middle Button Window]
Pos=349,0
Size=1251,539
Collapsed=0

[Window][Middle Upper Window]
Pos=0,561
Size=347,339
Collapsed=0

[Window][Chessboard]
Pos=202,19
Size=988,444
Collapsed=0
DockId=0x00000002,0

[Window][Analyzer]
Pos=1192,19
Size=408,881
Collapsed=0
DockId=0x00000005,0

[Docking][Data]
DockSpace       ID=0x3BC79352 Window=0x4647B76E Pos=0,19 Size=1600,881 Split=X
  DockNode      ID=0x00000004 Parent=0x3BC79352 SizeRef=1190,881 Split=X Selected=0x54723243
    DockNode    ID=0x00000006 Parent=0x00000004 SizeRef=200,881 Selected=0x54723243
    DockNode    ID=0x00000001 Parent=0x00000004 SizeRef=988,881 Split=Y
      DockNode  ID=0x00000002 Parent=0x00000001 SizeRef=400,202 Selected=0xA6994AC8
      DockNode  ID=0x00000003 Parent=0x00000001 SizeRef=400,198 Selected=0xAA633A8E
  DockNode      ID=0x00000005 Parent=0x3BC79352 SizeRef=408,881 CentralNode=1 Selected=0xDE6D6DEC


)";

}

namespace Resources::Shaders {

inline const char* FRAGMENT_SHADER = R"(
#version 450 core

out vec4 o_Colour;

in vec4 v_Colour;
in vec2 v_TexCoord;
in float v_TextureSlot;

uniform sampler2D u_Textures[32];

void main() {
    int index = int(v_TextureSlot);
    if (index == 0) {
        o_Colour = v_Colour;
    } else {
        o_Colour = texture(u_Textures[index], v_TexCoord) * v_Colour;
    }
}
)";

inline const char* VERTEX_SHADER = R"(
#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float textureSlot;

out vec4 v_Colour;
out vec2 v_TexCoord;
out float v_TextureSlot;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * position;
    v_Colour = colour;
    v_TexCoord = texCoord;
    v_TextureSlot = textureSlot;
}
)";

}