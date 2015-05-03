uniform sampler2DRect image;
uniform int imgWidth,imgHeight;
uniform float rand;
uniform float timer;
uniform int flags;
uniform vec2 blur_vec;
uniform float level;

int flgs;
float pix_w,pix_h;
varying vec3 pos;

void main (void)
{
    
    float s = sin(pos.y * level);
    vec2 texCoord = vec2(pos.x + s, pos.y * s);
    vec4 col = texture2DRect(image, texCoord);
    
	gl_FragColor = col;
}
