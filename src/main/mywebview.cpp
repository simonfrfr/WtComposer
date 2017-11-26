// Copyright (c) 2018 TSASPC
//
// This file is part of WtComposer
//
// WtComposer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// WtComposer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WtComposer.  If not, see <http://www.gnu.org/licenses/>.

#include "mainwindow.h"

const QString g_strHighlightClassName = "wtc_highlight";

MyWebView::MyWebView(QWidget *parent) : QWebEngineView(parent)
{
    QApplication::instance()->installEventFilter(this);
    setMouseTracking(true);
	m_strCurrentElemId = "";
	installEventFilter(this);
    setAcceptDrops(true);
    QObject::connect( this, SIGNAL(loadStarted())     , this, SLOT(on_loadStarted()));
    QObject::connect( this, SIGNAL(loadFinished(bool)), this, SLOT(on_loadFinished(bool)) );
	// set qt style to webview
	setStyleSheet("background-color: lightgray;");
	// set css style for highlighting element
	QString     strStyle = "border-style  : solid    !important; "
						   "border-width  : 2px      !important; "
						   "border-color  : #f0f090  !important; ";
    SetHighlightStyleClass(g_strHighlightClassName, strStyle);
    openChannel();
}
void MyWebView::onHover(int x, int y){
    std::cout <<"("<< x << ", " << y << ")" << std::endl;
}
QString MyWebView::readFile (const QString& filename)
{
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        return stream.readAll();
    }
    else {
        qDebug()<<"Couldn't load "<< filename <<" API!";
    }
    return "";
}
//Insteaad of Event Filter, Let JS handle this stuff
bool MyWebView::eventFilter(QObject *watched, QEvent *event)
{
	if (!m_boolEnableEvtProcess) { return false; }

    if (watched->parent() == this && event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QWebEngineView *view          = dynamic_cast<QWebEngineView*>(watched);
		QPoint pos              = view->mapFromGlobal(mouseEvent->globalPos());
        // Will incorperate QWebChannel

        /*
        auto *frame        = view->page()->frameAt(mouseEvent->pos());
		if (frame!=NULL)
		{
			QWebHitTestResult hitTestResult = frame->hitTestContent(pos);
			// if the hovered elem is not the same as the previously hovered
			if (hitTestResult.element() != m_old_hover_element)
			{
				QWebElement elemCurrent = hitTestResult.element();
				// if dragging, overwrite with closer WContainer
				if (m_boolIsDraggingWidget)
				{
					elemCurrent = FindCloserContainer(elemCurrent);
				}
				if (!elemCurrent.isNull())
				{
					// Change color
					ChangeHoveredElemColor(elemCurrent);
					// Message to print
					m_strCurrentElemId = elemCurrent.attribute("id");
					// Emit message
					QStringList strlistClasses = elemCurrent.classes();
					strlistClasses.removeAll(g_strHighlightClassName);
					Q_EMIT mouseMovedOverElem(m_strCurrentElemId, strlistClasses.join(' '));
				}
            }
        }*/
	}
	else if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
         //std::cout << "QEvent::MouseButtonPress" << std::endl;
    /*	if (mouseEvent->button() == Qt::LeftButton)
		{
            QWebEngineView *view = dynamic_cast<QWebView*>(watched);
			QPoint pos = view->mapFromGlobal(mouseEvent->globalPos());
			QWebFrame *frame = view->page()->frameAt(mouseEvent->pos());
			if (frame != NULL)
			{
				QWebHitTestResult hitTestResult = frame->hitTestContent(pos);
                QWebElement welemTemp = hitTestResult.element();
                QWebElement elemCurrent = FindCloserWidget(welemTemp);
				// if the clicked elem is not the same as the previously clicked
				if (elemCurrent != m_old_click_element)
				{
					// Change color
					ChangeClickedElemColor(elemCurrent);
					// Message to print
					m_strCurrentElemId = elemCurrent.attribute("id");
					// Emit message
					Q_EMIT mouseLeftClickedOverElem(m_strCurrentElemId);
				}
			}
        }*/
	}
	return false;
}

//Not Needed Anymore... Let JS Handle this...
QString MyWebView::oldClickElement(){
    return m_old_click_element;
}
/*QString MyWebView::GetCloserContainerId()
{
    Element elemCurrent = FindCloserContainer(m_old_click_element,"spitback");

    return "id";
}
*/
void MyWebView::ChangeHoveredElemColor(Element hitTestResult)
{
	if (!m_boolEnableEvtProcess) { return; }
	// approach of creating class in user css for qwebview, and then toggle the class
    if (m_old_hover_element != "" && m_old_hover_element != "null")
        // Restore old element
        this->page()->runJavaScript("document.getElementById(\""+m_old_hover_element+"\").removeClass(\""+g_strHighlightClassName+"\");");

	// Store new as old
	m_old_hover_element = hitTestResult;
	// Highlight
    this->page()->runJavaScript("document.getElementById(\""+m_old_hover_element+"\").addClass(\""+g_strHighlightClassName+"\");");

}

void MyWebView::ChangeClickedElemColor(Element hitTestResult)
{
	if (!m_boolEnableEvtProcess) { return; }

	// Restore old element
    if (m_old_click_element != "") {
        this->page()->runJavaScript("document.getElementById(\""+m_old_click_element+"\").style.border"+" = \""+m_old_click_border+"\";");
    }
    // Store new as old
	m_old_click_element = hitTestResult;
	// Store old properties to be able to restore later
    this->page()->runJavaScript("document.getElementById(\""+m_old_click_element+"\").style.border;", [&](const QVariant &result){
        m_old_click_border = result.toString();
        this->page()->runJavaScript("document.getElementById(\""+m_old_click_element+"\").style.border = \"3px solid #FF0000\";");
    });
}

void MyWebView::on_HighlightTreeSelectedElem(QString name)
{
	if (!m_boolEnableEvtProcess) { return; }
   // QWebElement welemTemp = page()->mainFrame()->documentElement();
   // QWebElement webelem = getElementById(welemTemp, name);
    //"document.getElementById(\""+name+"\");"
/*	if (webelem.isNull())
	{
		qDebug() << "[ERROR] Invalid QWebElement in MyWebView::on_HighlightTreeSelectedElem.";
		return;
    }*/
    ChangeClickedElemColor(name);
}


void MyWebView::dragEnterEvent(QDragEnterEvent *event)
{
	if (!m_boolEnableEvtProcess) { return; }

	m_boolIsDraggingWidget = true;

	MyWidgetView *source = qobject_cast<MyWidgetView *>(event->source());

	if (source)
	{
		event->setDropAction(Qt::CopyAction);
		event->accept();
	}

}

void MyWebView::dragMoveEvent(QDragMoveEvent *event)
{
	if (!m_boolEnableEvtProcess) { return; }

	MyWidgetView *source = qobject_cast<MyWidgetView *>(event->source());

	if (source)
	{
		event->setDropAction(Qt::CopyAction);
		event->accept();
	}

	QMouseEvent mouseEvt(QEvent::MouseMove, QPointF(event->pos()), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
	eventFilter(this, &mouseEvt);
}

void MyWebView::dropEvent(QDropEvent *event)
{
	if (!m_boolEnableEvtProcess) { return; }

	m_boolIsDraggingWidget = false;

	MyWidgetView *source = qobject_cast<MyWidgetView *>(event->source());

	if (source)
	{
		// TODO : Code here or in other event to reject drag if hovered item does not inherit from WContainerWidget
		Q_EMIT receivedDragOnWebview(event->mimeData()->data(g_strWtwMime), m_strCurrentElemId);
		event->setDropAction(Qt::CopyAction);
		event->accept();
    }
}

void MyWebView::leaveEvent(QEvent * event)
{
	if (!m_boolEnableEvtProcess) { return; }

	// Restore old element
    if (m_old_hover_element!="")
        this->page()->runJavaScript("document.getElementById(\""+m_old_hover_element+"\").removeClass(\""+g_strHighlightClassName+"\");");

    //m_old_hover_element.removeClass(g_strHighlightClassName);
}

void MyWebView::on_loadStarted()
{
	m_boolEnableEvtProcess = false;
    this->page()->runJavaScript("document.getElementById(\""+m_old_hover_element+"\").removeClass(\""+g_strHighlightClassName+"\");", [&](const QVariant &result){

            //m_old_hover_element.removeClass(g_strHighlightClassName);

            m_strCurrentElemId = "";

            this->page()->runJavaScript("document.getElementById(\""+m_old_click_element+"\").style.border"+" = \""+m_old_click_border+"\";");


            m_old_click_element = "";
    });

}

void MyWebView::on_loadFinished(bool ok)
{
	m_boolEnableEvtProcess = true;
	QObject    *p_parent  = parent();
	MainWindow *p_mwindow = qobject_cast<MainWindow*>(p_parent);
	while (p_mwindow == NULL)
	{
		p_parent  = p_parent->parent();
		p_mwindow = qobject_cast<MainWindow*>(p_parent);
		if (p_mwindow)
		{
			m_pMainWindow = p_mwindow;
			Q_EMIT m_pMainWindow->RequestAllProperties("");
		}
    }
    openChannel();
}

void MyWebView::openChannel(){
        this->page()->setWebChannel(&m_web_channel);
        m_web_channel.registerObject(QStringLiteral("mywebview"), this);//Ok Now we want to
        this->page()->runJavaScript(readFile(":/qtwebchannel/qwebchannel.js"));
        this->page()->runJavaScript(readFile(":runner.js"));
        this->page()->runJavaScript("initialise();");
        std::cout << "Channel Opened!" << std::endl;

}

void MyWebView::SetHighlightStyleClass(QString strClassName, QString &strTmpStyle)
{
	QByteArray  strComposedStyle("." + strClassName.toUtf8() + " { " + strTmpStyle.toUtf8()  + " }");

    this->page()->runJavaScript("fetchStyle(\""+QUrl("data:text/css;charset=utf-8;base64," + strComposedStyle.toBase64()).toString()+"\")");
}

bool MyWebView::bIsContainer(Element elem)
{
    WDomElem * welem = m_pMainWindow->m_treemodel.getElemByName(elem);
    // check if valid parent
	if (welem)
	{
		QDomElement delem = welem->getElem();
		if (delem.attribute(g_strClassAttr).compare("WContainerWidget") == 0 ||
			delem.attribute(g_strClassAttr).compare("WAnchor"         ) == 0 ||
			delem.attribute(g_strClassAttr).compare("WGroupBox"       ) == 0 ||
			delem.attribute(g_strClassAttr).compare("WPanel"          ) == 0 ||
			delem.attribute(g_strClassAttr).compare("WMenuItem"       ) == 0 ||
			delem.attribute(g_strClassAttr).compare("WStackedWidget"  ) == 0 ||
			delem.attribute(g_strClassAttr).compare("WTabItem"        ) == 0)
		{
            return true;
		}
	}
    return false;
}

void MyWebView::FindCloserWidget(Element elem,QString returnFunctor)
{
    WDomElem * welem = m_pMainWindow->m_treemodel.getElemByName(elem);
	// check if valid parent
    if (welem)
    {
        //tell js
        this->page()->runJavaScript(returnFunctor+"(\""+elem+"\")");
	}
	else
	{
        this->page()->runJavaScript("document.getElementById(\""+elem+"\").parentNode.id;", [&](const QVariant &result){
            //QWebElement welemTemp = elem.parent();
            FindCloserWidget(result.toString(),returnFunctor);
        });
    }
}


