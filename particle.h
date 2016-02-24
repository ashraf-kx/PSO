#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <vector>
using namespace std;

class particle : public QObject
{
    Q_OBJECT
public:
    explicit particle(QObject *parent = 0);

    struct Best{
        vector<double> position;
        vector<double> sol;
        double         cost;
    };

    vector<double> Position;
    double Cost;
    vector<double> Sol;
    vector<double> Velocity;

    Best mBest;
};

#endif // PARTICLE_H
