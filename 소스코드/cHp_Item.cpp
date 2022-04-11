#include "DXUT.h"
#include "cHp_Item.h"
#include "GSystem.h"
#include "cPlayer_Heal_Eff.h"

extern GSystem* Active_GSystem;

extern int Player_Life;
extern SoundCLIP_Component* PowerUp_Sound;

cHp_Item::cHp_Item()
{

}

cHp_Item::~cHp_Item()
{

}

void cHp_Item::NEW()
{
	ingame_gameobject = Active_GSystem->Find(L"Ingame");
	Player = Active_GSystem->Find(L"Player");

	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

	Hp_Item_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Hp_Item_Sc");
	Hp_Item_Sc->Load_Texture(L"Item/HpUp.png", 1, 1, false);
	Hp_Item_Sc->Lock_Check();

	gameObject->Set_Center(true);
	gameObject->Render_Stack = 3;
	gameObject->transform.Set_LocalScale(0.3, 0.3, 0.3);

	Sel = ITEMSTATE::START;
	Item_Pos = {0, 0, 0};
}

void cHp_Item::Awake()
{

}

void cHp_Item::Start()
{

}

void cHp_Item::Notice(Notice_Item* notice)
{

}

void cHp_Item::Update()
{
	switch (Sel)
	{
	case ITEMSTATE::START:
		Item_Pos = GVec3<float>(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
		Sel = ITEMSTATE::DROP;
		break;
	case ITEMSTATE::DROP:
		if (ingame_memmap->GetGap<char>(Item_Pos.x, Item_Pos.y) == (char)AREA::CLEAR)
		{
			Sel = ITEMSTATE::EAT;
			PowerUp_Sound->Play_Sound(false);
		}
		break;
	case ITEMSTATE::EAT:
	{
		if (Player_Life < 3)
			Player_Life += 1;
		gameObject->Add_Component<Color_Component>(L"Hp_Item_Cr")->Setup(GCOLOR(1, 1, 1, 1), GCOLOR(1, 1, 1, 0), -0.5f, COLOR_ACTIONTYPE::ONEWAY, 0xFFFFFFFF);
		gameObject->Add_Component<TRS_Component>(L"Hp_Item_Trs")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(0.3, 0.3, 0.3), GVec3<float>(0.5, 0.5, 0.5), -0.5f, TRS_LOOPTYPE::ONEWAY, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);

		GameObject* Eff = new GameObject(L"Player_Heal_Eff");
		Eff->Add_Component<cPlayer_Heal_Eff>(L"Player_Heal_Eff_Script");
		Eff->transform.Set_LocalPosition(Player->transform.Get_LocalPosition()->x, Player->transform.Get_LocalPosition()->y, 0);
		Sel = ITEMSTATE::ITEM_DIE;
		break;
	}
	case ITEMSTATE::ITEM_DIE:
		//gameObject->Destroy = true;
		break;
	}

	gameObject->transform.Set_LocalPosition(Item_Pos.x + PG_LEFT, Item_Pos.y + PG_TOP, 0);
}

void cHp_Item::Late_Update()
{

}

void cHp_Item::Final_Update()
{

}

void cHp_Item::Render()
{

}

void cHp_Item::Reload()
{

}

void cHp_Item::Change()
{

}

void cHp_Item::Release()
{
	delete this;
}
