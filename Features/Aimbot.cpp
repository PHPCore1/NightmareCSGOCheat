void DoAimbot() const
	{
		float best_fov = g_Settings.fAimbotFOV;
		Vector view_angles;
		Vector engine_angles;

		for (int it = 1; it <= g_pEngine->GetMaxClients(); ++it)
		{
			C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity(it);

			if (!pPlayerEntity || pPlayerEntity->IsDormant() || !pPlayerEntity->IsAlive() || pPlayerEntity == pLocal || pPlayerEntity->GetTeam() == pLocal->GetTeam() || !GetAsyncKeyState(VK_LBUTTON) || g_Settings.bMenuOpened)
				continue;

			g_pEngine->GetViewAngles(engine_angles);

			Vector angles;

			switch (g_Settings.iAimbotBone)
			{
			//case 0: angles = MATH::NormalizeAngle(MATH::CalcAngle(pLocal->GetEyePosition(), (pPlayerEntity->GetBonePosition(8))), g_Settings.f_AimbotSmooth()); break;
			case 1: angles = MATH::NormalizeAngle(MATH::CalcAngle(pLocal->GetEyePosition(), pPlayerEntity->GetBonePosition(7))); break;
			case 2: angles = MATH::NormalizeAngle(MATH::CalcAngle(pLocal->GetEyePosition(), pPlayerEntity->GetBonePosition(6))); break;
			case 3: angles = MATH::NormalizeAngle(MATH::CalcAngle(pLocal->GetEyePosition(), pPlayerEntity->GetBonePosition(5))); break;
			}

			float fov = (engine_angles - angles).Length2D();

			if (fov < best_fov)
			{
				best_fov = fov;
				view_angles = angles;
			}

			/*const auto diff = pLocal->GetEyePosition() - pPlayerEntity->GetBonePosition;

			//g_pEngine->SetViewAngles(view_angles);
			switch (g_Settings.iAimbotBone)
			{
			case 0: diff = pPlayerEntity->GetBonePosition(8); break;
			case 1: diff = pPlayerEntity->GetBonePosition(7); break;
			case 2: diff = pPlayerEntity->GetBonePosition(6); break;
			case 3: diff = pPlayerEntity->GetBonePosition(5); break;
			}

			Vector aimAngle;
			MATH::VectorAngles(diff, aimAngle);
			aimAngle -= pLocal->GetPunchAngles() * 2.f;
			MATH::NormalizeAngle(aimAngle);

			auto relativeAngle = pCmd->viewangles - aimAngle;
			const auto unitAngle = relativeAngle / relativeAngle.Length();
			auto smoothedAngle = unitAngle / g_Settings.iAimbotSmooth / (fov / g_Settings.fAimbotFOVIndepence > 1.f ? fov / g_Settings.fAimbotFOVIndepence : 1.f);
			if (smoothedAngle.Length() > relativeAngle.Length()) smoothedAngle = relativeAngle;

			g_pEngine->SetViewAngles(smoothedAngle);*/
		}

		if (best_fov != g_Settings.fAimbotFOV)
		{
			g_pEngine->SetViewAngles(view_angles);
		}
	}

	void DoAimbotRCS() const
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			Vector recoil = pLocal->GetPunchAngles();
			pCmd->viewangles -= recoil * 2.f;
		}
	}
