#pragma once
#include "GScript.h"

class cEnemy_BaseBullet : public GScript
{

public:

	GVec3<float> BulletPos;

	float BulletSpeed;
	float BulletRotate;
	bool IsRadian;
	bool IsStage3;
	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	cEnemy_BaseBullet();
	~cEnemy_BaseBullet();

	BaseComponent* Instantiate()
	{
		cEnemy_BaseBullet* ins_cpmp = new cEnemy_BaseBullet(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	SpriteRenderer_Component* Enemy_Die_Eff_Sc = NULL;
	FrameAni_Component* Enemy_Die_Eff_Ani = NULL;

	GameObject* Eff;

	bool Col_Check(GVec2<float> min, GVec2<float> max, AREA area);

	void BulletSet(GVec3<float> _pos, float _speed, float _ang, bool _isradian, bool _stage3);

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

