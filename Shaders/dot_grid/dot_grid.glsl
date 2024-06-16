uniform float _XSpeed;
uniform float _YSpeed;

void main(void) {
    vec2 uv = _TexCoord * (_ImageSize / _ImageSize.y);

    float gridSize = 15.0;
    vec2 dotPos = fract((uv * gridSize) - vec2(_Time * _XSpeed, _Time * _YSpeed));

    float dist = length(dotPos - 0.5);
    float dot = smoothstep(0.02, 0.03, 0.05 - dist);

    vec3 bgColor = vec3(0.1, 0.1, 0.1);
    vec3 dotColor = vec3(1.0, 1.0, 1.0);

    vec3 color = mix(bgColor, dotColor, dot);
    _FragColor = vec4(color, 1.0);
}
