#include "BuildManager.h"

#include <Logger.h>

BuildManager::BuildManager(Ui::ApplicationClass* ui, const QString& currPath)
	: wnd(ui), currentPath(currPath), buildPath(currPath + "/build"), buildInfos("build"), updater(currPath + "/build")
{
	buildInfos.addRules({ "current_tag" });
	buildInfos.readFile();
	ui->tagEdit->setText(buildInfos.get("current_tag")[0]);

	connect(ui->updateButton, &QPushButton::clicked, [this]() { GenerateNewBuild("0", wnd->archivePathField->text()); });
	connect(ui->buildButton, &QPushButton::clicked, [this]() { GenerateNewBuild(wnd->tagEdit->text(), wnd->archivePathField->text()); });
}

bool BuildManager::isRequired(const QString& newestTag)
{
	QStringList
		current = getBuildTag().split("."),
		newest = newestTag.split(".");
	int ii = 0;
	for (; ii < current.size() && ii < newest.size(); ++ii)
	{
		if (current[ii].toInt() > newest[ii].toInt())
			return false;
		else if (current[ii].toInt() < newest[ii].toInt())
			return true;
	}
	if (newest.size() > current.size())
		for (; ii < newest.size(); ++ii)
			if (newest[ii].toInt() > 0)
				return true;
	return false;
}

bool BuildManager::isBuildValid()
{
	QDir buildDir(buildPath);
	QDirIterator it(buildDir, QDirIterator::Subdirectories);
	QStringList dirs = { "EXILED" }, files = { "Assembly-CSharp.dll","Assembly-CSharp_publicized.dll" };

	while (it.hasNext())
	{
		QString fileName = it.next();
		QFileInfo file(fileName);

		if (file.isDir())
		{
			if (!dirs.removeOne(fileName))
				return false;
		}
		else
		{
			if (!files.removeOne(fileName))
				return false;
		}
	}

	return dirs.size() == 0 && files.size() == 0;
}

QString BuildManager::getBuildTag() const
{
	return buildInfos.get("current_tag")[0];
}

void BuildManager::GenerateNewBuild(const QString& tag, const QString& archiveFullPath)
{
	if (!QFile::exists(archiveFullPath))
	{
		Logger::get()->Failed("'" + archiveFullPath + "' cannot be found...");
		return;
	}
	else if (isBuildValid() && !isRequired(tag))
	{
		Logger::get()->Info("An up-to-date build already exists, the build won't be updated.");
	}
	else
	{
		if (!QDir(wnd->gamePathField->text()).exists())
		{
			Logger::get()->Failed("'" + wnd->gamePathField->text() + "' directory doesn't exist !");
			return;
		}
		if (!QDir(wnd->exiledPathField->text()).exists())
		{
			Logger::get()->Failed("'" + wnd->exiledPathField->text() + "' directory doesn't exist !");
			return;
		}

		CleanBuild();
		publicizer.Bring(publicizer.Publicize(wnd->gamePathField->text(), "Assembly-CSharp.dll", currentPath),
			"Assembly-CSharp_publicized.dll", buildPath);
		extractor.Open(archiveFullPath);

		buildInfos.set("current_tag", tag);
		buildInfos.writeFile();
	}
	
	updater.setExiledPath(wnd->exiledPathField->text());
	updater.setGamePath(wnd->gamePathField->text());
	updater.cleanProjects();
	for (int ii = 0; ii < wnd->projectList->count(); ++ii)
		updater.addProject(wnd->projectList->item(ii)->text());

	updater.UpdateExiled(false);
	updater.UpdateGame(false);
	updater.UpdateProjects();

	Logger::get()->Success("Operation successful, all has been updated !");
}

bool BuildManager::CleanBuild()
{
	QDir dir(buildPath);
	if (dir.entryList().size() <= 0)
		return false;
	foreach(QString file, dir.entryList())
		dir.remove(file);
	return true;
}
