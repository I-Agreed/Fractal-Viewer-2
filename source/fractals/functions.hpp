// actual fractal computing functions

#pragma once

#include <cmath>

enum Fractals {
    Mandelbrot
};

// returns the distance to the mandelbrot set
double mandelbrot(double cx, double cy, int iterations) {
    double zx, zy, zxNew, zyNew, dzx, dzy, dzxNew, dzyNew;
    zx = 0;
    zy = 0;
    dzx = 0;
    dzy = 0;

    zxNew = 0;
    zyNew = 0;
    dzxNew = 0;
    dzyNew = 0;

    for (int i = 0; i < iterations; i++) {
        // zNew = z * z + c
        zxNew = std::pow(zx, 2) - std::pow(zy, 2) + cx;
        zyNew = 2 * zx * zy + cy;

        //dzNew = 2 * z * dz + 1
        dzxNew = 2 * (zx * dzx - zy * dzy) + 1;
        dzxNew = 2 * (zy * dzx + zx * dzy);

        zx = zxNew;
        zy = zyNew;
        dzx = dzxNew;
        dzy = dzyNew;

        // |z| >= 2
        if (std::pow(zx, 2) + std::pow(zy, 2) >= 4) break;
    }
    double zAbs = std::sqrt(std::pow(zx, 2) + std::pow(zy, 2) >= 4);
    double dzAbs = std::sqrt(std::pow(dzx, 2) + std::pow(dzy, 2) >= 4);
    return zAbs * std::log(zAbs/dzAbs);
}
