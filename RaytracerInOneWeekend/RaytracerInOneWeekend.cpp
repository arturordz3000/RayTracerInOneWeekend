#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "sphere.h"
#include "hitable_list.h"

std::ofstream out("image.ppm");

vec3 color(const ray& r, hitable *world)
{
    hit_record rec;
    if (world->hit(r, 0, MAXFLOAT, rec))
    {
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        
        // Since the unit_direction variable can have positive and negative values in its "Y" coordinate (-1 < Y < 1),
        // we need to tranform those values so that 0 < t < 1;
        float t = 0.5 * (unit_direction.y() + 1);
        
        // We now interpolate between white (1, 1, 1) and blue (0.5, 0.7, 1.0) depending on the ray's up/downess
        return (1 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    std::cout.rdbuf(out.rdbuf());
    
    int width = 200;
    int height = 100;
    
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    
    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);
    
    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r, world);
            
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    return 0;
}
