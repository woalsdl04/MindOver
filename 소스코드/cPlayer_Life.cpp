#include "DXUT.h"
#include "cPlayer_Life.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

extern int Player_Life;

cPlayer_Life::cPlayer_Life()
{

}

cPlayer_Life::~cPlayer_Life()
{

}

void cPlayer_Life::NEW()
{
	Player_gameobject = Active_GSystem->Find(L"Player");
	Player_Pos = Player_gameobject->transform.Get_LocalPosition();

	for(int i = 0; i < 3; i++)
	{
		Player_Life_Obj[i] = new GameObject(L"Player_Life");
		Player_Life_Obj[i]->Add_Component<SpriteRenderer_Component>(L"Player_Life_Sc")->Load_Texture(L"Ui/Player_Life.png", 1, 1, false);
		Player_Life_Obj[i]->Get_Component<SpriteRenderer_Component>()->Lock_Check();

		Player_Life_Obj[i]->Set_Center(true);
		Player_Life_Obj[i]->Render_Stack = 11; // Ui바 위
		Player_Life_Obj[i]->transform.Set_LocalScale(GVec3<float>(0.4, 0.4, 0)); //반으로 줄이기
		Player_Life_Obj[i]->transform.Set_LocalPosition(GVec3<float>(370 + Pos_x, 1010, 0));
		Pos_x += 125;
	}
}

void cPlayer_Life::Awake()
{

}

void cPlayer_Life::Start()
{

}

void cPlayer_Life::Notice(Notice_Item* notice)
{


}

void cPlayer_Life::Update()
{

	switch (Player_Life)
	{
	case 0:
		Player_Life_Obj[0]->Active = false;
		Player_Life_Obj[1]->Active = false;
		Player_Life_Obj[2]->Active = false;
		break;
	case 1:
		Player_Life_Obj[0]->Active = true;
		Player_Life_Obj[1]->Active = false;
		Player_Life_Obj[2]->Active = false;
		break;
	case 2:
		Player_Life_Obj[0]->Active = true;
		Player_Life_Obj[1]->Active = true;
		Player_Life_Obj[2]->Active = false;
		break;
	case 3:
		Player_Life_Obj[0]->Active = true;
		Player_Life_Obj[1]->Active = true;
		Player_Life_Obj[2]->Active = true;
		break;
	}


	if (Player_Pos->y > 790)
	{
		if (Pos_y < 1150)
			Pos_y += 180 * DT;
	}
	else
	{
		if (Pos_y > 1010)
			Pos_y -= 180 * DT;
	}

	for (int i = 0; i < 3; i++)
	{
		Player_Life_Obj[i]->transform.Get_LocalPosition()->y = Pos_y;
	}
}

void cPlayer_Life::Late_Update()
{

}

void cPlayer_Life::Final_Update()
{

}

void cPlayer_Life::Render()
{

}

void cPlayer_Life::Reload()
{

}

void cPlayer_Life::Change()
{

}

void cPlayer_Life::Release()
{
	delete this;
}
