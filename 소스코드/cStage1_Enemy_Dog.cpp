#include "DXUT.h"
#include "cStage1_Enemy_Dog.h"
#include "GSystem.h"
#include "cPlayer_Die_Eff.h"
#include "cEnemy_Die_Eff.h"

extern GSystem* Active_GSystem;
extern bool Hit_Check;
extern MOVEMODE PlayerState;
extern bool IsEnemyDie_Check;

extern GameObject* Eff_Prefab;
extern GameObject* Boss3_Die_Eff_Prefab;

cStage1_Enemy_Dog::cStage1_Enemy_Dog()
{

}

cStage1_Enemy_Dog::~cStage1_Enemy_Dog()
{

}

void cStage1_Enemy_Dog::NEW()
{

}

void cStage1_Enemy_Dog::Awake()
{

}

void cStage1_Enemy_Dog::Start()
{
	gameObject->Set_Center(true);
	Enemy_Pos = GVec3<float>(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
	//gameObject->transform.Set_LocalPosition(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
	gameObject->Render_Stack = 4; //Àû
	gameObject->transform.Set_LocalRotation(0, 0, 0);

	ingame_gameobject = Active_GSystem->Find(L"Ingame");

	if (!ingame_gameobject)
	{
		GLog(L"Ingame_GameObject NULL");
		return;
	}

	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

	if (!ingame_memmap)
	{
		GLog(L"Ingame_MemMap NULL");
		return;
	}

	rot = 0;
	J_Speed = 160;
}

void cStage1_Enemy_Dog::Notice(Notice_Item* notice)
{


}

bool cStage1_Enemy_Dog::Col_Check(GVec2<float> min, GVec2<float> max, AREA area)
{
	for (int i = min.y; i < max.y; i++)
	{
		for (int j = min.x; j < max.x; j++)
		{
			if (ingame_memmap->GetGap<char>(j, i) == (char)area)
			{
				return true;
			}

		}
	}

	return false;
}

void cStage1_Enemy_Dog::Update()
{
	WorldTime = timeGetTime();

	//rot += 1;

	if (Col_Check(GVec2<float>(Enemy_Pos.x - 50, Enemy_Pos.y - 50), GVec2<float>(Enemy_Pos.x + 50, Enemy_Pos.y + 50), AREA::ACTION)) //ÇÃ·¹ÀÌ¾î »ç¸Á
	{
		Hit_Check = true;
	}

	if (ingame_memmap->GetGap<char>(Enemy_Pos.x, Enemy_Pos.y) == (char)AREA::CLEAR)/* && IsEnemyDie_Check == true*/ // Àû »ç¸Á
	{
		GameObject* Eff;
		if(IsStage3)
		{
			Eff = Active_GSystem->Instantiate(Boss3_Die_Eff_Prefab);
			Eff->transform.Set_LocalScale(0.5f, 0.5f, 0.5f);
		}
		else
			Eff = Active_GSystem->Instantiate(Eff_Prefab);

		Eff->transform.Set_LocalPosition(Enemy_Pos.x + PG_LEFT, Enemy_Pos.y + PG_TOP, 0);
		Eff->Prefab = false;
		Sel = ENEMY_STATE::ENEMY_DEAD;
	}

	int r;
	switch (Sel)
	{
	case ENEMY_STATE::ENEMY_IDLE:
		r = rand() % 5;

		switch (r)
		{
		default:
			J_Time = WorldTime + (rand() % 1) * 1000;
			Sel = ENEMY_STATE::ENEMY_THINKING;
			break;

		case 1:

			TarGetPos = GVec3<float>(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
			GVec3<float> cha = TarGetPos - Enemy_Pos;
			ang = Get_Degree2D(GVec2<float>(0, -1), GVec2<float>(cha.x, cha.y));
			gameObject->transform.Set_LocalRotation(ang);
			Sel = ENEMY_STATE::ENEMY_MOVE;

			break;
		}

		break;
	case ENEMY_STATE::ENEMY_THINKING:
		if (J_Time < WorldTime)
		{

			Sel = ENEMY_STATE::ENEMY_IDLE;
		}
		break;
	case ENEMY_STATE::ENEMY_MOVE:
	{
		GVec3<float> cha = (TarGetPos - Enemy_Pos);
		float len = Lenth(cha);
		float DS = J_Speed * DT;
		GVec3<float> Ex = cha * (DS / len);

		if (DS > len) // µµÂø
		{
			Enemy_Pos = TarGetPos;
			Sel = ENEMY_STATE::ENEMY_IDLE;
		}
		else //°¡´Â Áß
		{
			if (ingame_memmap->GetGap<char>(Enemy_Pos.x + Ex.x, Enemy_Pos.y + Ex.y) != (char)AREA::NORMAL)
			{
				Sel = ENEMY_STATE::ENEMY_IDLE;
				return;
			}

			Vec2 NextPos; 
			NextPos.x = Enemy_Pos.x  + Ex.x;
			NextPos.y = Enemy_Pos.y + Ex.y;
			Vec3 dir = Vec3(Ex.x, Ex.y, Ex.z);
			//D3DXVec3Normalize(&dir, &dir);
			rot = atan2(Ex.y, Ex.x);

			Enemy_Pos = Enemy_Pos + Ex;
		}

		//J_Pos = Vec2(0, 0);

		break;
	}
	case ENEMY_STATE::ENEMY_DEAD:
	{
		gameObject->Active = false;
	}
	}
	
	//gameObject->transform.Set_LocalRotation(0, 0, D3DXToDegree(rot));
	gameObject->transform.Set_LocalPosition(Enemy_Pos.x + PG_LEFT, Enemy_Pos.y + PG_TOP, 0);
}

void cStage1_Enemy_Dog::Late_Update()
{

}

void cStage1_Enemy_Dog::Final_Update()
{

}

void cStage1_Enemy_Dog::Render()
{

}

void cStage1_Enemy_Dog::Reload()
{

}

void cStage1_Enemy_Dog::Change()
{

}

void cStage1_Enemy_Dog::Release()
{
	delete this;
}
