#pragma once
#include "GScript.h"

class cEnemy_Rocket : public GScript
{

public:

	cEnemy_Rocket();
	~cEnemy_Rocket();
	GVec3<float> BulletPos;

	float BulletSpeed;
	float BulletRotate;
	float Rocket_Boost;
	bool IsRadian;
	GameObject* Player_gameobject;
	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	BaseComponent* Instantiate()
	{
		cEnemy_Rocket* ins_cpmp = new cEnemy_Rocket(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};
	float ang;
	GameObject* Eff;
	float WorldTime;
	int J_time;
	void BulletSet(GVec3<float> _pos, float _speed, float _ang, bool _worldtime);

	bool Col_Check(GVec2<float> min, GVec2<float> max, AREA area);

	void NEW();

	void Awake();

	void Start();

	void Notice(Notice_Item* notice);

	void Render();

	void Update();

	void Late_Update();

	void Final_Update();

	void Reload();

	void Change();

	void Release();

};

