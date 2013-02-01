uniform sampler2DRect image;
uniform float rand;
uniform int range;

varying vec3 pos;


void main (void)
{
    float e = 2.718281828459045235360287471352;
    vec2 texCoord = vec2(pos.x , pos.y);
    vec4 col = texture2DRect(image,texCoord);
    
    vec3 k =   vec3(0.8,0.8,0.8);
    vec3 min = vec3(0.0,0.0,0.0);
    vec3 max = vec3(1.0,1.0,1.0);
    
    col.r = (1.0/(1.0+pow(e,(-k.r*((col.r*2.0)-1.0)*20.0)))*(max.r-min.r)+min.r);
    col.g = (1.0/(1.0+pow(e,(-k.g*((col.g*2.0)-1.0)*20.0)))*(max.g-min.g)+min.g);
    col.b = (1.0/(1.0+pow(e,(-k.b*((col.b*2.0)-1.0)*20.0)))*(max.b-min.b)+min.b);
    
    gl_FragColor.rgba = col.rgba;
}