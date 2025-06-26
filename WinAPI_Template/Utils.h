#pragma once

// ��׸� 1���� ����
#define DEG_TO_RAD		0.017453f

// ����
#define PI				3.141592653f
// 2����
#define PI_2			6.28318306f

#define FLOAT_EPSILON		0.001f

// �Ǽ� -> ����
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)

// �� �Ǽ��� ������ ��
#define FLOAT_EQUAL(f1, f2)	(fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	// �� �� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);

	// ��ŸƮ -���� ���� ��������
	float getAngle(float startX, float startY, float endX, float endY);
}
