/*
Adapter Design Pattern:
Adapter converts the interface of a class into another interface
that client expects. Adapter lets clients work together
that couldn't otherwise because of incompatible interface.


Real World Examples:
1. If there are any 3rd party libraries that converts the data.
*/

#include <bits/stdc++.h>
using namespace std;

class XMLDataProvider
{
public:
    string getXMLData(string data)
    {
        cout << "Current data:" << data << endl;
        cout << "Now the data is converted to XML Data" << endl;
        return data + "(XML)";
    }
};

// This report is mean to convert to JSON data.
class Converter
{
public:
    virtual string getConvertedData(string data) = 0;
    virtual ~Converter() {};
};

class XMLtoJsonConverter : public Converter
{
    XMLDataProvider *xmlprovider;

public:
    XMLtoJsonConverter(XMLDataProvider *provider) : xmlprovider(provider) {};
    string getConvertedData(string data) override
    {
        string xmlData = xmlprovider->getXMLData(data);
        cout << "The XML data is now converting to JSON Format" << endl;
        string jsonData = xmlData + "(converted to JSON)";
        return jsonData;
    }
};

class Client
{
public:
    void getReport(Converter *conv, string rawData)
    {
        string newData = conv->getConvertedData(rawData);
        cout << "Client Returns: " << newData << endl;
        return;
    }
};

int main()
{

    XMLDataProvider *xmlDataprov = new XMLDataProvider();
    Converter *jsonConv = new XMLtoJsonConverter(xmlDataprov);
    Client *cli = new Client();
    string rawData = "Bindu Satya in str format";
    cli->getReport(jsonConv, rawData);

    delete xmlDataprov;
    delete cli;
    delete jsonConv;
    return 0;
}