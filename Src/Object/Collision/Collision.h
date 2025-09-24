#pragma once
class Collision
{
	Collision();
	~Collision();
	void Init(void);
	void Update(void);
	bool HitSphere(VECTOR pos1, float radius1, VECTOR pos2, float radius2);

};

