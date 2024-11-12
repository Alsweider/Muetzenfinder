#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QClipboard>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboardText = clipboard->text();
    ui->plainTextEdit->setPlainText(clipboardText);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    QRegularExpression farbenRegex(
        "(lila|türkis|rot|blau|grün|violett|pink|gelb|cyan|schwarz|"
        "(weiss|weiß)[nmr]?|grau|braun|ocker[n]?|dunkelgrau[n]?|hellgrün[n]?|orange[n]?|flieder[n]?|"
        "blutrot[n]?|graubraun[n]?|fleischfarbe[n]?|cremefarbe[n]?)"
        "(e[nmr]?|em|es)?", QRegularExpression::CaseInsensitiveOption);

    QString text = ui->plainTextEdit->toPlainText();
    QStringList gefundeneFarben;

    QRegularExpressionMatchIterator matchIterator = farbenRegex.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        gefundeneFarben << match.captured(0);
    }

    QString filteredText = gefundeneFarben.join("\n");

    ui->plainTextEdit_2->setPlainText(filteredText);

}

void MainWindow::on_pushButton_2_clicked()
{
    QString textToCopy = ui->plainTextEdit_2->toPlainText();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(textToCopy);
}




