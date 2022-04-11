#pragma once
#include "GScript.h"

class cPlayer_Heal_Eff : public GScript
{

public:

	cPlayer_Heal_Eff();
	~cPlayer_Heal_Eff();

	BaseComponent* Instantiate()
	{
		cPlayer_Heal_Eff* ins_cpmp = new cPlayer_Heal_Eff(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};
	SpriteRenderer_Component* Player_Heal_Eff_Sc = NULL;
	FrameAni_Component* Player_Heal_Eff_Ani = NULL;

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

