#include "ArchiveExtractor.h"

#include <Logger.h>

ArchiveExtractor::ArchiveExtractor()
{
    //
}

void ArchiveExtractor::Open(const QString& archiveFullPath, bool removeCopy)
{
    QFile f(archiveFullPath);
    if (!f.exists())
        Logger::get()->Failed("'" + archiveFullPath + "' file couldn't be found !");

    QFile::copy(archiveFullPath, QDir::currentPath() + "/build/Exiled.tar.gz");
    Logger::get()->Info("A copy of the archive has been made in 'build'.");

    QProcess* p = new QProcess();
    p->setWorkingDirectory(QDir::currentPath());
    p->start("cmd.exe", { "/C", "Extractor.bat" });

    if (p->waitForFinished(5000))
        Logger::get()->Success("Archive was successfully extracted in 'build'.");
    else Logger::get()->Failed("Extraction failed...");

    if (removeCopy)
    {
        QFile r(QDir::currentPath() + "/build/Exiled.tar.gz");
        r.remove();
        Logger::get()->Info("The copied archive has been removed...");
    }
}
