#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <sonic/sonic.h>
#include "nanobench.h"
using namespace std;

#include "nlohmann/json.hpp"
using json_nl = nlohmann::json;

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "json/json.h"
using Value = Json::Value;
using Reader = Json::Reader;

#include "ejson/parser.h"

// Paths for adjusting test and validation files
#define BASE_DIR "../../"

// To output to the valid.json file for easy verification of correct parsing
void outPutValidJson(std::string const & src)
{
    auto ofs = ofstream(BASE_DIR "valid.json");
    ofs << src;
}

std::string getSourceString()
{
    if (auto ifs = ifstream(BASE_DIR "test.json"))
    {
        return string{istreambuf_iterator<char>(ifs), istreambuf_iterator<char>()};
    }
    return {};
}

void benchSomething(const char * description, const std::function<void()> & func, int times = 100)
{
    ankerl::nanobench::Bench().minEpochIterations(times).run(description, func);
}

#define PARSE(v1) "Parse:" #v1
#define STRING(v1) "Stringify:" #v1
#define FIND(v1) "FindMember:" #v1

const char * s_json_key = "editor.suggest.showMethods";

TEST(Bench, Json)
{
    json_nl json;
    Value j;
    Reader r;
    rapidjson::Document json_doc;
    sonic_json::Document sonic_json_doc;
    ejson::JObject ejson;
    // bench json parse
    auto data = getSourceString();
    ejson = std::move(ejson::Parser::FromJSON(data));
    {
        benchSomething(PARSE(nlohmann), [&]() { json = std::move(json_nl::parse(data)); });
        benchSomething(PARSE(jsoncpp), [&]() { r.parse(data, j); });
        benchSomething(PARSE(rapid_json), [&]() { json_doc.Parse(data.c_str()); });
        benchSomething(PARSE(sonic_json), [&]() { sonic_json_doc.Parse(data); });
        benchSomething(PARSE(ejson), [&]() { ejson = std::move(ejson::Parser::FromJSON(data)); });
    }
    // bench json stringify
    {
        string out;
        benchSomething(STRING(nlohmann), [&]() { out = std::move(json.dump()); });
        benchSomething(
            STRING(jsoncpp),
            [&]()
            {
                Json::FastWriter writer;
                writer.omitEndingLineFeed();
                out = std::move(writer.write(j));
            });
        benchSomething(
            STRING(rapid_json),
            [&]()
            {
                rapidjson::StringBuffer buffer;
                auto writer = rapidjson::Writer(buffer);
                json_doc.Accept(writer);
                EXPECT_TRUE(buffer.GetLength() > 72000);
            });
        benchSomething(
            STRING(sonic_json),
            [&]()
            {
                sonic_json::WriteBuffer wb;
                sonic_json_doc.Serialize(wb);
                EXPECT_TRUE(wb.Size() > 72000);
            });
        benchSomething(STRING(ejson), [&]() { out = std::move(ejson.to_string(2)); });
        outPutValidJson(out);
    }
    // bench find member
    {
        benchSomething(
            FIND(nlohmann),
            [&]()
            {
                auto it = json.find(s_json_key);
                EXPECT_TRUE(it != json.end());
            });
        benchSomething(
            FIND(jsoncpp),
            [&]()
            {
                auto value = j.find(s_json_key);
                EXPECT_NE(value, nullptr);
            });
        benchSomething(
            FIND(rapid_json),
            [&]()
            {
                auto status = json_doc.HasMember(s_json_key);
                EXPECT_TRUE(status);
            });
        benchSomething(
            FIND(sonic_json),
            [&]()
            {
                auto status = sonic_json_doc.HasMember(s_json_key);
                EXPECT_TRUE(status);
            });
        benchSomething(
            FIND(ejson),
            [&]()
            {
                auto status = ejson.has_key(s_json_key);
                EXPECT_TRUE(status);
            });
    }
}
