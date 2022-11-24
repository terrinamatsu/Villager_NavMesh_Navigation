#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Setup NGLScene Widget
  m_gl = new NGLScene(this);
  ui->m_mainWindowGridLayout->addWidget(m_gl);

  // Connect signals & slots
  connect(ui->m_numVillagersSlider, SIGNAL(valueChanged(int)), m_gl, SLOT(changeNumVillagers(int)));
  connect(ui->m_gameSpeedSlider, SIGNAL(valueChanged(int)), m_gl, SLOT(changeGameSpeed(int)));
}

MainWindow::~MainWindow()
{
  delete ui;
}

