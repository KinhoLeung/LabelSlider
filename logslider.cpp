#include "LogSlider.h"

LogSlider::LogSlider(QWidget *parent)
    : QSlider(parent), m_logMin(1.0), m_logMax(100.0)
{
    connect(this, &QSlider::valueChanged, this, &LogSlider::handleValueChanged);
    updateRange();
}

LogSlider::LogSlider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent), m_logMin(1.0), m_logMax(100.0)
{
    connect(this, &QSlider::valueChanged, this, &LogSlider::handleValueChanged);
    updateRange();
}

void LogSlider::setLogRange(double minVal, double maxVal)
{
    if (minVal <= 0 || maxVal <= 0 || minVal >= maxVal) {
        return; // 对数范围必须为正数且最小值小于最大值
    }
    
    m_logMin = minVal;
    m_logMax = maxVal;
    updateRange();
}

double LogSlider::logValue() const
{
    return linearToLog(value());
}

void LogSlider::setLogValue(double value)
{
    if (value < m_logMin || value > m_logMax) {
        return;
    }
    
    int linearVal = logToLinear(value);
    setValue(linearVal);
}

void LogSlider::handleValueChanged(int value)
{
    double logVal = linearToLog(value);
    emit logValueChanged(logVal);
}

double LogSlider::linearToLog(int linearValue) const
{
    if (maximum() == minimum()) {
        return m_logMin;
    }
    
    // 将线性值[minimum(), maximum()]映射到对数值[m_logMin, m_logMax]
    double ratio = double(linearValue - minimum()) / (maximum() - minimum());
    double logMin = qLn(m_logMin);
    double logMax = qLn(m_logMax);
    
    return qExp(logMin + ratio * (logMax - logMin));
}

int LogSlider::logToLinear(double logValue) const
{
    if (logValue <= 0) {
        return minimum();
    }
    
    double logMin = qLn(m_logMin);
    double logMax = qLn(m_logMax);
    double logVal = qLn(logValue);
    
    if (logMax == logMin) {
        return minimum();
    }
    
    double ratio = (logVal - logMin) / (logMax - logMin);
    return minimum() + int(ratio * (maximum() - minimum()));
}

void LogSlider::updateRange()
{
    // 使用较大的线性范围以获得更好的精度
    setRange(0, 1000);
}