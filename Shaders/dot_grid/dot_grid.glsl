uniform float _XSpeed;
uniform float _YSpeed;

float smooth_circle_using_length(vec2 position, float radius) {
    vec2 d = position - vec2(0.5);
    return 1.0 - smoothstep(0.0, radius, length(d));
}

void main(void) {
    vec2 uv = _TexCoord * (_ImageSize / _ImageSize.y);

    float gridSize = 15.0;
    vec2 dotPos = fract((uv * gridSize) - vec2(_Time * _XSpeed, _Time * _YSpeed));

    float dot = smooth_circle_using_length(dotPos, 0.1);

    vec3 bgColor = vec3(0.1, 0.1, 0.1);
    vec3 dotColor = vec3(0.2, 0.2, 0.2);

    vec3 color = mix(bgColor, dotColor, dot);
    _FragColor = vec4(color, 1.0);
}
