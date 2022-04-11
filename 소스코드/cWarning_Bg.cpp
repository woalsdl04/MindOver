#include "DXUT.h"
#include "cWarning_Bg.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

cWarning_Bg::cWarning_Bg()
{

}

cWarning_Bg::~cWarning_Bg()
{

}

void cWarning_Bg::NEW()
{
	gameObject->Add_Component<SpriteRenderer_Component>(L"Warning_Bg_Sc")->Load_Texture(L"Warning/Warning_Bg.png", 1, 1, false);
	gameObject->Get_Component<SpriteRenderer_Component>()->Lock_Check();
}

void cWarning_Bg::Awake()
{

}

void cWarning_Bg::Start()
{

}

void cWarning_Bg::Notice(Notice_Item* notice)
{


}

void cWarning_Bg::Update()
{

}

void cWarning_Bg::Late_Update()
{

}

void cWarning_Bg::Final_Update()
{

}

void cWarning_Bg::Render()
{

}

void cWarning_Bg::Reload()
{

}

void cWarning_Bg::Change()
{

}

void cWarning_Bg::Release()
{
	delete this;
}
