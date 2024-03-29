#include <qapplication.h>
#include <qmainwindow.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qslider.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include "plot.h"
#include "qwt_color_map.h"

class MainWindow: public QMainWindow
{
public:
    MainWindow( QWidget * = NULL );

private:
    Plot *d_plot;
};

#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent )
{
    QTabWidget* tabWidget = new QTabWidget(this);
    QPushButton* pushButton = new QPushButton(this);
    QObject::connect(pushButton, &QPushButton::pressed, [this]()
    {
       d_plot->d_spectrogram->setData( new SpectrogramData() );
       d_plot->setAxisScale( QwtPlot::yRight, 100000, 900000 );
       d_plot->replot();
    });
    d_plot = new Plot( this );
    tabWidget->addTab(pushButton, "Button");


    QWidget* plotContainer = new QWidget(tabWidget);
    QVBoxLayout* layout = new QVBoxLayout(plotContainer);
    layout->addWidget(d_plot);

    // size policy
    QSizePolicy policy;
    // if I don't use expanding policy, the plots don't take all the space
    // try commenting 'em
    policy.setVerticalPolicy(QSizePolicy::Expanding);
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    d_plot->setSizePolicy(policy);

    tabWidget->addTab(plotContainer, "Plot");

    setCentralWidget( tabWidget );

    QToolBar *toolBar = new QToolBar( this );

#ifndef QT_NO_PRINTER
    QToolButton *btnPrint = new QToolButton( toolBar );
    btnPrint->setText( "Print" );
    btnPrint->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnPrint );
    connect( btnPrint, SIGNAL( clicked() ),
        d_plot, SLOT( printPlot() ) );

    toolBar->addSeparator();
#endif

    toolBar->addWidget( new QLabel("Color Map " ) );
    QComboBox *mapBox = new QComboBox( toolBar );
    mapBox->addItem( "RGB" );
    mapBox->addItem( "Indexed Colors" );
    mapBox->addItem( "Hue" );
    mapBox->addItem( "Alpha" );
    mapBox->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    toolBar->addWidget( mapBox );
    connect( mapBox, SIGNAL( currentIndexChanged( int ) ),
             d_plot, SLOT( setColorMap( int ) ) );

    toolBar->addWidget( new QLabel( " Opacity " ) );
    QSlider *slider = new QSlider( Qt::Horizontal );
    slider->setRange( 0, 255 );
    slider->setValue( 255 );
    connect( slider, SIGNAL( valueChanged( int ) ),
        d_plot, SLOT( setAlpha( int ) ) );

    toolBar->addWidget( slider );
    toolBar->addWidget( new QLabel("   " ) );

    QCheckBox *btnSpectrogram = new QCheckBox( "Spectrogram", toolBar );
    toolBar->addWidget( btnSpectrogram );
    connect( btnSpectrogram, SIGNAL( toggled( bool ) ),
        d_plot, SLOT( showSpectrogram( bool ) ) );

    QCheckBox *btnContour = new QCheckBox( "Contour", toolBar );
    toolBar->addWidget( btnContour );
    connect( btnContour, SIGNAL( toggled( bool ) ),
        d_plot, SLOT( showContour( bool ) ) );

    addToolBar( toolBar );

    btnSpectrogram->setChecked( true );
    btnContour->setChecked( false );

}

int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    a.setStyle( "Windows" );

    MainWindow mainWindow;
    mainWindow.resize( 600, 400 );
    mainWindow.show();

    return a.exec();
}
