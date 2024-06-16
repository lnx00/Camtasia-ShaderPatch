vec3 blueprint(vec2 uv) {
    float lineWidth = 0.02;
    float line = step(1.0 - lineWidth, abs(fract(uv.x) - 0.5) + abs(fract(uv.y) - 0.5));
    return mix(vec3(0.0, 0.2, 0.6), vec3(1.0), line);
}

float vignette(vec2 uv) {
    vec2 aspect = vec2(_ImageSize.x / _ImageSize.y, 1.0);
    uv = (uv - 0.5) * aspect + 0.5;

    float dist = length(uv - 0.5);
    return smoothstep(1.5, 0.2, dist);
}

void main() {
    vec2 uv = _TexCoord * (_ImageSize / _ImageSize.y);

    // Move the pattern diagonally
    uv -= _Time * 0.05;

    // Scale the pattern to make it larger
    uv *= 4.0;

    // Get the blueprint color
    vec3 color = blueprint(uv);

    // Apply vignette effect
    float vig = vignette(_TexCoord);
    color *= vig;

    _FragColor = vec4(color, 1.0);
}