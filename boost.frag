uniform float time;

void main()
{
    gl_FragColor=vec4((sin(float(4)*time)+float(4))/float(6),0,0,1);
}
