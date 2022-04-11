#include "DXUT.h"
#include "cStage2_Enemy_Poison.h"
#include "cEnemy_Gas.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;
extern bool Hit_Check;
extern MOVEMODE PlayerState;
extern GameObject* Eff_Prefab;
extern GameObject* Gas_Prefab;

cStage2_Enemy_Poison::cStage2_Enemy_Poison()
{

}

cStage2_Enemy_Poison::~cStage2_Enemy_Poison()
{

}

void cStage2_Enemy_Poison::NEW()
{
	gameObject->Set_Center(true);
	gameObject->transform.Set_LocalScale(0.5, 0.5, 0.5);
	Enemy_Pos = GVec3<float>(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);

	ingame_gameobject = Active_GSystem->Find(L"Ingame");

	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

	J_Speed = 160;
}

void cStage2_Enemy_Poison::Awake()
{

}

void cStage2_Enemy_Poison::Start()
{
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
}

void cStage2_Enemy_Poison::Notice(Notice_Item* notice)
{


}

bool cStage2_Enemy_Poison::Col_Check(GVec2<float> min, GVec2<float> max, AREA area)
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

void cStage2_Enemy_Poison::Update()
{
	WorldTime = timeGetTime();

	//rot += 1;

	if (Col_Check(GVec2<float>(Enemy_Pos.x - 50, Enemy_Pos.y - 50), GVec2<float>(Enemy_Pos.x + 50, Enemy_Pos.y + 50), AREA::ACTION)) //ÇÃ·¹ÀÌ¾î »ç¸Á
	{
		Hit_Check = true;
	}

	if (ingame_memmap->GetGap<char>(Enemy_Pos.x, Enemy_Pos.y) == (char)AREA::CLEAR)/* && IsEnemyDie_Check == true*/ // Àû »ç¸Á
	{
		GameObject* Eff = Active_GSystem->Instantiate(Eff_Prefab);
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
			Sel = ENEMY_STATE::ENEMY_MOVE;
			break;
		case 2:
			Sel = ENEMY_STATE::ENEMY_ATTACK;
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

			//Vec2 NextPos;
			//NextPos.x = Enemy_Pos.x + Ex.x;
			//NextPos.y = Enemy_Pos.y + Ex.y;
			//Vec3 dir = Vec3(Ex.x, Ex.y, Ex.z);
			////D3DXVec3Normalize(&dir, &dir);
			//rot = atan2(Ex.y, Ex.x);

			Enemy_Pos = Enemy_Pos + Ex;
		}
		//J_Pos = Vec2(0, 0);

		break;
	}
	case ENEMY_STATE::ENEMY_ATTACK:
	{
		Gas = Active_GSystem->Instantiate(Gas_Prefab);
		Gas->Get_Component<cEnemy_Gas>(L"cEnemy_Gas_Prefab_Script")->BulletSet(Enemy_Pos);
		Gas->Prefab = false;

		Sel = ENEMY_STATE::ENEMY_THINKING;
		J_Time = WorldTime + 1500;
		
		return;

		break;
	}
	case ENEMY_STATE::ENEMY_DEAD:
	{
		gameObject->Active = false;

		break;
	}
	}

	//gameObject->transform.Set_LocalRotation(0, 0, D3DXToDegree(rot));
	gameObject->transform.Set_LocalPosition(Enemy_Pos.x + PG_LEFT, Enemy_Pos.y + PG_TOP, 0);
}

void cStage2_Enemy_Poison::Late_Update()
{

}

void cStage2_Enemy_Poison::Final_Update()
{

}

void cStage2_Enemy_Poison::Render()
{

}

void cStage2_Enemy_Poison::Reload()
{

}

void cStage2_Enemy_Poison::Change()
{

}

void cStage2_Enemy_Poison::Release()
{
	delete this;
}
