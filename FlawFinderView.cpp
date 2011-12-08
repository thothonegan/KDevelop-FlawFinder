//
/// \file KDevelop-FlawFinder/FlawFinderView.cpp
/// \brief Main view for the plugin
//
// Copyright (C) 2011  Kenneth Perry (thothonegan@gmail.com)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//

#include "FlawFinderView.h"

#include "FlawFinderPlugin.h"

#include <kaction.h>
#include <klocale.h>
#include <kprocess.h>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/iproject.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/iuicontroller.h>

#include <project/projectmodel.h>

FlawFinderView::FlawFinderView (FlawFinderPlugin* plugin, QWidget* parent)
: QWidget (parent), m_plugin (plugin)
{
	m_ui.setupUi (this);
	
	setObjectName ("FlawFinder");
	setWindowIcon(SmallIcon("debugger"));
	setWindowTitle(i18n("FlawFinder"));
	setWhatsThis(i18n("FlawFinder"));
	
	setupActions();
	
	connect (m_ui.listOutput, SIGNAL(currentRowChanged(int)), this, SLOT(slotListItemPressed()));
}

QList<QAction*> FlawFinderView::toolBarActions (void) const
{
	return m_toolbarActions;
}

void FlawFinderView::slotRunFlawFinder (void)
{
	m_ui.listOutput->clear();
	
	QList<KDevelop::IProject*> allProjects = m_plugin->core()->projectController()->projects();

	foreach (KDevelop::IProject* p, allProjects)
	{
		QList<KDevelop::ProjectFileItem*> allFiles = p->files();
		
		QList<QString> paths;
		
		foreach (KDevelop::ProjectFileItem* item, allFiles)
		{
			QString path = item->url().path();
			
			/// \todo Use KURL to tell you if its type is c++ source?
			if (path.endsWith(".cpp"))
			{
				//m_ui.listOutput->addItem (path);
				paths.push_back(path);
			}
		}
		
		QStringList arguments;
		arguments << "--singleline" << "--quiet" << "--dataonly";
		arguments << paths;
		
		// Run the process
		QProcess process;
		process.start("flawfinder", arguments);
		process.waitForFinished();
		
		// Parse output
		
		QByteArray array = process.readLine();
		
		while (!array.isEmpty())
		{
			array = array.replace("\n", "");

			m_ui.listOutput->addItem (array);
		
			array = process.readLine();
		}
	}
	
	m_ui.listOutput->addItem ("Finished");
}

void FlawFinderView::slotListItemPressed (void)
{
	QListWidgetItem* item = m_ui.listOutput->currentItem();
	
	if (!item)
		return;
	
	QString text = item->text();
	
	m_ui.listOutput->addItem (text);
	
	if (text.split(" ").size() == 0)
		return;
	
	QString firstSet = text.split(" ")[0];
	
	if (firstSet.split(":").size() < 2)
		return;
	
	QString path = firstSet.split(":")[0];
	QString row = firstSet.split(":")[1];
	
	if (path != "" && row != "")
	{
		KTextEditor::Cursor cursor (row.toInt() - 1, 0); // its 0 based, line counts are 1 based
		
		KUrl url (path);
		KDevelop::ICore::self()->documentController()->openDocument(url, KTextEditor::Range (cursor, 0));
	}
}

// --- private ---

void FlawFinderView::setupActions (void)
{
	KAction* action = new KAction (this);
	action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	action->setText (i18n("Run FlawFinder"));
	action->setIcon(KIcon("dirsync"));
	
	connect (action, SIGNAL(triggered(bool)), this, SLOT(slotRunFlawFinder()));
	
	m_toolbarActions.push_back(action);
}
