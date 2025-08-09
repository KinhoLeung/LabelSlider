## LogSlider（Qt 对数滑块）

[English](README.md) | [中文](README_CN.md)

一个基于Qt的对数滑块组件，为指数数据范围提供平滑的对数缩放交互体验。

### 特性

- 📊 在线性滑块位置与值范围 \[`min`, `max`\] 之间进行对数映射
- ⚙️ 通过 `setLogRange(min, max)` 配置对数范围
- 🔢 使用真实数值读写：`logValue()` / `setLogValue(double)`
- 📡 数值变化时发出 `logValueChanged(double)` 信号
- 🔄 兼容 Qt 5 与 Qt 6，支持水平/垂直方向

### 应用场景

- 🔊 **音频/视频控制**: 音量、频率或增益控制
- 🔬 **科学应用**: 指数范围的参数调整
- 💰 **金融工具**: 利率、缩放因子
- 🎨 **图形应用**: 缩放级别、透明度控制
- ⚡ **工程工具**: 测量刻度、校准

### 环境要求

- Qt 5.6+ 或 Qt 6.x（Widgets）
- C++11 或更高
- 平台：Windows、macOS、Linux

### 集成方式

1. 将 `logslider.h` 和 `logslider.cpp` 复制到您的Qt项目中
2. 在代码中包含头文件：
   ```cpp
   #include "logslider.h"
   ```
3. 将文件添加到项目的构建系统中（CMake、qmake等）

#### qmake（.pro）

```pro
QT += widgets

SOURCES += \
    logslider.cpp

HEADERS += \
    logslider.h
```

#### CMake（Qt 6）

```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_sources(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/logslider.cpp
)

target_include_directories(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(your_target PRIVATE Qt6::Widgets)
```

#### CMake（Qt 5）

```cmake
find_package(Qt5 REQUIRED COMPONENTS Widgets)

target_sources(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/logslider.cpp
)

target_include_directories(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(your_target PRIVATE Qt5::Widgets)
```

### 使用示例

创建 `LogSlider`，设置对数范围，并监听 `logValueChanged`：

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

        slider->setLogRange(1.0, 1000.0);   // 对数范围
        slider->setLogValue(10.0);          // 设置初始"真实"数值

        connect(slider, &LogSlider::logValueChanged, this, [label](double v) {
            label->setText(QString("Value: %1").arg(v, 0, 'f', 3));
        });

        layout->addWidget(label);
        layout->addWidget(slider);
        setLayout(layout);
    }
};
```

### API 速览

- 构造函数
  - `LogSlider(QWidget *parent = nullptr)`
  - `LogSlider(Qt::Orientation orientation, QWidget *parent = nullptr)`
- 范围
  - `void setLogRange(double minVal, double maxVal)`
  - `double logMinimum() const`
  - `double logMaximum() const`
- 数值
  - `double logValue() const`
  - `void setLogValue(double value)`
- 信号
  - `void logValueChanged(double value)`

### 注意事项

- 该组件使用了 `Q_OBJECT` 与自定义信号，需确保工程启用 MOC（即作为 Qt 工程构建）。
- 组件内部使用较大的线性范围（默认 0–1000）以提升映射精度。
- 若出现 `qLn`/`qExp` 未定义等问题，请在 `.cpp` 中包含 `<QtMath>`，或改用 `<cmath>` 的 `std::log`/`std::exp`。
- 在区分大小写的系统上，`#include` 路径需与文件名大小写一致。

### 规划/想法

- 支持自定义内部线性分辨率
- 对数刻度的刻度线与标签
- 可选对数底（如 10 底 vs 自然底）

### 参与贡献

欢迎提交 Issue 和 PR。请附上问题描述、复现步骤（如适用）以及平台/Qt 版本信息。

