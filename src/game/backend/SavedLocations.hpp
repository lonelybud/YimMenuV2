#pragma once

namespace YimMenu
{
	struct SavedLocation
	{
		std::string name;
		float x, y, z;
	};

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SavedLocation, name, x, y, z);

	class SavedLocations
	{
	private:
		std::filesystem::path GetSavedLocationsFilePath();
		std::map<std::string, std::vector<SavedLocation>> m_AllSavedLocations;

	private:
		bool FetchSavedLocationsImpl();
		bool SaveNewLocationImpl(const std::string& category, SavedLocation t);
		bool DeleteSavedLocationImpl(const std::string& category, const std::string& location_name);
		std::vector<SavedLocation> SavedLocationsFilteredListImpl(std::string filter = "");

		static SavedLocations& GetInstance()
		{
			static SavedLocations instance{};
			return instance;
		}

	public:
		static std::map<std::string, std::vector<SavedLocation>>& GetAllSavedLocations()
		{
			return GetInstance().m_AllSavedLocations;
		}

		static bool FetchSavedLocations()
		{
			return GetInstance().FetchSavedLocationsImpl();
		};

		static bool SaveNewLocation(const std::string& category, SavedLocation t)
		{
			return GetInstance().SaveNewLocationImpl(category, t);
		};

		static bool DeleteSavedLocation(const std::string& category, const std::string& location_name)
		{
			return GetInstance().DeleteSavedLocationImpl(category, location_name);
		};

		static std::vector<SavedLocation> SavedLocationsFilteredList(std::string filter = "")
		{
			return GetInstance().SavedLocationsFilteredListImpl(filter);
		};
	};

}