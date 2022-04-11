#pragma once
#include "GScript.h"

class cIngameManager : public GScript
{
public:

	
	GameObject* Gamestart_Ui = NULL;
	GameObject* GameOver = NULL;
	GameObject* GameClear = NULL;

	SpriteRenderer_Component* GameClear_Sc = NULL;
	SpriteRenderer_Component* GameOver_Ui_Sc = NULL;
	float WorldTime = 0;
	int StartTime = 0;
	bool IsGamestart = true;
	bool IsWarning = false;
	cIngameManager();
	~cIngameManager();

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

