#include "runtimePatcher.h"

#include "utilities/utilities.h"

namespace RuntimePatcher
{
	void Patch()
	{
		const auto dataHandler = RE::TESDataHandler::GetSingleton();
		assert(dataHandler);
		if (!dataHandler) {
			logger::error("Failed to get Data Handler. This is likely going to cause a crash later on, not related to this mod.");
			return;
		}

		const auto effectToAdd = dataHandler->LookupForm<RE::EffectSetting>(0x801, "AnimatedBoundWeapons.esp");
		if (!effectToAdd) {
			logger::error("Failed to find the dual cast effect!");
			return;
		}

		const auto& spellArray = dataHandler->GetFormArray<RE::SpellItem>();
		for (auto* spell : spellArray) {
			if (!spell || !spell->GetPlayable()) {
				continue;
			}
			if (spell->GetDelivery() != RE::MagicSystem::Delivery::kSelf) {
				continue;
			}
			if (spell->GetCastingType() != RE::MagicSystem::CastingType::kFireAndForget) {
				continue;
			}

			bool hasBoundWeapon = false;
			bool hasDualCastCondition = false;
			for (const auto* effect : spell->effects) {
				if (!effect || !effect->baseEffect) {
					continue;
				}
				
				auto* head = effect->conditions.head;
				while (head) {
					const auto& data = head->data;
					if (data.functionData.function.any(RE::FUNCTION_DATA::FunctionID::kEffectWasDualCast)) {
						hasDualCastCondition = true;
						break;
					}
					head = head->next;
				}
				if (hasDualCastCondition) {
					break;
				}

				const auto* baseEffect = effect->baseEffect;
				if (baseEffect->GetArchetype() != RE::EffectSetting::Archetype::kBoundWeapon) {
					continue;
				}

				hasBoundWeapon = true;

			}
			if (!hasBoundWeapon || hasDualCastCondition) {
				continue;
			}

			for (auto* effect : spell->effects) {
				if (!effect || !effect->baseEffect) {
					continue;
				}

				auto* tail = effect->baseEffect->conditions.head;
				while (tail && tail->next) {
					tail = tail->next;
				}

				auto* newConditionItem = new RE::TESConditionItem();
				if (!newConditionItem) {
					logger::error("Failed to create new condition item for {}!", spell->GetName());
					break;
				}

				//Value
				RE::CONDITION_ITEM_DATA condData{};

				//Flags
				condData.flags.global = false;
				condData.flags.isOR = false;
				condData.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kEqualTo;
				condData.flags.swapTarget = false;
				condData.flags.usePackData = false;
				condData.flags.usesAliases = false;

				//ConditionItemData
				condData.object = RE::CONDITIONITEMOBJECT::kSelf;

				//FunctionData
				condData.functionData.function = RE::FUNCTION_DATA::FunctionID::kEffectWasDualCast;;
				
				//Append to conditionItem
				newConditionItem->data = condData;

				//Finally, set
				if (tail) {
					tail->next = newConditionItem;
				}
				else {
					effect->baseEffect->conditions.head = newConditionItem;
				}
				newConditionItem->next = nullptr;
			}

			auto newEffect = new RE::Effect();
			newEffect->baseEffect = effectToAdd;
			newEffect->cost = 0.0f;
			newEffect->effectItem.area = 0;
			newEffect->effectItem.duration = 60;
			newEffect->effectItem.magnitude = 1.0f;

			spell->effects.push_back(newEffect);
		}
	}
}