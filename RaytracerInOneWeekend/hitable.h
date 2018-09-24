//
//  hitable.h
//  RayTracerInOneWeekend
//
//  Created by Arturo de Jesús Rodriguez Arteaga on 23/09/18.
//  Copyright © 2018 Cervello. All rights reserved.
//

#ifndef hitable_h
#define hitable_h

#include "ray.h"

struct hit_record
{
    float t;
    vec3 p;
    vec3 normal;
};

class hitable
{
    public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif /* hitable_h */
