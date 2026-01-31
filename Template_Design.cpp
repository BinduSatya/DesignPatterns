/*
Template Design:
This Design Pattern is used to design the skeleton of the algorithm,
for an operation deferring some steps to subclasses. Template method
let subclasses redefine certain steps of an algorithm without changing
the algorithm structure.

- It is used to make a fix order of execution of steps as a template.
- Implementation may change, but not the order
- 
*/

#include <bits/stdc++.h>
using namespace std;

class ModelTrainer
{
public:
    void TrainPipeline(const string dataPath)
    {
        loadData(dataPath);
        preprocessData();
        trainModel();
        evaluateModel();
        saveModel();
    }

protected:
    void loadData(const string &path)
    {
        cout << "[Common] Loading dataset from path " << path << endl;
    }

    virtual void preprocessData()
    {
        cout << "[Common] Splitting Data into Training, Testing and Normalizing" << endl;
    }

    virtual void trainModel() = 0;
    virtual void evaluateModel() = 0;

    virtual void saveModel()
    {
        cout << "[Common] Saving Model to disk as default Format" << endl;
    }
};

class NeuralNetworkTrainer : public ModelTrainer
{
protected:
    void trainModel() override
    {
        cout << "Training the Neural Network Model..." << endl;
    }

    void evaluateModel() override
    {
        cout << "Evaluating the Neural Network Model..." << endl;
    }

    void saveModel() override
    {
        cout << "Saving Neural Network Model to disk..." << endl;
    }
};

class DecisionTreeTrainer : public ModelTrainer
{
protected:
    void trainModel() override
    {
        cout << "Training the Decision Tree Model..." << endl;
    }

    void evaluateModel() override
    {
        cout << "Evaluating the Decision Tree Model..." << endl;
    }
};

int main()
{
    cout << "--------Neural Network Model is being Trained--------" << endl;
    ModelTrainer *neuralNetwork = new NeuralNetworkTrainer();
    neuralNetwork->TrainPipeline("C:BinduSatya/Works/neuralData");

    cout << "--------Decision Tree Model is being Trained--------" << endl;
    ModelTrainer *decisionTree = new DecisionTreeTrainer();
    decisionTree->TrainPipeline("C:BinduSatya/Works/DecisionTree");
}