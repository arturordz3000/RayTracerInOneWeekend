#ifdef _WIN32
#include "stdafx.h"
#endif
#include <iostream>
#include <fstream>
#include "ray.h"

std::ofstream out("image.ppm");

void setFile()
{
    std::cout.rdbuf(out.rdbuf());
}

bool hit_sphere(const vec3& center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    
    return discriminant > 0;
}

vec3 color(const ray& r)
{
    if (hit_sphere(vec3(0, 0, -1), 0.5, r))
        return vec3(1, 0, 0);
    
    vec3 unit_direction = unit_vector(r.direction());
    
    // Since the unit_direction variable can have positive and negative values in its "Y" coordinate (-1 < Y < 1),
    // we need to tranform those values so that 0 < t < 1;
    float t = 0.5 * (unit_direction.y() + 1);
    
    // We now interpolate between white (1, 1, 1) and blue (0.5, 0.7, 1.0) depending on the ray's up/downess
    return (1 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    setFile();
    
    int width = 200;
    int height = 100;
    
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    
    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    return 0;
}
