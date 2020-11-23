#include "Application.h"
#include "ThemeLoaderAction.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent),
    generalSettings("general"), pathSettings("path"),
    styleSheetCache("themes")
{
    ui.setupUi(this);
    buildManager = new BuildManager(&ui, QDir::currentPath());
	setWindowTitle("EXILED Local Updater - for Windows 10 (x64)");

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
	themeList = new QActionGroup(ui.menuTheme);
	themeList->addAction(new ThemeLoaderAction(ui.menuTheme, this, "", &styleSheetCache));
	foreach (QString theme, styleSheetCache.AllStyleSheets())
		themeList->addAction(new ThemeLoaderAction(ui.menuTheme, this, theme, &styleSheetCache));

	// Menu Bar //
	connect(ui.actionSave, &QAction::triggered, this, &Application::SaveLogs);
	connect(ui.actionClear, &QAction::triggered, this, &Application::ClearAll);
	connect(ui.actionDisplay, &QAction::triggered, this, &Application::PrintDisplay);
	connect(ui.actionInformations, &QAction::triggered, this, &Application::DisplayInfo);
	// -- Links
	connect(ui.actionApplication, &QAction::triggered, [this]() { QDesktopServices::openUrl(QUrl("https://github.com/TrueAbastien/ExiledLocalUpdater")); });
	connect(ui.actionEXILED, &QAction::triggered, [this]() { QDesktopServices::openUrl(QUrl(generalSettings.get("repository_url")[0])); });
	connect(ui.actionThemes, &QAction::triggered, [this]() { QDesktopServices::openUrl(QUrl("https://qss-stock.devsecstudio.com/templates.php")); });
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

void Application::Cleanup()
{
	logs.WriteText(ui.logView->toPlainText());

	generalSettings.set("theme_name", styleSheetCache.Get());
	generalSettings.writeFile();
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

void Application::ClearAll()
{
	ui.gamePathField->setText("");
	ui.exiledPathField->setText("");
	ui.projectList->clear();
	ui.archivePathField->setText("");
}

void Application::SaveLogs()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Create Logs"), QDir::currentPath(), tr("Text files (*.txt)"));
	if (!path.isEmpty())
	{
		LogSaver log(path);
		log.WriteText(ui.logView->toPlainText());
	}
	else Logger::get()->Warn("No file was selected, logs weren't saved as desired...");
}

void Application::PrintDisplay()
{
	Logger::get()->Info("Current theme is: " + styleSheetCache.Get() + ".");
}

void Application::DisplayInfo()
{
	QMessageBox::about(this, "Informations", "This project was made by Abastien,"
		" as a small Qt application to ease the process of locally updating your EXILED files & dependencies.");
}
