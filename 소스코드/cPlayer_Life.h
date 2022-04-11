#pragma once
#include "GScript.h"

class cPlayer_Life : public GScript
{

public:

	cPlayer_Life();
	~cPlayer_Life();

	GameObject* Player_Life_Obj[3] = {NULL, NULL, NULL};
	int Pos_x = 0;
	float Pos_y = 1010;

	GameObject* Player_gameobject;
	GVec3<float>* Player_Pos;

	BaseComponent* Instantiate()
	{
		cPlayer_Life* ins_cpmp = new cPlayer_Life(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

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

