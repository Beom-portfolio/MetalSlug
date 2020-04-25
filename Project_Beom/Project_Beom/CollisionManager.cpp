#include "pch.h"
#include "CollisionManager.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::CollisionRect(ObjectManager::MAPOBJ* DstList, ObjectManager::MAPOBJ* SrcList)
{
	// 렉트 충돌 검사
	RECT rc = {};

	for (auto& Dst : *DstList)
	{
		if (Dst.second->GetDeadCheck() || !Dst.second->GetCollideOnCheck())
			continue;

		for (auto& Src : *SrcList)
		{
			if (Src.second->GetDeadCheck() || !Src.second->GetCollideOnCheck())
				continue;

			if (IntersectRect(&rc, &Dst.second->GetCollideRect(), &Src.second->GetCollideRect()))
			{
				// 충돌 하였다면 서로 충돌 처리를 한다. 
				Src.second->CollisionActivate(Dst.second);
				Dst.second->CollisionActivate(Src.second);
				break;
			}
			else
			{
				Src.second->CollisionDeactivate(Dst.second);
				Dst.second->CollisionDeactivate(Src.second);
			}
		}
	}
}

void CollisionManager::CollisionRectEx(ObjectManager::MAPOBJ* DstList, ObjectManager::MAPOBJ* SrcList)
{
	// 충돌한 경우 서로 밀려나게 한다.
	int moveX = 0;
	int moveY = 0;

	for (auto& Dst : *DstList)
	{
		if (Dst.second->GetDeadCheck() || !Dst.second->GetCollideOnCheck())
			continue;

		for (auto& Src : *SrcList)
		{
			if (Src.second->GetDeadCheck() || !Src.second->GetCollideOnCheck())
				continue;

			if (CheckCollisionRectDist(&moveX, &moveY, Dst.second, Src.second))
			{
				int PosX = 0;
				int PosY = 0;

				if (moveX > moveY)
				{
					PosX = (int)Dst.second->GetInfo().Pos_X;
					PosY = (int)Dst.second->GetInfo().Pos_Y;

					if (Src.second->GetInfo().Pos_Y > PosY)
						moveY *= -1;

					Dst.second->SetPosition((float)PosX, (float)PosY + moveY);
				}
				else
				{
					PosX = (int)Dst.second->GetInfo().Pos_X;
					PosY = (int)Dst.second->GetInfo().Pos_Y;

					if (Src.second->GetInfo().Pos_X > PosX)
						moveX *= -1;

					Dst.second->SetPosition((float)PosX + moveX, (float)PosY);
				}
			}
		}
	}
}

void CollisionManager::CollisionPixelToRectDir(ObjectManager::MAPOBJ* pixel, ObjectManager::MAPOBJ* rect)
{
	for (auto& Dst : *pixel)
	{
		if (Dst.second->GetDeadCheck() || !Dst.second->GetCollideOnCheck())
			continue;

		const PIXELCOLLIDERINFO* pixelCollide = Dst.second->GetPixelCollider();

		if (nullptr == pixelCollide)
			continue;


		for (auto& Src : *rect)
		{
			int dir = 0;

			GAMEOBJINFO info = Src.second->GetInfo();
			GAMEOBJINFO collideInfo = Src.second->GetCollideInfo();
			RECT rc = Src.second->GetCollideRect();
			POSITION CamPos = GET_MANAGER<CameraManager>()->GetPos();
			rc.bottom -= (int)CamPos.Y;
			rc.top -= (int)CamPos.Y;
			rc.left -= (int)CamPos.X;
			rc.right -= (int)CamPos.X;

			int addr;

			for (auto collColor : pixelCollide->CollPixels)
			{
				// 아래 
				addr = rc.bottom * pixelCollide->Width + (int)info.Pos_X;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == collColor.r &&
					pixelCollide->vecPixel[addr].g == collColor.g &&
					pixelCollide->vecPixel[addr].b == collColor.b)
				{
					dir |= DIR_BOTTOM;
				}
				// 위
				addr = rc.top * pixelCollide->Width + (int)info.Pos_X;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == collColor.r &&
					pixelCollide->vecPixel[addr].g == collColor.g &&
					pixelCollide->vecPixel[addr].b == collColor.b)
				{
					dir |= DIR_TOP;
				}
				// 왼쪽
				addr = (int)info.Pos_Y * pixelCollide->Width + (int)rc.left;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == collColor.r &&
					pixelCollide->vecPixel[addr].g == collColor.g &&
					pixelCollide->vecPixel[addr].b == collColor.b)
				{
					dir |= DIR_LEFT;
				}
				// 오른쪽
				addr = (int)info.Pos_Y * pixelCollide->Width + (int)rc.right;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == collColor.r &&
					pixelCollide->vecPixel[addr].g == collColor.g &&
					pixelCollide->vecPixel[addr].b == collColor.b)
				{
					dir |= DIR_RIGHT;
				}

				Src.second->CollisionPixelPart((DIRECTION)dir, Dst.second, collColor);
			}
		}
	}
}

void CollisionManager::CollisionPixelToPoint(ObjectManager::MAPOBJ* pixel, ObjectManager::MAPOBJ* rect)
{
	for (auto& Dst : *pixel)
	{
		if (true == Dst.second->GetDeadCheck())
			continue;

		const PIXELCOLLIDERINFO* pixelCollide = Dst.second->GetPixelCollider();

		if (nullptr == pixelCollide)
			continue;

		for (auto& Src : *rect)
		{
			GAMEOBJINFO rc = Src.second->GetInfo();
			int addr = (int)rc.Pos_Y * pixelCollide->Width + (int)rc.Pos_X;
			if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
			for (auto collColor : pixelCollide->CollPixels)
			{
				if (pixelCollide->vecPixel[addr].r == collColor.r &&
					pixelCollide->vecPixel[addr].g == collColor.g &&
					pixelCollide->vecPixel[addr].b == collColor.b)
				{
					//printf("Collide! ");
				}
			}
		}
	}
}

bool CollisionManager::CheckCollisionRectDist(int* moveX, int* moveY, GameObject* Dst, GameObject* Src)
{
	// 각 축의 합이 두 객체간의 축의 거리보다 큰 경우 => 충돌
	// 충돌된 거리를 구한다.

	// 축의 합을 구한다.
	int width = (Dst->GetCollideInfo().Size_X / 2) + (Src->GetCollideInfo().Size_X / 2);
	int height = (Dst->GetCollideInfo().Size_Y / 2) + (Src->GetCollideInfo().Size_Y / 2);

	int distX = abs((int)Dst->GetInfo().Pos_X - (int)Src->GetInfo().Pos_X);
	int distY = abs((int)Dst->GetInfo().Pos_Y - (int)Src->GetInfo().Pos_Y);

	//  충돌된 경우
	if ((width > distX) && (height > distY))
	{
		// 충돌된 길이를 구한다.
		*moveX = width - distX;
		*moveY = height - distY;

		return true;
	}

	return false;
}