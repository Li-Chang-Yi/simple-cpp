//#include <QApplication>
//#include <QTableWidget>
//#include "TableEditor.h"
//#include <QVBoxLayout>
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    // 创建窗口并设置标题
//    QWidget widget;
//    widget.setWindowTitle("TableWidget with Navigation, Editing, and Yellow Selection");

//    // 创建QTableWidget对象
//    QTableWidget *tableWidget = new QTableWidget(3, 3);

//    // 创建TableEditor对象并将tableWidget传递进去
//    TableEditor *editor = new TableEditor(tableWidget, &widget);

//    // 设置窗口布局
//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(editor);
//    widget.setLayout(mainLayout);

//    // 显示窗口
//    widget.resize(700, 700);
//    widget.show();

//    return app.exec();
//}


//#include <QApplication>
//#include <QWidget>
//#include <QLineEdit>
//#include <QLabel>
//#include <QHBoxLayout>
//#include <QTableWidget>
//#include <QTableWidgetItem>

//class CustomLineEdit : public QLineEdit
//{
//    Q_OBJECT

//public:
//    explicit CustomLineEdit(QWidget *parent = nullptr)
//        : QLineEdit(parent), arrowLabel(new QLabel("↑", this)) // 初始化label并设置箭头文本
//    {
//        // 设置布局，将arrowLabel置于最右侧
//        QHBoxLayout *layout = new QHBoxLayout(this);
//        layout->addStretch();           // 在箭头标签前留空，使其贴右
//        layout->addWidget(arrowLabel);   // 将label添加到右侧
//        layout->setContentsMargins(0, 0, 0, 0); // 去除边距

//        // 设置Label的样式
//        arrowLabel->setStyleSheet("color: gray; font-weight: bold;"); // 灰色和加粗样式
//        arrowLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);   // 右对齐和垂直居中

//        // 禁用label的鼠标事件，以便不会干扰QLineEdit的编辑功能
//        arrowLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
//    }

//private:
//    QLabel *arrowLabel; // 用于显示箭头的label
//};

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    // 创建主窗口
//    QWidget window;
//    window.setWindowTitle("Custom Line Edit in Table Example");
//    window.resize(400, 200);

//    // 创建 QTableWidget
//    QTableWidget *tableWidget = new QTableWidget(3, 3, &window); // 创建 3x3 的表格
//    tableWidget->setFixedSize(380, 180);

//    // 创建自定义输入框并添加到 (1, 1) 单元格
//    CustomLineEdit *customLineEdit = new CustomLineEdit();
//    tableWidget->setCellWidget(1, 1, customLineEdit); // 将自定义输入框添加到表格中的指定单元格

//    // 创建布局并将表格添加到窗口中
//    QVBoxLayout *layout = new QVBoxLayout(&window);
//    layout->addWidget(tableWidget);

//    // 显示窗口
//    window.show();

//    return app.exec();
//}

//#include "main.moc"

//#include <QApplication>
//#include <QWidget>
//#include <QLineEdit>
//#include <QLabel>
//#include <QHBoxLayout>
//#include <QTableWidget>
//#include <QTableWidgetItem>
//#include <QPushButton>
//#include <QVBoxLayout>

//class CustomLineEdit : public QLineEdit
//{
//    Q_OBJECT

//public:
//    explicit CustomLineEdit(QWidget *parent = nullptr)
//        : QLineEdit(parent), arrowLabel(new QLabel("↑", this)) // 初始化label并设置箭头文本
//    {
//        // 设置布局，将arrowLabel置于最右侧
//        QHBoxLayout *layout = new QHBoxLayout(this);
//        layout->addStretch();           // 在箭头标签前留空，使其贴右
//        layout->addWidget(arrowLabel);   // 将label添加到右侧
//        layout->setContentsMargins(0, 0, 0, 0); // 去除边距

//        // 设置Label的初始样式（黑色箭头）
//        arrowLabel->setStyleSheet("color: black; font-weight: bold;");
//        arrowLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);   // 右对齐和垂直居中

//        // 设置LineEdit的初始样式：黄色背景和黑色字体
//        this->setStyleSheet("background-color: yellow; color: black;");

//        // 禁用label的鼠标事件，以便不会干扰QLineEdit的编辑功能
//        arrowLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
//    }

//    // 方法用于切换箭头颜色
//    void setArrowColor(const QString &color)
//    {
//        arrowLabel->setStyleSheet("color: " + color + "; font-weight: bold;");
//    }

//private:
//    QLabel *arrowLabel; // 用于显示箭头的label
//};

//class MainWindow : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit MainWindow(QWidget *parent = nullptr) : QWidget(parent)
//    {
//        setWindowTitle("Custom Line Edit in Table with Confirm Button Example");
//        resize(400, 200);

//        // 创建 QTableWidget
//        tableWidget = new QTableWidget(3, 3, this); // 创建 3x3 的表格
//        tableWidget->setFixedSize(380, 180);

//        // 创建自定义输入框并添加到 (1, 1) 单元格
//        customLineEdit = new CustomLineEdit();
//        tableWidget->setCellWidget(1, 1, customLineEdit);

//        // 创建确认按钮
//        QPushButton *confirmButton = new QPushButton("确认", this);

//        // 创建布局并将表格和按钮添加到窗口中
//        QVBoxLayout *layout = new QVBoxLayout(this);
//        layout->addWidget(tableWidget);
//        layout->addWidget(confirmButton);

//        // 连接确认按钮的点击信号到槽函数
//        connect(confirmButton, &QPushButton::clicked, this, &MainWindow::onConfirmButtonClicked);
//    }

//private slots:
//    void onConfirmButtonClicked()
//    {
//        // 将自定义输入框的文本设置为“李昌义”
//        customLineEdit->setText("李昌义");

//        // 选中文本内容，并设置选中文字的样式（黄底黑字）
//        customLineEdit->selectAll();
//        customLineEdit->setStyleSheet("QLineEdit { background-color: yellow; color: black; }"
//                                      "QLineEdit::selection { background-color: yellow; color: black; }");

//        // 更改箭头颜色为黄色
//        customLineEdit->setArrowColor("red");

//        // 更改单元格的背景颜色为白色
//        QTableWidgetItem *item = tableWidget->item(1, 1);
//        if (!item) {
//            item = new QTableWidgetItem();
//            tableWidget->setItem(1, 1, item);
//        }
//        item->setBackground(Qt::white);  // 设置单元格背景为白色
//    }

//private:
//    QTableWidget *tableWidget;
//    CustomLineEdit *customLineEdit;
//};

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    MainWindow window;
//    window.show();

//    return app.exec();
//}

//#include "main.moc"



//#include <QApplication>
//#include <QTableWidget>
//#include <QLineEdit>
//#include <QLabel>
//#include <QWidget>
//#include <QHBoxLayout>
//#include <QPalette>

//class CustomCellWidget : public QWidget {
//public:
//    CustomCellWidget(QWidget *parent = nullptr) : QWidget(parent) {
//        // 创建 QLineEdit 和 QLabel 控件
//        QLineEdit *lineEdit = new QLineEdit(this);
//        QLabel *label = new QLabel("Label", this);

//        // 设置水平布局，将两个控件加入布局
//        QHBoxLayout *layout = new QHBoxLayout(this);
//        layout->addWidget(lineEdit);
//        layout->addWidget(label);
//        layout->setContentsMargins(0, 0, 0, 0);  // 去除边距
//        setLayout(layout);

//        // 设置焦点策略，使 QWidget 可接收焦点
//        setFocusPolicy(Qt::StrongFocus);

////        // 设置焦点样式，背景色为黄色，字体为黑色
////        QPalette palette = this->palette();
////        palette.setColor(QPalette::Background, Qt::yellow);
////        palette.setColor(QPalette::WindowText, Qt::black);
////        setAutoFillBackground(true);
////        setPalette(palette);
//    }

//protected:
//    // 重写焦点事件来更新样式
//    void focusInEvent(QFocusEvent *event) override {
//        setStyleSheet("background-color: yellow; color: black;");
//        QWidget::focusInEvent(event);
//    }

//    void focusOutEvent(QFocusEvent *event) override {
//        setStyleSheet("");
//        QWidget::focusOutEvent(event);
//    }
//};

//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);

//    // 创建一个 2x2 的 QTableWidget
//    QTableWidget table(2, 2);

//    // 创建自定义单元格控件
//    CustomCellWidget *cellWidget = new CustomCellWidget();

//    // 将自定义控件设置到表格的一个单元格内
//    table.setCellWidget(0, 0, cellWidget);

//    // 显示表格并设置初始化焦点到 cellWidget
//    table.show();
//    cellWidget->setFocus();

//    return app.exec();
//}


//#include "main.moc"

//#include <QApplication>
//#include <QWidget>
//#include <QLineEdit>
//#include <QHBoxLayout>
//#include <QTimer>
//#include <QKeyEvent>

//class InputWidget : public QWidget {
//    Q_OBJECT

//public:
//    InputWidget(int characterCount, QWidget *parent = nullptr) : QWidget(parent) {
//        QHBoxLayout *layout = new QHBoxLayout(this);
//        layout->setSpacing(5);

//        for (int i = 0; i < characterCount; ++i) {
//            QLineEdit *charEdit = new QLineEdit(this);
//            charEdit->setFixedWidth(20);
//            charEdit->setAlignment(Qt::AlignCenter);
//            charEdit->setMaxLength(1);
//            charEdit->setReadOnly(true);  // 设置为只读，去除光标闪烁
//            charEdit->installEventFilter(this);
//            charEdit->setPlaceholderText("_");
//            layout->addWidget(charEdit);
//            charEdits.append(charEdit);
//        }

//        currentIndex = 0;
//        charEdits[currentIndex]->setFocusPolicy(Qt::NoFocus); // 去除光标
//        timer = new QTimer(this);
//        connect(timer, &QTimer::timeout, this, &InputWidget::togglePlaceholder);
//        timer->start(500);
//    }

//protected:
//    bool eventFilter(QObject *obj, QEvent *event) override {
//        if (event->type() == QEvent::KeyPress) {
//            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//            if ((keyEvent->key() >= Qt::Key_0 && keyEvent->key() <= Qt::Key_9) ||
//                (keyEvent->key() >= Qt::Key_A && keyEvent->key() <= Qt::Key_F)) {

//                QLineEdit *currentEdit = charEdits[currentIndex];
//                currentEdit->setText(keyEvent->text());

//                // 更新为下一个字符框，并去掉光标
//                currentIndex = (currentIndex + 1) % charEdits.size();
//                charEdits[currentIndex]->setFocusPolicy(Qt::NoFocus);

//                return true;
//            }
//        }
//        return QWidget::eventFilter(obj, event);
//    }

//private slots:
//    void togglePlaceholder() {
//        if (charEdits[currentIndex]->placeholderText() == "_") {
//            charEdits[currentIndex]->setPlaceholderText("");
//        } else {
//            charEdits[currentIndex]->setPlaceholderText("_");
//        }
//    }

//private:
//    QVector<QLineEdit *> charEdits;
//    int currentIndex;
//    QTimer *timer;
//};

//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);

//    InputWidget inputWidget(6);  // 设置字符数
//    inputWidget.setWindowTitle("Input Widget");
//    inputWidget.resize(150, 50);
//    inputWidget.show();

//    return app.exec();
//}

//#include "main.moc"

//#include <QApplication>
//#include <QWidget>
//#include <QLineEdit>
//#include <QHBoxLayout>
//#include <QTimer>
//#include <QKeyEvent>

//class InputWidget : public QWidget {
//    Q_OBJECT

//public:
//    InputWidget(int characterCount, QWidget *parent = nullptr) : QWidget(parent), currentIndex(0) {
//        QHBoxLayout *layout = new QHBoxLayout(this);

//        // 创建每个字符框
//        for (int i = 0; i < characterCount; ++i) {
//            QLineEdit *charEdit = new QLineEdit(this);
//            charEdit->setFixedWidth(20);
//            charEdit->setAlignment(Qt::AlignCenter);
//            charEdit->setMaxLength(1);
//            charEdit->setReadOnly(true);
//            layout->addWidget(charEdit);
//            charEdits.append(charEdit);
//        }

//        charEdits[currentIndex]->setPlaceholderText("_"); // 初始显示闪烁的下划线

//        timer = new QTimer(this);
//        connect(timer, &QTimer::timeout, this, [=]() {
//            charEdits[currentIndex]->setPlaceholderText(
//                charEdits[currentIndex]->placeholderText().isEmpty() ? "_" : "");
//        });
//        timer->start(500);  // 每隔0.5秒切换显示状态
//    }

//protected:
//    void keyPressEvent(QKeyEvent *event) override {
//        if ((event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) ||
//            (event->key() >= Qt::Key_A && event->key() <= Qt::Key_F)) {

//            charEdits[currentIndex]->setText(event->text());
//            charEdits[currentIndex]->setPlaceholderText("");  // 移除当前框的下划线

//            currentIndex = (currentIndex + 1) % charEdits.size();  // 移动到下一个框
//            charEdits[currentIndex]->setPlaceholderText("_");  // 设置新位置的下划线
//        }
//    }

//private:
//    QVector<QLineEdit *> charEdits;
//    int currentIndex;
//    QTimer *timer;
//};

//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);

//    InputWidget inputWidget(6);  // 设置字符数
//    inputWidget.setWindowTitle("Input Widget");
//    inputWidget.resize(150, 50);
//    inputWidget.show();

//    return app.exec();
//}

//#include "main.moc"

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QTimer>
#include <QKeyEvent>

class InputWidget : public QWidget {
    Q_OBJECT

public:
    InputWidget(int characterCount, QWidget *parent = nullptr) : QWidget(parent), currentIndex(0) {
        QHBoxLayout *layout = new QHBoxLayout(this);

        // 创建每个字符框
        for (int i = 0; i < characterCount; ++i) {
            QLineEdit *charEdit = new QLineEdit(this);
            charEdit->setFixedWidth(20);
            charEdit->setAlignment(Qt::AlignCenter);
            charEdit->setMaxLength(1);
            charEdit->setReadOnly(true);
            layout->addWidget(charEdit);
            charEdits.append(charEdit);
        }

        // 初始设置第一个框的闪烁下划线
        charEdits[currentIndex]->setPlaceholderText("1");

        // 启动定时器，控制当前框的闪烁
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [=]() {
            // 切换当前输入框的下划线显示状态
            charEdits[currentIndex]->setPlaceholderText(
            charEdits[currentIndex]->placeholderText().isEmpty() ? "_" : "");
        });
        timer->start(500);  // 每隔0.5秒切换显示状态
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if ((event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) ||
            (event->key() >= Qt::Key_A && event->key() <= Qt::Key_F)) {

            // 设置当前框的输入文本并清除闪烁的下划线
            charEdits[currentIndex]->setText(event->text());
            charEdits[currentIndex]->setPlaceholderText("");

            // 跳转到下一个输入框并设置其闪烁的下划线
            currentIndex = (currentIndex + 1) % charEdits.size();
            charEdits[currentIndex]->setPlaceholderText("_");
        }
    }

private:
    QVector<QLineEdit *> charEdits;
    int currentIndex;
    QTimer *timer;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    InputWidget inputWidget(6);  // 设置字符数
    inputWidget.setWindowTitle("Input Widget");
    inputWidget.resize(150, 50);
    inputWidget.show();

    return app.exec();
}

#include "main.moc"






