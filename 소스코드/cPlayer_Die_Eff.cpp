#include "DXUT.h"
#include "cPlayer_Die_Eff.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

cPlayer_Die_Eff::cPlayer_Die_Eff()
{

}

cPlayer_Die_Eff::~cPlayer_Die_Eff()
{

}

void cPlayer_Die_Eff::NEW()
{
	Player_Die_Eff_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Player_Die_Eff_Sr");
	Player_Die_Eff_Sc->Load_Texture(L"Eff/Player_Die_Eff.png", 5, 1, false);
	Player_Die_Eff_Sc->Lock_Check();

	gameObject->Set_Center(true);
	gameObject->Render_Stack = 6;
	Player_Die_Eff_Ani = gameObject->Add_Component<FrameAni_Component>(L"Player_Die_Eff_Ani");
	Player_Die_Eff_Ani->Set_FrameTime(75, false);
}

void cPlayer_Die_Eff::Awake()
{

}

void cPlayer_Die_Eff::Start()
{

}

void cPlayer_Die_Eff::Notice(Notice_Item* notice)
{
	if(notice->Notice_Command == GNOTICE::ANI_END)
	{
		gameObject->Destroy = true;
	}
}

void cPlayer_Die_Eff::Update()
{

}

void cPlayer_Die_Eff::Late_Update()
{

}

void cPlayer_Die_Eff::Final_Update()
{

}

void cPlayer_Die_Eff::Render()
{

}

void cPlayer_Die_Eff::Reload()
{

}

void cPlayer_Die_Eff::Change()
{

}

void cPlayer_Die_Eff::Release()
{
	delete this;
}
