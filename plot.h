#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>

class SpectrogramData: public QwtRasterData
{
public:
    SpectrogramData()
    {
        setInterval( Qt::XAxis, QwtInterval( -1.5, 1.5 ) );
        setInterval( Qt::YAxis, QwtInterval( -1.5, 1.5 ) );
        setInterval( Qt::ZAxis, QwtInterval( 0.0, 10.0 ) );
    }

    virtual double value( double x, double y ) const
    {
        const double c = 0.842;
        //const double c = 0.33;

        const double v1 = x * x + ( y - c ) * ( y + c );
        const double v2 = x * ( y + c ) + x * ( y + c );

        return 1.0 / ( v1 * v1 + v2 * v2 );
    }
};

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    enum ColorMap
    {
        RGBMap,
        IndexMap,
        HueMap,
        AlphaMap
    };

    Plot( QWidget * = NULL );

    QwtPlotSpectrogram *d_spectrogram;

public Q_SLOTS:
    void showContour( bool on );
    void showSpectrogram( bool on );
    void setColorMap( int );
    void setAlpha( int );

#ifndef QT_NO_PRINTER
    void printPlot();
#endif

private:

    int d_mapType;
    int d_alpha;
};
