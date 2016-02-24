#include "pso.h"

PSO::PSO(QObject *parent) :
    QObject(parent)
{
    uint startTime = QDateTime::currentDateTime().toTime_t();
    mModel = new Model();
    // Problem Definition
    mModel->openFile("/home/angel/Desktop/PSO/W_value.txt");
    mModel->init_w();
    mModel->createModel();

    nVar = mModel->m;     // Number of Decision Variables
    VarSize[0]=1;
    VarSize[1]=nVar;      // Size of Decision Variables Matrix

    VarMin=0.0;             // Lower Bound of Variables
    VarMax=1.0;             // Upper Bound of Variables

    //![2] PSO Parameters
    MaxIt = 1000;         // Maximum Number of Iterations
    nPop  = 80;           // Population Size (Swarm Size)

    //![] PSO Parameters
    w     = 1.0;             // Inertia Weight
    wdamp = 0.99;          // Inertia Weight Damping Ratio
    c1    = 1.5;           // Personal Learning Coefficient
    c2    = 2.0;           // Global Learning Coefficient

    //![4] Velocity Limits
    VelMax = 0.1*(VarMax-VarMin);
    VelMin = -VelMax;

    nParticleMutation   = 1;    // Number of Mutations Performed on Each Particle
    nGlobalBestMutation = 3;    // Number of Mutations Performed on Global Best

    mGlobalBest.cost =  std::numeric_limits<double>::max(); // Inf.

    createParticles(nPop);

    // PSO Main Loop.
    for(uint it=0; it<MaxIt; it++){
        for(uint i=0;i<nPop;i++){

            // Update Velocity.
            vector<double> vectPart_0 = VectorByValue((particles.at(i))->Velocity,w);
            vector<double> RndVector;
            RndVector.clear();
                vector<double> tempVect = VectorByValue(unifrnd(RndVector,nVar,VarMin,VarMax),c1);
            vector<double> vectPart_1 = VectorByVector(tempVect,VectorA_MunisVector_B((particles.at(i))->mBest.position,(particles.at(i))->Position));
                RndVector.clear();
                tempVect = VectorByValue(unifrnd(RndVector,nVar,VarMin,VarMax),c2);
            vector<double> vectPart_2 = VectorByVector(tempVect,VectorA_MunisVector_B(mGlobalBest.position,(particles.at(i))->Position));
            (particles.at(i))->Velocity = VectorPlusVector(VectorPlusVector(vectPart_0,vectPart_1),vectPart_2);

            // Apply Velocity Limits.
            (particles.at(i))->Velocity = VelocityLimits((particles.at(i))->Velocity,VelMin,VelMax);

            // Update Position.
            (particles.at(i))->Position = VectorPlusVector((particles.at(i))->Position,(particles.at(i))->Velocity);

            // Velocity Mirror Effect.  <== Hadhi mat2atharch fel execution , men ba3d nziidhaa.

            // Apply Position Limits.
            (particles.at(i))->Position = PositionLimits((particles.at(i))->Position,VarMin,VarMax);

            // Evaluation.
            evaluation eval = cost((particles.at(i))->Position, mModel->d, mModel->w, mModel->n);
            (particles.at(i))->Cost = eval.cost;
            (particles.at(i))->Sol  = eval.Sol;

            // Perform Mutation.
            for (uint j=1; j<nParticleMutation; j++){

                particle *newParticle = new particle();
                newParticle = particles.at(i);
                newParticle->Position = mutate((particles.at(i))->Position);

                evaluation eval = cost(newParticle->Position, mModel->d, mModel->w, mModel->n); // i kwn where the pbl is.
                newParticle->Cost = eval.cost;
                newParticle->Sol  = eval.Sol;

                if (newParticle->Cost <= (particles.at(i))->Cost)
                    particles.at(i) = newParticle;
            }

            // Update Personal Best.
            if ((particles.at(i))->Cost < (particles.at(i))->mBest.cost){
                (particles.at(i))->mBest.position = (particles.at(i))->Position;
                (particles.at(i))->mBest.cost     = (particles.at(i))->Cost;
                (particles.at(i))->mBest.sol      = (particles.at(i))->Sol;

                // Update Global Best.
                if ( (particles.at(i))->mBest.cost < mGlobalBest.cost ){
                    mGlobalBest.position = (particles.at(i))->mBest.position;
                    mGlobalBest.cost     = (particles.at(i))->mBest.cost;
                    mGlobalBest.sol      = (particles.at(i))->mBest.sol;
                }
            }


        }

        // Perform Mutation on Global Best.
        for( uint i=1; i<nGlobalBestMutation; i++){
            particle *newParticle = new particle();
            newParticle->mBest =  mGlobalBest;
            newParticle->Position = mutate(mGlobalBest.position);

            evaluation eval = cost(newParticle->Position, mModel->d, mModel->w, mModel->n);
            newParticle->Cost = eval.cost;
            newParticle->Sol  = eval.Sol;

            if (newParticle->Cost <= mGlobalBest.cost)
                mGlobalBest = newParticle->mBest;
        }
        w = w*wdamp;
        xData<< it;
        yData<< mGlobalBest.cost;
        // Display each time the Best Cost.
        qDebug()<<"iteration ( "<<it<<" ) "<<" Best Cost : ( "<<mGlobalBest.cost<<" )";
    }

    uint endTime  = QDateTime::currentDateTime().toTime_t();
    executionTime = endTime - startTime;


}

void PSO::createParticles(uint nPop){
    qDebug()<<"creating particles .....";
    // Create nPop particles.
    for(uint i=0; i< nPop;i++){
        // create Empty particle.
        mParticle = new particle();

        // Initialize Position For One Particle.
        mParticle->Position = unifrnd(tempPosition,nVar, VarMin, VarMax);

        // Initialize Velocity
        vector<double> velocity(nVar);
        mParticle->Velocity = velocity;

        // Evaluation.
        evaluation eval = cost(mParticle->Position, mModel->d, mModel->w, mModel->n);  // create a structure evaluation .

        // Update Personal(or local) Best .
        mParticle->mBest.position = mParticle->Position;
        mParticle->mBest.sol      = eval.Sol;
        mParticle->mBest.cost     = eval.cost;

        // Update Global Best
        if(mParticle->mBest.cost < mGlobalBest.cost)
            mGlobalBest.position = mParticle->mBest.position;
            mGlobalBest.cost     = mParticle->mBest.cost;
            mGlobalBest.sol      = mParticle->mBest.sol;

        // Add The New particle To Swarm.
        particles.push_back(mParticle);
    }
    qDebug()<<"... particles Created successfully.";
}

vector<double> PSO::unifrnd(vector<double> position, uint varSize, double varMin, double varMax)
{
    position.clear();
    for(uint i=0;i<varSize;i++){
        double f = (double)rand() / RAND_MAX;
        position.push_back(varMin + f * (varMax - varMin));
    }
    return position;
}

vector<double> PSO::mutate(vector<double> x)
{
    uint size = x.size();
    vector<double> y;
    y.clear();
    if(size >= 2){
    // get Two Random numbers From intervall [1 ... sizes].
    int i1 = 1 + ((double)rand() / RAND_MAX) * (size - 1); // drow one number aleatoire from  1..n.
    int i2 = 1 + ((double)rand() / RAND_MAX) * (size - 1); // draw 2nd .
    // copy x TO y.
    y = x;
    // Now mutate in Y.
    swap(y.at(i1),y.at(i2));
    }else qDebug()<<"size smaller than 2 in PSO::mutate()";
    return y;
}

PSO::evaluation PSO::cost(vector<double> position, double mat_d[][40], double mat_W[][20], int nbr_row_w)
{
    // first, copy vector to new one with a structure .
    vector<double> p;
    p.clear();
    mPosition tempPostion;
    vector<mPosition> mList;
        for(uint i =0;i<position.size();i++){
            tempPostion.indice = i;
            tempPostion.value = position.at(i);
            mList.push_back(tempPostion);
        }

    // Sort Postion Vector for one Particle ascendanly.
    mList = sortVector(mList);  // Sort the mList Ascendanly.
    sort(position.begin(), position.end(), greater<double>());  // Sort the position Vector TWO. LOL
    // Get p : The vector of indices after the SORT() operation. notice Take Only n Elt NOW.

    for(int i=0; i<nbr_row_w; i++){
        p.push_back(mList.at(i).indice);
    }
    //  calcule cost .
    double z=0;
    for(int i=1; i<nbr_row_w; i++){
        for(int j=i+1; j<nbr_row_w; j++){
            z += mat_W[i][j]*mat_d[(int)p.at(i)][(int)p.at(j)];
        }
    }
    evaluation output;
    output.Sol  = p;
    output.cost = z;
    // Function Cost 2D DONE. 01:53*2016/02/14.
    return output;
}

int PSO::getMin(vector<mPosition> mVector,uint begin,uint end){
    double min  = (mVector.at(begin)).value;
    int ind_min = begin;

    for(uint i=begin; i<end; i++){
        if(min>(mVector.at(i)).value){
            ind_min = i;
            min = (mVector.at(i)).value;
        }
    }
    return ind_min;
}

vector<PSO::mPosition> PSO::sortVector(vector<mPosition> mVector){
    // get Vector Size.
    int num_elt = mVector.size();
    int  ind_min;
    for(int i=0; i<num_elt; i++){
        ind_min = getMin(mVector,i,num_elt);
        if(i != ind_min)
            swap(mVector.at(i),mVector.at(ind_min));
    }
    return mVector;
}

vector<double> PSO::VectorByValue(vector<double> Velocity,double w){
    uint size = Velocity.size();
    for(uint i=0; i<size; i++){
        Velocity.at(i) = w*Velocity.at(i);
    }
    return Velocity;
}

vector<double> PSO::VectorA_MunisVector_B(vector<double> mVectorA,vector<double> mVectorB){
    vector<double> Vector;
    Vector.clear();

    if(mVectorA.size() == mVectorB.size()){ // just in Case Show Error.
        for (uint i = 0; i < mVectorA.size(); ++i) {
            Vector.push_back(mVectorA.at(i)-mVectorB.at(i));
        }
    }
    return Vector;
}

vector<double> PSO::VectorByVector(vector<double> mVectorA,vector<double> mVectorB){
    vector<double> Vector;
    Vector.clear();

    if(mVectorA.size() == mVectorB.size()){ // just in Case Show Error.
        for (uint i = 0; i < mVectorA.size(); ++i) {
            Vector.push_back(mVectorA.at(i)*mVectorB.at(i));
        }
    }
    return Vector;
}

vector<double> PSO::VectorPlusVector(vector<double> mVectorA,vector<double> mVectorB){
    vector<double> Vector;
    Vector.clear();

    if(mVectorA.size() == mVectorB.size()){ // just in Case Show Error.
        for (uint i = 0; i < mVectorA.size(); ++i) {
            Vector.push_back(mVectorA.at(i)+mVectorB.at(i));
        }
    }
    return Vector;
}

vector<double> PSO::VelocityLimits(vector<double> Vector,double min,double max){

    for(uint i=0; i<Vector.size();i++){
        if(Vector.at(i)>max) Vector.at(i) = max;
        if(Vector.at(i)<min) Vector.at(i) = min;
    }
    return Vector;
}

vector<double> PSO::PositionLimits(vector<double> Vector,double min,double max){

    for(uint i=0; i<Vector.size();i++){
        if(Vector.at(i)>max) Vector.at(i) = max;
        if(Vector.at(i)<min) Vector.at(i) = min;
    }
    return Vector;
}
