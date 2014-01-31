#include "dialogaddnode.h"
#include "ui_dialogaddnode.h"
#include <iostream>

using namespace std;

DialogAddNode::DialogAddNode(QStringList* parentList, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddNode)
{
    nodeNameList = new QStringList;
    nodeNameList->append("Project");
    nodeNameList->append("Domain");
    nodeNameList->append("Mesh");
    nodeNameList->append("Prescription");
    nodeNameList->append("Material");
    nodeNameList->append("Field");
    nodeNameList->append("Function");

    nodeNameList->append("verbose");
    nodeNameList->append("output");
    nodeNameList->append("save");
    nodeNameList->append("plot");
    nodeNameList->append("bc");
    nodeNameList->append("bf");
    nodeNameList->append("sf");
    nodeNameList->append("init");
    nodeNameList->append("max_time");
    nodeNameList->append("nb_steps");
    nodeNameList->append("nb_iter");
    nodeNameList->append("tolerance");
    nodeNameList->append("integer");
    nodeNameList->append("double");
    nodeNameList->append("complex");
    nodeNameList->append("mesh_file");
    nodeNameList->append("init_file");
    nodeNameList->append("restart_file");
    nodeNameList->append("bc_file");
    nodeNameList->append("bf_file");
    nodeNameList->append("sf_file");
    nodeNameList->append("save_file");
    nodeNameList->append("plot_file");
    nodeNameList->append("data_file");
    nodeNameList->append("aux_file");
    nodeNameList->append("parameter");

    nodeNameList->append("vertex");
    nodeNameList->append("line");
    nodeNameList->append("circle");
    nodeNameList->append("subdomain");

    nodeNameList->append("Nodes");
    nodeNameList->append("Elements");
    nodeNameList->append("Sides");

    nodeNameList->append("Variable");
    nodeNameList->append("Data");

    nodeNameList->append("BoundaryCondition");
    nodeNameList->append("BodyForce");
    nodeNameList->append("Source");
    nodeNameList->append("BoundaryForce");
    nodeNameList->append("Traction");
    nodeNameList->append("Flux");
    nodeNameList->append("Initial");

    nodeNameList->append("Density");
    nodeNameList->append("SpecificHeat");
    nodeNameList->append("ThermalConductivity");
    nodeNameList->append("MeltingTemperature");
    nodeNameList->append("EvaporationTemperature");
    nodeNameList->append("ThermalExpansion");
    nodeNameList->append("LatentHeatMelting");
    nodeNameList->append("LatentHeatEvaporation");
    nodeNameList->append("ElectricConductivity");
    nodeNameList->append("ElectricResistivity");
    nodeNameList->append("MagneticPermeability");
    nodeNameList->append("Viscosity");
    nodeNameList->append("YoungModulus");
    nodeNameList->append("PoissonRation");

    nodeNameList->sort();

    ui->setupUi(this);
    ui->parentList->addItems(*parentList);
    ui->parentList->setFixedWidth(100);
    ui->tagList->addItems(*nodeNameList);
    ui->tagList->setFixedWidth(100);

    this->parent = parent;

    QObject::connect(ui->btnAddNode, SIGNAL(clicked()), this, SLOT(addNode()));
    QObject::connect(ui->btnAddNode, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

DialogAddNode::~DialogAddNode()
{
    delete ui;
}

void DialogAddNode::addNode()
{
    parent->addNode(ui->parentList->currentText(), ui->tagList->currentText(), ui->textNode->text());
}
