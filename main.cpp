#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace web::http::client;

class ContentAnalyzer {
private:
    std::map<std::string, double> weights = {
        {"engagement", 2.0},
        {"accessibility", 1.5},
        {"visual_design", 1.5},
        {"content_depth", 2.0},
        {"innovation", 1.0},
        {"performance", 1.0},
        {"user_feedback", 1.0},
        {"scalability", 1.0}
    };

    std::string formatDouble(double value, int precision = 1) {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(precision) << value;
        return stream.str();
    }

public:
    std::map<std::string, double> analyzeContent(const std::string& content) {
        return {
            {"engagement", std::min(2.0, content.length() / 100.0)},
            {"accessibility",
