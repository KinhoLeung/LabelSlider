## LogSlider (Qt logarithmic slider)

[English](README.md) | [中文](README_CN.md)

A Qt-based logarithmic slider widget that provides smooth logarithmic scaling for better user interaction with exponential data ranges.

### Features

- 📊 Logarithmic mapping between the slider's linear position and a value range \[`min`, `max`\]
- ⚙️ Configurable log range via `setLogRange(min, max)`
- 🔢 Read/Set by real-world value with `logValue()` / `setLogValue(double)`
- 📡 Signal `logValueChanged(double)` emitted whenever the value changes
- 🔄 Works with Qt 5 and Qt 6; supports horizontal and vertical orientations

### Use Cases

- 🔊 **Audio/Video Controls**: Volume, frequency, or gain controls
- 🔬 **Scientific Applications**: Parameter adjustment with exponential ranges
- 💰 **Financial Tools**: Interest rates, scaling factors
- 🎨 **Graphics Applications**: Zoom levels, opacity controls
- ⚡ **Engineering Tools**: Measurement scales, calibration

### Requirements

- Qt 5.6+ or Qt 6.x (Widgets)
- C++11 or newer
- Platforms: Windows, macOS, Linux

### Integration

1. Copy `logslider.h` and `logslider.cpp` to your Qt project
2. Include the header file in your code:
   ```cpp
   #include "logslider.h"
   ```
3. Add the files to your project's build system (CMake, qmake, etc.)

#### qmake (.pro)

```pro
QT += widgets

SOURCES += \
    logslider.cpp

HEADERS += \
    logslider.h
```

#### CMake (Qt 6)

```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# If you are adding the sources directly to an existing target
target_sources(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/logslider.cpp
)

target_include_directories(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(your_target PRIVATE Qt6::Widgets)
```

#### CMake (Qt 5)

```cmake
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# If you are adding the sources directly to an existing target
target_sources(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/logslider.cpp
)

target_include_directories(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(your_target PRIVATE Qt5::Widgets)
```

### Usage

Create a `LogSlider`, set the logarithmic range, and react to `logValueChanged`:

```cpp
#include "logslider.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class DemoWidget : public QWidget {
    Q_OBJECT
public:
    DemoWidget() {
        auto *layout = new QVBoxLayout(this);
        auto *label = new QLabel("Value: 0", this);
        auto *slider = new LogSlider(Qt::Horizontal, this);

        slider->setLogRange(1.0, 1000.0);   // value range in log scale
        slider->setLogValue(10.0);          // set initial value (not position)

        connect(slider, &LogSlider::logValueChanged, this, [label](double v) {
            label->setText(QString("Value: %1").arg(v, 0, 'f', 3));
        });

        layout->addWidget(label);
        layout->addWidget(slider);
        setLayout(layout);
    }
};
```

### API at a glance

- Constructors
  - `LogSlider(QWidget *parent = nullptr)`
  - `LogSlider(Qt::Orientation orientation, QWidget *parent = nullptr)`
- Range
  - `void setLogRange(double minVal, double maxVal)`
  - `double logMinimum() const`
  - `double logMaximum() const`
- Value
  - `double logValue() const`
  - `void setLogValue(double value)`
- Signals
  - `void logValueChanged(double value)`

### Notes

- This widget uses `Q_OBJECT` and a custom signal, so MOC must run (i.e., build it as part of a Qt project with meta-object support).
- Internally, the slider range is set to a relatively large linear range (default 0–1000) for better precision before mapping to log space.
- If you see missing symbols like `qLn`/`qExp`, ensure `<QtMath>` is included in the `.cpp`, or replace with `<cmath>` equivalents (`std::log`, `std::exp`).
- Make sure your include statements match the exact filename case on case-sensitive filesystems.

### Roadmap / Ideas

- Option to customize the internal linear resolution
- Tick marks and labels that reflect logarithmic spacing
- Optional base selection (e.g., base-10 vs. natural logarithm)

### Contributing

Issues and pull requests are welcome. Please include a short description, reproduction steps (if applicable), and platform/Qt version info.

