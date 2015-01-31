varying vec2 pixpos;
uniform sampler2D iChannel0;

void main() {
    gl_FragColor = vec4(texture2D(iChannel0, vec2(pixpos.x, 1.0-pixpos.y)));
}