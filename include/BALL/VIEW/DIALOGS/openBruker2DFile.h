// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: openBruker2DFile.h,v 1.9.2.1 2006/02/01 13:23:39 amoll Exp $

#ifndef BALL_VIEW_DIALOGS_OPENBRUKER2DFILE_H
#define BALL_VIEW_DIALOGS_OPENBRUKER2DFILE_H

#ifndef BALL_COMMON_H
# include <BALL/common.h>
#endif

#ifndef BALL_VIEW_WIDGETS_REGULARDATA2DWIDGET_H
# include <BALL/VIEW/WIDGETS/regularData2DWidget.h>
#endif

#ifndef BALL_FORMAT_BRUKER2DFILE_H
# include <BALL/FORMAT/bruker2DFile.h>
#endif

#include <QtGui/qwidget.h>

namespace BALL
{
	namespace VIEW
	{
		/** Interface to select and open spectra stored in the bruker file format.
    		\ingroup  ViewDialogs
		*/
		class BALL_VIEW_EXPORT OpenBruker2DFile
			: public QWidget,
				public ModularWidget
		{
			Q_OBJECT
			BALL_EMBEDDABLE(OpenBruker2DFile, ModularWidget)
			public:

			/** Constructors and Destructors
			*/
			//@{
			/// Constructor.
			OpenBruker2DFile(QWidget *parent = 0, const char *name = 0);

			/// Destructor
			virtual ~OpenBruker2DFile()
				throw();
			//@}

			/** Assignment
			*/

			/** Initialization. This method is called automatically before the main application is started. 
					It adds the	dialog's menu entries and connections.
			*/
			virtual void initializeWidget(MainControl& main_control)
				throw();

			public slots:

			/** Open the bruker2DFile.
			 */
			virtual void openFile()
				throw();

		};
	}
}

#endif