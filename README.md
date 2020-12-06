# **E**xiled **L**ocal **U**pdater (ELU)
### ```A Windows 10 (x64) application to automatically update your local EXILED related files```

With a bit of configuration and the push of a button, this application allows you to automatically:
- Update your Server Files with the EXILED Bootstraped Assembly.
- Publicize the Game Assembly and use it as a dependency.
- Extract the content of the selected EXILED Archive.
- Replace your Plugins folder in your EXILED root folder with the extracted version.
- Update all your projects dependencies (DLL) with every Assembly format (firstpass, publicized, \& original) and the extracted EXILED files.

## User Guide

### Update Release

To update your EXILED release, you'll need to follow those requirements:
- Register your **EXILED** path (ex: ```%AppData%/Roaming/EXILED```).
- Specify your Server DLL folder in **Game** (ex: ```Steam/steamapps/common/SCP Secret Laboratory Dedicated Server/SCPSL_Data/Managed```).
- Add your project(s) dependencies/references folder with **Add Project**.

Once all this is done, to build a specific release:
- Download the latest release on the [EXILED Github](https://github.com/galaxy119/EXILED/releases) (ex: ```Exiled.tar.gz```).
- Specify the archive path in the bottom field and its tag in the following field.
- Either:
  - Build & Update your release locally with the **Build & Update All** button.
  - Update from the latest build with **Update from Latest** button.

> :warning: Your build tag won't allow you to rebuild your current build if you do not specify a tag superior to the previous one.

### Change Theme

You can change your application current theme by selecting a **.qss** file under ```View > Theme```.

You can find other **.qss** files [here](https://qss-stock.devsecstudio.com/templates.php) and add them under your ```themes``` folder in the ELU local files.

### Miscelleanous

> ```Coming soon...```

## Developer Guide

> ```Coming soon...```

## Roadmap

> ```Coming soon...```

---

*Updated the 16th of November*
