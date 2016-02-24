#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <vector>
#include <stdlib.h>
#include <list>
#include <iostream>
#include <fstream>
#include <istream>
#include <math.h>
#include <qdebug.h>
#include <QStringList>
using namespace std;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);

public:
        void createModel();
        bool openFile(const char* path);
        void init_w();
        void init_n();
        void init_mat_d();
        void Tokenize(const string& str,vector<string>& tokens,const string& delimiters);
        void define_w_Size();
        void init_x(); // declaration des prototype des methode fel Header <Metfahmiin>
        void init_y();
        virtual ~Model();

    double w[20][20];       // matrix2D w.
    double d[40][40];         // matrix2D d.
    int n;                // n = number of ROWs in w. 20
    int m;               // m = taille de vector X,Y.

    vector<string> w_value;

    int x[40];
    int y[40];

};

#endif // MODEL_H
