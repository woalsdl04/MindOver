#include "DXUT.h"
#include "cBg.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

extern int Stage;

cBg::cBg()
{

}

cBg::~cBg()
{

}

void cBg::NEW()
{
	Bg_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Bg_Sc");

	switch (Stage)
	{
	case 1:
		Bg_Sc->Load_Texture(L"Stage1/Bg.png", 1, 1, false);
		break;
	case 2:
		Bg_Sc->Load_Texture(L"Stage2/Bg.png", 1, 1, false);
		break;
	case 3:
		Bg_Sc->Load_Texture(L"Stage3/Bg.png", 1, 1, false);
		break;
	}
	

	Bg_Sc->Lock_Check();
	
	gameObject->Render_Stack = 1;
	gameObject->transform.Set_LocalPosition((WISIZE_X - Bg_Sc->Gtex->width) / 2, (WISIZE_Y - Bg_Sc->Gtex->height) / 2, 0);
}

void cBg::Awake()
{

}

void cBg::Start()
{

}

void cBg::Notice(Notice_Item* notice)
{


}

void cBg::Update()
{

}

void cBg::Late_Update()
{

}

void cBg::Final_Update()
{

}

void cBg::Render()
{

}

void cBg::Reload()
{

}

void cBg::Change()
{

}

void cBg::Release()
{
	delete this;
}
