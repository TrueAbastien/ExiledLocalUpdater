#include "FileUpdater.h"

#include <Logger.h>

FileUpdater::FileUpdater(const QString& build)
	: buildPath(build)
{
}

void FileUpdater::UpdateExiled(bool checkValidity)
{
	if (checkValidity && !QDir(exiledPath).exists())
	{
		Logger::get()->Warn("Exiled Files weren't updated, '" + exiledPath + "' path is not valid.");
		return;
	}

	QDir target(exiledPath + "/Plugins");
	if (target.exists())
	{
		target.removeRecursively();
		Logger::get()->Print("'" + exiledPath + "/Plugins' was deleted.");
	}
	QDir(exiledPath).mkdir("Plugins");

	QStringList dirToCopy = { "" };
	for (int ii = 0; ii < dirToCopy.size(); ++ii)
	{
		QDir current(buildPath + "/EXILED/Plugins" + dirToCopy[ii]);

		foreach (QString d, current.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
		{
			dirToCopy.append("/" + d);
			current.mkpath(exiledPath + "/Plugins/" + d);
		}

		foreach(QString f, current.entryList(QDir::Files))
		{
			QFile::copy(current.path() + "/" + f, exiledPath + "/Plugins" + dirToCopy[ii] + "/" + f);
		}
	}

	QFile loader(exiledPath + "/Exiled.Loader.dll");
	if (loader.exists()) loader.remove();
	QFile::copy(buildPath + "/EXILED/Exiled.Loader.dll", exiledPath + "/Exiled.Loader.dll");

	Logger::get()->Info("Exiled Files were successfully updated !");
}

void FileUpdater::UpdateGame(bool checkValidity)
{
	if (checkValidity && !QDir(gamePath).exists())
	{
		Logger::get()->Warn("Game Files weren't updated, '" + gamePath + "' path is not valid.");
		return;
	}

	QFile assembly(gamePath + "/Assembly-CSharp.dll");
	if (assembly.exists())
		assembly.remove();
	QFile publicized(gamePath + "/Assembly-CSharp_publicized.dll");
	if (publicized.exists())
		publicized.remove();

	QFile::copy(buildPath + "/Assembly-CSharp.dll", gamePath + "/Assembly-CSharp.dll");
	QFile::copy(buildPath + "/Assembly-CSharp_publicized.dll", gamePath + "/Assembly-CSharp_publicized.dll");

	Logger::get()->Info("Game Files were successfully updated !");
}

void FileUpdater::UpdateProjects(bool checkValidity)
{
	foreach(QString p, projectsPath)
	{
		QDir project(p);
		if (checkValidity && !project.exists())
		{
			Logger::get()->Warn("Project Dependencies weren't updated, '" + p + "' path is not valid.");
			continue;
		}

		// Game
		QFile ap(p + "/Assembly-CSharp_publicized.dll");
		if (ap.exists()) ap.remove();
		QFile::copy(buildPath + "/Assembly-CSharp_publicized.dll", p + "/Assembly-CSharp_publicized.dll");
		QFile af(p + "/Assembly-CSharp-firstpass.dll");
		if (af.exists()) af.remove();
		QFile::copy(gamePath + "/Assembly-CSharp-firstpass.dll", p + "/Assembly-CSharp-firstpass.dll");

		// Exiled
		foreach(auto fi, exiledDependencies)
		{
			QFile file(p + "/" + fi.second);
			if (file.exists())
				file.remove();
			QFile::copy(buildPath + "/EXILED/" + fi.first + fi.second, p + "/" + fi.second);
		}
	}
}

void FileUpdater::cleanProjects()
{
	projectsPath.clear();
	Logger::get()->Print("Project list has been cleared.");
}

void FileUpdater::addProject(const QString& proj)
{
	if (!projectsPath.contains(proj))
	{
		if (QDir(proj).exists())
		{
			projectsPath.append(proj);
			Logger::get()->Print("'" + proj + "' project was successfully added.");
		}
		else Logger::get()->Warn("'" + proj + "' project couldn't be added, its references cannot be found...");
	}
	else Logger::get()->Warn("'" + proj + "' project couldn't be added, it is already listed...");

}

void FileUpdater::setProjects(const QStringList& projs)
{
	projectsPath.clear();
	foreach(QString proj, projs)
		addProject(proj);
}

void FileUpdater::setGamePath(const QString& path)
{
	gamePath = path;
	Logger::get()->Print("'" + path + "' is the new Game Files path");
}

void FileUpdater::setExiledPath(const QString& path)
{
	exiledPath = path;
	Logger::get()->Print("'" + path + "' is the new Exiled Root path");
}

QStringList FileUpdater::getProjects() const
{
	return projectsPath;
}

QString FileUpdater::getGame() const
{
	return gamePath;
}

QString FileUpdater::getExiled() const
{
	return exiledPath;
}
