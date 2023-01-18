#include "nanobench.h"
#include "gtest/gtest.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
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

// 用于调整测试和验证文件的路径
#define BASE_DIR "../../"

// 输出到valid.json文件方便查看验证是否解析正确
void outPutValidJson(std::string const &src) {
  auto ofs = ofstream(BASE_DIR "valid.json");
  ofs << src;
}

// 获取用于测试的json数据
std::string getSourceString() {
  auto ifs = ifstream(BASE_DIR "test.json");
  if (ifs) {
    return string{istreambuf_iterator<char>(ifs), istreambuf_iterator<char>()};
  }
  return {};
}

void benchSomething(const char *description, const std::function<void()> &func,
                    int times = 100) {
  ankerl::nanobench::Bench().minEpochIterations(times).run(description, func);
}

#define PARSER(v1) "Parse:" #v1
#define STRING(v1) "Stringify:" #v1

TEST(bench, json) {
  // get src string
  auto data = getSourceString();

  {
    json_nl json;
    benchSomething(PARSER(nlohmann),
                   [&]() { json = std::move(json_nl::parse(data)); });
    string out;
    benchSomething(STRING(nlohmann), [&]() { out = std::move(json.dump()); });
    outPutValidJson(out);
  }

  {
    Value j;
    Reader r;
    benchSomething(PARSER(jsoncpp), [&]() { r.parse(data, j); });
    string out;
    benchSomething(STRING(jsoncpp),
                   [&]() { out = std::move(j.toStyledString()); });
    outPutValidJson(out);
  }
  bool status{};

  {
    rapidjson::Document json;
    benchSomething(PARSER(rapid_json), [&]() { json.Parse(data.c_str()); });
    string out;

    benchSomething(STRING(rapid_json), [&]() {
      rapidjson::StringBuffer buffer;
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      json.Accept(writer);
      out = buffer.GetString();
    });

    ankerl::nanobench::doNotOptimizeAway(status);
    benchSomething("FindMember:rapid_json", [&]() {
      status = json.HasMember("editor.suggest.showMethods");
    });
    outPutValidJson(out);
  }
  EXPECT_EQ(status, true);

  status = false;

  {
    ankerl::nanobench::doNotOptimizeAway(status);
    ejson::JObject json;
    benchSomething(PARSER(ejson),
                   [&]() { json = ejson::Parser::FromJSON(data); });
    string out;
    benchSomething(STRING(ejson), [&]() { out = std::move(json.to_string()); });
    benchSomething("FindMember:ejson", [&]() {
      status = json.at("editor.suggest.showMethods").ref.type() != ejson::kNull;
    });
    outPutValidJson(out);
  }
  EXPECT_EQ(status, true);
}