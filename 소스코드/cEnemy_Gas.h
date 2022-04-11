#pragma once
#include "GScript.h"

class cEnemy_Gas : public GScript
{

public:

	cEnemy_Gas();
	~cEnemy_Gas();

	GVec3<float> BulletPos;

	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	BaseComponent* Instantiate()
	{
		cEnemy_Gas* ins_cpmp = new cEnemy_Gas(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	void BulletSet(GVec3<float> _pos);

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

