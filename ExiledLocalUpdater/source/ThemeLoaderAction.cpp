#include "ThemeLoaderAction.h"

ThemeLoaderAction::ThemeLoaderAction(QMenu* parent, QWidget* app, const QString& name, ThemeCache* cache)
	: QAction(parent), fileName(name), themeCache(cache), wnd(app)
{
	parent->addAction(this);
	setText(name.left(name.lastIndexOf(".")));
	if (text().isEmpty()) setText("---");

	setCheckable(true);
	connect(this, &QAction::triggered, this, &ThemeLoaderAction::LoadTheme);
}

void ThemeLoaderAction::LoadTheme()
{
	themeCache->Set(wnd, fileName);
}