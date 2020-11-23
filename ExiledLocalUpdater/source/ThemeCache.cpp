#include "ThemeCache.h"

ThemeCache::ThemeCache(QString dir)
{
	if (!dir.isEmpty())
		LoadAt(dir);
}

void ThemeCache::LoadAt(QString dir)
{
	this->clear();
	stylesheetDirectory = QDir(dir);
	allStyleSheets = stylesheetDirectory.entryList(QStringList() << "*.qss" << "*.QSS", QDir::Files);

	foreach(QString file, allStyleSheets)
	{
		QFile temporaryFile(dir + "/" + file);
		temporaryFile.open(QFile::ReadOnly);
		this->insert(file, new QString(QLatin1String(temporaryFile.readAll())));
	}
}

QStringList ThemeCache::AllStyleSheets() const
{
	return allStyleSheets;
}

void ThemeCache::Set(QWidget* wdg, QString styleName)
{
	if (this->contains(styleName))
	{
		wdg->setStyleSheet(*this->object(styleName));
		current = styleName;
	}
	else if (styleName.isEmpty())
	{
		wdg->setStyleSheet("");
		current = "";
	}
}

QString ThemeCache::Get() const
{
	return current;
}
