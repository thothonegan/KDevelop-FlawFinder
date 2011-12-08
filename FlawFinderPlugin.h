//
/// \file KDevelop-FlawFinder/FlawFinderPlugin.h
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

#ifndef KDEVELOPFLAWFINDER_FLAWFINDERPLUGIN_H
#define KDEVELOPFLAWFINDER_FLAWFINDERPLUGIN_H

#include <interfaces/iplugin.h>

#include <QVariant>

class FlawFinderPlugin : public KDevelop::IPlugin
{
	Q_OBJECT
	public:
		//
		/// \brief Create the plugin
		//
		FlawFinderPlugin (QObject* parent, const QVariantList& args = QVariantList());
	
		//
		/// \brief Destroy the plugin
		//
		virtual ~FlawFinderPlugin (void);
		
		//
		/// \brief Unload the plugin
		//
		virtual void unload (void);
		
	private slots:
		//
		/// \brief Initilize the plugin
		//
		void init (void);
		
	private:
		//
		/// \brief The factory used to create stuff
		//
		class FlawFinderViewFactory* m_factory;
		
};

#endif // KDEVELOPFLAWFINDER_FLAWFINDERPLUGIN_H
