/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * main function - 'main' function for application
 *
 * Copyright (C) 2014 Krzysztof Marczak
 *
 * This file is part of Mandelbulber.
 *
 * Mandelbulber is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Mandelbulber is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 */

#include "main.hpp"
#include "system.hpp"
#include "fractparams.hpp"
#include "interface.hpp"
#include "initparameters.hpp"
#include "fractal_list.hpp"
#include "undo.h"
#include "global_data.hpp"
#include "settings.hpp"
#include <qapplication.h>

//TODO add autosave of settings

int main(int argc, char *argv[])
{
	//Initialization of system functions
	InitSystem();

	//configure debug output
	qInstallMessageHandler(myMessageOutput);

	//class for interface windows
	gMainInterface = new cInterface;

	WriteLog("Prepare QApplication");
	gApplication = new QApplication(argc, argv);
	gApplication->setOrganizationName("Mandelbulber");
	gApplication->setApplicationName("Mandelbulber");

	// Set language from locale
	WriteLog("Prepare translator");
	QTranslator main_translator;
	QTranslator qt_data_translator;
	QString locale = QLocale::system().name();
	WriteLogString("locale", locale);
	main_translator.load(locale, systemData.sharedDir + QDir::separator() + "language");
	qt_data_translator.load("qt_data_" + locale, systemData.sharedDir + QDir::separator() + "language");

	WriteLog("Instaling translator");
	gApplication->installTranslator(&main_translator);
	gApplication->installTranslator(&qt_data_translator);

	//registering types for queued connections
	qRegisterMetaType<cHistogram>("cHistogram");
	qRegisterMetaType<QList<QByteArray> >("QList<QByteArray>");
	qRegisterMetaType<cParameterContainer>("cParameterContainer");
	qRegisterMetaType<cFractalContainer>("cFractalContainer");
	qRegisterMetaType<sTextures>("sTextures");

	//Create default directiories and copy all needed files
	WriteLog("CreateDefaultFolders()");
	if(!CreateDefaultFolders())
	{
		qCritical() << "Files/directories initialization failed" << endl;
		return 73;
	}

	//create internal database with parameters
	gPar = new cParameterContainer;
	gParFractal = new cFractalContainer;
	gPar->SetContainerName("main");
	InitParams(gPar);
	for(int i=0; i<NUMBER_OF_FRACTALS; i++)
	{
		gParFractal->at(i).SetContainerName(QString("fractal") + QString::number(i));
		InitFractalParams(&gParFractal->at(i));
	}
	//Define list of fractal formulas
	DefineFractalList(&fractalList);

	//Netrender
	gNetRender = new CNetRender(systemData.numberOfThreads);

	gMainInterface->ShowUi();

	//loading AppSettings
	if(QFile(systemData.dataDirectory + "mandelbulber.ini").exists())
	{
		cSettings parSettings(cSettings::formatAppSettings);
		parSettings.LoadFromFile(systemData.dataDirectory + "mandelbulber.ini");
		parSettings.Decode(gPar, gParFractal, gAnimFrames);
		gMainInterface->SynchronizeInterface(gPar, gParFractal, cInterface::write);
		gMainInterface->ComboMouseClickUpdate();
	}

	//Alocate container for animation frames
	gAnimFrames = new cAnimationFrames;

	gFlightAnimation = new cFlightAnimation(gMainInterface, gAnimFrames, gMainInterface->mainWindow);

	//write parameters to ui
	gMainInterface->SynchronizeInterface(gPar, gParFractal, cInterface::write);

	//start main Qt loop
	WriteLog("application->exec()");
	int result = gApplication->exec();

	//clean objects when exit
	delete gPar; gPar = NULL;
	delete gParFractal;
	delete gFlightAnimation;
	delete gAnimFrames;
	delete gNetRender;
	delete gMainInterface;
	delete gApplication;
	return result;
}

