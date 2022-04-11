#pragma once
#include "GScript.h"

class cEnemy_Die_Eff : public GScript
{

public:

	cEnemy_Die_Eff();
	~cEnemy_Die_Eff();

	BaseComponent* Instantiate()
	{
		cEnemy_Die_Eff* ins_cpmp = new cEnemy_Die_Eff(*this);

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

