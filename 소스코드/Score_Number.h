#pragma once
#include "GScript.h"

class Score_Number : public GScript
{

public:

	Score_Number();
	~Score_Number();


	BaseComponent* Instantiate()
	{
		Score_Number* ins_cpmp = new Score_Number(*this);

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

