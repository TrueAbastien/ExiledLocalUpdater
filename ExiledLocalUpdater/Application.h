#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QDesktopServices>

#include "Logger.h"
#include "SettingFile.h"
#include "ThemeCache.h"
#include "BuildManager.h"
#include "LogSaver.h"


class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = Q_NULLPTR);
    void Cleanup();

private:
    Ui::ApplicationClass ui;

    SettingFile generalSettings, pathSettings;
    ThemeCache styleSheetCache;
    BuildManager* buildManager;
    LogSaver logs;

    QActionGroup* themeList;

private slots:
    void FindGameFiles();
    void FindExiledRoot();
    void FindProjectFolder();
    void FindArchive();

    void ClearAll();
    void SaveLogs();
    void PrintDisplay();
    void DisplayInfo();
};
