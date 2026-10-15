# YimMenuV2

This menu is not the original yim menu and is generally not recommended for general public. I just use it personally. I have added/removed features as I see fit.
Before using this menu I recommended using the official [YimMenuV2](https://github.com/YimMenu/YimMenuV2) and check readme guide there for usage.

## Important notes related to architecture

I have modified the code which resulted in following changes:

- State: No settings will be saved to disc.
- Folder: This menu creates different folder so it will not interfere with yim menu folder.
- Lobbies & players: Play alone in private lobby (highly recommended). If you want to play with other modders then turn on "Allow Players in Lobby" in "Misc".
- Features: original features are removed/modifed. new features from original menu are only added as needed
- Lua: No support.
- Language: Only english
- Commands: Not implemented
- Hotkey: Only implemented for menu toggle.
- UI components: custom UI components like tab etc removed! there is currently only one file that maintain few reusable components (`src\game\frontend\components\components.hpp`), other than that use basic imgui code. The basic steps to render ui is to create submenu (or use existing one). In that create a `SubmenuMenuCategory` and write UI code in its `SubmenuMenuCategory->Draw` function.

## Credits

The menu is a fork and thereby sync changes from original yimmenu fork like game updates, anticheat updates and new features. I try my best not to modifiy their source code and preserve the original author (committer) works.

This menu other than original yim source includes external code from other sources and as such I respect those original authers works as well.
In this repo where i have used external code, the reference to their original source will be mentioned with a `//` comment in the starting of file or close to the code.

Credits to people with most code references:
- [ImagineNothing on UC](https://www.unknowncheats.me/forum/members/3627117.html)
- [ShinyWasabi on UC](https://www.unknowncheats.me/forum/members/4767140.html)