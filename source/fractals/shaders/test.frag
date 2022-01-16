
uniform vec2 u_resolution;

in vec4 gl_FragCoord;

void main()
{
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    gl_FragColor = vec4(st.xy, 0.0, 1.0);
}