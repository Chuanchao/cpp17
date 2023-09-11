//
// Created by Chuanchao Lyu on 2022/11/27.
//

#include "DBmysql.h"
#include <toml++/toml.h>
#include <exception>

using namespace std;
namespace HFTrading {

    std::unique_ptr<DBmysql> DBmysql::CreateDBmysql() {
        return std::make_unique<DBmysql>();
    }

    void DBmysql::init(const std::string &config) {
        toml::table tbl;
        try {
            //auto db = "../../config/DBconfig";
            tbl = toml::parse_file(config);
        }
        catch (const toml::parse_error &err) {
            std::cerr << "Parsing failed:\n" << err << std::endl;
        }
        std::vector<mysqlinfo> dbinfos;
        auto dbs = tbl["database"];
        for (auto &node: *dbs.as_array()) {
            auto &db_meta = *node.as_table();
            mysqlinfo tmp;
            try {
                tmp.name = *db_meta["name"].value<std::string>();
                tmp.ip = *db_meta["ip"].value<std::string>();
                tmp.user = *db_meta["user"].value<std::string>();
                tmp.password = *db_meta["password"].value<std::string>();
                tmp.port = *db_meta["port"].value<unsigned int>();
                dbinfos.push_back(tmp);
            }
            catch (const exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        for (const auto &db: dbinfos) {
            m_dbs.emplace(std::piecewise_construct,
                          std::forward_as_tuple(db.name),
                          std::forward_as_tuple(false));
            //m_dbs[db.name].set_option(new mysqlpp::ReconnectOption(true));
            try {
                m_dbs[db.name].connect(db.name.c_str(), db.ip.c_str(), db.user.c_str(), db.password.c_str(),
                                            db.port);
                _logger->info("connect to {} successed!", db.name);
            }
            catch (mysqlpp::BadQuery &ex) {
                _logger->error("Mysql connect error:{}", ex.what());
            }
        }


    }

    bool DBmysql::QueryShortScore(const std::string &db, const std::string &date, std::vector<StockScore> &ss) {
        char *buff = new char[300];
        snprintf(buff, 500, "select * from shortside where tradedate = '%s' order by score asc;", date.c_str());
        _logger->info("DBMysql::QueryShortScore");
        function<void(const mysqlpp::StoreQueryResult &, vector<StockScore> &)> func
                = bind(&DBmysql::ParseShortScore, this, placeholders::_1, placeholders::_2);
        try {
            return queryByStore(buff, ss, m_dbs.at(db), func);
        }
        catch (const out_of_range &ex) {
            _logger->warn(ex.what());
            return false;
        }
    }

    void DBmysql::ParseShortScore(const mysqlpp::StoreQueryResult &res, std::vector<StockScore> &ss) {
        for (size_t i = 0; i < res.size(); i++) {
            StockScore tmp;
            tmp.code = std::string(res[i]["code"].data(), res[i]["code"].length());
            tmp.tradedate = std::string(res[i]["tradedate"].data(), res[i]["tradedate"].length());
            tmp.score = atof(const_cast<char *>(res[i]["score"].data()));
            ss.push_back(tmp);
        }
    }
}