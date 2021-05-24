#version 130

uniform sampler2D tex;
uniform float saturation;

void main()
{
    vec4 color = texture2D(tex, gl_TexCoord[0].xy);
	// Originally 0.33f
    float grayscale = 0.15f * (color.r + color.g + color.b);

    vec4 gray = color;
    gray.rgb = vec3(grayscale);

    gl_FragColor =  (1 - saturation*saturation) * gl_Color * mix(gray, color, saturation);
}
