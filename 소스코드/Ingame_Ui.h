#pragma once
#include "GScript.h"

class Ingame_Ui : public GScript
{

public:

	Ingame_Ui();
	~Ingame_Ui();

	BaseComponent* Instantiate()
	{
		Ingame_Ui* ins_cpmp = new Ingame_Ui(*this);

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

