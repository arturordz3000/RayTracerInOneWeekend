//
//  sphere.h
//  RayTracerInOneWeekend
//
//  Created by Arturo de Jesús Rodriguez Arteaga on 23/09/18.
//  Copyright © 2018 Cervello. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "hitable.h"

class sphere : public hitable
{
public:
    sphere() {};
    sphere(vec3 cen, float r) : center(cen), radius(r) {};
    virtual bool hit(const ray&, float tmin, float tmax, hit_record& rec) const;
    
    vec3 center;
    float radius;
};

void create_hit_record(const ray &r, const vec3 center, const float radius, const float t, hit_record &rec)
{
    rec.t = t;
    rec.p = r.point_at_parameter(t);
    rec.normal = (rec.p - center) / radius;
}

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    /***
     * The original algorithm was:
     
     vec3 oc = r.origin() - center;
     float a = dot(r.direction(), r.direction());
     float b = 2.0 * dot(oc, r.direction());
     float c = dot(oc, oc) - radius * radius;
     
     // A discriminant lesser than 0 means that there's no hit point
     float discriminant = b * b - 4 * a * c;
     
     // This is the general formula to solve a quadratic equation
     (-b - sqrt(discriminant)) / (2 * a);
     ***/
    
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    
    // We remove the "2", since the discriminant is computed with a square b (b ^ 2),
    // which in turn results in b getting a value of 4x = 4 * dot(oc, r.direction())
    float b = dot(oc, r.direction());
    
    float c = dot(oc, oc) - radius * radius;
    
    // We also elminate the "4" here, 'cause is cancelled along with the "2" above
    float discriminant = b * b - a * c;
    
    if (discriminant > 0)
    {
        float discriminantRoot = sqrt(discriminant);
        
        // We also eliminate the "2" here, 'cause is cancelled along with the "2" and "4" above.
        float temp = (-b - discriminantRoot) / a; // First result out of 2 possible
        
        if (temp < tmax && temp > tmin)
        {
            create_hit_record(r, center, radius, temp, rec);
            return true;
        }
        
        temp = (-b + discriminantRoot) / a; // Second result out of 2 possible
        
        if (temp < tmax && temp > tmin)
        {
            create_hit_record(r, center, radius, temp, rec);
            return true;
        }
    }
    
    return false;
}

#endif /* sphere_h */
