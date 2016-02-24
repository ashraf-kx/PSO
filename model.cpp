#include "model.h"

Model::Model(QObject *parent) :
    QObject(parent)
{
    qDebug()<<"1) => create Model... ";
}

void Model::createModel(){
    // init array x & y.
    init_x();
    init_y();
    // create Matrix D m3amra bel les valeur  Zero
    m=40;
    //d[m][40];
    for(int i=0; i<m; i++){
        for(int j=0;j<m;j++){
            d[i][j]=0;
        }
    }
    // calcul Of D.
    init_mat_d();
    init_n();
    // display in Terminal Values of D.
    /*for(int i=0; i<m; i++){
        for(int j=0;j<m;j++){
            qDebug()<<d[i][j]<<" ";
        }
        qDebug()<<endl;
    }*/
}

// load values of table X[] from a File Named "X_value.txt"
void Model::init_x(){
    ifstream in;     // Create an input file stream.
    in.open("/home/angel/Desktop/PSO/X_value.txt");   // Use it to read from a file named X_value.txt. <OK>
    if ( ! in ) {
        qDebug() << "Error: Can't open the file named .\n";
    }
    string mString;
    QStringList x_value_list;
    while ( in ) {
        getline(in,mString);   // Get the first line from the file, if any Continue if the line was sucessfully read.
        if(mString != "") {
            x_value_list = QString::fromStdString(mString).split(" ");
        }
    }
    // charge to x[40] array
    for(int i=0;i<x_value_list.size();i++){
        x[i] = x_value_list.at(i).toInt();
    }
    // all DONE.
}

// load values of table y[] from a File Named "Y_value.txt"
void Model::init_y(){
    ifstream in;     // Create an input file stream.
    in.open("/home/angel/Desktop/PSO/Y_value.txt");   // Use it to read from a file named Y_value.txt.
    if ( ! in ) {
        qDebug() << "Error: Can't open the file named .\n";

    }
    string mString;
    QStringList y_value_list;
    while ( in ) {
        getline(in,mString);   // Get the first line from the file, if any Continue if the line was sucessfully read.
        if(mString != "") {
            y_value_list = QString::fromStdString(mString).split(" ");
        }
    }
    // charge to y[40] array
    for(int i=0;i<y_value_list.size();i++){
        y[i] = y_value_list.at(i).toInt();
    }
    // all DONE.
}

bool Model::openFile(const char* path){
    w_value.clear(); // clear All Old Content.
    ifstream in;     // Create an input file stream.
    in.open(path);   // Use it to read from a file named data.txt.
    if ( ! in ) {
        qDebug() << "Error: Can't open the file named "<<path<<".\n";
        return false;
    }
    string mString;
    while ( in ) {
        getline(in,mString);   // Get the first line from the file, if any Continue if the line was sucessfully read.
        if(mString != "") w_value.push_back(mString);
    }
    return true;
}

void Model::define_w_Size(){
    //w[][w_value.size()];
}

void Model::init_w(){
    qDebug()<<"Initialization begin ..."<<endl;
    w[20][w_value.size()];  //matrix W taille 20x20
    // get every Line & convert String => float.
    vector<string> tokens;
    for(uint I=0; I<w_value.size();I++){
        tokens.clear();
        Tokenize(w_value.at(I),tokens," "); // split oneLine : whiteSpace delimiter.

        for(uint i=0; i<tokens.size();i++){
            // convert each value To Float
            double val  = strtof(tokens.at(i).c_str(), NULL);
            // Fill matrix2D
            w[i][I] = val;
        }
    }
    // Units 19 and 20, must be as close as possible
    w[19][20]=10000;
    w[20][19]=10000;

    // Units 11 and 16, must be as close as possible
    w[11][16]=20000;
    w[16][11]=20000;

    // Units 1 and 13, must be as far as possible
    w[1][13]=-10000;
    w[13][1]=-10000;
    qDebug()<<"......... Model Created Successfully."<<endl;
}

void Model::Tokenize(const string& str,vector<string>& tokens,const string& delimiters){
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void Model::init_n(){
    n = w_value.size();
}

void Model::init_mat_d(){
    for (int p=0; p<m; p++){
        for (int q=p+1; q<m; q++){
            d[p][q] = sqrt(pow((x[p]-x[q]),2)+pow((y[p]-y[q]),2));
            d[q][p] = d[p][q];
        }
    }
}

Model::~Model(){

}
