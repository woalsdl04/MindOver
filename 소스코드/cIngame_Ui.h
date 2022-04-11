#pragma once
#include "GScript.h"

class cIngame_Ui : public GScript
{

public:
	
	GameObject* Player_gameobject;
	SpriteRenderer_Component* Ingame_Ui_Sc = NULL;
	GVec3<float>* Player_Pos;
	GVec3<float> J_Pos;

	GameObject* Life_Time_Ui = NULL;
	GFont* Life_Time_Ui_Font = NULL;

	GameObject* ClearPer_Ui = NULL;
	GFont* ClearPer_Ui_Font = NULL;

	GameObject* Score_Ui = NULL;
	GFont* Score_Ui_Font = NULL;

	GameObject* Stage_Ui = NULL;
	GFont* Stage_Ui_Font = NULL;

	float LifeTime = 180;
	
	cIngame_Ui();
	~cIngame_Ui();

	BaseComponent* Instantiate()
	{
		cIngame_Ui* ins_cpmp = new cIngame_Ui(*this);

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

