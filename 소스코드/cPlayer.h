#pragma once
#include "GScript.h"

class cPlayer : public GScript
{

public:
	int Direction = 0;
	GameObject* ingame_gameobject = NULL;
	GameObject* Boss_gameobject = NULL;
	GameObject* ingame_gameobject_Ui = NULL;
	//GameObject* Eff = NULL;

	SpriteRenderer_Component* Player_Sc = NULL;
	SpriteRenderer_Component* Mask_Sc = NULL;
	MeMMap_Component* ingame_memmap = NULL;
	Line_Component* ingame_Line = NULL;
	Color_Component* Player_Color = NULL;
	GVec3<float> Joo_Pos = {0, 0, 0};
	GVec3<float>* Boss_Pos;
	KEYSTATE KeyState = KEYSTATE::IDLE;


	bool Find_Normal_OK;
	bool Find_OutLine_OK;
	bool Find_ActionLine_OK;
	bool Find_ClearArea_OK;


	GVec3<float> Find_Normal_Pos;
	GVec3<float> Find_OutLine_Pos;
	GVec3<float> Find_ActionLine_Pos;
		
	bool MooJuck = false;
	cPlayer();
	~cPlayer();

	BaseComponent* Instantiate()
	{
		cPlayer* ins_cpmp = new cPlayer(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	void Play_Sound(CSound* SoundCLIP, bool Loop);
	
	void CreateDevice();
	GVec3<float> Calc_Step();
	void Player_Die();
	void Delete_OutLine();
	void MeM2_MaskBg();
	void Get_FindNext_Pos(GVec3<float> ms);
	void JInput();
	void NormalUpdate();
	void AttackUpdate();
	void ReturnUpdate();
	void ComplUpdate();
	void Draw_Action_Line(bool draw);

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

