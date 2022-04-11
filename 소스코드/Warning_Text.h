#pragma once
#include "GScript.h"

class Warning_Text : public GScript
{

public:

	Warning_Text();
	~Warning_Text();
	
	BaseComponent* Instantiate()
	{
		Warning_Text* ins_cpmp = new Warning_Text(*this);

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

