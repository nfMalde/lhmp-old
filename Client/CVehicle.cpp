#include "CVehicle.h"
#include "CCore.h"

extern CCore *g_CCore;
CVehicle::CVehicle()
{
	this->SetActive(true);
	isActive = true;
	//sprintf(sName, "Player");
	playerPos.x = -1985.97f;
	playerPos.y = -5.03f;
	playerPos.z = 4.28f;
	actual.x = -1985.97f;
	actual.y = -5.03f;
	actual.z = 4.28f;
	interpolationVector.x = 0;
	interpolationVector.y = 0;
	interpolationVector.z = 0;
	tempVector.x = 0;
	tempVector.y = 0;
	tempVector.z = 0;

	vehPos.x = -1985.98f;
	vehPos.y = -5.03f;
	vehPos.z = 4.28f;

	speed.x = 0.0f;
	speed.y = 0.0f;
	speed.z = 0.0f;

	rotation.x = -0.006f;
	rotation.y = 0.003f;
	rotation.z = -0.999f;
	secondRot.x = -0.0138f;
	secondRot.y = 0.9999f;
	secondRot.z = 0.0038f;
	actual = playerPos;
	previous = playerPos;
	isSpawned = 0;
	damage = 100.0f;
	shotdamage = 10;
	onGas = false;

	fHealth = 200.0f;
	skinId = 0;

	timeDiff = timeGetTime();
	timeLastMessage = timeDiff;

	for (int i = 0; i < 4; i++)
		this->Seat[i] = -1;

	horn = 0;
	roofState = 0;
	damage = 100.0f;

	explodedCar = NULL;
}
CVehicle::~CVehicle()
{

}
void CVehicle::SetActive(bool b)
{
	isActive = b;
}

bool CVehicle::IsActive()
{
	return isActive;
}

void CVehicle::UpdateGameObject()
{
	if (this->GetEntity() != NULL)
	{
		if (Seat[0] != g_CCore->GetLocalPlayer()->GetOurID())
		{
			//g_CCore->GetLog()->AddLog("VehicleUpdate");
			//g_CCore->GetGame()->SetCarPosition(this->GetEntity(), this->GetPosition());
			g_CCore->GetGame()->SetCarRotation(this->GetEntity(), this->GetRotation());
			
		}
	}
	/*if (this->EntityBase == 0) return;
	if (this->fHealth == 0) return;
	*(float*)(this->EntityBase + 0x24) = this->playerPos.x;
	*(float*)(this->EntityBase + 0x28) = this->playerPos.y;
	*(float*)(this->EntityBase + 0x2C) = this->playerPos.z;

	/**(float*)(this->EntityBase + 0x30) = this->rotation1;
	*(float*)(this->EntityBase + 0x38) = this->rotation2;
	*(float*)(this->EntityBase + 0x238) = this->rotation3;
	*/
	/*(float*)(this->EntityBase + 0x644) = this->fHealth;
	*(byte*)(this->EntityBase + 0x74) = this->state;*/




	/*sLocalPlayer.rotation1 = *(float*) ((*(DWORD*)((*(DWORD*)0x006F9464)+0xE4))+0x30);
	sLocalPlayer.rotation2 = *(float*) ((*(DWORD*)((*(DWORD*)0x006F9464)+0xE4))+0x38);

	sLocalPlayer.state	= *(BYTE*) ((*(DWORD*)((*(DWORD*)0x006F9464)+0xE4))+0x70);
	*/
}

void CVehicle::SetUpInterpolation()
{
	this->interpolation.SetUpInterpolation(this->playerPos);
}

void CVehicle::Interpolate()
{
	// this func should be called in Endscene
	// hardcoded by Romop5, 25.12 at 0:10 AM :D :D :D

	if (this->GetEntity() != 0 && this->Seat[0] != g_CCore->GetLocalPlayer()->GetOurID())
	{
		bool hasDriver = !(this->Seat[0] == -1);

		this->playerPos = interpolation.Interpolate();

		DWORD entity = this->GetEntity();
		float x = this->speed.x, y = this->speed.y, z = this->speed.z;
		_asm
		{
			pushad
			mov EDX,entity
			mov EAX, x
			MOV DWORD PTR DS : [EDX+0x1F7C], EAX
			mov EAX, y
			MOV DWORD PTR DS : [EDX+0x1F80], EAX
			mov EAX, z
			MOV DWORD PTR DS : [EDX+0x1F84], EAX
			popad
		}
		
		if (hasDriver == false)
		{
			//g_CCore->GetGame()->CarUpdate(this->GetEntity(), this->playerPos, this->rotation);
			if ((*(float*)(entity + 0x40C) - this->playerPos.x) > 0.3 || (*(float*)(entity + 0x410) - this->playerPos.y) > 0.3 || (*(float*)(entity + 0x414) - this->playerPos.z) > 0.3)
			{
				//g_CCore->GetGame()->CarUpdate(this->GetEntity(), this->playerPos, this->rotation);
				*(float*)(entity + 0x40C) = this->playerPos.x;
				*(float*)(entity + 0x410) = this->playerPos.y;
				*(float*)(entity + 0x414) = this->playerPos.z;

				*(float*)(entity + 0xD28) = this->rotation.x;
				*(float*)(entity + 0xD2C) = this->rotation.y;
				*(float*)(entity + 0xD30) = this->rotation.z;

				*(float*)(entity + 0xD40) = this->secondRot.x;
				*(float*)(entity + 0xD44) = this->secondRot.y;
				*(float*)(entity + 0xD48) = this->secondRot.z;

				// takmer dokonale
				/*_asm
				{

					//MOV EAX, 0x0
					MOV EAX, 0x3DA9FBE8
						PUSH EAX; / Arg3 = 00000000
						PUSH EAX; | Arg2	0
						//MOV EAX, 0x3DA9FBE8
						PUSH EAX; | Arg1   	0x3DA9FBE8
						MOV ESI, entity
						ADD ESI, 0x70
						MOV ECX, ESI; | base + 0x70
						MOV EAX, 0x0052E6D0
						CALL EAX; game.0052E6D0; \game.0052E6D0
				}*/
				/*_asm {
					MOV ESI, entity
					PUSH 0x10; / Arg1 = 00000010
					LEA ECX, DWORD PTR DS : [ESI + 0x70]; |
					MOV EAX, 0x0052C3B0
					CALL EAX; Game.0052C3B0; \Game.0052C3B0


					}*/
				/*_asm {
					MOV ESI, entity
					MOV ECX, ESI
					MOV EAX, DWORD PTR DS : [ESI]
					PUSH 0x31
					CALL DWORD PTR DS : [EAX + 0x34]


					}*/
				//}
				// car_calm func
				_asm
				{
					PUSH 0x1
						MOV ECX, entity
						MOV EAX, 0x00470D30
						CALL EAX; Game.00470D30
						TEST AL, AL
						JE end
						PUSH 0x14; / Arg1 = 00000014
						MOV ECX, entity
						ADD ECX, 0x70; |
						MOV EAX, 0x0051A920
						CALL EAX; Game.0051A920; \Game.0051A920
					end:


				}
			}
		
		}
		else
		{
			*(float*)(entity + 0x40C) = this->playerPos.x;
			*(float*)(entity + 0x410) = this->playerPos.y;
			*(float*)(entity + 0x414) = this->playerPos.z;

			*(float*)(entity + 0xD28) = this->rotation.x;
			*(float*)(entity + 0xD2C) = this->rotation.y;
			*(float*)(entity + 0xD30) = this->rotation.z;

			*(float*)(entity + 0xD40) = this->secondRot.x;
			*(float*)(entity + 0xD44) = this->secondRot.y;
			*(float*)(entity + 0xD48) = this->secondRot.z;
		}

		/**(float*)(entity + 0xD40) = this->secondRot.x;
		*(float*)(entity + 0xD44) = this->secondRot.y;
		*(float*)(entity + 0xD48) = this->secondRot.z;*/

		*(INT16*)(entity + 0x6A6) = 0;			// zabrzdene kolesa - int16 lebo to ma velkost WORD
		
		*(byte*)(this->GetEntity() + 0x51C) = this->GetHornState();
		*(float*)(this->GetEntity() + 0x490) = (this->IsOnGas() ? 1.0f: 0.0f);
	}
}


void CVehicle::SendSync()
{
	if (Seat[0] == g_CCore->GetLocalPlayer()->GetOurID() && this->GetEntity())	
	// we are allow to stream only vehicle which is driven by us
	{
		Vector3D pos, rot, speed;
		pos.x = *(float*)(this->GetEntity() + 0x40C);
		pos.y = *(float*)(this->GetEntity() + 0x410);
		pos.z = *(float*)(this->GetEntity() + 0x414);

		rot.x = *(float*)(this->GetEntity() + 0x30);
		rot.y = *(float*)(this->GetEntity() + 0x34);
		rot.z = *(float*)(this->GetEntity() + 0x38);

		secondRot.x = *(float*)(this->GetEntity() + 0xD40);
		secondRot.y = *(float*)(this->GetEntity() + 0xD44);
		secondRot.z = *(float*)(this->GetEntity() + 0xD48);
		//char buff[255];
		//sprintf(buff, "Rot %f %f %f", rot.x, rot.y, rot.z);
		//g_CCore->GetLog()->AddLog(buff);
		speed.x = *(float*)(this->GetEntity() + 0x1F7C);
		speed.y = *(float*)(this->GetEntity() + 0x1F80);
		speed.z = *(float*)(this->GetEntity() + 0x1F84);

		this->wheels  = *(float*)(this->GetEntity() + 0x710);
		this->onGas = (*(float*)(this->GetEntity() + 0x490) == 1.0f);

		this->SetRotation(rot);
		this->previous = pos;
		this->actual = pos;
		this->SetPosition(pos);
		this->SetSecondRot(secondRot);
		//this->timeLastMessage = RakNet::GetTimeMS();
		interpolation.SetTimestamp(RakNet::GetTimeMS());
		interpolation.SetUpInterpolation(pos);
		interpolation.SetPosition(pos);
		VEH::SYNC syncData;
		syncData.ID = g_CCore->GetVehiclePool()->GetVehicleIdByBase(this->GetEntity());
		syncData.position = pos;
		syncData.rotation = rot;
		syncData.secondRot = secondRot;
		syncData.speed = speed;
		syncData.wheels = wheels;
		syncData.gasOn = this->onGas;
		syncData.horn = (*(byte*)(this->GetEntity() + 0x51C) == 1);
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)ID_TIMESTAMP);
		bsOut.Write(RakNet::GetTimeMS());
		bsOut.Write((RakNet::MessageID)ID_GAME_LHMP_PACKET);
		bsOut.Write((RakNet::MessageID)LHMP_VEHICLE_SYNC);
		bsOut.Write(syncData);
		g_CCore->GetNetwork()->SendServerMessage(&bsOut, LOW_PRIORITY, UNRELIABLE);
		//g_CCore->GetLog()->AddLog("vehicle stream");
	}

}

void CVehicle::PlayerEnter(int ID, int seat)
{
	this->Seat[seat] = ID;
	if (ID == g_CCore->GetLocalPlayer()->GetOurID())
		g_CCore->GetLocalPlayer()->IDinCar = g_CCore->GetVehiclePool()->GetVehicleIdByBase(this->GetEntity());
}
void CVehicle::PlayerExit(int ID)
{
	for (int i = 0; i < 4;i++)
		if (Seat[i] == ID)
			this->Seat[i] = -1;
	if (ID == g_CCore->GetLocalPlayer()->GetOurID())
		g_CCore->GetLocalPlayer()->IDinCar = -1;
}

void CVehicle::SetSpeed(Vector3D sp)
{
	this->speed = sp;
	if (this->GetEntity() != NULL)
	{
		*(float*)(this->GetEntity() + 0x1F7C) = this->speed.x;
		*(float*)(this->GetEntity() + 0x1F80) = this->speed.y;
		*(float*)(this->GetEntity() + 0x1F84) = this->speed.z;
	}	
}
Vector3D CVehicle::GetSpeed()
{
	return this->speed;
}

void CVehicle::ToggleRoof(byte state)
{
	this->roofState = state;
	if (this->GetEntity() != NULL)
	{
		g_CCore->GetGame()->ToggleVehicleRoof(this->GetEntity(), state);
	}
}

byte CVehicle::GetRoofState()
{
	return this->roofState;
}

void	CVehicle::SetWheelsAngle(float ang)
{
	this->wheels = ang;
	if (this->GetEntity() != NULL)
	{
		*(float*)(this->GetEntity() + 0x710) = this->wheels;
	}
}
float	CVehicle::GetWheelsAngle()
{
	return this->wheels;
}

int		CVehicle::GetSeat(int ID)
{
	return this->Seat[ID];
}

void CVehicle::SetSeat(int ID, int pID)
{
	this->Seat[ID] = pID;
}

void CVehicle::SetVehiclePosition(Vector3D pos)
{
	this->vehPos = pos;
}
Vector3D CVehicle::GetVehiclePosition()
{
	return this->vehPos;
}

void CVehicle::SetHornState(bool b)
{
	this->horn = b;
}
bool CVehicle::GetHornState()
{
	return this->horn;
}

void CVehicle::SetSecondRot(Vector3D rot)
{
	this->secondRot = rot;
}
Vector3D CVehicle::GetSecondRot()
{
	return this->secondRot;
}

Vector3D	CVehicle::GetTempVect()
{
	return this->tempVector;
}
Vector3D	CVehicle::GetInterVect()
{
	return this->interpolationVector;
}


float	CVehicle::GetDamage()
{
	return damage;
}
void	CVehicle::SetDamage(float dmg)
{
	this->damage = dmg;
	if (this->GetEntity() != NULL)
	{
		*(float*)(this->GetEntity() + 0x2A4) = this->damage;
	}
	char buff[30];
	sprintf(buff, "Damage: %f", dmg);
	g_CCore->GetLog()->AddLog(buff);
}


byte	CVehicle::GetShotDamage()
{
	return shotdamage;
}
void	CVehicle::SetShotDamage(byte dmg)
{
	this->shotdamage = dmg;
	if (this->GetEntity() != NULL)
	{
		*(float*)(this->GetEntity() + 0x2094) = this->damage;
	}
	char buff[30];
	sprintf(buff, "ShotDamage: %d", dmg);
	g_CCore->GetLog()->AddLog(buff);
}


bool	CVehicle::IsOnGas()
{
	return this->onGas;
}
void	CVehicle::SetIsOnGas(bool gas)
{
	this->onGas = gas;
}


int		CVehicle::GetPlayerSeat(int pp)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->Seat[i] == pp)
			return i;
	}
	return -1;
}


DWORD		CVehicle::GetExplodedCar()
{
	return this->explodedCar;
}
void		CVehicle::SetExplodedCar(DWORD base)
{
	this->explodedCar = base;
}