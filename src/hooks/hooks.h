#pragma once

#include "utilities/utilities.h"

namespace Hooks
{
	void Install();
	class DontLowerHands : public Utilities::Singleton::ISingleton<DontLowerHands>
	{
	public:
		void Install();

	private:
		static void DrawWeaponMagicHands(RE::Character* a_this, bool a_draw);

		inline static REL::Relocation<decltype(DrawWeaponMagicHands)> _drawWeaponMagicHands;
		inline static RE::TESNPC* unsheathingSpectre;
	};
}