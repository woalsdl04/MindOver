#pragma once

#include "GScene_Manager.h"

class cGameManager : public GScene_Manager
{

public:
	GameObject* Title_Bg = NULL;
	GameObject* Ingame_Manager = NULL;
	GameObject* MaskBg = NULL;
	GameObject* Ingame_Bg = NULL;
	GameObject* Ingame_Base_Bg = NULL;
	GameObject* Ingame = NULL;
	GameObject* Player = NULL;
	GameObject* Ingame_Ui = NULL;
	GameObject* Boss = NULL;
	GameObject* Hp_Item = NULL;
	GameObject* SpeedUp_Item = NULL;
	GameObject* Stage1_Enemy_Man[3] = { NULL, NULL, NULL };
	GameObject* Stage1_Enemy_Man_Prefab = NULL;
	GameObject* Stage2_Enemy_Gas[3] = { NULL, NULL, NULL };
	GameObject* Stage2_Enemy_Gas_Prefab = NULL;
	GameObject* Stage1_Enemy_Dog[3] = { NULL, NULL, NULL };
	GameObject* Stage1_Enemy_Dog_Prefab = NULL;
	GameObject* Player_Life_MN = NULL;
	SpriteRenderer_Component* Enemy_Sc;

	//SpriteRenderer_Component* B
	
	void NEW() {};

	void Change_Scene(DWORD ID);

	void Awake() {};
	void Start() {};

	void Update() {};
	void Render() {};

	void CreateDevice() {};
	void LostDevice() {};

	void Reload() {};
	void Release() {};

};

