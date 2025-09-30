#pragma once

class Player;
class EnemyManager;
class EnemyBase;
class ShotBase;



class Collision
{
public:
	Collision();
	~Collision();
	void Init(Player*player, EnemyManager* enemyManager);
	void Update(void);
	bool HitSphere(VECTOR pos1, float radius1, VECTOR pos2, float radius2);

private:

	Player* player_;
	EnemyManager* enemyManager_;
	std::vector<EnemyBase*> enemys_;
	std::vector<ShotBase*> shots_;


};

