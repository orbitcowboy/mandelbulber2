/*
 * mylineedit.hpp
 *
 *  Created on: May 10, 2014
 *      Author: krzysztof
 */

#ifndef MYSPINBOX_HPP_
#define MYSPINBOX_HPP_

#include <QtGui>
#include <QtCore>
#include <QSpinBox>
#include <QMenu>
#include "../src/parameters.hpp"

class MySpinBox : public QSpinBox
{
	Q_OBJECT

public:
	MySpinBox(QWidget *parent = 0)  : QSpinBox(parent)
	{
		actionResetToDefault = NULL;
		parameterContainer = NULL;
		gotDefault = false;
		defaultValue = 0;
	};

	void AssignParameterContainer(cParameterContainer *container) {parameterContainer = container;}
	void AssingParameterName(QString name) {parameterName = name;}

private:
	QAction *actionResetToDefault;
	QString GetType(const QString &name);
	cParameterContainer *parameterContainer;
	QString parameterName;

	int GetDefault();
	int defaultValue;
	bool gotDefault;

protected:
	void contextMenuEvent(QContextMenuEvent *event);
	void paintEvent(QPaintEvent *event);
};



#endif /* MYSPINBOX_HPP_ */