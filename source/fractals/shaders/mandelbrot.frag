// Author:
// Title:
#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 cameraPos;
uniform float zoom;
out vec4 FragColor;

vec2 pixel_pos_to_number_pos(in vec2 pixel) {
	    return (vec2(pixel.x, u_resolution.y - pixel.y - 1) - cameraPos) * zoom;
}

float mandelbrot(in float cx, in float cy) {
    // Bulb checking:
    float p = sqrt(pow(cx-0.25, 2.0) + pow(cy, 2.0));
    if (cx <= p - 2.0*pow(p, 2.0) + 0.25 || pow(cx + 1.0, 2.0) + pow(cy, 2.0) <= 0.0625) {
        return 0.0;
    }
    
    float zx = 0.0;
    float zy = 0.0;
    float dzx = 0.0;
    float dzy = 0.0;

    float zxNew = 0.0;
    float zyNew = 0.0;
    float dzxNew = 0.0;
    float dzyNew = 0.0;

    for (int i = 0; i < 100; i++) {
        // zNew = z * z + c
        zxNew = pow(zx, 2.0) - pow(zy, 2.0) + cx;
        zyNew = 2.0 * zx * zy + cy;

        //dzNew = 2 * z * dz + 1
        dzxNew = 2.0 * (zx * dzx - zy * dzy) + 1.0;
        dzyNew = 2.0 * (zy * dzx + zx * dzy);

        zx = zxNew;
        zy = zyNew;
        dzx = dzxNew;
        dzy = dzyNew;

        // |z| >= 2
        if (pow(zx, 2.0) + pow(zy, 2.0) >= 4.0) break;
    }
    float zAbs = sqrt(pow(zx, 2.0) + pow(zy, 2.0));
    float dzAbs = sqrt(pow(dzx, 2.0) + pow(dzy, 2.0));
    float value = zAbs * log(zAbs) / dzAbs;
    return value;
}

vec3 colour_pixel(in float value) {
    const float pi = 3.14159265359;

    float r, g, b;
    if (value != 0.0) {
        r = (sin(log(value)/2.0) + 1.0) / 2.0;
        g = 0.0;
        b = (sin(log(value)/2.0 + pi) + 1.0) / 2.0;
    } else {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }
    vec3 pixelColour = vec3(r, g, b);
    return pixelColour;
}

void main() {
    vec2 pixelPos = gl_FragCoord.xy;
    vec2 numberPos = pixel_pos_to_number_pos(pixelPos);

    vec3 color = vec3(0.0, 0.0, 0.0);
    float value = 0.0;

    value = mandelbrot(numberPos.x, numberPos.y);
    color = colour_pixel(value);

    FragColor = vec4(color,1.0);
}

