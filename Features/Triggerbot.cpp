  void Shot() const
	{
		if (this->pLocal->GetMoveType() == MoveType_t::MOVETYPE_LADDER)
			return;

		pCmd->buttons |= IN_ATTACK;
		Sleep(20);

		/*/*(int*)(g_pEngine->GetAppID + g::pLocalEntity->GetAttack1) = 5;
		Sleep(20);
		*(int*)(g_pEngine->GetAppID + g::pLocalEntity->GetAttack1) = 4;/*/
	}
    
    void DoTriggerbot() const
    {
        if (this->pLocal->GetMoveType() == MoveType_t::MOVETYPE_LADDER)
            return;

		int localTeam = g::pLocalEntity->GetTeam();

		int crosshair = g::pLocalEntity->GetCrosshairID();

		if (crosshair != 0 && crosshair < 64) {
			C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity((crosshair -1) * 0x10);

			int entityTeam = pPlayerEntity->GetTeam();
			int entityHealth = pPlayerEntity->GetHealth();

			bool isDormant = pPlayerEntity->IsDormant();

			if (entityTeam != pLocal->GetTeam() && entityHealth > 0 && !isDormant) {

				Shot();
			}
		}
    }
