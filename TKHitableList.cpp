//
//
#include "TKHitableList.h"

bool TKHitableList::hit(const TKRay &r, float t_min, float t_max, TKHitRecord &rec) const
{
	TKHitRecord tmp_rec;
	bool hit_anything = false;
	double close_so_far = t_max;
	for(int i=0; i<list_size; ++i){
		if(list[i]->hit(r, t_min, close_so_far, tmp_rec)== true){
			hit_anything = true;
			close_so_far = tmp_rec.t;
			rec = tmp_rec;
		}
	}
	return hit_anything;
}


