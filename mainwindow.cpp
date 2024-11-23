#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QClipboard>
#include <QRegularExpression>
#include <QIcon>

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
        "(graubraun|dunkelgrau|hellgrün|blutrot|fleischfarbe|cremefarbe[n]?|"
        "lila|türkis|rot|blau|grün|violett|pink|gelb|cyan|schwarz|"
        "(weiss|weiß)[nmr]?|grau|braun|ocker[n]?|orange[n]?|flieder[n]?)"
        "(e[nmr]?|em|es)?", QRegularExpression::CaseInsensitiveOption);

    QString text = ui->plainTextEdit->toPlainText();
    QString htmlOutput = "<ol>";

    QRegularExpressionMatchIterator matchIterator = farbenRegex.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();

        QString colorName = match.captured(0);
        QString squareColor = "black"; //Standardfarbe

        // Farbe zuordnen
        if (colorName.contains("hellgrün", Qt::CaseInsensitive)) {
            squareColor = "lime";
        } else if (colorName.contains("dunkelgrau", Qt::CaseInsensitive)){
            squareColor = "#a9a9a9";
        } else if (colorName.contains("graubraun", Qt::CaseInsensitive)) {
            squareColor = "#3D3635";
        } else if (colorName.contains("blutrot", Qt::CaseInsensitive)){
            squareColor = "#880000";
        } else if (colorName.startsWith("grün", Qt::CaseInsensitive)) {
            squareColor = "green";
        } else if (colorName.contains("gelb", Qt::CaseInsensitive)) {
            squareColor = "yellow";
        } else if (colorName.contains("violett", Qt::CaseInsensitive) || colorName.contains("lila", Qt::CaseInsensitive)) {
            squareColor = "violet";
        } else if (colorName.contains("pink", Qt::CaseInsensitive)) {
            squareColor = "pink";
        } else if (colorName.contains("schwarz", Qt::CaseInsensitive)) {
            squareColor = "black";
        } else if (colorName.contains("weiß", Qt::CaseInsensitive) || colorName.contains("weiss", Qt::CaseInsensitive)) {
            squareColor = "white";
        } else if (colorName.endsWith("grau", Qt::CaseInsensitive)) {
            squareColor = "#d3d3d3";
        } else if (colorName.contains("orange", Qt::CaseInsensitive)) {
            squareColor = "orange";
        } else if (colorName.contains("türkis", Qt::CaseInsensitive)) {
            squareColor = "turquoise";
        } else if (colorName.contains("creme", Qt::CaseInsensitive)) {
            squareColor = "#FFFDD0";
        } else if (colorName.contains("ocker", Qt::CaseInsensitive)) {
            squareColor = "#cc7722";
        }  else if (colorName.contains("cyan", Qt::CaseInsensitive)) {
            squareColor = "cyan";
        } else if (colorName.contains("braun", Qt::CaseInsensitive)) {
            squareColor = "brown";
        } else if (colorName.contains("blau", Qt::CaseInsensitive)) {
            squareColor = "blue";
        } else if (colorName.contains("flieder", Qt::CaseInsensitive)){
            squareColor = "#9f97fc";
        } else if (colorName.contains("rot", Qt::CaseInsensitive)) {
            squareColor = "red";
        }

        //HTML-Ausgabe mit farbigem Quadrat
        htmlOutput += QString(
                          "<li>"
                          "<span style=\"color: %2; font-size: 1.2em;\">&#x25A0;</span> %1"
                          "</li>")
                          .arg(colorName, squareColor);
    }

    htmlOutput += "</ol>";
    qDebug() << "Generated HTML:\n" << htmlOutput;

    //Wenn kein Eingabetext vorhanden ist, wird das Listenfeld deaktiviert.
    if (ui->plainTextEdit->toPlainText().trimmed().isEmpty()){
        ui->textEditFarbliste->setEnabled(false);
    } else {
        //Listenfeld aktivieren
        ui->textEditFarbliste->setEnabled(true);
    }

    //Ausgabe in Listenfeld setzen
    ui->textEditFarbliste->setHtml(htmlOutput);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString textToCopy = ui->textEditFarbliste->toPlainText();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(textToCopy);
}




