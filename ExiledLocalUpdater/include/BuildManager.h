#pragma once
#include <QObject>
#include <QDirIterator>
#include <QFileDialog>

#include "ui_MainWindow.h"
#include "SettingFile.h"

#include "ArchiveExtractor.h"
#include "AssemblyPublicizer.h"
#include "FileUpdater.h"

class BuildManager : public QObject
{
	Q_OBJECT

public:
	BuildManager(Ui::ApplicationClass* ui, const QString& currPath);

	bool isRequired(const QString& newestTag);
	bool isBuildValid();
	QString getBuildTag() const;

	void GenerateNewBuild(const QString& tag, const QString& archiveFullPath);
	bool CleanBuild();

private:
	Ui::ApplicationClass* wnd;
	SettingFile buildInfos;
	QString currentPath, buildPath;

	ArchiveExtractor extractor;
	AssemblyPublicizer publicizer;
	FileUpdater updater;
};