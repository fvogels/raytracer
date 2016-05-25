#ifndef COLOR_H
#define COLOR_H

struct color final
{
    double r, g, b;

    color() : color(0, 0, 0) { }

    color(double r, double g, double b)
        : r(r), g(g), b(b) { }

    void clamp();
    color clamped() const;
};

color operator +(const color&, const color&);
color operator *(const color&, double);
color operator *(double, const color&);
color operator /(const color&, double);

color& operator +=(color&, const color&);
color& operator *=(color&, double);
color& operator /=(color&, double);


// Example usage: color c = colors::black();
namespace colors
{
    inline color black()   { return color{ 0, 0, 0 }; }
    inline color white()   { return color{ 1, 1, 1 }; }
    inline color red()     { return color{ 1, 0, 0 }; }
    inline color green()   { return color{ 0, 1, 0 }; }
    inline color blue()    { return color{ 0, 0, 1 }; }
    inline color yellow()  { return color{ 1, 1, 0 }; }
    inline color magenta() { return color{ 1, 0, 1 }; }
    inline color cyan()    { return color{ 0, 1, 1 }; }
}

#endif
