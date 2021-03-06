#pragma once
#include "Car.h"
#include "Gun.h"
//represets the player himself and handles interaction between the player and his car.
class PlayerController
{
public:
	Car * car;
	Gun* gun;
	SDL_GameController* controller;
	int Mx, My;
	bool DarkMode = false;
	int Guntype = 1;

	PlayerController()
	{
		car = nullptr;
		controller = nullptr;
		
	}

	void HandleEvent(Vector<Projectile*>&projectiles)
	{
		if (Guntype == 1)
		{
			gun->Gun::Fire(projectiles);
		}
		else if (Guntype == 2)
		{
			gun->Gun::FireBackward(projectiles);
		}
		else if (Guntype == 3)
		{
			gun->Gun::ShortGun(projectiles);
		}
		else if (Guntype == 4)
		{
			gun->Gun::ShortGunBackward(projectiles);
		}
		else if (Guntype == 5)
		{
			gun->Gun::ForFun(projectiles);
		}
	}

	void HandleInputState(const Uint8* keystates, SDL_Event event, Vector<Projectile*>&projectiles)
	{
		//Keyboard
		if (car == nullptr)
			return;
		// Accelerate, brake, turn
		if (keystates[SDL_SCANCODE_A])
		{
			if (car->velocity.Magnitude() > 1)
				car->facingDegrees -= 4;
		}
		else if (keystates[SDL_SCANCODE_D])
		{
			if (car->velocity.Magnitude() > 1)
				car->facingDegrees += 4;
		}
		if (keystates[SDL_SCANCODE_W])
			car->Accelerate();

		//switich gun's elements
		if (keystates[SDL_SCANCODE_Q])//Fire
		{
			gun->Element = 1;
		}
		else if (keystates[SDL_SCANCODE_E])//Nature
		{
			gun->Element = 2;
		}
		else if (keystates[SDL_SCANCODE_LSHIFT])//Water
		{
			gun->Element = 3;
		}

		//switich gun's type
		if (keystates[SDL_SCANCODE_1])//Fire
		{
			Guntype = 1;
		}
		else if (keystates[SDL_SCANCODE_2])//Nature
		{
			Guntype = 2;
		}
		else if (keystates[SDL_SCANCODE_3])//Water
		{
			Guntype = 3;
		}
		else if (keystates[SDL_SCANCODE_4])//Water
		{
			Guntype = 4;
		}
		else if (keystates[SDL_SCANCODE_5])//Water
		{
			Guntype = 5;
		}

		//Mouse
		//get mouse position for gun's facing degree
			gun->facingDegrees = atan2(My - car->position.y, Mx - car->position.x) * 180 / (float)M_PI;
		//if left button down
		if (SDL_GetMouseState(&Mx, &My)&SDL_BUTTON_LMASK)
		{
			HandleEvent(projectiles);
		}


		//Game controller
		//turn left
		//Sint16 accelAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		//if(accelAxis<-18000)
		//{
		//	if (car->velocity.Magnitude() > 3)
		//		car->facingDegrees -= 2;
		//}
		//
		////turn right
		//Sint16 accelAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		//if (accelAxis>18000)
		//{
		//	if (car->velocity.Magnitude() > 3)
		//		car->facingDegrees += 2;
		//}
		//
		//accelerate
		//if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A))
	}

	void CreateCar(GPU_Image* Image, int _element)
	{
		car = new Car(Image, _element);
	}

	void CreateGun(GPU_Image* image, GPU_Image* _projectilesImage, float sp, int _damage, float firerate)
	{
		gun = new Gun(image, _projectilesImage, sp, _damage, firerate);
	}
};