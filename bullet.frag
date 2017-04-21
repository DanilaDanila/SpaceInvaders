uniform float time;

void main()
{
    gl_FragColor=vec4((sin(float(4)*time)+float(1))/float(2),(sin(float(4)*time+float(2))+float(1))/float(2),(sin(float(4)*time+float(4))+float(1))/float(2),1);
}
