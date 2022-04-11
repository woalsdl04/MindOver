#include "DXUT.h"
#include "Score_Number.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;
extern int TotalScore;

Score_Number::Score_Number()
{

}

Score_Number::~Score_Number()
{

}

void Score_Number::NEW()
{
	/*gameObject->Add_Component<Color_Component>(L"Number_Color")->Setup(GCOLOR(1, 1, 1, 0), GCOLOR(1, 1, 1, 1), -0.5, COLOR_ACTIONTYPE::ONEWAY, 0xFFFFFFFF);
	gameObject->Add_Component<TRS_Component>(L"Number_TRS")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(0.7, 0.7, 0.7), GVec3<float>(1, 1, 1), -2, TRS_LOOPTYPE::ONEWAY, TRS_SPEEDTYPE::SPEEDUP, 0, 0xFFFFFFFF);*/
}

void Score_Number::Awake()
{

}

void Score_Number::Start()
{

}

void Score_Number::Notice(Notice_Item* notice)
{


}

void Score_Number::Update()
{

}

void Score_Number::Late_Update()
{

}

void Score_Number::Final_Update()
{

}

void Score_Number::Render()
{
	gameObject->Get_Component<SpriteRenderer_Component>()->Active = true;

	int score = (int)TotalScore;
	
	int a = 0;

	while (score > 0)
	{
		int num = score % 10;

		//num = abs(num - 10);

		RECT rect = { 133 * num, 0, (133 * num) + 133, 133};
		gameObject->Get_Component<SpriteRenderer_Component>()->PutImage_Piece(&rect, WISIZE_X/2 + (-100 * a), WISIZE_Y/2 + 30, 0xFFFFFFFF);

		GLog(L"num: %d", num);

		a++;
		score /= 10;
	}
	gameObject->Get_Component<SpriteRenderer_Component>()->Active = false;
}

void Score_Number::Reload()
{

}

void Score_Number::Change()
{

}

void Score_Number::Release()
{
	delete this;
}
