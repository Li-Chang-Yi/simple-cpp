#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>

class TableEditor : public QWidget
{
    Q_OBJECT

public:
    TableEditor(QTableWidget *table, QWidget *parent = nullptr);

private:
    QTableWidget *tableWidget;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QTimer *timeTimer;  // 定时器用于实时更新系统时间
    QTimer *dateTimer;  // 定时器用于每小时更新系统日期

    bool isEditing;
    QLineEdit *currentLineEdit;
    int editPosition;  // 当前编辑光标位置

    void setupUI();
    void setupConnections();

    void enterEditMode();   // 确认键进入编辑模式
    void exitEditMode();    // 取消键退出编辑模式并保存更改

    void highlightSelectedCharacter(); // 高亮选中字符

    void handleUpButton();
    void handleDownButton();
    void handleLeftButton();
    void handleRightButton();

    void handleTextEdited(const QString &text);
    void encryptCellContent();

private slots:
    void updateSystemTime();  // 更新系统时间槽函数
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // TABLEEDITOR_H

