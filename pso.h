#ifndef PSO_H
#define PSO_H

#include <QObject>
#include "model.h"
#include <vector>
#include "particle.h"
#include <stdlib.h>
#include <limits>
#include <QDateTime>

using namespace std;

class PSO : public QObject
{
    Q_OBJECT
public:
    // help : to Sort Postion Vector & get the indices array.
    struct mPosition {
        int    indice;
        double value;
    };

    struct evaluation {
        vector<double> Sol;
        double cost;
    };

    //! [1] Problem Definition
    Model *mModel;
    uint nVar;        // Number of Decision Variables
    int VarSize[2]; // Size of Decision Variables Matrix
    double VarMin;         // Lower Bound of Variables
    double VarMax;        // Upper Bound of Variables

    //! [2] PSO Parameters
    uint MaxIt;        // Maximum Number of Iterations
    uint nPop;        // Population Size (Swarm Size)
    double w;                  // Inertia Weight
    double wdamp;          // Inertia Weight Damping Ratio
    double c1;            // Personal Learning Coefficient
    double c2;           // Global Learning Coefficient

    /* If you would like to use Constriction Coefficients for PSO,
     uncomment the following block and comment the above set of parameters. */

    //! [3] Constriction Coefficients
    // double phi1=2.05;
    // double phi2=2.05;
    // double phi=phi1+phi2;
    // double chi=2/(phi-2+sqrt(phi^2-4*phi));
    // double w=chi;          //Inertia Weight
    // double wdamp=1;        // Inertia Weight Damping Ratio
    // double c1=chi*phi1;    // Personal Learning Coefficient
    // double c2=chi*phi2;    // Global Learning Coefficient

    //! [4] Velocity Limits
    double VelMax;
    double VelMin;

    uint nParticleMutation;      // Number of Mutations Performed on Each Particle
    uint nGlobalBestMutation;   // Number of Mutations Performed on Global Best

    QVector<double> xData;
    QVector<double> yData;

    //! [5] Initialization
    vector<particle*> particles;
    particle *mParticle;
    vector<double> tempPosition;
    particle::Best mGlobalBest;
    uint executionTime;

    explicit PSO(QObject *parent = 0);

    vector<double> unifrnd(vector<double> position,uint varSize,double varMin, double varMax);
    vector<double> mutate(vector<double> x);
    evaluation cost(vector<double> position,double mat_d[][40],double mat_W[][20], int nbr_row_w);
    int  getMin(vector<mPosition> mVector, uint begin, uint end);
    vector<PSO::mPosition> sortVector(vector<mPosition> mVector);
    void createParticles(uint nPop);
    vector<double> VectorByValue(vector<double> Velocity, double w);
    vector<double> VectorA_MunisVector_B(vector<double> mVectorA, vector<double> mVectorB);
    vector<double> VectorByVector(vector<double> mVectorA, vector<double> mVectorB);
    vector<double> VectorPlusVector(vector<double> mVectorA, vector<double> mVectorB);
    vector<double> VelocityLimits(vector<double> Vector, double min, double max);
    vector<double> PositionLimits(vector<double> Vector, double min, double max);
};

#endif // PSO_H
