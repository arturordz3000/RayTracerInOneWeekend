//
//  hitable_list.h
//  RayTracerInOneWeekend
//
//  Created by Arturo de Jesús Rodriguez Arteaga on 27/09/18.
//  Copyright © 2018 Cervello. All rights reserved.
//

#ifndef hitable_list_h
#define hitable_list_h

#include "hitable.h"

class hitable_list: public hitable
{
public:
    hitable_list() {}
    hitable_list(hitable **list, int n) { this->list = list; list_size = n; }
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    
    hitable **list;
    int list_size;
};

bool hitable_list::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = tmax;
    
    for (int i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, tmin, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    
    return hit_anything;
}

#endif /* hitable_list_h */
