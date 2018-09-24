#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "ray.h"

std::ofstream out("image.ppm");

void setFile()
{
    std::cout.rdbuf(out.rdbuf());
}

float hit_sphere(const vec3& center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    
    // A discriminant lesser than 0 means that there's no hit point
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        // This is the general formula to solve a quadratic equation
        return (-b - sqrt(discriminant)) / (2 * a);
    }
}

vec3 color(const ray& r)
{
    // Sphere center
    vec3 c = vec3(0, 0, -1);
    
    // t is the result of the quadratic equation Ax2 + 2Bx + C = 0
    float t = hit_sphere(c, 0.5, r);
    
    if (t >= 0)
    {
        // Hit point
        vec3 p = r.point_at_parameter(t);
        
        // The normal vector of a sphere is given by the hit point minus the sphere center (p - c)
        vec3 N = unit_vector(p - c);
        
        // Converting the normal vector to the range of 0 to 1
        return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    
    vec3 unit_direction = unit_vector(r.direction());
    
    // Since the unit_direction variable can have positive and negative values in its "Y" coordinate (-1 < Y < 1),
    // we need to tranform those values so that 0 < t < 1;
    t = 0.5 * (unit_direction.y() + 1);
    
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
