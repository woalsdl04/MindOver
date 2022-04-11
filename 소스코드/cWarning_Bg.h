#pragma once
#include "GScript.h"

class cWarning_Bg : public GScript
{

public:

	cWarning_Bg();
	~cWarning_Bg();

	BaseComponent* Instantiate()
	{
		cWarning_Bg* ins_cpmp = new cWarning_Bg(*this);

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

