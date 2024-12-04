#pragma once

namespace RuntimePatcher
{
	//Credit: PO3 Light Placer
	union VOID_PARAM
	{
		char* c;
		std::int32_t i;
		float        f;
		RE::TESForm* ptr;
	};

	void Patch();
}