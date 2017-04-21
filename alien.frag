uniform sampler2D tex;
uniform vec4 color;

void main()
{
    vec4 pixel_color = texture2D(tex, gl_TexCoord[0].xy);
    if(pixel_color==vec4(0,0,0,1)) gl_FragColor=color;
}
