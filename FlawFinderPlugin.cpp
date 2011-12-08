//
/// \file KDevelop-FlawFinder/FlawFinderPlugin.cpp
/// \brief Plugin for using FlawFinder in KDevelop
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

#include "FlawFinderPlugin.h"

#include <kaboutdata.h>
#include <kpluginfactory.h>
#include <kpluginloader.h>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>

#include "FlawFinderView.h"

K_PLUGIN_FACTORY (FlawFinderFactory, registerPlugin<FlawFinderPlugin>(); )
K_EXPORT_PLUGIN (FlawFinderFactory (KAboutData ("FlawFinder", "FlawFinder",
	ki18n("FlawFinder Plugin"), "1.0", ki18n("Use FlawFinder in KDevelop"),
	KAboutData::License_GPL)))


class FlawFinderViewFactory : public KDevelop::IToolViewFactory
{
	public:
		FlawFinderViewFactory (FlawFinderPlugin* plugin)
		: m_plugin (plugin)
		{}
		
		virtual QWidget* create (QWidget* parent = NULL)
		{
			return new FlawFinderView (m_plugin, parent);
		}
		
		QList<QAction*> toolBarActions (QWidget* w) const
		{
			FlawFinderView* view = qobject_cast<FlawFinderView*>(w);
			if (view)
				return view->toolBarActions();
			
			return KDevelop::IToolViewFactory::toolBarActions(w);
		}
		
		virtual Qt::DockWidgetArea defaultPosition (void)
		{ return Qt::BottomDockWidgetArea; }
		
		virtual QString id() const
		{ return "com.hackerguild.KDevelop.FlawFinder"; }
		
	private:
		FlawFinderPlugin* m_plugin;
};

FlawFinderPlugin::FlawFinderPlugin (QObject* parent, const QVariantList& args)
: IPlugin (FlawFinderFactory::componentData(), parent)
{
	init();
}

FlawFinderPlugin::~FlawFinderPlugin (void)
{

}

void FlawFinderPlugin::unload (void)
{
	core()->uiController()->removeToolView(m_factory);
}

// --- private slots ---

void FlawFinderPlugin::init (void)
{
	m_factory = new FlawFinderViewFactory (this);
	core()->uiController()->addToolView("FlawFinder", m_factory);
}
