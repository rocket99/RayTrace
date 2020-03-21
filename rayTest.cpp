//
//rayTest.cpp
//

#include "TKRay.h"
#include "TKSphere.h"
#include "TKHitableList.h"
#include "TKCamera.h"
#include "TKMaterial.h"
#include "TKMath.h"

#include <vector>


void writePPMFile(const char *fileName, uint32_t width, uint32_t height, uint8_t *data)
{
	if(data == nullptr){
		return;
	}
	char buf[512]; memset(buf, 0, sizeof(char)*512);
	sprintf(buf, "P3\n%d %d\n255\n", width, height);
	FILE *fp = fopen(fileName, "wt");
	if(fp == nullptr){
		return;
	}
	fwrite(buf, 1, strlen(buf), fp);

	uint32_t  k = 0;
	for(int i=height-1; i>=0; --i){
		for(uint32_t j=0; j<width; ++j){
			k = i*width+j;
			sprintf(buf, "%d %d %d\n", data[3*k], data[3*k+1], data[3*k+2]);
			fwrite(buf, 1, strlen(buf), fp);
			k += 3;
		}
	}
	fclose(fp);
}

glm::vec3 color(const TKRay &ray, TKHitable *world, int depth) {
	TKHitRecord rec;
	if(world->hit(ray, 0.001f, MAXFLOAT, rec)==true){
		TKRay scattered;
		glm::vec3 attenuation;
		if(depth < 50 && rec.mat_ptr->scatter(ray, rec, attenuation, scattered)){
			return attenuation*color(scattered, world, depth+1);
		}else{
			return glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}
	
	glm::vec3 unir_direction = glm::normalize( ray.direction() );
	float t = 0.5*(unir_direction.y + 1.0);
	return (1.0f-t)*glm::vec3(1.0f, 1.0f, 1.0f) + t*glm::vec3(0.5, 0.7, 1.0);
}

std::vector<TKHitable *> random_scene(){
	printf("1\n");
	int n = 500;
	std::vector<TKHitable *> list;
	list.push_back(new TKSphere(glm::vec3(0.0, -1000.0, 0.0), 1000, new TKLambertian(glm::vec3(0.5f, 0.5f, 0.5f))));
	int i = 1;
	for(int a = -10; a < 10; ++ a){
		for(int b = -10; b < 10; ++ b){
			float choose_mat = drand48();
			glm::vec3 center = glm::vec3(a+0.9f*drand48(), 0.2f, b+0.9f*drand48());
			if((center-glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f){
				if(choose_mat < 0.8f){
					/*
					list.push_back(new TKSphere(center, 0.2,
												new TKLambertian(glm::vec3(drand48()*drand48(),
																		   drand48()*drand48(),
																		   drand48()*drand48()))));
					*/					
					list.push_back(new TKMovingSphere(center, center+glm::vec3(0.0f, 0.5f*drand48(), 0.0f),
													  0.0, 1.0, 0.2,
													  new TKLambertian(glm::vec3(drand48()*drand48(),
																		   drand48()*drand48(),
																		   drand48()*drand48()))));
				}else if(choose_mat < 0.95){
					list.push_back(new TKSphere(center, 0.2f,
												new TKMetal(glm::vec3(0.5f*(1+drand48()),
																	  0.5*(1+drand48()),
																	  0.5*(1+drand48())),
															0.5*drand48())));
				}else{
					list.push_back(new TKSphere(center, 0.2f, new TKDielectric(1.5)));
				}
				++ i;
			}
		}
	}
	list.push_back(new TKSphere(glm::vec3(0.0, 1.0, 0.0), 1.0, new TKDielectric(1.5)));
	list.push_back(new TKSphere(glm::vec3(-4, 1.0, 0.0), 1.0, new TKLambertian(glm::vec3(0.4, 0.2, 0.1))));
	list.push_back(new TKSphere(glm::vec3(4, 1, 0), 1.0, new TKMetal(glm::vec3(0.7, 0.6, 0.5), 0.0)));
	printf("2 %d, %ld\n", i, list.size());

	return list;
}

int main(int argc, char *argv[]){
	if(argc >= 0){
		printf("args count %d\n", argc);
	}
	for(int i=0; i<argc; ++i){
		printf("%s ", argv[i]); 
	}
	printf("\n");

	const uint32_t col = 1920;
	const uint32_t row = 1080;
	const uint32_t ns = 10;
	
	uint8_t *data = (uint8_t *)malloc(sizeof(uint8_t)*row*col*3);
		
	std::vector<TKHitable *>objs = random_scene();
	TKHitable *world = new TKHitableList(objs.data(), objs.size());
	
	printf("world 0x%p\n", world);
	glm::vec3 lookfrom(-13.0f, 7.0f, 8.0f);
	glm::vec3 lookat(0.0, 0.0, -1.0f);
	float dist_to_focus = /*12.0f*/(lookfrom - lookat).length();
	float aperture = 0.0f;
	
	TKCamera cam(lookfrom, lookat,
				 glm::vec3(0.0, 1.0, 0.0),
				 20.0f, float(col)/float(row), aperture, dist_to_focus, 0.0f, 1.0f);
	printf("start ray trace\n");
	for(int i = 0; i<row; ++i){
		for(uint32_t j = 0; j<col; ++j){
			glm::vec3 c = glm::vec3(0.0f, 0.0f, 0.0f);
			for (uint32_t s = 0; s<ns; ++s) {
				float u = float(j+drand48()) / float(col);
				float v = float(i+drand48()) / float(row);
				TKRay ray = cam.getRay(u, v);
				c += color(ray, world, 0);
			}
			c /= float(ns);
			c.x = sqrt(c.x);
			c.y = sqrt(c.y);
			c.z = sqrt(c.z);
			data[3*(i*col+j)+0] = (int)(c.x*255.99f);
			data[3*(i*col+j)+1] = (int)(c.y*255.99f);
			data[3*(i*col+j)+2] = (int)(c.z*255.99f);
        }
	}
	
	writePPMFile("/home/sky/test.ppm", col, row, data);
	free(data);
	return 0;
}


