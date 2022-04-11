#include "DXUT.h"
#include "cWarning_Back.h"
#include "GSystem.h"
#include "Warning_Text.h"

extern GSystem* Active_GSystem;

cWarning_Back::cWarning_Back()
{

}

cWarning_Back::~cWarning_Back()
{

}

void cWarning_Back::NEW()
{
	gameObject->Add_Component<SpriteRenderer_Component>(L"Warning_Back_Sc")->Load_Texture(L"Warning/Warning_Back.png", 1, 1, false);
	gameObject->Get_Component<SpriteRenderer_Component>()->Lock_Check();

	gameObject->Set_Center(true);
	gameObject->Add_Component<TRS_Component>(L"Warning_Back_TRS")->Set_TRS(TRS_ENUM::MOVE, GVec3<float>(-(WISIZE_X / 2), WISIZE_Y/2, 0), GVec3<float>((WISIZE_X / 2), WISIZE_Y / 2, 0), -0.8, TRS_LOOPTYPE::ONEWAY, TRS_SPEEDTYPE::AVERAGE, 0, 1);
	Active_GScene->Set_Camera_Action(CAMERA_ACTION_TYPE::EARTHQUAKE3, -0.05, 2, 50);
	cWarning_Text = NULL;
	/*Pos_x = -(WISIZE_X/2);
	gameObject->transform.Set_LocalPosition(Pos_x, WISIZE_Y / 2, 0);*/
}

void cWarning_Back::Awake()
{

}

void cWarning_Back::Start()
{

}

void cWarning_Back::Notice(Notice_Item* notice)
{
	if(notice->Notice_Command == GNOTICE::TRS_END && cWarning_Text == NULL)
	{
		cWarning_Text = new GameObject(L"Warning_Text");
		cWarning_Text->Render_Stack = 8;
		cWarning_Text->Add_Component<Warning_Text>(L"Warning_Text_Script");
		Active_GScene->Camera_Sprite->Active = true;
		Active_GScene->Camera_Color->Setup(GCOLOR(1, 1, 1, 0), GCOLOR(1, 0, 0, 0.6), -1.5, COLOR_ACTIONTYPE::ROUNDTRIP, 0xFFFFFFFF);
		Active_GScene->Camera_Color->Active = true;
	}
}

void cWarning_Back::Update()
{
	/*if (Pos_x < WISIZE_X / 2)
		Pos_x += 400 * DT;
	else if(Pos_x > WISIZE_X / 2)
	{
		Pos_x = WISIZE_X / 2; 
		Warning_Text = new GameObject(L"Warning_Text");
		
	}*/
	


	//gameObject->transform.Get_LocalPosition()->x = Pos_x;
}

void cWarning_Back::Late_Update()
{
	
}

void cWarning_Back::Final_Update()
{

}

void cWarning_Back::Render()
{

}

void cWarning_Back::Reload()
{

}

void cWarning_Back::Change()
{

}

void cWarning_Back::Release()
{
	delete this;
}
