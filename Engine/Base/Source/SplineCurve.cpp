#include "..\Include\SplineCurve.h"



SplineCurve::SplineCurve()
{
	m_points.reserve(16);
}


SplineCurve::~SplineCurve()
{
}
void SplineCurve::AddPoint(Vector3 _point)
{
	m_points.emplace_back(_point);

	if (m_points.size() > 3)
		CalcDistanceRatio();
}

void SplineCurve::CalcDistanceRatio()
{
	float totlaDistance = 0;
	m_distanceRatio.clear();
	vector<float> distantList;
	for (int i = 1; i < m_points.size() - 2; ++i)
	{
		totlaDistance += Nalmak_Math::Distance(m_points[i], m_points[i + 1]);
		distantList.emplace_back(totlaDistance);
	}

	for (auto& distance : distantList)
	{
		m_distanceRatio.emplace_back(distance / totlaDistance);
	}

}

Vector3 SplineCurve::GetPoint(int _index, float _ratio)
{
	Vector3 point;
	D3DXVec3CatmullRom(&point, &m_points[_index-2], &m_points[_index-1], &m_points[_index], &m_points[_index + 1], _ratio);

	return point;
}

void SplineCurve::SubPoint(int _index)
{
	if (_index >= m_points.size())
		return;
	m_points.erase(m_points.begin() + _index);
}

void SplineCurve::DrawCurve()
{
#ifdef _DEBUG
	if (m_points.size() < 3)
	{
		assert(L"Spline Curve must have points at least 3! " && 0);
		return;
	}
#endif // _DEBUG

	int index = 0;
	m_line.clear();

	// first curve -> first_p, p0, p1, p2
	for (int i = 0; i < 10; ++i)
	{
		Vector3 out;
		D3DXVec3CatmullRom(&out, &m_points[0], &m_points[0], &m_points[1], &m_points[2], i * 0.1f);
		m_line.emplace_back(out);
	}

	// middle curves
	for (; index < m_points.size() - 3; ++index)
	{
		for (int i = 0; i < 10; ++i)
		{
			Vector3 out;
			D3DXVec3CatmullRom(&out, &m_points[index], &m_points[index + 1], &m_points[index + 2], &m_points[index + 3], i * 0.1f);
			m_line.emplace_back(out);
		}
	}

	// last curve pn-2, pn-1, pn, lastp

	for (int i = 0; i < 11; ++i)
	{
		Vector3 out;
		D3DXVec3CatmullRom(&out, &m_points[index], &m_points[index + 1], &m_points[index + 2], &m_points[index + 2], i * 0.1f);
		m_line.emplace_back(out);
	}
}

Vector3 SplineCurve::GetPoint(float _ratio)
{
	
	_ratio = Nalmak_Math::Clamp(_ratio, 0.f, 1.f);

	int index = 0;
	Vector3 point;
	for (int i = 0; i < m_distanceRatio.size(); ++i)
	{
		if (_ratio <= m_distanceRatio[i])
		{
			
			float total;
			float patial;
			if (i == 0)
			{
				total = m_distanceRatio[i];
				patial = _ratio;
				
			}
			else
			{
				total = m_distanceRatio[i] - m_distanceRatio[i - 1];
				patial = _ratio - m_distanceRatio[i - 1];

			}

			point = GetPoint(i + 2, patial / total);
			break;
			
		}
	}
	return point;

}

void SplineCurve::DeletePoints()
{
	m_points.clear();
}
/*
void CSpline::DrawCardinalSpline(bool _bIs4Point)
{
	float fX = 0.0f, fY = 0.0f;
	float fT2 = 0.0f;    // fT * fT
	float fT3 = 0.0f;    // fT * fT * fT

						 // ������ ���� ����
	m_bIs4Point = _bIs4Point;

	// �������� 3��
	if (!m_bIs4Point)
	{
		for (float fT = 0.0f; fT < 1.0f; fT += 0.0001f)
		{
			fT2 = fT * fT;

			fX = m_arrPointsX[0] +
				(-3.0f * m_arrPointsX[0] + 4.0f * m_arrPointsX[2] - m_arrPointsX[1]) * fT +
				(2.0f * m_arrPointsX[0] - 4.0f * m_arrPointsX[2] + 2.0f * m_arrPointsX[1]) * fT2;
			fY = m_arrPointsY[0] +
				(-3.0f * m_arrPointsY[0] + 4.0f * m_arrPointsY[2] - m_arrPointsY[1]) * fT +
				(2.0f * m_arrPointsY[0] - 4.0f * m_arrPointsY[2] + 2.0f * m_arrPointsY[1]) * fT2;

			PUT_PIXEL((int)fX, (int)fY);
		}
	}
	// �������� 4��
	// ������ 1-2, 3-4 ������ ���� �׸���,
	// ������ 2-3�� ���� �߰��ؼ� �ϳ��� ��ġ�� ���
	else
	{
		// ������ 3���� �̿������� ������ �׷����� �κ���
		// ������ 2�� ������ �׷������ϱ� ������ �ݸ� ����
		// �������� ��ġ�� �����ص� �Ĳ��� �׷����� �ϱ� ���ؼ�
		// fT���� 0.0001f�� ����
		for (float fT = 0.0f; fT < 0.5f; fT += 0.0001f)
		{
			fT2 = fT * fT;

			// ������ 1���� ������ 2 ����
			fX = m_arrPointsX[0] +
				(-3.0f * m_arrPointsX[0] + 4.0f * m_arrPointsX[1] - m_arrPointsX[2]) * fT +
				(2.0f * m_arrPointsX[0] - 4.0f * m_arrPointsX[1] + 2.0f * m_arrPointsX[2]) * fT2;
			fY = m_arrPointsY[0] +
				(-3.0f * m_arrPointsY[0] + 4.0f * m_arrPointsY[1] - m_arrPointsY[2]) * fT +
				(2.0f * m_arrPointsY[0] - 4.0f * m_arrPointsY[1] + 2.0f * m_arrPointsY[2]) * fT2;

			PUT_PIXEL((int)fX, (int)fY);


			// ������ 3���� ������ 4 ����
			fX = m_arrPointsX[3] +
				(-3.0f * m_arrPointsX[3] + 4.0f * m_arrPointsX[2] - m_arrPointsX[1]) * fT +
				(2.0f * m_arrPointsX[3] - 4.0f * m_arrPointsX[2] + 2.0f * m_arrPointsX[1]) * fT2;
			fY = m_arrPointsY[3] +
				(-3.0f * m_arrPointsY[3] + 4.0f * m_arrPointsY[2] - m_arrPointsY[1]) * fT +
				(2.0f * m_arrPointsY[3] - 4.0f * m_arrPointsY[2] + 2.0f * m_arrPointsY[1]) * fT2;

			PUT_PIXEL((int)fX, (int)fY);
		}

		for (float fT = 0.0f; fT < 1.0f; fT += 0.0001f)
		{
			fT2 = fT * fT;
			fT3 = fT * fT * fT;

			// ������ 2���� ������ 3 ����
			fY = m_arrPointsY[1] +
				(-m_arrPointsY[0] + m_arrPointsY[2]) * fT +
				(2.0f * m_arrPointsY[0] + (-2.0f * m_arrPointsY[1]) + m_arrPointsY[2] - m_arrPointsY[3]) * fT2 +
				(-m_arrPointsY[0] + m_arrPointsY[1] + (-m_arrPointsY[2]) + m_arrPointsY[3]) * fT3;
			fX = m_arrPointsX[1] +
				(-m_arrPointsX[0] + m_arrPointsX[2]) * fT +
				(2.0f * m_arrPointsX[0] + (-2.0f * m_arrPointsX[1]) + m_arrPointsX[2] - m_arrPointsX[3]) * fT2 +
				(-m_arrPointsX[0] + m_arrPointsX[1] + (-m_arrPointsX[2]) + m_arrPointsX[3]) * fT3;

			PUT_PIXEL((int)fX, (int)fY);
		}
	}
}
*/