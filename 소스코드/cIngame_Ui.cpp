#include "DXUT.h"
#include "cIngame_Ui.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

extern int Stage;

float ClearPer = 0;
extern int TotalScore;

cIngame_Ui::cIngame_Ui()
{

}

cIngame_Ui::~cIngame_Ui()
{

}

void cIngame_Ui::NEW()
{
	Ingame_Ui_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Ingame_Ui_Sc");
	Ingame_Ui_Sc->Load_Texture(L"Ui/Ingame.png", 1, 1, false);
	Ingame_Ui_Sc->Lock_Check();

	Player_gameobject = Active_GSystem->Find(L"Player");
	gameObject->Set_Center(true);

	gameObject->transform.Set_LocalPosition(GVec3<float>(WISIZE_X / 2, PLAYG_HEIGHT + 50, 0));
	gameObject->transform.Set_LocalScale(GVec3<float>(0.9, 0.9, 1));
	gameObject->Render_Stack = 10;

	Life_Time_Ui = new GameObject(L"Life_Time_Ui");
	Life_Time_Ui->transform.Set_LocalScale(1, 1, 0);
	Life_Time_Ui->Render_Stack = 11;

	Life_Time_Ui_Font = Life_Time_Ui->Add_Component<GFont>(L"Life_Time_Ui_Font");
	Life_Time_Ui_Font->Setup(50, L"Fixedsys");
	Life_Time_Ui_Font->Local_Rect = GRECT<int>{ 0, 0, WISIZE_X, WISIZE_Y };
	//Ui_Font_FC->Align = DT_CENTER | DT_BOTTOM;*/

	ClearPer_Ui = new GameObject(L"ClearPer_Ui");
	ClearPer_Ui->transform.Set_LocalScale(1, 1, 0);
	ClearPer_Ui->Render_Stack = 11;

	ClearPer_Ui_Font = ClearPer_Ui->Add_Component<GFont>(L"ClearPer_Ui_Font");
	ClearPer_Ui_Font->Setup(30, L"Fixedsys");
	ClearPer_Ui_Font->Local_Rect = GRECT<int>{ 0, 0, WISIZE_X, WISIZE_Y };

	Score_Ui = new GameObject(L"Score_Ui");
	Score_Ui->transform.Set_LocalScale(1, 1, 0);
	Score_Ui->Render_Stack = 11;

	Score_Ui_Font = Score_Ui->Add_Component<GFont>(L"Score_Ui_Font");
	Score_Ui_Font->Setup(35, L"Fixedsys");
	Score_Ui_Font->Local_Rect = GRECT<int>{ 0, 0, WISIZE_X, WISIZE_Y };

	Stage_Ui = new GameObject(L"Stage_Ui");
	Stage_Ui->transform.Set_LocalScale(1, 1, 0);
	Stage_Ui->Render_Stack = 11;


	Stage_Ui_Font = Stage_Ui->Add_Component<GFont>(L"Stage_Ui_Font");
	Stage_Ui_Font->Setup(50, L"Fixedsys");
	Stage_Ui_Font->Local_Rect = GRECT<int>{ 0, 0, WISIZE_X, WISIZE_Y };
	Stage_Ui_Font->Color = 0xFF00FFFF;

	Player_Pos = Player_gameobject->transform.Get_LocalPosition();
	J_Pos = GVec3<float>(WISIZE_X / 2, PLAYG_HEIGHT + 50, 0); //초기값 위치

	ClearPer = 0;
	//Score = 0;
}

void cIngame_Ui::Awake()
{

}

void cIngame_Ui::Start()
{

}

void cIngame_Ui::Notice(Notice_Item* notice)
{
	

}

void cIngame_Ui::Update()
{
	LifeTime -= (1 * DT)/2;

	if(LifeTime <= 30) //30초 이하
	Life_Time_Ui_Font->Color = 0xFFFF0000;

	if(Player_Pos->y > 790)
	{
		if(J_Pos.y < 1100)
		J_Pos.y += 180 * DT;
	}
	else
	{
		if (J_Pos.y > PLAYG_HEIGHT +
			50)
			J_Pos.y -= 180 * DT;
	}
	
	Life_Time_Ui_Font->Set_Text(L"%d", (int)LifeTime);
	ClearPer_Ui_Font->Set_Text(L"%.1f%%", ClearPer);
	Score_Ui_Font->Set_Text(L"Score:%d", TotalScore);
	Stage_Ui_Font->Set_Text(L"<%d>", Stage);
	

	//Ui_Font->transform.Set_LocalPosition(GVec3<float>(J_Pos.x, J_Pos.y, 0));
	Life_Time_Ui->transform.Set_LocalPosition(GVec3<float>(J_Pos.x/2 - 35, J_Pos.y/2, 0));
	ClearPer_Ui->transform.Set_LocalPosition(GVec3<float>((J_Pos.x / 2) + 365, (J_Pos.y / 2) - 15, 0));
	Score_Ui->transform.Set_LocalPosition(GVec3<float>(J_Pos.x / 2 + 130, (J_Pos.y / 2) + 10, 0));
	Stage_Ui->transform.Set_LocalPosition(GVec3<float>(J_Pos.x / 2 - 428, (J_Pos.y / 2) - 20, 0));

	gameObject->transform.Set_LocalPosition(J_Pos);
}

void cIngame_Ui::Late_Update()
{

}

void cIngame_Ui::Final_Update()
{

}

void cIngame_Ui::Render()
{

}

void cIngame_Ui::Reload()
{

}

void cIngame_Ui::Change()
{

}

void cIngame_Ui::Release()
{
	delete this;
}
