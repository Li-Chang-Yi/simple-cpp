#include <QApplication>
#include <QPushButton>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Open Virtual Keyboard");
    QObject::connect(&button, &QPushButton::clicked, []() {
        bool result = QProcess::startDetached("C:\\Windows\\System32\\osk.exe");
        if (!result) {
            qDebug() << "Failed to start osk.exe";
        }
    });

    button.resize(200, 100);
    button.show();

    return app.exec();
}

