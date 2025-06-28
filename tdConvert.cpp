
#define EOD_X       10
#define EOD_Y       0
#define EOD_Z       15

static double  _tdConv_x   = 0.0,
        _tdConv_y   = 0.0,
        _tdConv_z   = 0.0;

static double  _tdConvEodx = 0.0,
        _tdConvEody = 0.0,
        _tdConvEodz = 0.0;

double  gdTraining  = 0.0,
        gdElevation = 0.0;
        
        
static void tdConvert_cart_2
    (
    double dTraining, 
    double dElevation, 
    double dRange
    )
{
    _tdConv_x = dRange * cos(dElevation) * cos(dTraining);
    _tdConv_y = dRange * cos(dElevation) * sin(dTraining);
    _tdConv_z = dRange * cos(dElevation) * tan(dElevation);
}


static void tdConvert_cart(double dTr, double dEl, double dRa)
{
    _tdConv_x = dRa * cos(dTr);
    _tdConv_y = dRa * sin(dTr);
    _tdConv_z = dRa * tan(dEl);
}

static void tdConvert_offset()
{
    _tdConvEodx = _tdConv_x + EOD_X;
    _tdConvEody = _tdConv_y + EOD_Y;
    _tdConvEodz = _tdConv_z + EOD_Z;
}

void tdConvert
    (
    double dTraining,
    double dElevation,
    double dRange
    )
{
    // Convert to cartesian
    tdConvert_cart_2(dTraining, dElevation, dRange);
    
    // Apply the Director offsets
    tdConvert_offset();
    
    double dTmpRange = sqrt(_tdConvEodx * _tdConvEodx + _tdConvEody * _tdConvEody + _tdConvEodz * _tdConvEodz);
    
    gdTraining = atan2(_tdConvEodx, _tdConvEody);
    gdElevation = asin(_tdConvEodz / dTmpRange);
}