//
//rayTest.cpp
//

#include "TKRay.h"
#include "TKSphere.h"
#include "TKHitableList.h"
#include "TKCamera.h"
#include "TKMaterial.h"
#include "TKMath.h"

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

int main(int argc, char *argv[]){
	if(argc >= 0){
		printf("args count %d\n", argc);
	}
	for(int i=0; i<argc; ++i){
		printf("%s ", argv[i]); 
	}
	printf("\n");

	const uint32_t col = 1200;
	const uint32_t row = 800;
	const uint32_t ns = 100;
	
	uint8_t *data = (uint8_t *)malloc(sizeof(uint8_t)*row*col*3);
	
	TKHitable *list[5];
	TKLambertian *m0 = new TKLambertian(glm::vec3(0.1, 0.3, 0.8));
	TKLambertian *m1 = new TKLambertian(glm::vec3(0.8, 0.8, 0.0));
	list[0] = new TKSphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5, m0);
	list[1] = new TKSphere(glm::vec3(0.0f, -100.5f, -1.0f), 100, m1);
	TKMetal *m2 = new TKMetal(glm::vec3(0.8, 0.6, 0.2), 0.6);
	TKDielectric *m3 = new TKDielectric(1.5);
	list[2] = new TKSphere(glm::vec3(1.0, 0.0, -1.0), 0.5, m2);
	list[4] = new TKSphere(glm::vec3(-1.0, 0.0, -1.0), 0.5, m3);
	list[3] = new TKSphere(glm::vec3(-1.0, 0.0, -1.0), -0.45, m3);
	TKHitable *world = new TKHitableList(list, 5);

	glm::vec3 lookfrom(4.0f, 4.0f, 3.0f);
	glm::vec3 lookat(0.0, 0.0, -1.0f);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 1.0f;
	
	TKCamera cam(lookfrom, lookat,
				 glm::vec3(0.0, 1.0, 0.0),
				 20.0f, float(col)/float(row), aperture, dist_to_focus);
	for(int i = 0; i<row; ++i){
		for(uint32_t j = 0; j<col; ++j){
			glm::vec3 c = glm::vec3(0.0f, 0.0f, 0.0f);
			for (uint32_t s = 0; s<ns; ++s) {
				float u = float(j+drand48()) / float(col);
				float v = float(i+drand48()) / float(row);
				TKRay ray = cam.getRay(u, v);
				glm::vec3 p = ray.point_at_parameter(2.0f);
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


