#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,
    ui(new Ui::MainWindow),
    turno('X')
{
    ui->setupUi(this);
    startArrays();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startArrays()
{
    tablero.resize(3, std::vector<int>(3));

    for (std::size_t fila = 0; fila < mNumeroDeFilas; fila++)
    {
        for (std::size_t columna = 0; columna < mNumeroDeColumnas; columna++)
        {
            tablero[fila][columna] = 0;
        }
    }

    if (botones.size() != mNumeroMaximoFichas)
    {
        botones.push_back(ui->boton1);
        botones.push_back(ui->boton2);
        botones.push_back(ui->boton3);
        botones.push_back(ui->boton4);
        botones.push_back(ui->boton5);
        botones.push_back(ui->boton6);
        botones.push_back(ui->boton7);
        botones.push_back(ui->boton8);
        botones.push_back(ui->boton9);
    }

    juego = "Active";
    contador = 0;
    ui->pushButton->setDisabled(true);
    ui->label->setText("Es el turno del jugador: " + QString(QChar::fromLatin1(turno)));
    enableAllButtons();
}

void MainWindow::buttonClicked(int fila, int columna, QPushButton* botonPresionado)
{
    contador++;
    setIcon(botonPresionado);
    setMatriz(fila, columna);
    checkTable();
    changeTurn();
    botonPresionado->setEnabled(false);
}

void MainWindow::setIcon(QPushButton* botonPresionado)
{
    botonPresionado->setText(QString(QChar::fromLatin1(turno)));
    if(turno == 'X'){
        botonPresionado->setStyleSheet("QPushButton{ background-color: #0D7ADF; "
                                       "color: white;"
                                       "font: 700 12pt;}");
    }
    else if (turno == 'O'){
        botonPresionado->setStyleSheet("QPushButton{ background-color: #FF8B00;"
                                       "color: white; "
                                       "font: 700 12pt;}");
    }

}

void MainWindow::setMatriz(int fila, int columna)
{
    tablero[fila][columna] = (turno == 'X' ? 1 : 5);
}

void MainWindow::checkTable()
{
    int filas [3];
    int columnas [3];
    int diagonalLeft;
    int diagonalRight;

    for (int fila = 0; fila < mNumeroDeFilas; fila++)
    {
        filas[fila] = 0;
        columnas[fila] = 0;
        diagonalLeft = 0;
        diagonalRight = 0;

        for (int columna = 0; columna < mNumeroDeColumnas; columna++)
        {
            filas[fila] += tablero[fila][columna];
            columnas[fila] += tablero[columna][fila];
            diagonalLeft += tablero[columna][columna];
            diagonalRight += tablero[columna][2 - columna];
            /*Se hace de esta forma debido a ser lo más simple posible
            con operaciones sencillas y lógica donde se emplean diversos
            elementos realizados en metodos anteriores*/

        }

        if (filas[fila] == 3 || columnas[fila] == 3 || diagonalLeft == 3 || diagonalRight == 3 ||
            filas[fila] == 15 || columnas[fila] == 15 || diagonalLeft == 15 || diagonalRight == 15)
        {
            showWinner();

        }
        else if (contador == mNumeroMaximoFichas)
        {
            juego = "No Win";
        }
    }
}

void MainWindow::changeTurn()
{
    if (juego == "Winner"){
        ui->label->setText("El ganador es el jugador " + QString(QChar::fromLatin1(turno)));
        return;
    } else if (juego == "No Win"){
        ui->label->setText("No ha ganado ninguno de los jugadores");
        ui->pushButton->setEnabled(true);
        return;
    } else if (juego == "Active"){
        turno = (turno == 'X' ? 'O' : 'X');
        ui->label->setText("Es el turno del jugador: " + QString(QChar::fromLatin1(turno)));
    }


}

void MainWindow::showWinner()
{
    juego = "Winner";
    disableAllButtons();
    ui->pushButton->setEnabled(true);

}

void MainWindow::disableAllButtons()
{
    for (std::size_t i = 0; i < botones.size(); i++)
    {
        botones[i]->setDisabled(true);
    }
}

void MainWindow::enableAllButtons()
{
    for (std::size_t i = 0; i < 9; i++)
    {
        botones[i]->setEnabled(true);
        botones[i]->setText("");
        botones[i]->setStyleSheet("");
    }
}

void MainWindow::on_boton1_clicked()
{
    buttonClicked(0, 0, ui->boton1);
}

void MainWindow::on_boton2_clicked()
{
    buttonClicked(0, 1, ui->boton2);
}

void MainWindow::on_boton3_clicked()
{
    buttonClicked(0, 2, ui->boton3);
}

void MainWindow::on_boton4_clicked()
{
    buttonClicked(1, 0, ui->boton4);
}

void MainWindow::on_boton5_clicked()
{
    buttonClicked(1, 1, ui->boton5);
}

void MainWindow::on_boton6_clicked()
{
    buttonClicked(1, 2, ui->boton6);
}

void MainWindow::on_boton7_clicked()
{
    buttonClicked(2, 0, ui->boton7);
}

void MainWindow::on_boton8_clicked()
{
    buttonClicked(2, 1, ui->boton8);
}

void MainWindow::on_boton9_clicked()
{
    buttonClicked(2, 2, ui->boton9);
}

void MainWindow::on_pushButton_clicked()
{
    startArrays();
}

