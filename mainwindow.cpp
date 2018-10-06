#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot1();
    MainWindow::makePlot2();

    ObiektRegulacji = new ObiektDyskretny;
    ObiektRegulacji->attach(this);

    id=new Identyfikacja(1, 2, 1, 0.99, 1000, 100000, startowyFi);
    wczytajGPC();
    wczytajObiekt();
    GeneratorStalej* temp1 =new GeneratorStalej(ui->stala_wzmocnienie->value());
    Regulator->stworzGenerator(temp1);
    ObiektRegulacji->attach(Regulator);
    petla=new PetlaSterowania(ObiektRegulacji,Regulator,id);
    connect(&timer, SIGNAL(timeout()),this,SLOT(addData()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ObiektRegulacji;
    delete Regulator;
    delete petla;
}

void MainWindow::makePlot1(){
    ui->plot1->addGraph();
    ui->plot1->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->plot1->addGraph();
    ui->plot1->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    ui->plot1->axisRect()->setupFullAxesBox();
    ui->plot1->xAxis->setLabel("i");
    ui->plot1->yAxis->setLabel("y(i)");
    ui->plot1->yAxis->grid();

    connect(ui->plot1->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot1->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot1->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot1->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::makePlot2(){
    ui->plot2->addGraph();
    ui->plot2->graph(0)->setPen(QPen(QColor(0, 128, 0)));
    ui->plot2->axisRect()->setupFullAxesBox();
    ui->plot2->xAxis->setLabel("i");
    ui->plot2->yAxis->setLabel("u(i)");
    connect(ui->plot2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot2->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::blad(std::string blad)
{
    ui->blad->setText(QString::fromStdString(blad));
}

void MainWindow::addData()
{
    static int i = 0;
    petla->krokPetli();

    vec_i.append(i);

    if(stac>0 && vec_i.last()==stac)
        ObiektRegulacji->zmienObiekt();

    if(i>70)
    {
        ui->plot1->xAxis->setRange(i+0.25, 70, Qt::AlignRight);
        ui->plot2->xAxis->setRange(i+0.25, 70, Qt::AlignRight);
    }
    else
    {
        ui->plot1->xAxis->setRange(0, 70);
        ui->plot2->xAxis->setRange(0, 70);
    }

    ui->plot1->graph(0)->addData(vec_i.last(), vec_y.last());
    ui->plot1->graph(1)->addData(vec_i.last(), vec_w.last());
    ui->plot2->graph(0)->addData(vec_i.last(), vec_u.last());

    replot();
    i++;



}

void MainWindow::update(double wy )
{
    vec_y.push_back(wy);
    static int i =0;
    vec_w.push_back(petla->odczytWartZad());
    vec_u.push_back(petla->odczytSterowania());
    i++;
}
void MainWindow::replot()
{
   ui->plot1->yAxis->rescale(true);
   ui->plot2->graph(0)->rescaleValueAxis();
   ui->plot1->replot();
   ui->plot2->replot();
}

void MainWindow::updateParam(std::vector<double> A, std::vector<double> B, double k, double war, int dA, int dB)
{
    ui->listWidget->clear();
    ui->listWidgetB->clear();

    ui->k->setValue(k);
    ui->dB->setValue(dB+1);
    ui->dA->setValue(dA);
    ui->alfa->setValue(war);
    ui->czasprzelaczenia->setValue(stac);

    for (auto i = A.begin(); i != A.end(); ++i)
    {
        QString valueAsString = QString::number(*i);
        ui->listWidget->addItem(valueAsString);
    }

    for (auto i = B.begin(); i != B.end(); ++i)
    {
        QString valueAsString = QString::number(*i);
        ui->listWidgetB->addItem(valueAsString);
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    speedValue = value;
    ui->label_2->setNum(speedValue);
    timer.setInterval(speedValue);

}

void MainWindow::on_startButton_clicked()
{
    if(ui->startButton->isChecked()){
        ui->startButton->setText("Stop");
        timer.start(speedValue);
    } else {
        ui->startButton->setText("Start");
        timer.stop();
    }
}

void MainWindow::wczytajObiekt()
{
    std::vector<double> AVector, BVector, AVector_2, BVector_2;
    double k, war;

    try{
        boost::property_tree::ptree old_tree;
        boost::property_tree::read_json("../test1/konfiguracja.json", old_tree);

        try{
           k = old_tree.get<double>("k");
           if(k<1){
               k=1;
               blad("Nieprawidłowa wartość k!");
           }
        }
        catch(std::exception const& e)
        {
            blad(e.what());
        }

        try{
           war = old_tree.get<double>("wariancja");
           if(war<0)
           {
               war=0;
               blad("Wariancja < 0!");
           }
        }
        catch(std::exception const& e)
        {
            blad(e.what());
        }


        stac = old_tree.get<int>("stac");

        if(stac <= 0)
        {
            BOOST_FOREACH(boost::property_tree::ptree::value_type &obj, old_tree.get_child("obiekty"))
            {
                unsigned long objID = obj.second.get<unsigned long>("id");
                if(objID==1)
                {
                    BOOST_FOREACH( boost::property_tree::ptree::value_type &param, obj.second.get_child( "a" ) )
                            {
                                AVector.push_back(param.second.get_value<double>());
                            };

                    BOOST_FOREACH( boost::property_tree::ptree::value_type &param, obj.second.get_child( "b" ) )
                            {
                                BVector.push_back(param.second.get_value<double>());
                            };
                 }
             }
        } else
        {
            BOOST_FOREACH(boost::property_tree::ptree::value_type &obj, old_tree.get_child( "obiekty"))
            {
                unsigned long objID = obj.second.get<unsigned long>("id");
                    BOOST_FOREACH( boost::property_tree::ptree::value_type &param, obj.second.get_child( "a" ) )
                            {
                                if(objID==1)
                                    AVector.push_back(param.second.get_value<double>());
                                else if(objID==2)
                                    AVector_2.push_back(param.second.get_value<double>());
                            };

                    BOOST_FOREACH( boost::property_tree::ptree::value_type &param, obj.second.get_child( "b" ) )
                            {
                                if(objID==1)
                                    BVector.push_back(param.second.get_value<double>());
                                else if(objID==2)
                                    BVector_2.push_back(param.second.get_value<double>());

                            };

             }
            ObiektRegulacji->dodajWektor(AVector_2,BVector_2);
        }
        ObiektRegulacji->ustawParam(AVector, BVector, k, war);

    }
    catch(std::exception const& e)
    {
        blad(e.what());
    }
}

void MainWindow::on_ZapiszY_clicked()
{
     boost::property_tree::ptree tree;
     boost::property_tree::ptree yElement;
     boost::property_tree::ptree yChild;
     boost::property_tree::ptree uElement;
     boost::property_tree::ptree uChild;
     for( QVector<double>::iterator it = vec_y.begin(); it != vec_y.end(); it++)
     {
         yElement.put_value(*it);
         yChild.push_back(std::make_pair("",yElement));
     }
     for( QVector<double>::iterator it = vec_u.begin(); it != vec_u.end(); it++)
     {
         uElement.put_value(*it);
         uChild.push_back(std::make_pair("",uElement));
     }
      tree.add_child("y",yChild);
      tree.add_child("u",uChild);

      try{
          boost::property_tree::write_json("../test1/stan.json", tree);
      }
      catch(std::exception const& e)
      {
          blad(e.what());
      }
}

void MainWindow::on_WczytajPlik_clicked()
{
    wczytajObiekt();
}

void MainWindow::ustawRegulator(regulator *r)
{
    ObiektRegulacji->detach(Regulator);
    delete Regulator;
    Regulator=r;
    ObiektRegulacji->attach(r);
    petla->ustawRegulator(r);
    GeneratorPodstawowy* gen = new GeneratorStalej(0);
    r->stworzGenerator(gen);
    pobierzGenerator();
}

void MainWindow::pobierzGenerator(){
    GeneratorPodstawowy* gen = new GeneratorStalej(0);

    if(ui->stala->isChecked())
    {
        delete gen;
        gen = new GeneratorStalej(ui->stala_wzmocnienie->value());
    }
    if(ui->impuls->isChecked())
    {
        gen = new ImpulsDekorator(gen, ui->impuls_skok->value());
    }
    if(ui->sinus->isChecked())
    {
        gen = new SinusDekorator(ui->sinus_amplituda->value(), ui->sinus_okres->value(), gen);
    }
    if(ui->trojkat->isChecked())
    {
        gen = new TrojkatDekorator(ui->trojkat_amplituda->value(), ui->trojkat_okres->value(), gen);
    }
    if(ui->szum->isChecked())
    {
        gen = new SzumDekorator(ui->szum_wariancja->value(), gen);
    }

    if(ui->prostokat->isChecked())
    {
        gen = new ProstokatDekorator(ui->pr_amplituda->value(), ui->pr_okres->value(), ui->pr_wypelnienie->value(), gen);
    }
        petla->zmienGenerator(gen);
}
void MainWindow::on_pushButton_clicked()
{
    pobierzGenerator();

    boost::property_tree::ptree tree1;

    tree1.put("stała.wzmocnienie", ui->stala_wzmocnienie->value());
    tree1.put("impuls.skok", ui->impuls_skok->value());
    tree1.put("sinus.amplituda", ui->sinus_amplituda->value());
    tree1.put("sinus.okres", ui->sinus_okres->value());
    tree1.put("trójkąt.amplituda", ui->trojkat_amplituda->value());
    tree1.put("trójkąt.okres", ui->trojkat_okres->value());
    tree1.put("szum.wariancja", ui->szum_wariancja->value());
    tree1.put("prostokąt.amplituda", ui->pr_amplituda->value());
    tree1.put("prostokąt.okres", ui->pr_okres->value());
    tree1.put("prostokąt.wypełnienie", ui->pr_wypelnienie->value());
    boost::property_tree::write_json("../test1/generator.json", tree1);
}

void MainWindow::zapiszRegP(){
    boost::property_tree::ptree tree1;
    tree1.put("regulator", "P");
    tree1.put("k", ui->kP->value());
    boost::property_tree::write_json("../test1/regulator.json", tree1);
}

void MainWindow::zapiszRegPID(){
    boost::property_tree::ptree tree1;
    tree1.put("regulator", "PID");
    tree1.put("k", ui->kPID->value());
    tree1.put("Ti", ui->tiPID->value());
    tree1.put("Td", ui->tdPID->value());
    tree1.put("N", ui->nPID->value());
    tree1.put("B", ui->bPID->value());
    tree1.put("Tp", ui->tpPID->value());
    boost::property_tree::write_json("../test1/regulator.json", tree1);
}
void MainWindow::on_zastosujP_clicked()
{

    if(ui->checkBoxP->isChecked())
    {
        Regulator->zmianaNastaw(ui->kP->value());
        zapiszRegP();
        rodzajReg=false;
    }
    else if(ui->checkBoxPID->isChecked())
    {
        zapiszRegPID();
        rodzajReg=false;
    }
    else if(ui->checkBoxGPC->isChecked())
    {
        zapiszRegPID();
        rodzajReg=true;
    }
    regulator* temp;
        try{
            temp = regulator::odczyt_ustawien(rodzajReg);
        }
        catch(std::string e)
        {blad(e);}
        ustawRegulator(temp);

}

void MainWindow::wczytajGPC(){
    boost::property_tree::ptree GPCtree;
    boost::property_tree::read_json("../test1/regulatorGPC.json", GPCtree);
    Regulator = new RegulatorGPC(GPCtree.get<double>("H"),GPCtree.get<double>("L"),GPCtree.get<double>("a"),GPCtree.get<double>("p"),GPCtree.get<double>("k"),GPCtree.get<double>("stA"), GPCtree.get<double>("stB"), id );

}

void MainWindow::on_odczytajGPC_clicked()
{


}
