#include "Application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent),
    generalSettings("general"), pathSettings("path"),
    styleSheetCache("themes")
{
    ui.setupUi(this);
    buildManager = new BuildManager(&ui, QDir::currentPath());

    // Logger //
    Logger::get(ui.logView);

    // Settings //
    generalSettings.setRules({ "theme_name", "repository_url" });
    generalSettings.readFile();
    pathSettings.setRules({ "latest_archive", "exiled_root", "game_files", "projects_dependencies" });
    pathSettings.readFile();

    // Themes //
    styleSheetCache.Set(this, generalSettings.get("theme_name").first());

    // Build Setup //
    ui.gamePathField->setText(pathSettings.get("game_files")[0]);
    ui.exiledPathField->setText(pathSettings.get("exiled_root")[0]);
    ui.projectList->addItems(pathSettings.get("projects_dependencies", true));
	ui.archivePathField->setText(pathSettings.get("latest_archive")[0]);

    // Connection //
	connect(ui.gamePathBtn, &QPushButton::clicked, this, &Application::FindGameFiles);
	connect(ui.exiledPathBtn, &QPushButton::clicked, this, &Application::FindExiledRoot);
	connect(ui.findArchiveTBtn, &QToolButton::clicked, this, &Application::FindArchive);
	connect(ui.projectAddBtn, &QPushButton::clicked, this, &Application::FindProjectFolder);

	// Tool Bar //
	//
}

void Application::Cleanup()
{
	// Logs //
	/*QFile f(QDir::currentPath() + "/logs.txt");
	f.resize(0);
	QTextStream out(&f);
	out << ui.logView->toPlainText();
	f.close();*/

	//
}

void Application::FindGameFiles()
{
	QString folderName = QFileDialog::getExistingDirectory(ui.gamePathField, tr("Open Folder"), ui.gamePathField->text());
	if (!folderName.isEmpty() && QDir(folderName).exists())
	{
		if (QFile::exists(folderName + "/Assembly-CSharp.dll"))
		{
			ui.gamePathField->setText(folderName);
			Logger::get()->Info("'" + folderName + "' was set as Game folder.");

			pathSettings.set("game_files", folderName);
			pathSettings.writeFile();
		}
		else Logger::get()->Warn("'" + folderName + "' couldn't be set as Game folder...");
	}
}

void Application::FindExiledRoot()
{
	QString folderName = QFileDialog::getExistingDirectory(ui.exiledPathField, tr("Open Folder"), ui.exiledPathField->text());
	if (!folderName.isEmpty() && QDir(folderName).exists())
	{
		if (QDir(folderName + "/Plugins").exists())
		{
			ui.exiledPathField->setText(folderName);
			Logger::get()->Info("'" + folderName + "' was set as Exiled root folder.");

			pathSettings.set("exiled_root", folderName);
			pathSettings.writeFile();
		}
		else Logger::get()->Warn("'" + folderName + "' couldn't be set as Exiled root folder...");
	}
}

void Application::FindProjectFolder()
{
	QString folderName = QFileDialog::getExistingDirectory(ui.projectPathField, tr("Open Folder"), ui.projectPathField->text());
	if (!folderName.isEmpty() && QDir(folderName).exists())
	{
		ui.projectPathField->setText(folderName);
		ui.projectList->addItem(folderName);
		Logger::get()->Info("'" + folderName + "' was added as a Project folder.");

		QStringList original = pathSettings.get("projects_dependencies");
		original.append(folderName);
		pathSettings.set("projects_dependencies", original);
		pathSettings.writeFile();
	}
}

void Application::FindArchive()
{
	QString fileName = QFileDialog::getOpenFileName(ui.archivePathField, tr("Open Archive"), ui.archivePathField->text(), tr("Archives (*.tar.gz)"));
	if (!fileName.isEmpty() && QFile::exists(fileName))
	{
		ui.archivePathField->setText(fileName);
		Logger::get()->Info("'" + fileName + "' is the new Exiled archive.");

		pathSettings.set("latest_archive", fileName);
		pathSettings.writeFile();
	}
}
