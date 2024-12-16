#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

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
            {"accessibility", content.length() > 50 ? 1.5 : 0.8},
            {"visual_design", 1.3},
            {"content_depth", std::min(2.0, content.length() / 200.0)},
            {"innovation", 0.7},
            {"performance", std::min(1.0, content.length() / 500.0)},
            {"user_feedback", 0.9},
            {"scalability", 0.8}
        };
    }

    double calculateTotalScore(const std::map<std::string, double>& scores) {
        double total = 0.0;
        for (const auto& [category, score] : scores) {
            total += score * weights.at(category);
        }
        return std::round(total * 10.0) / 10.0;
    }
};

void handlePost(http_request request) {
    request
        .extract_json()
        .then([=](json::value body) {
            try {
                auto url = body[U("url")].as_string();

                // Simulated content fetch for demonstration
                std::string content = "This is sample content for URL: " + url;

                // Analyze content
                ContentAnalyzer analyzer;
                auto scores = analyzer.analyzeContent(content);
                double total_score = analyzer.calculateTotalScore(scores);

                // Build JSON response
                json::value response;
                response[U("total_score")] = json::value::number(total_score);

                json::value scores_json;
                for (const auto& [category, score] : scores) {
                    scores_json[U(category)] = json::value::number(score);
                }
                response[U("scores")] = scores_json;

                // Send response
                request.reply(status_codes::OK, response);
            } catch (const std::exception& e) {
                request.reply(status_codes::BadRequest, U("Error processing request"));
            }
        })
        .catch([](const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        });
}

int main() {
    http_listener listener(U("http://localhost:8080"));

    listener.support(methods::POST, handlePost);

    try {
        listener
            .open()
            .then([&listener]() { std::cout << "Server is running at: " << listener.uri().to_string() << std::endl; })
            .wait();

        while (true);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
