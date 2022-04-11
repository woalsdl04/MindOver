#include "DXUT.h"
#include "cGame_Start_Ui.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

cGame_Start_Ui::cGame_Start_Ui()
{

}

cGame_Start_Ui::~cGame_Start_Ui()
{

}

void cGame_Start_Ui::NEW()
{
	Gamestart_Ui_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Gamestart_Ui_Sr");
	Gamestart_Ui_Sc->Load_Texture(L"Ui/Gamestart2.png", 4, 7, false);
	Gamestart_Ui_Sc->Lock_Check();

	Gamestart_Ui_Ani = gameObject->Add_Component<FrameAni_Component>(L"Gamestart_Ui_Ani");
	Gamestart_Ui_Ani->Set_FrameTime(50, false);


	gameObject->Set_Center(true);
	//gameObject->Render_Stack = 5;
	gameObject->transform.Set_LocalPosition(WISIZE_X / 2, WISIZE_Y / 2, 0);
}

void cGame_Start_Ui::Awake()
{

}

void cGame_Start_Ui::Start()
{

}

void cGame_Start_Ui::Notice(Notice_Item* notice)
{
	if(notice->Notice_Command == GNOTICE::ANI_END)
	{
		gameObject->Destroy = true;
		//gameObject->Active = false;
	}
}

void cGame_Start_Ui::Update()
{
	 
}

void cGame_Start_Ui::Late_Update()
{

}

void cGame_Start_Ui::Final_Update()
{

}

void cGame_Start_Ui::Render()
{

}

void cGame_Start_Ui::Reload()
{

}

void cGame_Start_Ui::Change()
{

}

void cGame_Start_Ui::Release()
{
	delete this;
}
