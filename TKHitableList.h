#ifndef __TK_HitableList_h__
#define __TK_HitableList_h__

#include "TKHitable.h"

class TKHitableList :public TKHitable
{
public:
	TKHitableList() {};
	TKHitableList(TKHitable **l, int n) {
		list = l;
		list_size = n;
	}
	virtual bool hit(const TKRay &r, float t_min, float t_max, TKHitRecord &rec) const;
	TKHitable **list;
	int list_size;
};

#endif


