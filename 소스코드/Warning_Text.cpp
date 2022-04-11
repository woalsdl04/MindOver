#include "DXUT.h"
#include "Warning_Text.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

Warning_Text::Warning_Text()
{

}

Warning_Text::~Warning_Text()
{

}

void Warning_Text::NEW()
{
	gameObject->Add_Component<SpriteRenderer_Component>(L"Warning_Text_Sc")->Load_Texture(L"Warning/Warning_Text.png", 1, 1, false);
	gameObject->Get_Component<SpriteRenderer_Component>()->Lock_Check();

	gameObject->Set_Center(true); 
	gameObject->transform.Set_LocalPosition(WISIZE_X/2, WISIZE_Y/2, 0);
	gameObject->Add_Component<Color_Component>(L"Warning_Text_Color")->Setup(GCOLOR(1, 1, 1, 0), GCOLOR(1, 1, 1, 0.7), -1, COLOR_ACTIONTYPE::ROUNDTRIP, 6);
}

void Warning_Text::Awake()
{

}

void Warning_Text::Start()
{

}

void Warning_Text::Notice(Notice_Item* notice)
{
	if (notice->Notice_Command == GNOTICE::COLOR_END)
	{
		GLog(L"z");
		GameObject* Warning_Bar = Active_GSystem->Find(L"Warning_Back");
		if (Warning_Bar) Warning_Bar->Destroy = true;
		gameObject->Destroy = true;
		Active_GScene->Camera_Sprite->Active = false;
		Active_GScene->Camera_Color->Active = false;
	}
}

void Warning_Text::Update()
{

}

void Warning_Text::Late_Update()
{

}

void Warning_Text::Final_Update()
{

}

void Warning_Text::Render()
{

}

void Warning_Text::Reload()
{

}

void Warning_Text::Change()
{

}

void Warning_Text::Release()
{
	delete this;
}
