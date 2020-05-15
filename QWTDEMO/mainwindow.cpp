#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#include <qwt_legend.h>

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include <qwt_plot_magnifier.h>

#include <qwt_plot_panner.h>

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QwtPlot *d_plot = new QwtPlot( this );
    setCentralWidget(d_plot); // привязать поле к границам окна

    d_plot->setTitle( "Graphic X and Y" ); // заголовок
        d_plot->setCanvasBackground( Qt::black ); // цвет фона

        // Параметры осей координат
        d_plot->setAxisTitle(QwtPlot::yLeft, "Y");
        d_plot->setAxisTitle(QwtPlot::xBottom, "X");
        d_plot->insertLegend( new QwtLegend() );


        // Включить сетку
        // #include <qwt_plot_grid.h>
        QwtPlotGrid *grid = new QwtPlotGrid(); //
        grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
        grid->attach( d_plot ); // добавить сетку к полю графика

        // Кривая
           //#include <qwt_plot_curve.h>
           QwtPlotCurve *curve = new QwtPlotCurve();
           curve->setTitle( "Graphic 1" );
           curve->setPen( Qt::red, 3 ); // цвет и толщина кривой
           curve->setRenderHint
                   ( QwtPlotItem::RenderAntialiased, true ); // сглаживание

           // Маркеры кривой
           // #include <qwt_symbol.h>
           QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
               QBrush( Qt::yellow ), QPen( Qt::blue, 1 ), QSize( 8, 8 ) );
           curve->setSymbol( symbol );

           // Добавить точки на ранее созданную кривую
           QPolygonF points;

                  points << QPointF( 0.0, 0.0 ) // координаты x, y
               << QPointF( 1.5, 2.0 ) << QPointF( 3.0, 2.0 )
               << QPointF( 3.5, 3.0 ) << QPointF( 5.0, 3.0 );

            curve->setSamples( points ); // ассоциировать набор точек с кривой

            curve->attach( d_plot ); // отобразить кривую на графике


            // Кривая 2
               //#include <qwt_plot_curve.h>
               QwtPlotCurve *curve2 = new QwtPlotCurve();
               curve2->setTitle( "Graphic 2" );
               curve2->setPen( Qt::white, 3 ); // цвет и толщина кривой
               curve2->setRenderHint
                       ( QwtPlotItem::RenderAntialiased, true ); // сглаживание

               // Маркеры кривой
               // #include <qwt_symbol.h>
               QwtSymbol *symbol2 = new QwtSymbol( QwtSymbol::Ellipse,
                   QBrush( Qt::yellow ), QPen( Qt::blue, 1 ), QSize( 8, 8 ) );
               curve2->setSymbol( symbol2 );

               // Добавить точки на ранее созданную кривую
               QPolygonF points2;

                      points2 << QPointF( 0.0, 0.0 ) // координаты x, y
                   << QPointF( 2.5, 0.0 ) << QPointF( 4.5, 2.0 )
                   << QPointF( 6.5, 3.0 ) << QPointF( 8.0, 7.0 );

                curve2->setSamples( points2 ); // ассоциировать набор точек с кривой

                curve2->attach( d_plot ); // отобразить кривую на графике



            d_plot->setAxisScale(QwtPlot::xBottom, 0, 5);

            // Включить возможность приближения/удаления графика
                 // #include <qwt_plot_magnifier.h>
                 QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(d_plot->canvas());
                 // клавиша, активирующая приближение/удаление
                 magnifier->setMouseButton(Qt::MidButton);


                 // Включить возможность перемещения по графику
                 // #include <qwt_plot_panner.h>
                 QwtPlotPanner *d_panner = new QwtPlotPanner( d_plot->canvas() );
                 // клавиша, активирующая перемещение
                 d_panner->setMouseButton( Qt::RightButton );

                 // Включить отображение координат курсора и двух перпендикулярных
                     // линий в месте его отображения
                     // #include <qwt_plot_picker.h>

                      // настройка функций
                     QwtPlotPicker *d_picker =
                             new QwtPlotPicker(
                                 QwtPlot::xBottom, QwtPlot::yLeft, // ассоциация с осями
                     QwtPlotPicker::CrossRubberBand, // стиль перпендикулярных линий
                     QwtPicker::ActiveOnly, // включение/выключение
                     d_plot->canvas() ); // ассоциация с полем

                     // Цвет перпендикулярных линий
                     d_picker->setRubberBandPen( QColor( Qt::red ) );

                     // цвет координат положения указателя
                     d_picker->setTrackerPen( QColor( Qt::black ) );

                     // непосредственное включение вышеописанных функций
                     d_picker->setStateMachine( new QwtPickerDragPointMachine() );

}

MainWindow::~MainWindow()
{
    delete ui;
}
