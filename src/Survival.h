#pragma once

using SurvivalModeCallback = REL::Relocation<bool()>;

namespace Survival
{
	enum class Feature : int32_t
	{
		HUDIndicators  = 0,
		InventoryUI    = 1,
		SleepToLevelUp = 2,
		ArrowWeight    = 3,
		LockpickWeight = 4,
	};

	enum class Preference : int32_t
	{
		None,
		AlwaysDisabled,
		AlwaysEnabled,
	};

	class Settings
	{
	public:
		void ForceEnable();
		void RequestDisable();
		void ModReset();
		void UserEnable();
		void UserDisable();
		void UserReset();

		bool IsEnabled(SurvivalModeCallback gameCallback);

		static Settings* GetSingleton(Feature feature)
		{
			static Settings hudIndicators;
			static Settings inventoryUI;
			static Settings sleepToLevelUp;
			static Settings arrowWeight;
			static Settings lockpickWeight;

			switch (feature)
			{
			case Feature::HUDIndicators:
				return &hudIndicators;
			case Feature::InventoryUI:
				return &inventoryUI;
			case Feature::SleepToLevelUp:
				return &sleepToLevelUp;
			case Feature::ArrowWeight:
				return &arrowWeight;
			case Feature::LockpickWeight:
				return &lockpickWeight;
			default:
				return nullptr;
			}
		}

		Preference UserPreference = Preference::None;
		Preference ModPreference = Preference::None;
	};

	inline Settings* GetSettings(Feature feature)
	{
		return Settings::GetSingleton(feature);
	}

	inline bool IsEnabled(Feature feature, SurvivalModeCallback gameCallback)
	{
		auto settings = GetSettings(feature);
		if (!settings)
		{
			return gameCallback();
		}
		else
		{
			return settings->IsEnabled(gameCallback);
		}
	}
}
