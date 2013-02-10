/*
 * Particle_Attractor.cpp - attractor particle
 * Release into public domain.
 */

#include "Particle_Attractor.h"

byte Particle_Attractor::ax = 0;
byte Particle_Attractor::ay = 0;
signed char Particle_Attractor::af = 0;

Particle_Attractor::Particle_Attractor()
{
    isAlive = false;
}

void Particle_Attractor::update(void)
{
    int dx, dy;
    signed char acx, acy;
    float mult;
    //age
    //ttl--;

    dx = ax - x;
    dy = ay - y;
    mult = (float)af/sqrt(dx*dx+dy*dy);
    acx = (signed char)(mult*dx);
    acy = (signed char)(mult*dy);

//    acx = -1*af;
//    acy = -1;

    //apply acceleration
    vx = min(vx+acx, PS_MAX_X);
    vy = min(vy+acy, PS_MAX_Y);

    //apply velocity
    unsigned int newX, newY;
    if (y == 0 || y == PS_MAX_Y) {
        vy = -1*vy;
    }
    if (x == 0 || x == PS_MAX_X) {
        vx = -1*vx;
    }
    if (ttl == 0 || (vx == 0 && vy == 0)) {
        isAlive = false;
    } else {
        x = min(max(x+vx, 0), PS_MAX_X);
        y = min(max(y+vy, 0), PS_MAX_Y);
    }
}
