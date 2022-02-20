#pragma once
#include <QObject>
#include <QStringList>
#include <QDir>

class FileUpdater : public QObject
{
	Q_OBJECT

public:
	FileUpdater(const QString& build);

	void UpdateExiled(bool checkValidity = true);
	void UpdateGame(bool checkValidity = true);
	void UpdateProjects(bool checkValidity = true);

	void cleanProjects();
	void addProject(const QString& proj);
	void setProjects(const QStringList& projs);

	void setGamePath(const QString& path);
	void setExiledPath(const QString& path);

	QStringList getProjects() const;
	QString getGame() const;
	QString getExiled() const;

private:
	QStringList projectsPath;
	QString gamePath, exiledPath;

	QString buildPath;
	const QList<QPair<QString, QString>> exiledDependencies =
	{
		{ "", "Exiled.Loader.dll" },
		{ "Plugins/", "Exiled.Events.dll" },
		{ "Plugins/", "Exiled.Permissions.dll" },
		{ "Plugins/", "Exiled.Updater.dll" },
		{ "Plugins/", "Exiled.CustomRoles.dll" },
		{ "Plugins/", "Exiled.CreditTags.dll" },
		{ "Plugins/", "Exiled.CustomItems.dll" },
		{ "Plugins/dependencies/", "0Harmony.dll" },
		{ "Plugins/dependencies/", "Exiled.API.dll" },
		{ "Plugins/dependencies/", "YamlDotNet.dll" }
	};
};
