#pragma once
#include "GScript.h"

class cPlayer_Die_Eff : public GScript
{

public:

	cPlayer_Die_Eff();
	~cPlayer_Die_Eff();

	BaseComponent* Instantiate()
	{
		cPlayer_Die_Eff* ins_cpmp = new cPlayer_Die_Eff(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};
	SpriteRenderer_Component* Player_Die_Eff_Sc = NULL;
	FrameAni_Component* Player_Die_Eff_Ani = NULL;

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

