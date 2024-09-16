#include <bits/stdc++.h>

#include <optional>
using namespace std;
// requirements- create table, drop table, insert row, get row, filter row,delete row
enum DataTypes
{
    NULLOBJ,
    INTEGER,
    DOUBLE,
    STRING
};
class Utility
{
public:
    static string typeName(DataTypes type)
    {
        if (type == DataTypes::INTEGER)
            return "i";
        else if (type == DataTypes::DOUBLE)
            return "d";
        else if (type == DataTypes::STRING)
            return "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE";
        else
            return "NULL";
    }
};
class Record
{
private:
    unordered_map<string, any> data;

public:
    Record()
    {
    }
    Record(unordered_map<string, any> &info)
    {
        data = info;
    }
    unordered_map<string, any> getData()
    {
        return data;
    }
};

class Table
{

private:
    unordered_map<string, DataTypes> schema;
    map<string, Record> data; // custom type primaryIndex
    string primaryIndex;      // name

public:
    Table() {}
    Table(unordered_map<string, DataTypes> &schema, string primaryIndex)
    {
        this->schema = schema;
        this->primaryIndex = primaryIndex;
    }
    // bool addColumn(string name, DataTypes type)
    // {
    //     return false;
    // }
    bool validateRecord(unordered_map<string, any> &record)
    {
        // validation of data types, primary key missing or any other indexed field, repeated primary key
        for (auto x : record)
        {
            if (x.second.type().name() != Utility::typeName(schema[x.first]))
                return false;
        }
        //
        if (record.find(primaryIndex) == record.end())
            return false;
        if (!(data.find(any_cast<string>(record[primaryIndex])) == data.end()))
            return false;
        return true;
    }
    bool addRecord(unordered_map<string, any> record)
    {
        if (validateRecord(record))
        {
            Record newRecord = Record(record);
            data[any_cast<string>((newRecord.getData())[primaryIndex])] = newRecord;
            return true;
        }
        return false;
    }
    optional<Record> fetchRecord(string key) // based on primaryKey
    {
        if (data.find(key) == data.end())
            return nullopt;
        else
            return data[key];
    }
    vector<Record> getRecords(unordered_map<string, any> criteria, unordered_set<string> fields = unordered_set<string>()) // use of primary key
    {
        vector<Record> records;
        // todo:: returning specific fields only
        if (criteria.find(primaryIndex) == criteria.end()) // primarykey present
        {
            optional<Record> record = fetchRecord(any_cast<string>(criteria[primaryIndex]));
            if (record != nullopt)
            {
                records.push_back(record.value());
            }
        }
        else
        {
            // for (auto record : data)
            // {
            //     // record.second is the record
            //     int flag = 0;
            //     for (auto fields : criteria)
            //     {
            //         if (criteria[fields.first] != (record.second).getData()[fields.first])
            //         {
            //             flag = 1;
            //             break;
            //         }
            //     }
            //     if (flag == 0)
            //         records.push_back(record.second);
            // }

            for (auto &record : data)
            {
                bool match = true;
                for (auto field : criteria)
                {
                    // Get the data from the current record
                    unordered_map<string, any> recordData = record.second.getData();

                    // Find the field in the record data
                    auto it = recordData.find(field.first);
                    if (it != recordData.end())
                    {
                        // Compare data types first
                        if (it->second.type() != field.second.type())
                        {
                            match = false; // If types don't match, break
                            break;
                        }

                        // Compare data values based on their type
                        try
                        {
                            // For example, compare if the value is of type string
                            if (it->second.type() == typeid(string))
                            {
                                if (std::any_cast<string>(it->second) != std::any_cast<string>(field.second))
                                {
                                    match = false;
                                    break;
                                }
                            }
                            else if (it->second.type() == typeid(int))
                            {
                                if (std::any_cast<int>(it->second) != std::any_cast<int>(field.second))
                                {
                                    match = false;
                                    break;
                                }
                            }
                            else if (it->second.type() == typeid(double))
                            {
                                if (std::any_cast<double>(it->second) != std::any_cast<double>(field.second))
                                {
                                    match = false;
                                    break;
                                }
                            }
                            // Add other types if necessary
                        }
                        catch (const std::bad_any_cast &)
                        {
                            match = false; // If any_cast fails, break the loop
                            break;
                        }
                    }
                    else
                    {
                        match = false; // Field not found in the record
                        break;
                    }
                }
                if (match)
                {
                    records.push_back(record.second);
                }
            }

            // If all criteria match, add the record to the results
        }
        return records;
    }
};

class DB
{
private:
    unordered_map<string, Table> tables;

public:
    vector<string> getTables()
    {
        vector<string> names;
        for (auto x : tables)
            names.push_back(x.first);
        return names;
    }
    bool createTable(string tableName, unordered_map<string, DataTypes> &schema, string primaryIndex)
    {
        if (schema[primaryIndex] == DataTypes::STRING && tables.find(tableName) == tables.end())
        {
            Table table = Table(schema, primaryIndex);
            tables[tableName] = table;
            return true;
        }
        return false;
    }
    // bool dropTable(string tableName)
    // {
    // }
    // vector<Record> getRecords(string tableName, unordered_map<string, string> query, unordered_set<string> fields = unordered_set<string>())
    // {
    // }
    // bool saveRecords(string tableName, unordered_map<string, string> m)
    // {
    // }
    // bool deleteRecord(string tableName, string primaryId)
    // {
    // }
    // bool createIndex(string tableName, string fieldName)
    // {
    // }
};

int main()
{
    DB db = DB();
    unordered_map<string, DataTypes> schema;
    schema["field1"] = DataTypes::STRING;
    schema["field2"] = DataTypes::INTEGER;
    schema["field3"] = DataTypes::DOUBLE;
    schema["field4"] = DataTypes::STRING;
    cout << db.createTable("customers", schema, "field4") << endl;
    vector<string> names = db.getTables();
    for (auto x : names)
        cout << x << " ";
    cout << endl;
}
