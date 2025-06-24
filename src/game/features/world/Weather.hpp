#include "core/componentStates/CallCode.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	inline constexpr std::array g_WeatherCodes = {
	    "CLEAR",
	    "EXTRASUNNY",
	    "CLOUDS",
	    "OVERCAST",
	    "RAIN",
	    "CLEARING",
	    "THUNDER",
	    "SMOG",
	    "FOGGY",
	    "XMAS",
	    "SNOW",
	    "SNOWLIGHT",
	    "BLIZZARD",
	    "HALLOWEEN",
	    "NEUTRAL",
	    "RAIN_HALLOWEEN",
	    "SNOW_HALLOWEEN",
	};

	class SetWeather : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			MISC::SET_WEATHER_TYPE_PERSIST(weatherType);
		}

	public:
		const char* weatherType = g_WeatherCodes[0];
	};

	inline SetWeather _SetWeather{"setweather", "Set Weather", "Sets the specifed weather. Note that this effect is local"};
}