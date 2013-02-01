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
    pix_w = 1.0;
    pix_h = 1.0;
    flgs = flags;

	int step = 5;
	vec4 cols[25];
    vec2 texCoord = vec2(min(max(0.0,pos.x),1.0),min(max(0.0,pos.y),1.0));

	for (int i = 0;i < step;i++){
		for (int j = 0;j < step;j++){
			cols[i*step+j] = texture2DRect(image,vec2((pos.x+float(j)-1.0), (pos.y+float(i)-1.0)));
			cols[i*step+j].r = (cols[i*step+j].r + cols[i*step+j].g + cols[i*step+j].b) / 3.0;
		}
	}
	float mn = 1.0,mx = 0.0;
	for (int i = 0;i < step*step;i++){
		mn = min(cols[i].r,mn);
		mx = max(cols[i].r,mx);
	}
	float dst = abs(1.0 - (mx-mn));
	gl_FragColor.a = 1.0;
    gl_FragColor.rgb = vec3(dst,dst,dst)+cols[12].rgb;
}
