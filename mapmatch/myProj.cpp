// myProj.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

extern "C"{
#include "data.h"
#include "datadefs.h"
#include "geoutils.h"
#include "textutils.h"
}

#include "proj_api.h"

#pragma comment(lib,"E:\\zhanlj\\test\\test\\libs\\proj_i.lib")
//using namespace std;

LARGE_INTEGER BeginTime;
LARGE_INTEGER EndTime;
LARGE_INTEGER Frequency;

projUV chinaProjection(double longitude, double latitude);
projUV northAmericaProjection(double longitude, double latitude, projPJ pj);
double thisdist ( Point *p1, Point *p2 );

int main()
{

	//projUV p;
	//projPJ pj;
	////const char* bj1954="+proj=tmerc +ellps=krass +x_0=18500000 +y_0=0  +lat_0=0 +lon_0=105 +units=m +k=1.0";
	//const char* bj1954="+proj=tmerc +ellps=krass +lat_0=0 +lon_0=105 +units=m +k=1.0";
	//if (!(pj = pj_init_plus(bj1954)))
	//	return 1;

	//p.u = 106*DEG_TO_RAD;
	//p.v = 31*DEG_TO_RAD;
	//p = pj_fwd(p,pj);
	//std::cout.setf(std::ios_base::fixed);
	////std::cout<<"Beijing 1954 & krass椭球, (103.60,36.11)"<<std::endl;
	//std::cout<<"Beijing 1954 & krass椭球, (106,31)"<<std::endl;
	//std::cout<<"pj_fwd result:"<<p.u<<" "<<p.v<<std::endl;
	////p=pj_inv(p,pj);
	////p.u/=DEG_TO_RAD;
	////p.v/=DEG_TO_RAD;
	////std::cout<<"pj_inv result:"<<p.u<<" "<<p.v<<std::endl;
	//pj_free(pj);

	//*****************************************
	//std::cout<<"*****************************************"<<std::endl;
	////std::cout<<"输入用于测试的的中国地区的两点坐标："<<std::endl;
	//double xArray[2] = {-122.2445086,-122.2481928};
	//double yArray[2] = {47.2964240,47.2981713};
	////double xArray[2]={106,107};
	////double yArray[2]={31,32};


	//projUV pc1,pc2;
	//pc1 = chinaProjection(xArray[0],yArray[0]);
	//pc2 = chinaProjection(xArray[1],yArray[1]);

	//Point *p1,*p2;
	//p1 = new Point();
	//p2 = new Point();
	//p1->lon = xArray[0];
	//p1->lat = yArray[0];
	//p2->lon = xArray[1];
	//p2->lat = yArray[1];
	//double dist1 = thisdist(p1,p2);
	//std::cout<<"两点球面距离："<<dist1<<std::endl;
	//double x12 = (pc1.u - pc2.u)*(pc1.u - pc2.u);
	//double y12 = (pc1.v - pc2.v)*(pc1.v - pc2.v);
	//double dist2 = sqrt(x12 + y12);
	//std::cout<<"两点坐标距离："<<dist2<<std::endl;

	//projUV pn1,pn2;
	//pn1 = northAmericaProjection(xArray[0],yArray[0]);
	//pn2 = northAmericaProjection(xArray[1],yArray[1]);

	//double x22 = (pn1.u - pn2.u)*(pn1.u - pn2.u);
	//double y22 = (pn1.v - pn2.v)*(pn1.v - pn2.v);
	//double dist3 = sqrt(x22 + y22);
	//std::cout<<"两点坐标距离："<<dist3<<std::endl;

	//*****************************************
	std::cout<<"*****************************************"<<std::endl;
	
	std::string filePath="E:\\孙璐\\ACM_SIGSPATIAL\\ACM SIGSPATIAL CUP 2012\\RoadNetworkData\\WA_Nodes.txt";
	std::string outFilePath="E:\\孙璐\\ACM_SIGSPATIAL\\ACM SIGSPATIAL CUP 2012\\RoadNetworkData\\WA_Nodes_Projetion.txt";
	//FILE* nodefp;
	//nodefp = fopen(filePath.c_str(),"r");
	//Roads *data = (Roads*)malloc(sizeof(Roads));
	//readNodes(data, nodefp);

	std::ifstream fin(filePath.c_str());
	std::ofstream fout(outFilePath.c_str());
	projPJ pj1;
	const char* projection="+proj=tmerc +ellps=WGS84 +lat_0=0 +lon_0=-120 +units=m +k=1.0";
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&BeginTime);
	if (pj1 = pj_init_plus(projection))
	{		
		Node curNode;
		while(fin>>curNode.id>>curNode.loc.y>>curNode.loc.x)
		{
			projUV p;
			p.u = curNode.loc.y*DEG_TO_RAD;
			p.v = curNode.loc.x*DEG_TO_RAD;
			p = pj_fwd(p,pj1);
			//curP = northAmericaProjection(curNode.loc.lon, curNode.loc.lat, pj1);
			//std::cout<<curNode.id<<" "<<curP.u<<""<<curP.v<<std::endl;
			fout<<curNode.id<<" "<<p.u<<" "<<p.v<<std::endl;
		}
	}
	pj_free(pj1);
	QueryPerformanceCounter(&EndTime);
	std::cout<<(EndTime.QuadPart-BeginTime.QuadPart)*1000/Frequency.QuadPart;
	system("pause");
	

 	return 0;
}

projUV chinaProjection(double longitude, double latitude)
{
	projUV p;
	projPJ pj;
	const char* chinaProjection="+proj=tmerc +ellps=WGS84 +lat_0=0 +lon_0=105 +units=m +k=1.0";
	if (pj = pj_init_plus(chinaProjection))
	{
		p.u = longitude*DEG_TO_RAD;
		p.v = latitude*DEG_TO_RAD;
		p = pj_fwd(p,pj);
		//std::cout.setf(std::ios_base::fixed);
		//std::cout<<"中国范围内投影, ("<<longitude<<","<<latitude<<")"<<std::endl;
		//std::cout<<"pj_fwd result:"<<p.u<<" "<<p.v<<std::endl;
		//p=pj_inv(p,pj);
		//p.u/=DEG_TO_RAD;
		//p.v/=DEG_TO_RAD;
		//cout<<"pj_inv result:"<<p.u<<" "<<p.v<<endl;
		pj_free(pj);
	}
	return p;
}

projUV northAmericaProjection(double longitude, double latitude, projPJ pj)
{
	projUV p;

	p.u = longitude*DEG_TO_RAD;
	p.v = latitude*DEG_TO_RAD;
	p = pj_fwd(p,pj);
	//std::cout.setf(std::ios_base::fixed);
	//std::cout<<"华盛顿地区投影, ("<<longitude<<","<<latitude<<")"<<std::endl;
	//std::cout<<"pj_fwd result:"<<p.u<<" "<<p.v<<std::endl;
	//p=pj_inv(p,pj);
	//p.u/=DEG_TO_RAD;
	//p.v/=DEG_TO_RAD;
	//cout<<"pj_inv result:"<<p.u<<" "<<p.v<<endl;
	pj_free(pj);
	return p;
	
}

double thisdist ( Point *p1, Point *p2 ) {
	double dLat = (p1->y - p2->y) * PI / 180;
	double dLon = (p1->x - p2->x) * PI / 180;
	double lat1 = p1->y * PI / 180;
	double lat2 = p2->y * PI / 180;

	double a = sin(dLat / 2) * sin(dLat / 2) +
		sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2); 
	double c = 2 * atan2(sqrt(a), sqrt(1 - a)); 
	return R * c;
}		/* -----  end of function distance  ----- */
