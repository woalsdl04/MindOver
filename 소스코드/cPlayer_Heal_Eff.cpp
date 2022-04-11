#include "DXUT.h"
#include "cPlayer_Heal_Eff.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

cPlayer_Heal_Eff::cPlayer_Heal_Eff()
{

}

cPlayer_Heal_Eff::~cPlayer_Heal_Eff()
{

}

void cPlayer_Heal_Eff::NEW()
{
	Player_Heal_Eff_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Player_Heal_Eff_Sc");
	Player_Heal_Eff_Sc->Load_Texture(L"Eff/Heal_Eff.png", 7, 1, false);
	Player_Heal_Eff_Sc->Lock_Check();

	gameObject->Set_Center(true);
	gameObject->Render_Stack = 6;
	Player_Heal_Eff_Ani = gameObject->Add_Component<FrameAni_Component>(L"Player_Heal_Eff_Ani");
	Player_Heal_Eff_Ani->Set_FrameTime(75, false);
}

void cPlayer_Heal_Eff::Awake()
{

}

void cPlayer_Heal_Eff::Start()
{

}

void cPlayer_Heal_Eff::Notice(Notice_Item* notice)
{
	if (notice->Notice_Command == GNOTICE::ANI_END)
	{
		gameObject->Destroy = true;
	}
}

void cPlayer_Heal_Eff::Update()
{

}

void cPlayer_Heal_Eff::Late_Update()
{

}

void cPlayer_Heal_Eff::Final_Update()
{

}

void cPlayer_Heal_Eff::Render()
{

}

void cPlayer_Heal_Eff::Reload()
{

}

void cPlayer_Heal_Eff::Change()
{

}

void cPlayer_Heal_Eff::Release()
{
	delete this;
}
