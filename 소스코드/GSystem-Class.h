#pragma once
#include "GScript.h"

class GSystem_Class : public GScript
{

public:

	GSystem_Class();
	~GSystem_Class();

	BaseComponent* Instantiate()
	{
		GSystem_Class* ins_cpmp = new GSystem_Class(*this);

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

