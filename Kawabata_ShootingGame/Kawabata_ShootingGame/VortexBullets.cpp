#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#include "VortexBullets.h"

VortexBullets::VortexBullets(T_LOCATION location, float speed, int angle, unsigned int color)
	: BulletsBase(location, 6.0f, 5, T_LOCATION{ 0,0 }), color(color)
{
	int deg = angle % 360;
	double rad = (M_PI / 180) * deg;   //pxPΜΐl360x@

	//0Z(n/0)πρπ
	float x = static_cast<float>((abs(deg) == 90 || abs(deg) == 270) ? 0 : cos(rad)); //‘²cos
	float y = static_cast<float>(sin(rad));                                           //c²sin

	//(sin+cos)=1   cΖ‘Ιiήδ¦ sinEcosΕ
	this->speed = T_LOCATION{ (speed * x),(speed * y) };

	//ζΗέέ
	image = LoadGraph("images/bullets4.png");
}

//XV
void VortexBullets::Update()
{
	T_LOCATION newlocation = GetLocation();    //ΜΐW


	newlocation.y += speed.y;                  //ΐWπΟX
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //ΟXπ½f
}

//`ζ
void VortexBullets::Draw()
{
	//DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), color);
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
}
