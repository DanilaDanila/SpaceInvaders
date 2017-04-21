uniform float time;

void main()
{
    gl_FragColor=vec4(0,0,(sin(float(4)*time)+float(1))/float(6)+0.1,1);
}
