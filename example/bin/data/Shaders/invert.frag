uniform sampler2DRect image;
uniform int imgWidth,imgHeight;
uniform float rand;
uniform int flags;
uniform vec2 blur_vec;
uniform float val1,val2,val3,val4;
int flgs;
float pix_w,pix_h;
varying vec3 pos;

void main (void)
{
    vec2 texCoord = vec2(pos.x , pos.y);
	vec4 col = texture2DRect(image,texCoord);;
	col.r = 1.0 - col.r;
	col.g = 1.0 - col.g;
	col.b = 1.0 - col.b;
	gl_FragColor = col;
}
