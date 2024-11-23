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
            squareColor = "#00FF00"; //colLtGreen ?
        } else if (colorName.contains("cremefarbe", Qt::CaseInsensitive)){
            squareColor = "#F8DB83"; //colLtBrown
        } else if (colorName.contains("dunkelgrau", Qt::CaseInsensitive)){
            squareColor = "#a9a9a9";
        } else if (colorName.contains("graubraun", Qt::CaseInsensitive)) {
            squareColor = "#6b563f"; //colDkBrown
        } else if (colorName.contains("blutrot", Qt::CaseInsensitive)){
            squareColor = "#880000";
        } else if (colorName.contains("fleischfarbe", Qt::CaseInsensitive)){
            squareColor = "#FA8072"; //colsalmon
        } else if (colorName.startsWith("grün", Qt::CaseInsensitive)) {
            squareColor = "green";
        } else if (colorName.contains("gelb", Qt::CaseInsensitive)) {
            squareColor = "#FFFF00"; //colLtYellow
        } else if (colorName.contains("violett", Qt::CaseInsensitive) || colorName.contains("lila", Qt::CaseInsensitive)) {
            squareColor = "#B000CC"; //colDkMagenta
        } else if (colorName.contains("pink", Qt::CaseInsensitive)) {
            squareColor = "pink";
        } else if (colorName.contains("schwarz", Qt::CaseInsensitive)) {
            squareColor = "#000000"; //colBlack
        } else if (colorName.contains("weiß", Qt::CaseInsensitive) || colorName.contains("weiss", Qt::CaseInsensitive)) {
            squareColor = "#FFFFFF"; //colLtWhite
        } else if (colorName.endsWith("grau", Qt::CaseInsensitive)) {
            squareColor = "#d3d3d3";
        } else if (colorName.contains("orange", Qt::CaseInsensitive)) {
            squareColor = "#FF9900"; //colLtOrange
        } else if (colorName.contains("türkis", Qt::CaseInsensitive)) {
            squareColor = "turquoise";
        } else if (colorName.contains("creme", Qt::CaseInsensitive)) {
            squareColor = "#FFFDD0";
        } else if (colorName.contains("ocker", Qt::CaseInsensitive)) {
            squareColor = "#cc7722";
        }  else if (colorName.contains("cyan", Qt::CaseInsensitive)) {
            squareColor = "cyan";
        } else if (colorName.contains("braun", Qt::CaseInsensitive)) {
            squareColor = "#994400"; //colDkOrange
        } else if (colorName.contains("blau", Qt::CaseInsensitive)) {
            squareColor = "#0000B0"; //colDkBlue
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


//Farbreferenz von https://lotgd.de/templates/cozymood.css?v=0011
// .colDkBlue 		{ color: #0000B0; }
// .colDkGreen   	{ color: #00B000; }
// .colDkCyan		{ color: #00B0B0; }
// .colDkRed	 	{ color: #B00000; }
// .colDkMagenta 	{ color: #B000CC; }
// .colDkYellow  	{ color: #B0B000; }
// .colDkWhite   	{ color: #B0B0B0; }
// .colLtBlue		{ color: #0000FF; }
// .colLtGreen   	{ color: #00FF00; }
// .colLtCyan		{ color: #00FFFF; }
// .colLtRed	 	{ color: #FF0000; }
// .colLtMagenta 	{ color: #FF00FF; }
// .colLtYellow  	{ color: #FFFF00; }
// .colLtWhite   	{ color: #FFFFFF; }
// .colLtBlack   	{ color: #999999; }
// .colDkOrange  	{ color: #994400; }
// .colLtOrange  	{ color: #FF9900; }
// .colBlue  		{ color: #0070FF; }
// .colLime  		{ color: #DDFFBB; }
// .colBlack  		{ color: #000000; }
// .colRose 		{ color: #EEBBEE; }
// .colblueviolet 	{ color: #9A5BEE; }
// .colBlueViolet 	{ color: #9A5BEE; }
// .coliceviolet	{ color: #AABBEE; }
// .colLtBrown 	{ color: #F8DB83; }
// .colDkBrown 	{ color: #6b563f; }
// .colXLtGreen	{ color: #aaff99; }
// .colbeige  		{ color: #F5F5DC; }
// .colkhaki  		{ color: #F0E68C; }
// .coldarkkhaki  	{ color: #BDB76B; }
// .colaquamarine  { color: #7FFFD4; }
// .coldarkseagreen { color: #8FBC8F; }
// .collightsalmon { color: #FFA07A; }
// .colsalmon  	{ color: #FA8072; }
// .colwheat  		{ color: #F5DEB3; }
// .coltan  		{ color: #D2B48C; }
// .colLtLinkBlue 	{ color: #0099FF; }
// .colDkLinkBlue 	{ color: #006BB3; }
// .colDkRust 		{ color: #8D6060; }
// .colLtRust 		{ color: #B07878; }
// .colMdBlue 		{ color: #0000F0; }
// .colMdGrey 		{ color: #DDDDDD; }
// .colMedRed 		{ color: #780000; }
// .colburlywood 	{ color: #DEB887; }
// .colAttention 	{ background-color: #00FF00; color: #FF0000; }
// .colWhiteBlack 	{ background-color: #FFFFFF; color: #000000; }
// .colBack  		{ background-color: #00FFFF; color: #000000; }
// .trhead  		{ background-color:#003026; color: #fafafa; }
// .trlight 		{ background-color:#001f1f; }
// .hilight 		{ background-color:#005757; }
// .trhilight 		{ background-color:#005757; }
// .trdark 		{ background-color:#001410; }




