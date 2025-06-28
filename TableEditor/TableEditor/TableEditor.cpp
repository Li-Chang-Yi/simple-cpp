#include "TableEditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QHeaderView>
#include <QPalette>
#include <QDateTime>
#include <QTimer>
TableEditor::TableEditor(QTableWidget *table, QWidget *parent)
    : QWidget(parent), tableWidget(table), isEditing(false), currentLineEdit(nullptr), editPosition(0)
{
    // 隐藏水平和垂直表头
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->verticalHeader()->setVisible(false);

//     初始化单元格内容
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            tableWidget->setItem(row, col, new QTableWidgetItem());
        }
    }
    tableWidget->setItem(0, 0, new QTableWidgetItem(QString("123.456:789.369")));
    tableWidget->setItem(0, 1, new QTableWidgetItem(QString("【1】关闭")));
    tableWidget->setItem(1, 1, new QTableWidgetItem(QString("")));

    // 设置系统时间到 (0, 2) 单元格
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDate = currentDateTime.toString("yyyy-MM-dd");
    QTableWidgetItem *dateItem = new QTableWidgetItem(formattedDate);
    dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);  // 设置不可编辑
    tableWidget->setItem(0, 2, dateItem);

    // 设置系统时间到 (1, 0) 单元格，格式为 HH:mm:ss
    QString formattedTime = currentDateTime.toString("HH:mm:ss");
    QTableWidgetItem *timeItem = new QTableWidgetItem(formattedTime);
    timeItem->setFlags(timeItem->flags() & ~Qt::ItemIsEditable);  // 设置不可编辑
    tableWidget->setItem(1, 0, timeItem);


//    tableWidget->setItem(1, 1, new QTableWidgetItem(QString("")));
    // 初始化UI
    setupUI();

    // 设置选中单元格的背景颜色为黄色
    tableWidget->setStyleSheet(
        "QTableWidget::item:selected {"
        "background-color: yellow;"   // 选中单元格的背景颜色为黄色
        "color: black;"               // 选中单元格的字体颜色为黑色
        "}"
    );

    // 初始化选中第一个单元格
    tableWidget->setCurrentCell(0, 0);

    // 设置按钮连接槽函数
    setupConnections();

    // 创建定时器并连接到槽函数
    timeTimer = new QTimer(this);
    dateTimer = new QTimer(this);
    connect(timeTimer, &QTimer::timeout, this, &TableEditor::updateSystemTime);
    connect(dateTimer, &QTimer::timeout, this, &TableEditor::updateSystemTime);

    // 设置每秒更新一次时间
    timeTimer->start(1000);

    // 设置每小时更新一次日期
    dateTimer->start(3600000);

    // 初始化时间和日期
    updateSystemTime();
}

void TableEditor::setupUI()
{
    // 创建导航按钮和确认、取消按钮
    upButton = new QPushButton("Up");
    downButton = new QPushButton("Down");
    leftButton = new QPushButton("Left");
    rightButton = new QPushButton("Right");
    confirmButton = new QPushButton("Confirm");
    cancelButton = new QPushButton("Cancel");

    // 创建布局
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(upButton);
    buttonLayout->addWidget(downButton);
    buttonLayout->addWidget(rightButton);

    // 创建确认和取消按钮的布局
    QHBoxLayout *confirmCancelLayout = new QHBoxLayout;
    confirmCancelLayout->addWidget(confirmButton);
    confirmCancelLayout->addWidget(cancelButton);

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(confirmCancelLayout);

    setLayout(mainLayout);
}

void TableEditor::setupConnections()
{
    connect(upButton, &QPushButton::clicked, this, &TableEditor::handleUpButton);
    connect(downButton, &QPushButton::clicked, this, &TableEditor::handleDownButton);
    connect(leftButton, &QPushButton::clicked, this, &TableEditor::handleLeftButton);
    connect(rightButton, &QPushButton::clicked, this, &TableEditor::handleRightButton);
    connect(confirmButton, &QPushButton::clicked, this, &TableEditor::enterEditMode);
    connect(cancelButton, &QPushButton::clicked, this, &TableEditor::exitEditMode);
}

void TableEditor::enterEditMode()
{
    if (isEditing) return;

    int row = tableWidget->currentRow();
    int col = tableWidget->currentColumn();

    if (!tableWidget->item(row, col)) {
        return;
    }

    // 获取选中的单元格文本
    QString originalText = tableWidget->item(row, col)->text();

    // 创建一个QLineEdit，用于编辑文本
    currentLineEdit = new QLineEdit(originalText);

    // 设置QLineEdit的背景色为白色，选中文字背景色为黄色，文本颜色为黑色
    QPalette p = currentLineEdit->palette();
    p.setColor(QPalette::Base, Qt::white);  // 设置背景为白色
    p.setColor(QPalette::Text, Qt::black);  // 设置文本颜色为黑色
    p.setColor(QPalette::Highlight, Qt::yellow);  // 设置选中文字的背景色为黄色
    p.setColor(QPalette::HighlightedText, Qt::black); // 设置选中文字的颜色为黑色
    currentLineEdit->setPalette(p);

    tableWidget->setCellWidget(row, col, currentLineEdit);
    currentLineEdit->setFocus();

    if (originalText.isEmpty()) {
        // 如果文本为空，模拟高亮显示一个字符宽度的黄色背景
        editPosition = 0;  // 初始编辑位置为第一个空字符位置
        currentLineEdit->setSelection(editPosition, 1);  // 高亮选中空位置，显示为黄色
    }

    // 判断第一个字符是否为数字
    QChar firstChar = originalText[0];
    if (firstChar.isDigit() || (firstChar >= 'A' && firstChar <= 'F') ) {
        // 数字处理模式，设置初始编辑位置为第一个字符
        editPosition = 0;
        highlightSelectedCharacter();
    } else {
        // 文本处理模式，全选文本
        currentLineEdit->selectAll();
    }


    isEditing = true;

    // 连接信号槽，当用户输入文本时，实时更新选中高亮
    connect(currentLineEdit, &QLineEdit::textEdited, this, &TableEditor::handleTextEdited);
    // 连接信号槽，当用户结束输入时，将数字替换为加密的 '*'
    connect(currentLineEdit, &QLineEdit::editingFinished, this, &TableEditor::encryptCellContent);


}


void TableEditor::exitEditMode()
{
    if (!isEditing) return;

    int row = tableWidget->currentRow();
    int col = tableWidget->currentColumn();

    // 保存新的文本
    QString newText = currentLineEdit->text();
    tableWidget->item(row, col)->setText(newText);

    // 移除QLineEdit，恢复普通模式
    tableWidget->removeCellWidget(row, col);
    isEditing = false;
    currentLineEdit = nullptr;
}

void TableEditor::highlightSelectedCharacter()
{
    // 设置选中的字符的高亮颜色为黄色，字符颜色为黑色
    QPalette p = currentLineEdit->palette();
    p.setColor(QPalette::Highlight, Qt::yellow);   // 设置选中文字的背景色为黄色
    p.setColor(QPalette::HighlightedText, Qt::black); // 设置选中字符的颜色为黑色
    currentLineEdit->setPalette(p);

//    // 高亮选中位置的字符，设置选中范围为一个字符
//    currentLineEdit->setSelection(editPosition, 1);

    // 设置高亮选中当前位置的字符，如果单元格为空，则模拟选中一个字符宽度
    if (editPosition <= currentLineEdit->text().length()) {
        currentLineEdit->setSelection(editPosition, 1);
    }
}

//void TableEditor::handleUpButton()
//{
//    if (isEditing) {
//        QString text = currentLineEdit->text();

//        // 判断第一个字符是否为数字
//        QChar firstChar = text[0];
//        if (!firstChar.isDigit()) {
//            // 文本处理模式，按上下键切换文本
//            if (text == "【1】关闭") {
//                currentLineEdit->setText("【2】打开");
//            } else {
//                currentLineEdit->setText("【1】关闭");
//            }
//            currentLineEdit->selectAll();  // 全选文本
//        } else if (editPosition < text.length() && text[editPosition].isDigit()) {
//            // 数字处理模式，增加数字
//            int num = text[editPosition].digitValue();
//            num = (num + 1) % 10;  // 增加数字，循环从0到9
//            text[editPosition] = QChar('0' + num);
//            currentLineEdit->setText(text);
//            highlightSelectedCharacter();  // 保持高亮选中字符
//        }
//    } else {
//        int currentRow = tableWidget->currentRow();
//        int currentCol = tableWidget->currentColumn();
//        if (currentRow > 0) {
//            tableWidget->setCurrentCell(currentRow - 1, currentCol);
//        }
//    }
//}

//void TableEditor::handleDownButton()
//{
//    if (isEditing) {
//        QString text = currentLineEdit->text();

//        // 判断第一个字符是否为数字
//        QChar firstChar = text[0];
//        if (!firstChar.isDigit()) {
//            // 文本处理模式，按上下键切换文本
//            if (text == "【1】关闭") {
//                currentLineEdit->setText("【2】打开");
//            } else {
//                currentLineEdit->setText("【1】关闭");
//            }
//            currentLineEdit->selectAll();  // 全选文本
//        } else if (editPosition < text.length() && text[editPosition].isDigit()) {
//            // 数字处理模式，减少数字
//            int num = text[editPosition].digitValue();
//            num = (num + 9) % 10;  // 减少数字，循环从9到0
//            text[editPosition] = QChar('0' + num);
//            currentLineEdit->setText(text);
//            highlightSelectedCharacter();  // 保持高亮选中字符
//        }
//    } else {
//        int currentRow = tableWidget->currentRow();
//        int currentCol = tableWidget->currentColumn();
//        if (currentRow < tableWidget->rowCount() - 1) {
//            tableWidget->setCurrentCell(currentRow + 1, currentCol);
//        }
//    }
//}

void TableEditor::handleUpButton()
{
    if (isEditing) {
        QString text = currentLineEdit->text();

        // 判断第一个字符是否为数字或字母
        QChar currentChar = text[editPosition];
        if (!currentChar.isDigit() && !(currentChar >= 'A' && currentChar <= 'F')) {
            // 文本处理模式，按上下键切换文本
            if (text == "【1】关闭") {
                currentLineEdit->setText("【2】打开");
            } else {
                currentLineEdit->setText("【1】关闭");
            }
            currentLineEdit->selectAll();  // 全选文本
        } else if (editPosition < text.length()) {
            // 处理0-9和A-F的循环
            QString hexChars = "0123456789ABCDEF";
            int index = hexChars.indexOf(currentChar.toUpper());
            if (index != -1) {
                index = (index + 1) % hexChars.length();  // 循环增加字符
                text[editPosition] = hexChars[index];
                currentLineEdit->setText(text);
                highlightSelectedCharacter();  // 保持高亮选中字符
            }
        }
    } else {
        int currentRow = tableWidget->currentRow();
        int currentCol = tableWidget->currentColumn();
        if (currentRow > 0) {
            tableWidget->setCurrentCell(currentRow - 1, currentCol);
        }
    }
}

void TableEditor::handleDownButton()
{
    if (isEditing) {
        QString text = currentLineEdit->text();

        // 判断第一个字符是否为数字或字母
        QChar currentChar = text[editPosition];
        if (!currentChar.isDigit() && !(currentChar >= 'A' && currentChar <= 'F')) {
            // 文本处理模式，按上下键切换文本
            if (text == "【1】关闭") {
                currentLineEdit->setText("【2】打开");
            } else {
                currentLineEdit->setText("【1】关闭");
            }
            currentLineEdit->selectAll();  // 全选文本
        } else if (editPosition < text.length()) {
            // 处理0-9和A-F的循环
            QString hexChars = "0123456789ABCDEF";
            int index = hexChars.indexOf(currentChar.toUpper());
            if (index != -1) {
                index = (index - 1 + hexChars.length()) % hexChars.length();  // 循环减少字符
                text[editPosition] = hexChars[index];
                currentLineEdit->setText(text);
                highlightSelectedCharacter();  // 保持高亮选中字符
            }
        }
    } else {
        int currentRow = tableWidget->currentRow();
        int currentCol = tableWidget->currentColumn();
        if (currentRow < tableWidget->rowCount() - 1) {
            tableWidget->setCurrentCell(currentRow + 1, currentCol);
        }
    }
}


void TableEditor::handleLeftButton()
{
    if (isEditing) {
        QString text = currentLineEdit->text();

        QChar firstChar = text[0];
        // 如果是纯文本模式，左右键无效果，保持全选文本
        if (!firstChar.isDigit() && !(firstChar >= 'A' && firstChar <= 'F')) {
            currentLineEdit->selectAll();  // 保持全选文本
            return;  // 忽略左右键操作
        }

        // 数字或字母模式下的光标移动逻辑，跳过符号
        while (editPosition > 0) {
            editPosition--;  // 向左移动光标
            QChar currentChar = text[editPosition];
            if (currentChar.isDigit() || (currentChar >= 'A' && currentChar <= 'F')) {
                break;  // 找到数字或字母后停止移动
            }
        }

        highlightSelectedCharacter();  // 保持高亮选中字符
    } else {
        int currentRow = tableWidget->currentRow();
        int currentCol = tableWidget->currentColumn();
        if (currentCol > 0) {
            tableWidget->setCurrentCell(currentRow, currentCol - 1);
        }
    }
}

void TableEditor::handleRightButton()
{
    if (isEditing) {
        QString text = currentLineEdit->text();

        QChar firstChar = text[0];
        // 如果是纯文本模式，左右键无效果，保持全选文本
        if (!firstChar.isDigit() && !(firstChar >= 'A' && firstChar <= 'F')) {
            currentLineEdit->selectAll();  // 保持全选文本
            return;  // 忽略左右键操作
        }

        // 数字或字母模式下的光标移动逻辑，跳过符号
        while (editPosition < text.length() - 1) {
            editPosition++;  // 向右移动光标
            QChar currentChar = text[editPosition];
            if (currentChar.isDigit() || (currentChar >= 'A' && currentChar <= 'F')) {
                break;  // 找到数字或字母后停止移动
            }
        }

        highlightSelectedCharacter();  // 保持高亮选中字符
    } else {
        int currentRow = tableWidget->currentRow();
        int currentCol = tableWidget->currentColumn();
        if (currentCol < tableWidget->columnCount() - 1) {
            tableWidget->setCurrentCell(currentRow, currentCol + 1);
        }
    }
}


void TableEditor::keyPressEvent(QKeyEvent *event)
{
    if (isEditing && currentLineEdit) {
        switch (event->key()) {
            case Qt::Key_Up:
                handleUpButton();
                break;
            case Qt::Key_Down:
                handleDownButton();
                break;
            case Qt::Key_Left:
                handleLeftButton();
                break;
            case Qt::Key_Right:
                handleRightButton();
                break;
            default:
                QWidget::keyPressEvent(event);  // 其他按键交由基类处理
                break;
        }
    } else {
        switch (event->key()) {
            case Qt::Key_Up:
                handleUpButton();
                break;
            case Qt::Key_Down:
                handleDownButton();
                break;
            case Qt::Key_Left:
                handleLeftButton();
                break;
            case Qt::Key_Right:
                handleRightButton();
                break;
            default:
                QWidget::keyPressEvent(event);
                break;
        }
    }
}

void TableEditor::updateSystemTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 更新 (1, 0) 单元格的时间
    QString formattedTime = currentDateTime.toString("HH:mm:ss");
    if (tableWidget->item(1, 0) == nullptr) {
        tableWidget->setItem(1, 0, new QTableWidgetItem(formattedTime));
    } else {
        tableWidget->item(1, 0)->setText(formattedTime);
    }

    // 更新 (0, 2) 单元格的日期
    QString formattedDate = currentDateTime.toString("yyyy-MM-dd");
    if (tableWidget->item(0, 2) == nullptr) {
        tableWidget->setItem(0, 2, new QTableWidgetItem(formattedDate));
    } else {
        tableWidget->item(0, 2)->setText(formattedDate);
    }
}

void TableEditor::handleTextEdited(const QString &text)
{
    if (editPosition >= text.length()) {
        return; // 如果光标已经到达文本末尾，直接返回
    }

    // 设置新的文本，确保黄色背景移动到下一个字符
    QString newText = text;

    currentLineEdit->setText(newText);

    // 移动到下一个字符位置
    editPosition++;

    // 如果已经到达最后，editPosition不再改变
    if (editPosition > newText.length()) {
        editPosition = newText.length();
    }

    highlightSelectedCharacter();
}

void TableEditor::encryptCellContent()
{
    if (!currentLineEdit) return;

    QString text = currentLineEdit->text();
    QString encryptedText;

    // 将输入的数字全部替换为 '*'
    for (int i = 0; i < text.length(); ++i) {
        if (text[i].isDigit()) {
            encryptedText.append('*');
        } else {
            encryptedText.append(text[i]);
        }
    }

    // 更新单元格的文本
    int row = tableWidget->currentRow();
    int col = tableWidget->currentColumn();
    tableWidget->item(row, col)->setText(encryptedText);

    // 清除编辑控件并退出编辑模式
    tableWidget->removeCellWidget(row, col);
    isEditing = false;
}
