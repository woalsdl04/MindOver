#pragma once
#include "GScript.h"

class cWarning_Back : public GScript
{

public:

	cWarning_Back();
	~cWarning_Back();

	BaseComponent* Instantiate()
	{
		cWarning_Back* ins_cpmp = new cWarning_Back(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};
	GameObject* cWarning_Text;
	bool IsWarning_TextOn = false;
	float Pos_x = 0;

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

