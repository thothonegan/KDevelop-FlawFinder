//
/// \file KDevelop-FlawFinder/FlawFinderView.h
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

#ifndef FLAWFINDERVIEW_H
#define FLAWFINDERVIEW_H

#include <QWidget>

#include "ui_FlawFinderView.h"

class FlawFinderPlugin;

class FlawFinderView : public QWidget
{
	Q_OBJECT
	public:
		//
		/// \brief Create the view
		//
		FlawFinderView (FlawFinderPlugin* plugin, QWidget* parent);
		
		//
		/// \brief List of actions for the toolbar
		//
		QList<QAction*> toolBarActions (void) const;
		
	private slots:
		//
		/// \brief Run flawfinder on all of the current projects
		//
		void slotRunFlawFinder (void);
		
		//
		/// \brief An item on the list was clicked
		//
		void slotListItemPressed (void);
		
	private:
		//
		/// \brief Setup the toolbar actions
		//
		void setupActions (void);
		
		//
		/// \brief Toolbar actions
		//
		QList<QAction*> m_toolbarActions;
		
		//
		/// \brief The UI
		//
		Ui::FlawFinderView m_ui;
		
		//
		/// \brief The plugin we're attached to
		//
		FlawFinderPlugin* m_plugin;
};

#endif // FLAWFINDERVIEW_H
