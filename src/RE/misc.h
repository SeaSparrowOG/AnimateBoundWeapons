#pragma once

#include "Offset.h"

namespace RE
{
	inline void SetPlayerTeammate(RE::Actor* a_this, bool a_teammate, bool a_canDoFavor) {
		using func_t = decltype(&SetPlayerTeammate);
		static REL::Relocation<func_t> func{ Offset::Script::SetPlayerTeammate };
		func(a_this, a_teammate, a_canDoFavor);
	}
}