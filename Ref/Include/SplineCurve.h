#pragma once
#ifndef __SPLINECURVE_H__
#define __SPLINECURVE_H__

#include "Nalmak_Include.h"

class NALMAK_DLL SplineCurve
{
public:
	SplineCurve();
	~SplineCurve();

public:
	void AddPoint(Vector3 _point);
	void SubPoint(int _index);
	void DeletePoints();
	void DrawCurve();
	Vector3 GetPoint(float _ratio);
	list<Vector3>* GetCurve() { return &m_line; }
private:
	void CalcDistanceRatio();
	Vector3 GetPoint(int _index, float _ratio);
private:
	vector<Vector3> m_points;
	list<Vector3> m_line;
	vector<float> m_distanceRatio;
	// 점 3개로 커브 하나
	// 곡선 위의 점을 얻고 싶음, 기준 점들이 아니다
	// 4개 점 던지고, 

	// D3DXVec3CatmullRom(pOut, pV1, pV2, pV3, pV4, s)
	// = Q(s)라고 할 때,

	//Q(s) is a cubic function.
	//	Q(s) interpolates between p2 and p3 as s ranges from 0 to 1.
	//	Q(s) is parallel to the line joining p1 to p3 when s is 0.
	//	Q(s) is parallel to the line joining p2 to p4 when s is 1.
	// 0.5를 넣으면, v2 ~ v3 사이 중간점을 반환해줌


	// v1 = p2
	// v2 = p3
	// t1 = (p3 - p1) / 2
	// t2 = (p4 - p2) / 2
	//	v1 : pV1 
	//	v2 : pV2
	//	p3 : pV3
	//	p4 : pV4
	// 그니까 

	//원래 
	//Q(s) = (2s3 - 3s2 + 1) v1 + (-2s3 + 3s2) v2 + (s3 - 2s2 + s) t1 + (s3 - s2) t2

	//대입
	//Q(s) = (2s3 - 3s2 + 1) p2 + (-2s3 + 3s2) p3 + (s3 - 2s2 + s) (p3 - p1) / 2
	//	+ (s3 - s2)(p4 - p2) / 2

	//간략화
	//Q(s) = [(-s3 + 2s2 - s) p1 + (3s3 - 5s2 + 2) p2 +
	//	(-3s3 + 4s2 + s) p3 + (s3 - s2) p4] / 2

};
#endif

